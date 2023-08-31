#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH  800
#define HEIGHT 600

#define LENGTH    1200
#define TIME_STEP 0.1

// Variables globales para almacenar los datos
float t[LENGTH];
float command1[LENGTH];
float z1[LENGTH];
float stp1[LENGTH];
float command2[LENGTH];
float z2[LENGTH];
float stp2[LENGTH];

int idx = 0;

void displayMe(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
  glVertex3f(0.5, 0.0, 0.5);
  glVertex3f(0.5, 0.0, 0.0);
  glVertex3f(0.0, 0.5, 0.0);
  glVertex3f(0.0, 0.0, 0.5);
  glEnd();
  glFlush();
}

void initialize() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Color de fondo blanco
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Dibujar gráficas
  glColor3f(0.0f, 0.0f, 1.0f); // Azul
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < idx; i++) {
    glVertex2f(t[i], z1[i]);
  }
  glEnd();

  glColor3f(0.0f, 1.0f, 0.0f); // Verde
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < idx; i++) {
    glVertex2f(t[i], z2[i]);
  }
  glEnd();

  glColor3f(1.0f, 0.0f, 0.0f); // Rojo
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < idx; i++) {
    glVertex2f(t[i], stp1[i]);
  }
  glEnd();

  glColor3f(0.0f, 0.0f, 0.0f); // Black
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < idx; i++) {
    glVertex2f(t[i], stp2[i]);
  }
  glEnd();

  glFlush();
}

