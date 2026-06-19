#pragma once

typedef enum{STATE_IDLE,STATE_CONFIGURING,STATE_RUNNING,STATE_BREAK,STATE_ENDED,STATE_HYDRATION_REMINDER}chain_state_t;

void state_machine_init(void);
void state_machine_tick(void);
chain_state_t state_machine_get_current(void);
void state_machine_transition_to(chain_state_t new_state);

// Peripheral inputs
void state_machine_on_button_short_press(void);
void state_machine_on_button_long_press(void);
void state_machine_on_button_rotary_encoder_rotate(void);
void state_machine_on_button_encoder_press(void);
