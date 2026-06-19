#include "power.h"
#include "config.h"
#include "audio.h"
#include "display.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_cali_scheme.h"

static const char *TAG = "POWER";

static adc_oneshot_unit_handle_t adc_handle;
static adc_cali_handle_t cali_handle = NULL;
static bool low_battery_warned = false;

void power_init(void) {
    gpio_set_direction(PIN_POWER_DONE, GPIO_MODE_OUTPUT);
    gpio_set_level(PIN_POWER_DONE, 0);

    adc_oneshot_unit_init_cfg_t init_config = { .unit_id = ADC_UNIT_1 };
    adc_oneshot_new_unit(&init_config, &adc_handle);

    adc_oneshot_chan_cfg_t chan_config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };
    adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_2, &chan_config);
    adc_cali_curve_fitting_config_t cali_config = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };
    adc_cali_create_scheme_curve_fitting(&cali_config, &cali_handle);
    ESP_LOGI(TAG, "Power initialised");
}
int power_get_battery_mv(void){
    int raw_sum = 0;
    int samples = 32;
    for (int i = 0; i < samples; i++){
        int raw;
        adc_oneshot_read(adc_handle, ADC_CHANNEL_2, &raw);
        raw_sum += raw;
    }
    int raw_avg = raw_sum / samples
    int voltage_mv = 0;
    adc_cali_raw_to_voltage(cali_handle, raw_avg, &voltage_mv);
    return (int)(voltage_mv * POTENTIAL_DIVIDER_RATIO);
}

void power_check(void) {
    int batt_mv = power_get_battery_mv();
    ESP_LOGD(TAG, "Battery: %d mV");
    if (batt_mv< BATT_LOW_mV && !low_battery_warned) {
        ESP_LOGW(TAG, "low battery %d mV", batt_mv);
        audio_play_clip(CLIP_LOW_BATTERY);
        display_show_low_battery();
        low_battery_warned = true;
    }
    if batt_mv < BATT_EMPTY_mV {
        ESP_LOGE(TAG, "Critical Power State, shuttng yo down");
        power_shutdown();
    }
}
void power_shutdown(void) {
    ESP_LOGI(TAG, "Shutting down");
    audio_play_clip(CLIP_POWER_OFF);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    display_clear();
    display_refresh();
    gpio_set_level(PIN_POWER_DONE,1);
    while(1) {
        vTaskDelay (1000, portTICK_PERIOD_mS);
    }
}