void readDataFromFile() {
  FILE *file = fopen("data_PID_C.txt", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  int result;
  while ((result = fscanf(file, "%f %f %f %f %f %f %f\n", &t[idx], &command1[idx], &z1[idx],
                          &stp1[idx], &command2[idx], &z2[idx], &stp2[idx])) != EOF) {
    if (result != 7) {
      printf("Error reading data from file.\n");
      break;
    }

    idx++;
  }

  fclose(file);
}

int plotgen_gnuplot() {
  FILE *file = fopen("data_PID_C.txt", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  // Leer los datos del archivo
  float t, command1, z1, stp1, command2, z2, stp2;
  int   result;

  printf("set multiplot layout 2,1\n");

  printf("subplot 212\n");
  printf("plot '-' using 1:2 with lines lw 3 title 'Command PID1', \\\n");
  printf("     '-' using 1:3 with lines lw 3 title 'Command PID2'\n");

  while ((result = fscanf(file, "%f %f %f %f %f %f %f\n", &t, &command1, &z1, &stp1, &command2, &z2,
                          &stp2)) != EOF) {
    if (result == 7) {
      printf("%f %f\n", t, command1);
    } else {
      printf("e\n");
      break;
    }
  }

  printf("e\n");

  printf("subplot 211\n");
  printf("plot '-' using 1:4 with lines lw 3 title 'Setpoint object 1', \\\n");
  printf("     '-' using 1:5 with lines lw 3 title 'Setpoint object 2', \\\n");
  printf("     '-' using 1:6 with lines lw 3 title 'Response object 1', \\\n");
  printf("     '-' using 1:7 with lines lw 3 title 'Response object 2'\n");

  rewind(file);

  while ((result = fscanf(file, "%f %f %f %f %f %f %f\n", &t, &command1, &z1, &stp1, &command2, &z2,
                          &stp2)) != EOF) {
    if (result == 7) {
      printf("%f %f\n", t, stp1);
    } else {
      printf("e\n");
      break;
    }
  }

  rewind(file);

  while ((result = fscanf(file, "%f %f %f %f %f %f %f\n", &t, &command1, &z1, &stp1, &command2, &z2,
                          &stp2)) != EOF) {
    if (result == 7) {
      printf("%f %f\n", t, z1);
    } else {
      printf("e\n");
      break;
    }
  }

  rewind(file);

  while ((result = fscanf(file, "%f %f %f %f %f %f %f\n", &t, &command1, &z1, &stp1, &command2, &z2,
                          &stp2)) != EOF) {
    if (result == 7) {
      printf("%f %f\n", t, z2);
    } else {
      printf("e\n");
      break;
    }
  }

  printf("e\n");
  printf("unset multiplot\n");

  fclose(file);
  return 0;
}

typedef struct pid_s {
  float Kp;               // Proportional gain constant
  float Ki;               // Integral gain constant
  float Kd;               // Derivative gain constant
  float Kaw;              // Anti-windup gain constant
  float T_C;              // Time constant for derivative filtering
  float T;                // Time step
  float max;              // Max command
  float min;              // Min command
  float max_rate;         // Max rate of change of the command
  float integral;         // Integral term
  float err_prev;         // Previous error
  float deriv_prev;       // Previous derivative
  float command_sat_prev; // Previous saturated command
  float command_prev;     // Previous command
} pid_ctl_t;

typedef struct object_s {
  float m;     // Mass of the object
  float k;     // Damping constant
  float F_max; // Max force applied to the object
  float F_min; // Min force applied to the object
  float T;     // Time step
  float v;     // Velocity of the object
  float z;     // Position of the object
} object_t;

/**
 * @brief This function implements a PID controller.
 *
 * @param pid contains the controller parameters
 * @param measurement the current measurement of the process variable
 * @param setpoint desired value of the process variable
 * @return the control output of the PID controller (saturated based on max. min, max_rate)
 */
float PID_Step(pid_ctl_t *pid, float measurement, float setpoint) {

  float command;
  float command_sat;
  float deriv_filt;

  /* Error calculation */
  float const err = setpoint - measurement;

  /* Integral term calculation - including anti-windup */
  pid->integral += pid->Ki * err * pid->T + pid->Kaw * (pid->command_sat_prev - pid->command_prev) * pid->T;

  /* Derivative term calculation using filtered derivative method */
  deriv_filt      = (err - pid->err_prev + pid->T_C * pid->deriv_prev) / (pid->T + pid->T_C);
  pid->err_prev   = err;
  pid->deriv_prev = deriv_filt;

  /* Summing the 3 terms */
  command = pid->Kp * err + pid->integral + pid->Kd * deriv_filt;

  /* Remember command at previous step */
  pid->command_prev = command;

  /* Saturate command */
  if (command > pid->max) {
    command_sat = pid->max;
  } else if (command < pid->min) {
    command_sat = pid->min;
  } else {
    command_sat = command;
  }

  /* Apply rate limiter */
  if (command_sat > pid->command_sat_prev + pid->max_rate * pid->T) {
    command_sat = pid->command_sat_prev + pid->max_rate * pid->T;
  } else if (command_sat < pid->command_sat_prev - pid->max_rate * pid->T) {
    command_sat = pid->command_sat_prev - pid->max_rate * pid->T;
  } else {
    /* No action */
  }

  /* Remember saturated command at previous step */
  pid->command_sat_prev = command_sat;

  return command_sat;
}

/**
 * @brief This function implements a 1D object model based on the applied force F and
 * the object's mass, viscous damping coefficient k, max/min forces, and time step T.
 *
 * @param obj contains the object parameters
 * @param F is the force applied to the object
 * @return the position of the object in meters (z)
 */
float Object_Step(object_t *obj, float F) {

  /* Declare variables for the derivative dv/dt and the saturated force command */
  float dv_dt;
  float F_sat;

  /* Apply saturation to the input force */
  if (F > obj->F_max) {
    F_sat = obj->F_max;
  } else if (F < obj->F_min) {
    F_sat = obj->F_min;
  } else {
    F_sat = F;
  }

  /* Calculate the derivative dv/dt using the input force and the object's velocity and properties */
  dv_dt = (F_sat - obj->k * obj->v) / obj->m;

  /* Update the velocity and position of the object by integrating the derivative using the time step T */
  obj->v += dv_dt * obj->T;
  obj->z += obj->v * obj->T;

  /* Return the updated position of the object */
  return obj->z;
}

int main(int argc, char *argv[]) {

  // Current simulation time
  float t = 0;

  // Iteration counter
  int i = 0;

  // Setpoint and output of the first control loop
  float command1 = 0;
  float stp1     = 100;
  float z1       = 0;

  // Setpoint and output of the second control loop
  float command2 = 0;
  float stp2     = 50;
  float z2       = 0;

  // PID controller parameters for the first control loop
  pid_ctl_t pid1 = { 1, 0.1, 5, 0.1, 1, TIME_STEP, 100, -100, 40, 0, 0, 0, 0, 0 };

  // Object parameters for the first control loop
  object_t obj1 = { 10, 0.5, 100, -100, TIME_STEP, 0, 0 };

  // PID controller parameters for the second control loop
  pid_ctl_t pid2 = { 1.8, 0.3, 7, 0.3, 1, TIME_STEP, 100, -100, 40, 0, 0, 0, 0, 0 };

  // Object parameters for the second control loop
  object_t obj2 = { 10, 0.5, 100, -100, TIME_STEP, 0, 0 };

  // Open a file for logging simulation data
  FILE *file = fopen("data_PID_C.txt", "w");

  /* Implement iteration using a while loop */
  while (i < LENGTH) {
    /* Change setpoint at t = 60 seconds */
    if (t < 60) {
      stp1 = 100;
      stp2 = 50;
    } else {
      stp1 = 200;
      stp2 = 150;
    }

    // Execute the first control loop
    command1 = PID_Step(&pid1, z1, stp1);
    z1       = Object_Step(&obj1, command1);

    // Execute the second control loop
    command2 = PID_Step(&pid2, z2, stp2);
    z2       = Object_Step(&obj2, command2);

    // Log the current time and control loop values to the file
    fprintf(file, "%f %f %f %f %f %f %f\n", t, command1, z1, stp1, command2, z2, stp2);

    // Increment the time and iteration counter
    t = t + TIME_STEP;
    i = i + 1;
  }

  // Close the file and exit the program
  fclose(file);
  // plotgen_gnuplot();

  readDataFromFile();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("OpenGL Plot");
  glutDisplayFunc(drawScene);

  glutInitWindowPosition(100, 100);

  // glutDisplayFunc(displayMe);
  initialize();
  glutMainLoop();

  exit(0);
}