#pragma once

//#############
// This file contains the pin assignments for the study keychain project
//#############

// Button (Kalih Choc Switch)
#define PIN_BUTTON 5

// Rotary encoder
#define PIN_ENCODER_A 6
#define PIN_ENCODER_B 7
#define PIN_ENCODER_SW 4 

//I^2C (Oled Display)
#define PIN_i2C_SDA 12
#define PIN_i2C_SCL 17
#define I2C_FREQ_HZ 400000
#define OLED_ADDRESS 0x3C

// I^2S (audio amplifier)
#define PIN_I2S_DIN 8
#define PIN_I2S_BCLK 9
#define PIN_I2S_LRCLK 10

// Piezoelectric (audio feedback)
#define PIN_PIEZO 11

// Power Management 
#define PIN_POWER_DONE 18
#define PIN_BATTERY_SENS 15

//#############
//constants
//#############

//Study Session Duration (fixed)

#define SESSION_DEFAULT_SECONDS 3300
#define BREAK_DURATION_SECONDS 300

//Reminder

#define HYDRATION_REMINDER_SECONDS 3300

// Battery Monitoring
#define POTENTIAL_DIVIDER_RATIO 2f 
#define FULL_BATT_mV 4200
#define BATT_EMPTY_mV 3000
#define BATT_LOW_mV 3300

// Audio 
#define I2S_SAMPLE_RATE 16000 
#define I2S_BUFFER_SIZE 1024

// other UI/timing
#define IDLE_TIMEOUT_mS 30000
#define POWER_OFF_TIMEOUT_mS 14400000
#define LONG_PRESS_mS 2000
#define DEBOUNCE_mS 30
