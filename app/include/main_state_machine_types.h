#ifndef MAIN_STATE_MACHINE_TYPES_H
#define MAIN_STATE_MACHINE_TYPES_H

typedef struct main_sm_context_t main_sm_context_t;

typedef enum main_sm_state_t{
    MAIN_SM_STATE_INIT,
    MAIN_SM_STATE_TAKING_READINGS,
    MAIN_SM_STATE_CRITICAL_ERROR,
    MAIN_SM_STATE_NUM_STATES
} main_sm_state_t;

typedef enum main_sm_event_t{
    MAIN_SM_EVENT_START,
    MAIN_SM_EVENT_STOP,
    MAIN_SM_EVENT_ERROR
} main_sm_event_t;

typedef struct main_sm_t{
    main_sm_state_t current_state;
    main_sm_event_t event;
    main_sm_context_t * context;
} main_sm_t;

#endif
