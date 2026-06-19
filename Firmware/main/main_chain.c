#include "config.h"
#include "display.h"
#include "audio.h"
#include "input.h"
#include "power.h"
#include "statemachine.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MAIN"

void app_main(void) {
    ESP_LOGI(TAG, "Starrrrrrrrrrting");
    vTaskDelay( 500 / portTICK_PERIOD_MS);
    display_init();
    audio_init();
    input_init();
    power_init();
    state_machine_init();

    ESP_LOGI(TAG, "StudyPal Ready");

    int last_tick_ms = 0;
    int last_power_check_ms = 0;
    
    while (1) {
        int64_t now_ms = esp_timer_get_time() / 1000;
        input_check();
        if (now_ms - last_tick_ms >= 1000) {
            state_machine_tick();
            last_tick_ms = now_ms;
        }
        if (now_ms - last_power_check_ms >= 30000) {
            power_check();
            last_power_check_ms = now_ms;
        }
        vTaskDelay(20/portTICK_PERIOD_MS);
    }
} 