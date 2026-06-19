#include "display.h"
#include "config.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>
#include <stdio.h>
#include "font8x8.h"

static const char *TAG = "DISPLAY";

#define DISPLAY_OFF 0xAE
#define DISPLAY_ON 0xAF
#define SET_PAGE 0xB0
#define SET_COL_LOW 0x00
#define SET_COL_HIGH 0x10
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32
#define DISPLAY_PAGES (DISPLAY_HEIGHT/8)

static uint8_t framebuffer[DISPLAY_WIDTH*DISPLAY_HEIGHT];

static esp_err_t send_command(uint8_t cmd) {
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (OLED_ADDRESS << 1 )| I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x00, true);
    i2c_master_write_byte(handle, cmd, true);
    i2c_master_stop(handle);
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, handle, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(handle);
    return ret;
}

static esp_err_t send_data(const uint8_t *data, size_t len) {
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (OLED_ADDRESS << 1)| I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true);
    i2c_master_write(handle, data, len, true);
    i2c_master_stop(handle);
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, handle, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(handle);
    return ret;
}

void display_init(void) {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = PIN_i2C_SDA,
        .scl_io_num = PIN_i2C_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ_HZ,
    };
    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
    send_command(DISPLAY_OFF);
    send_command(0xD5); send_command(0x80);
    send_command(0xA8); send_command(0x1F);
    send_command(0xD3); send_command(0x00);
    send_command(0x40);
    send_command(0x8D); send_command(0x14);
    send_command(0x20); send_command(0x00);
    send_command(0xA1);
    send_command(0xC8);
    send_command(0xDA); send_command(0x02);
    send_command(0x81); send_command(0x8F);
    send_command(0xD9); send_command(0xF1);
    send_command(0xDB); send_command(0x40);
    send_command(0xA4);
    send_command(0xA6);
    send_command(DISPLAY_ON);
    memset(framebuffer, 0, sizeof(framebuffer));
    display_refresh();
    ESP_LOGI(TAG, "Display initialised");
}
void display_clear(void) {
    memset(framebuffer, 0, sizeof(framebuffer));
}
void display_refresh(void) {
    uint8_t page = 0;
    for (uint8_t page = 0; page < DISPLAY_PAGES; page++) {
       send_command(SET_PAGE | page);
       send_command(SET_COL_LOW | 0x0);
       send_command(SET_COL_HIGH | 0x0);
       send_data(&framebuffer[page * DISPLAY_WIDTH],DISPLAY_WIDTH); 
    }

}

static void draw_char(int x, int y, char c) {
 if (c <0x20 || c > 0x7E) c = '?';
 int idx = c - 0x20;
 int page =( y / 8);
 if (page < 0 || page >= DISPLAY_PAGES) return;
 for (int col = 0; col < 8; col++){
    int px = x + col;
    if (page<0 || page >= DISPLAY_WIDTH) continue;
    framebuffer[page * DISPLAY_WIDTH + px] = font8x8[idx][col];
 }

}

static void draw_text(int x, int y, const char *text) {
    int cursor_x = x;
    while (*text) {
        if (cursor_x + 8 > DISPLAY_WIDTH)
        break;
        draw_char(cursor_x, y, *text);
        cursor_x += 8;
        text++;
    }
}

void display_show_idle(int sessions_today) {
    display_clear();
    char buf[32];
    draw_text(0, 0, buf);
    snprintf(buf, sizeof(buf), "%d done today", sessions_today);
    draw_text(0, 16, buf);
    display_refresh();
}

void display_show_session_length(int seconds) {
    display_clear();
    char buf[32];
    int minutes = seconds / 60;
    snprintf(buf, sizeof(buf), "Length: %d min", minutes);
    draw_text(0, 0, buf);
    draw_text(0, 16, "Press to Start");
    display_refresh();
}

void display_show_break(int seconds_remaining) {
    display_clear();
    char buf[32];
    int minutes = seconds_remaining / 60;
    int secs = seconds_remaining % 60;
    snprintf(buf, sizeof(buf), "%02d:%02d", minutes, secs);
    draw_text(48, 12, buf);
    display_refresh();
}

void display_show_session_complete(int sessions_today) {
    display_clear();
    draw_text(0, 0, "session done!");
    char buf[32];
    snprintf(buf, sizeof(buf), "%d sessions today", sessions_today);
    draw_text(0, 16, buf);
    display_refresh();
}

void display_show_hydration_reminder(void) {
    display_clear();
    draw_text(0, 0, "drank yo watah init");
    draw_text(0, 16, "Hydwate yo self");
    display_refresh();
}
void display_show_low_battery(void) {
    display_clear();
    draw_text(0, 12, "Low battery");
    display_refresh();
}
void display_show_timer(int seconds_remaining){
 display_clear();
 char buf[32];
 int minutes = seconds_remaining / 60;
 int secs = seconds_remaining % 60;
 snprintf(buf, sizeof(buf), "%02d:%02d", minutes, secs);
 draw_text(48, 12, buf);
 display_refresh();
}

