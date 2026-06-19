#include "audio.h"
#include "config.h"
#include "driver/i2s_std.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>
#include <stdlib.h>

static const char *TAG = "AUDIO";

static i2s_chan_handle_t tx_handle;

void audio_init(void) {
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    chan_cfg.dma_desc_num = 4;
    chan_cfg.dma_frame_num = 256;
    i2s_new_channel(&chan_cfg, &tx_handle, NULL);
    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(I2S_SAMPLE_RATE),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT,I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = PIN_I2S_BCLK,
            .ws = PIN_I2S_LRCLK,
            .dout = PIN_I2S_DIN,
            .din = I2S_GPIO_UNUSED,
        },
    };
    i2s_channel_init_std_mode(tx_handle, &std_cfg);
    i2s_channel_enable(tx_handle);

    ESP_LOGI(TAG, "Audio initialised");

}

void audio_play_clip(audio_clip_t clip) {
    ESP_LOGI(TAG, "Playing clip %d", clip);
    audio_play_tone(500, 200);
}

void audio_play_tone(int frequency_hz, int duration_ms) {
    int total_samples = (I2S_SAMPLE_RATE * duration_ms) / 1000;
    int16_t *samples = malloc(total_samples * sizeof(int16_t));
    if (!samples) {
        ESP_LOGE(TAG, "Failed to allocate sample buffer");
        return;
    }

    for (int i = 0;i < total_samples; i++) {
        float t = (float)i/I2S_SAMPLE_RATE;
        samples[i] = (int16_t)(16000.0f * sinf(2.0f * 3.14159f *(float)frequency_hz * t));
    }
    size_t written;
    i2s_channel_write(tx_handle, samples, total_samples * sizeof(int16_t), &written, 1000 / portTICK_PERIOD_MS);
    free(samples);
}