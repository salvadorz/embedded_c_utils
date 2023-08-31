#include "cbuff.h"
#include "utils_debug.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
// clang-format off
//char display[4] = { '0', '^', '1', 'v' };

// Nodes States
typedef enum EL_ST_e {
  ST_L,
  ST_U,
  ST_1,
  ST_D,
  ST_MAX
} EL_ST_t;

typedef enum EL_Input_e {
  EL_IN_IDLE,
  EL_IN_DOWN,
  EL_IN_UP,
  EL_IN_MAX_STATES
} EL_Input_t;

typedef struct EL_FSM_St {
  char output;
  uint32_t time;
  EL_ST_t next[EL_IN_MAX_STATES];
} EL_FSM_States_t;

EL_FSM_States_t el_fsm[ST_MAX] = {
  //           char     time  Idd   Down   UP
  /*ST_L*/ { '0', 2000000, { ST_L, ST_L, ST_U } },
  /*ST_U*/ { '^',  500000, { ST_1, ST_1, ST_1 } },
  /*ST_1*/ { '1', 2000000, { ST_1, ST_D, ST_1 } },
  /*ST_D*/ { 'v',  500000, { ST_L, ST_L, ST_L } },
};

// clang-format on
CBUFF_CREATE(EL_Input_t, u8_cb, 10);

int main() {
  EL_Input_t request[]   = { 1, 2, 1, 0, 2, 1, 2, 1, 0, 2 };
  EL_ST_t    el_state    = ST_L;
  EL_Input_t input       = 0;
  uint32_t   wait_period = 0;
  char       display     = '0';

  for (int i = 0; i < 10; ++i) {
    if (NOT_OK == CBUFF_PUT(u8_cb, &request[i])) {
      printf("Failed to push data %d at head %d\n", request[i], u8_cb.u16_head);
      break;
    }
  }
  for (int i = 0; i < 10; ++i) {
    display = el_fsm[el_state].output;
    CBUFF_POP(u8_cb, &input);
    printf("Process %d  Elevator  %c  Request %d\r", i, display, input);
    SEND_OUT();
    wait_period = el_fsm[el_state].time;
    el_state    = el_fsm[el_state].next[input];
    usleep(wait_period);
  }
  printf("\n");
  SEND_OUT();
  return 0;
}
