A small-portable study companion that motivates you to study!!! (probably). Its purpose is to play voice clips (initially in my own voice lol, but you could ask your teacher's voice), it aims to run fixed focus session and reminds you to take a break and hyrdrate all in the formfactor of a keychain.

Why did I build this?

No clue.jk. I just finished 2 months of A-levels and being grinding those past papers for atleast half a year now; I realise it is really demoralising to be studying 3 in the morning alone - so this idea stemmed from those experiences. It's just a bit of fun really and isn't aimed as a full replacement for regular discipline and proper revision but might provide that little push to keep studying while staying healthy. I didn't want a big, bulky solution so I thought it would be cool if I could fit it on a keychain, that I could hang on my bag as such.
The StudyPal consists of a 2 layer PCB, larger than a regular keycap but still small enough to put in your pocket or hang on your bag. It runs an ESP32-S3, with audio functiionality (physically hidden under the keycap)

Functions:

1. It goes throgh focus sessions on variable length via the rotary encoder under the keycap.
2. It has audio playback through a speaker which aims to play motivational audio clips, session start-end cues and hydration reminders.
3. OLED display which shows timer, session stats and break progress througha slim slanted window on the keycap.
4. Keycap - short press for motivational cue, long press to end a session early or to power off
5. Hidden Rotary Encoder undeer the keycap to adjust session length
6. Battery powered via a single-cell LiPo with USB C charging and ESD protection

Schematic:
![Schematic](https://github.com/TutuThePerson/StudyKeyChain/blob/main/assets/Screenshot%202026-06-19%20131959.png)
PCB:
![PCB kicad](https://github.com/TutuThePerson/StudyKeyChain/blob/main/assets/Screenshot%202026-06-19%20162050.png)
![3D PCB kicad](https://github.com/TutuThePerson/StudyKeyChain/blob/main/assets/Screenshot%202026-06-19%20162218.png)
CASE:
![Assembled](https://github.com/TutuThePerson/StudyKeyChain/blob/main/assets/Screenshot%202026-06-19%20162341.png)
![Exploded](https://github.com/TutuThePerson/StudyKeyChain/blob/main/assets/Screenshot%202026-06-19%20162646.png)

The Technical Stuff:

Power sub-system:
 - USB-C in goes through TP4056 and manages LiPo charging at 1A (set by the 1200 ohm resistor). The charge status drives two LEDs where red = charging and green indicates fully charged/done. TPL5111 acts as a power switch by latching the AP2112k 3.3V LDO on when the user presses the Kalih  Choc Keycap, and cuts power when the firmware returns POWER_DONE.
 - A potential divider with 2 100k Ohm Resistor connectios is used to feed half the battery voltage so it can be read to monitor charge levels.

Microcontroller unit
- ESP-32-S3-WROOM-1-N8, has 8 MB of flash, firmware and audio clips/message fit comfortably in the unit.
- The Strapping pins should be handled as stated by the datasheet.
   - GPIO0:10k pullup resistor and a flash button to GND
   - GPIO45/46: 10k pull down resistors to each pin
   - EN: 10k puullup with a 1 micro Farad Capacitor connected to ground in parallel.

Audio:
- Audio is generated digitally by the microcontroller, and is streamed via I^2S to the class D amplifier, which in turn drives a speaked mounted under the keycap. Sound fires through the gapes just under the keycap edge.
- The amp's SD_MODE pin has a 100k ohm pullup to 3.3V, putting it in stereo mixed mono mode.

Display: 
- 0.96" OLED breakouut connected via I^2C, viewed from a slim window cut into the case, meaning the display is stationary so it shouldn't be easily damaged.
- I^2C has 4.7k pullups to both SDA and SCL to 3.3V

USB-C connector 
- 16 pin USB 2.0 receptable, D+ pads are tied together so directions works both ways - same goes for D- pads. These connections are then connected to the ESP32-S3's native USB pins. ESD protection is on both lines.

PCB
- 2 layer
- L1 : components + signal traces
- L2 : ground pour and some signal traces

Components:
1. ESP32-S3-WROOM-N8 MCU
2. TP4056 charging IC
3. TPL5111 power timer
4. AO3401 P-MOSFET
5. AP2122K - 3.3 LDO
6. MAX98357A audio amp
7. USBLC6-2SC6 ESD
8. USB-C connector 16-pin
9. 0.91" 128x32 SSD1306 OLED breakout
10. 28mm 8ohmn 2W speaker
11. 12mm piezo buzzer
12. Kalih Choc V1 Brown
13. EC11 Rotary Encoder
14. LiPo 803040 - 1000mah
15. Resistors (100k,10k,5.1k,4.7k,1.2k,1k - 0402)
16. Capacitors ( 100n,10u,1u = 0402)
17. LED (RED, GREEN - 0603)
18. 6mm tactile button
19. PCB
20. M3 self-tapping screws
21. 3D printed case + keycap

BOM:

Assembly:
 - Make sure you have all components listed available and casing 3D printed.
 - Solder all the components on the PCB as per the schematic
 - Connect the battery to the 2 pin connector (label in schematic file)
 - Place the PCB on top of the base and use M3 screws, preferably around 3-4mm
 - Flash firmware onto the ESP32 using the USB-C connector (If there is no output when flashing, hold the flash button to reset - forces chip into download mode)
 - Use plastic adhesive to adhere the the lid to the base - once everything works okay
 - Put on the keycap and enjoy!

Design Notes:
- You could go with a different mcu but I chose the ESP-32 as this one has native USB, decent peripheral support and has 8MB of memory which makes it a suitable cost-effective solution in this case. The atenna is not used, but it could be used in future alterations with firmware but if you really wanted bluetooth or wifi you can use ur phone lol
- I reccomend you get a stencil which would make soldering alot easier
- The system switches and the rotary encoder is located under the keycap as they are designed to be set-once parameters, not designed to be constantly adjusted so this would make the keycap look better.

