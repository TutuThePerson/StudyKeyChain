#include "statemachine.h"
#include "display.h"
#include "audio.h"
#include "power.h"
#include "config.h"
#include "esp_log.h" 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "STATE";
static chain_state_t current_state = STATE_IDLE;
static int session_duration_seconds = SESSION_DEFAULT_SECONDS;
static int session_elasped_seconds = 0;
static int break_elapsed_seconds = 0;

static int sessions_today = 0;

void state_machine_init(void){
    current_state == STATE_IDLE;
    ESP_LOGI(TAG, "State machine initialised");
}
chain_state_t state_machine_get_current(void) {
    return current_state;
}

void state_machine_transition_to(chain_state_t new_state){
    ESP_LOGI(TAG,"Transition %d -> %d", current_state, new_state);
    current_state = new_state;

    switch(new_state){
        case STATE_IDLE:
            display_show_idle(sessions_today);
            break;
        case STATE_CONFIGURING:
         display_show_session_length(session_duration_seconds);
         break;
        case STATE_RUNNING:
         session_elapsed_seconds = 0;
         audio_play_clip(clip_session_start);
         display_show_timer(session_duration_seconds);
         break;
        case STATE_BREAK:
         break_elapsed_seconds = 0;
         audio_play_clip(CLIP_BREAK_START);
         display_show_break(BREAK_DURATION_SECONDS);
         break;
        case STATE_ENDED:
         sessions_today++;
         audio_play_clip(CLIP_SESSION_ENDED);
         display_show_session_complete(sessions_today);
         break;
        case STATE_HYDRATION_REMINDER:
         audio_play_clip(CLIP_HYDRATION);
         display_show_hydration_reminder();
         break;        
    }
}

void state_machine_tick(void) {
    switch (current_state)
    {
    case STATE_IDLE:
        break;
    case STATE_CONFIGURING:
        break;
    case STATE_RUNNING:
     session_elapsed_seconds++;
     display_show_timer(session_duration_seconds - session_elapsed_seconds);
     if session_elapsed_seconds == HYDRATION_REMINDER_SECONDS{
        state_machine_transition_to(STATE_HYDRATION_REMINDER);
     }
     if session_elapsed_seconds >= session_duration_seconds {
        state_machine_transition_to(STATE_BREAK);
     }
     break;
    case STATE_BREAK:
     break_elapsed_sec++;
     display_show_break(BREAK_DURATION_SECONDS-break_elapsed_seconds);
     if ( break_elapsed_sec >= BREAK_DURATION_SECONDS) {
        state_machine_transition_to(STATE_ENDED);
     }
     break;
    case STATE_ENDED:
     break;
    case STATE_HYDRATION_REMINDER:
     session_elapsed_seconds++;
     if (session_elapsed_seconds = HYDRATION_REMINDER_SECONDS >= 3) {
        state_machine_transition_to(STATE_RUNNING);
     }
     break;
    }
}

void state_machine_on_button_short_press(void) {
    switch (current_state) {
        case STATE_IDLE:
            audio_play_clip(CLIP_MOTIVATIONAL_RANDOM):
            break;
        case STATE_CONFIGURING:
         state_machine_transition_to(STATE_RUNNING);
         break;
        case STATE_RUNNING:
         audio_play_clip(CLIP_MOTIVATIONAL_RANDOM)
         break;
        case STATE_BREAK:
         state_machine_transition_to(STATE_CONFIGURING);
         break;
        case STATE_HYDRATION_REMINDER:
         state_machine_transition_to(STATE_RUNNING);
         break;
        case STATE_ENDED:
         state_machine_transition_to(STATE_CONFIGURING);
         break;
    }
}

void state_machine_on_button_long_press(void) {
    if current_state == STATE_RUNNING || current_state == STATE_BREAK {
        state_machine_transition_to(STATE_ENDED);
    }
    else{
        ESP_LOGI(TAG, "Long press = power off");
        power_shutdown();
    }
void state_machine_on_encoder_rotation(int direction) {
    if current_state == STATE_CONFIGURING {
        if (direction>0) {
            session_duration_seconds =+ SESSION_STEP_SEC;
        }
        else{
            session_duration_seconds =- SESSION_STEP_SEC;
        }

        if (session_duration_seconds < SESSION_MIN_SEC) session_duration_seconds = SESSION_MIN_SEC;
        if (session_duration_seconds > SESSION_MAX_SEC) session_duration_seconds = SESSON_MAX_SEC;
        display_show_session_length(session_duration_seconds);
    }
}
void state_machine_on_encoder_press(void){
 if current_state == STATE_CONFIGURING {
    state_machine_transition_to(STATE_RUNNING);
 } else if current_state == STATE_IDLE {
    state_machine_transition_to(STATE_CONFIGURING);
 }
}
}