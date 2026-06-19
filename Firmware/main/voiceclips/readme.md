# Adding voice clips

## Recording
1. Record a short message with a maximum length of 3 seconds
2. Quiet room, no background noise
3. Speak clearly 

## Format requirements

- WAV format, 16kHz sample rate, mono 16 bit
- Recommend you use Audacity, you can export as WAV and set the settings there

## Clip  naming

Save your clips with these exact names:

- "session_start.wav"
- "session_end.wav"
- "break_start.wav"
- "hydration.wav"
- "motivational_01.wav", "motivational_02.wav, and so on.
- "low_battery.wav"
- "power_off.wav

# Embedding on the ESP

Update "main/CMakeLists.txt" to embed the clips

Should look something like below
idf_component_register(
    SRCS ...
    EMBED_FILES
     "voice_clips/session_start.wav"
     ... and so on.
)

Rebuild the firmware by funning idf.py build in your terminal 