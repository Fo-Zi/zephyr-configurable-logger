#ifndef MAIN_STATE_MACHINE_H
#define MAIN_STATE_MACHINE_H

#include "main_state_machine_types.h"

void main_sm_init(main_sm_t * sm);
void main_sm_handle_t(main_sm_t * sm);
void main_sm_run(main_sm_t * sm);

#endif
