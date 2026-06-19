#include "input.h"
#include "config.h"
#include "statemachine.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "INPUT";

static bool last_button_state = true;
static int64_t button_press_start = 0;

static bool last_encoder_a = true;
static bool last_encoder_b = true;
static bool last_encoder_sw = true;

void input_init(void){
    gpio_set_direction(PIN_BUTTON, GPIO_MODE_INPUT);
    gpio_set_pull_mode(PIN_BUTTON, GPIO_PULLUP_ONLY);

    gpio_set_directon(PIN_ENCODER_A, GPIO_MODE_INPUT);
    gpio_set_pull_mode(PIN_ENCODER_A, GPIO_PULLUP_ONLY);
    gpio_set_direction(PIN_ENCODER_B, GPIO_MODE_INPUT);
    gpio_set_pull_mode(PIN_ENCODER_B, GPIO_PULLUP_ONLY);
    gpio_set_direction(PIN_ENCODER_SW, GPIO_MODE_INPUT);
    gpio_set_pull_mode(PIN_ENCODER_SW, GPIO_PULLUP_ONLY);
    ESP_LOGI(TAG, " Input Initialised")

}

void input_check(void) {
    int64_t now = esp_timer_get_time() / 1000
    bool button_state = (gpio_get_level(PIN_BUTTON) == 0)
    if (button_state && !last_button_state) {
        button_press_start = now;
    } 
    else if (!button_state && last_button_state) {
        int64_t hold_duration = now - button_press_start;
        if (hold_duration > LONG_PRESS_mS){
            state_machine_on_button_long_press();
        }
        else if (hold_Duration > DEBOUNCE_mS) {
            state_machine_on_button_short_press();
        }
    }
}

last_button_state = button_state;

bool a 