#include "cbuff.h"
#include "utils_debug.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// clang-format off
char r_display[3] = { 'x', 'v', '^' };

// Nodes States
typedef enum EL_ST_e {
  ST_stp,
  ST_up,
  ST_dwn,
  ST_MAX
} EL_ST_t;

// State Request
typedef enum EL_Input_e {
  EL_IN_STP,
  EL_IN_DWN,
  EL_IN_UP,
  EL_IN_MAX_STATES
} EL_Input_t;

typedef struct EL_FSM_St {
  char output;
  uint32_t time;
  EL_ST_t next[EL_IN_MAX_STATES];
} EL_FSM_States_t;

EL_FSM_States_t el_fsm[ST_MAX] = {
  //               char                  time  STP   DWN   UP
  /*ST_stp*/ { '0', 2000000, { ST_stp, ST_dwn, ST_up } },
  /*ST_up */ { '^',  500000, { ST_stp, ST_up , ST_up } },
  /*ST_dwn*/ { 'v', 2000000, { ST_stp, ST_dwn, ST_dwn } },
};

// clang-format on
CBUFF_CREATE(EL_Input_t, req_cb, 10);

int main() {
  EL_Input_t request[]   = { EL_IN_UP,   EL_IN_DWN, EL_IN_DWN, EL_IN_STP, EL_IN_DWN,
                             EL_IN_STP, EL_IN_UP,   EL_IN_UP,   EL_IN_STP, EL_IN_STP };
  EL_ST_t    el_state    = ST_stp;
  EL_Input_t input       = 0;
  uint32_t   wait_period = 0;
  char       display     = '0';

  for (int i = 0; i < 10; ++i) {
    if (NOT_OK == CBUFF_PUT(req_cb, &request[i])) {
      printf("Failed to push data %d at head %d\n", request[i], req_cb.u16_head);
      break;
    }
  }
  char floor = el_fsm[el_state].output;
  for (int i = 0; i < 10; ++i) {
    if (ST_stp != el_state) {
      display = el_fsm[el_state].output;
      if (ST_up == el_state)
        ++floor;
      else if (ST_dwn == el_state)
        --floor;
    } else {
      display = floor;
    }
    CBUFF_POP(req_cb, &input);
    printf("Process %d  Elevator  %c  Request %c, floor:%c\n", i, display, r_display[input], floor);
    SEND_OUT();
    wait_period = el_fsm[el_state].time;
    el_state    = el_fsm[el_state].next[input];
    usleep(wait_period);
  }
  printf("\n");
  SEND_OUT();
  return 0;
}
