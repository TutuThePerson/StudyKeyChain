#pragma once

typedef enum {
    CLIP_SESSION_START,
    CLIP_SESSION_END,
    CLIP_BREAK_START,
    CLIP_HYDRATION,
    CLIP_MOTIVATIONAL_RANDOM,
    CLIP_LOW_BATTERY,
    CLIP_POWER_OFF
} audio_clip_t;

void audio_init(void);
void audio_play_clip(audio_clip_t clip);
void audio_play_tone(int frequency_hz, int duration_ms);