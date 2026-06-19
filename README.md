# Study Pal
A small-portable study companion that motivates you to study!!! (probably). Its purpose is to play voice clips (initially in my own voice lol, but you could ask your teacher's voice), it aims to run fixed focus session and reminds you to take a break and hyrdrate all in the formfactor of a keychain.

## Why did I build this?

No clue. jk. I just finished 2 months of A-levels and being grinding those past papers for atleast half a year now; I realise it is really demoralising to be studying 3 in the morning alone - so this idea stemmed from those experiences. It's just a bit of fun really and isn't aimed as a full replacement for regular discipline and proper revision but might provide that **little** push to keep studying while staying healthy. I didn't want a big, bulky solution so I thought it would be cool if I could fit it on a keychain, that I could hang on my bag as such.
The StudyPal consists of a 2 layer PCB, larger than a regular keycap but still small enough to put in your pocket or hang on your bag. It runs an ESP32-S3, with audio functionality (physically hidden under the keycap)

## Functions:

1. It goes through focus sessions on variable length via the rotary encoder under the keycap.
2. It has audio playback through a speaker which aims to play motivational audio clips, session start-end cues and hydration reminders.
3. OLED display which shows timer, session stats and break progress througha slim slanted window on the keycap.
4. Keycap - short press for motivational cue, long press to end a session early or to power off
5. Hidden Rotary Encoder undeer the keycap to adjust session length
6. Battery powered via a single-cell LiPo with USB C charging and ESD protection

### Schematic:

![Schematic](https://github.com/TutuThePerson/StudyKeyChain/blob/main/assets/Screenshot%202026-06-19%20131959.png "Schematic")

### PCB:

![PCB kicad](https://github.com/TutuThePerson/StudyKeyChain/blob/main/assets/Screenshot%202026-06-19%20162050.png "PCB")
![3D PCB kicad](https://github.com/TutuThePerson/StudyKeyChain/blob/main/assets/Screenshot%202026-06-19%20162218.png "3D RENDER PCB")

### CASE:

![Assembled](https://github.com/TutuThePerson/StudyKeyChain/blob/main/assets/Screenshot%202026-06-19%20162341.png)
![Exploded](https://github.com/TutuThePerson/StudyKeyChain/blob/main/assets/Screenshot%202026-06-19%20162646.png)

### ZINE:

![Zine](https://github.com/TutuThePerson/StudyKeyChain/blob/main/docs/zine.png)

## The Technical Stuff:

### Power sub-system:
 - USB-C in goes through TP4056 and manages LiPo charging at 1A (set by the 1200 ohm resistor). The charge status drives two LEDs where red = charging and green indicates fully charged/done. TPL5111 acts as a power switch by latching the AP2112k 3.3V LDO on when the user presses the Kalih  Choc Keycap, and cuts power when the firmware returns POWER_DONE.
 - A potential divider with 2 100k Ohm Resistor connectios is used to feed half the battery voltage so it can be read to monitor charge levels.

### Microcontroller unit
- ESP-32-S3-WROOM-1-N8, has 8 MB of flash, firmware and audio clips/message fit comfortably in the unit.
- The Strapping pins should be handled as stated by the datasheet.
   - GPIO0:10k pullup resistor and a flash button to GND
   - GPIO45/46: 10k pull down resistors to each pin
   - EN: 10k puullup with a 1 micro Farad Capacitor connected to ground in parallel.

### Audio:
- Audio is generated digitally by the microcontroller, and is streamed via I^2S to the class D amplifier, which in turn drives a speaked mounted under the keycap. Sound fires through the gapes just under the keycap edge.
- The amp's SD_MODE pin has a 100k ohm pullup to 3.3V, putting it in stereo mixed mono mode.

### Display: 
- 0.96" OLED breakouut connected via I^2C, viewed from a slim window cut into the case, meaning the display is stationary so it shouldn't be easily damaged.
- I^2C has 4.7k pullups to both SDA and SCL to 3.3V

### USB-C connector 
- 16 pin USB 2.0 receptable, D+ pads are tied together so directions works both ways - same goes for D- pads. These connections are then connected to the ESP32-S3's native USB pins. ESD protection is on both lines.

### PCB
- 2 layer
- L1 : components + signal traces
- L2 : ground pour and some signal traces

### Components:
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

### BOM:
|No.|ITEM NAME|QUANTITY|UNIT PRICE|TOTAL PRICE|URL|
|-|-|-|-|-|-|
|1.|ESP32-S3-WROOM-1-N8|1|£4.21|£4.21|https://www.digikey.co.uk/en/products/detail/espressif-systems/ESP32-S3-WROOM-1-N8/15200089?gclsrc=aw.ds&gad_source=4&gad_campaignid=22158564224&gbraid=0AAAAADrbLlhnVw0uKBiLMdcB-sG65GBBf&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTvIKuJ_ReG31ucZ_hla2_acCpvPbZDzBjPJQ6XUUpp84uHwSiiuX0xoCwkcQAvD_BwE|
|2.|TP4056 Charging IC|1|£1.00|£5.00 (pack of 5)|https://www.amazon.co.uk/TP4056-SOP-8-Chips-Battery-Charging-Black/dp/B0FKNDMF2P/ref=asc_df_B0FKNDMF2P?mcid=368bdd8ac8da35588938838a23d3121b&tag=googshopuk-21&linkCode=df0&hvadid=798872745271&hvpos=&hvnetw=g&hvrand=6100178580189971168&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9045986&hvtargid=pla-2500394808194&hvocijid=6100178580189971168-B0FKNDMF2P-&hvexpln=0&gad_source=1&th=1|
|3.|TPL5111 power timer|1|£0.88|£0.88|https://www.digikey.co.uk/en/products/detail/texas-instruments/TPL5111DDCR/6572460?gclsrc=aw.ds&gad_source=1&gad_campaignid=22862122441&gbraid=0AAAAADrbLlgQVVXCkqUfaoVzxNIXfxSpc&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTiPEFltT0Awucsop1SDP4kaz-Si9eJYKMLJsPOBMz68IH0QASfuYERoCycsQAvD_BwE|
|4.|AO3401 P-MOSFET|1|£0.16|£0.16|https://www.digikey.co.uk/en/products/detail/umw/ao3401a/16705973?_gl=1*1dbyrjm*_up*MQ..*_gs*MQ..&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTuxUWUAdx0OlqMmUVw_lGQ6Ks2z4ICRdgAn0Lsyy108cuNKoZz-Q6xoCMmgQAvD_BwE&gclsrc=aw.ds&gbraid=0AAAAADrbLlgQVVXCkqUfaoVzxNIXfxSpc|
|5.|AP2112K-3.3 LDO|1|£0.19|£0.19|https://www.digikey.co.uk/en/products/detail/diodes-incorporated/AP2112K-3.3TRG1/4470746?gclsrc=aw.ds&gad_source=1&gad_campaignid=22862122441&gbraid=0AAAAADrbLlgQVVXCkqUfaoVzxNIXfxSpc&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTuh9teA_Be3pTm024Dk6yNt-gf0ab-2VZLTyhhx_3Oep18vSbS-CVxoCBdUQAvD_BwE|
|6.|MAX98357A AUDIO AMP|1|£2.77|£2.77|https://www.digikey.co.uk/en/products/detail/analog-devices-inc-maxim-integrated/max98357aete-t/4936122?_gl=1*c84n35*_up*MQ..*_gs*MQ..&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTuh9teA_Be3pTm024Dk6yNt-gf0ab-2VZLTyhhx_3Oep18vSbS-CVxoCBdUQAvD_BwE&gclsrc=aw.ds&gbraid=0AAAAADrbLlgQVVXCkqUfaoVzxNIXfxSpc|
|7.|USBLC6-2SC6 ESD|1|£0.33|£0.33|https://www.digikey.co.uk/en/products/detail/analog-devices-inc-maxim-integrated/max98357aete-t/4936122?_gl=1*c84n35*_up*MQ..*_gs*MQ..&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTuh9teA_Be3pTm024Dk6yNt-gf0ab-2VZLTyhhx_3Oep18vSbS-CVxoCBdUQAvD_BwE&gclsrc=aw.ds&gbraid=0AAAAADrbLlgQVVXCkqUfaoVzxNIXfxSpc|
|8.|USB-C connector 16 pin|1|£1.65|£1.65|https://www.digikey.co.uk/en/products/detail/amphenol-cs-commercial-products/124019772112A/13683231?s=N4IgTCBcDaIIxgCwAY4E4DsGxwQQRAF0BfIA|
|9.|0.96" SSD1306 OLED BREAKOUT|1|£1.49|£1.49|https://www.aliexpress.com/item/1005006782987637.html?src=google&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&albagn=888888&ds_e_adid=784528327853&ds_e_matchtype=search&ds_e_device=c&ds_e_network=g&ds_e_product_group_id=2450481629254&ds_e_product_id=en1005006782987637&ds_e_product_merchant_id=5762056048&ds_e_product_country=GB&ds_e_product_language=en&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=23272714697&albag=191864323674&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gad_campaignid=23272714697&gbraid=0AAAAAD6I-hHm45nEfYGvpW1ul0Xa_aUvK&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTqelPrhuj-teLi2_5M1gNY1X_KmL8qYrg3Ja1ZjgTNmoLROe3uoV_BoCGpQQAvD_BwE|
|10.|28mm 8OHM 2W speaker|1|£0.17|£0.99 (pack of 6|https://www.aliexpress.com/item/1005011990029265.html?src=google&src=google&albch=shopping&acnt=494-037-6276&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&albagn=888888&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=en1005011990029265&ds_e_product_merchant_id=5615442231&ds_e_product_country=GB&ds_e_product_language=en&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=23838444405&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gad_campaignid=23838478926&gbraid=0AAAAADznYb9Tjhmiu8gZnpyHjGzt_AVWJ&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTpC4GITMxW7JZ_gwH_DKkAmmfL-4x2iZHYTlFu4uGa653W69FxaN4xoCgQYQAvD_BwE|
|11.|12mm PIEZO BUZZER|1|£0.05|£0.99 (pack of 20)|https://www.aliexpress.com/item/1005009235440867.html?aff_fsk=_oBXVPn9&aff_platform=aff_feeds&aff_short_key=_oBXVPn9&cn=326576&cv=90dc9d53ad3a459934a2d8241df6ed58&dp=CjwKCAjw0dPRBhAPEiwAE5vTTkq9sbbZYhgshjuYp10w0NHn-gP9twfAMcPxJ6pkkLDZD-1NDYWv2xoC9_UQAvD_BwE&isdl=y&src=Connexity2023GBchannelpdp_npi%3D6%40dis%21GBP%212.82%211.38%21%21%2124.86%2112.18%21%4012000048420433854%21affd%21%21%21%211%210%21&gad_source=1|
|12.|Kalih Choc V1|1|£0.35|£3.48( pack of 10)|https://www.aliexpress.com/item/1005011812362132.html?pdp_npi=6%40dis%21GBP%214.76%213.93%21%21%216.22%215.14%21%402141149b17804546007015542e1050%2112000056648742495%21affd%21%21%21%211%210%21&dp=CjwKCAjw0dPRBhAPEiwAE5vTTs9byTJE98HGOVUuRLit0qy7z5_IEwVLRvdjHZoqBJ4D4eDM5XYsqxoC35UQAvD_BwE%7C0AAAAA_4-1LmChaPg216sXwPEzC48t3U9F%7CCj4KCAjwrs7RBhAlEi4A0iCF2T91YG2VWsL8aLPr0dwMg0c-SuquarvAtsDi1puvcF1IGE6ZeDHKK2SOGgJxaw%7Cv1&cn=gb_a&gad_source=1&aff_fcid=ee3527ecf77e4d7780d1670d9f70dfbb-1781887110305-02357-_onKPRpM&aff_fsk=_onKPRpM&aff_platform=api-new-product-query&sk=_onKPRpM&aff_trace_key=ee3527ecf77e4d7780d1670d9f70dfbb-1781887110305-02357-_onKPRpM&terminal_id=9e5669d204254c5ab04439f61bb38a03&afSmartRedirect=y|
|13.|EC11 Rotary Encoder|1|£0.90|£0.90|https://www.aliexpress.com/item/1005007644083514.html?src=google&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&albagn=888888&ds_e_adid=784528327853&ds_e_matchtype=search&ds_e_device=c&ds_e_network=g&ds_e_product_group_id=2450481629254&ds_e_product_id=en1005007644083514&ds_e_product_merchant_id=554253349&ds_e_product_country=GB&ds_e_product_language=en&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=23272714697&albag=191864323674&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gad_campaignid=23272714697&gbraid=0AAAAAD6I-hHm45nEfYGvpW1ul0Xa_aUvK&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTik-lqorW_FRREKRxu3bsbL5fJEPnTf730tLHjCAXa9yslOBrI1fihoCXTEQAvD_BwE|
|14.|LiPo 803040 -1000mah|1|£3.79|£3.79|https://www.aliexpress.com/item/1005011940576057.html?pdp_npi=6%40dis%21GBP%218.02%213.37%21%21%2170.86%2129.76%21%402140d33617804244389434348e0e54%2112000057087402305%21affd%21%21%21%211%210%21&dp=CjwKCAjw0dPRBhAPEiwAE5vTTi8jvbgjW-nsZ-mxZvHJq-xZFKN8MW6a8BBxr674IHWoWD8EYPS5OBoC0IAQAvD_BwE%7C0AAAAA_4-1LmChaPg216sXwPEzC48t3U9F%7CCj4KCAjwrs7RBhAlEi4A0iCF2T91YG2VWsL8aLPr0dwMg0c-SuquarvAtsDi1puvcF1IGE6ZeDHKK2SOGgJxaw%7Cv1&cn=gb_a&gad_source=1&aff_fcid=cbd19955eae149ffaca815f329334e00-1781887469224-05611-_onKPRpM&aff_fsk=_onKPRpM&aff_platform=api-new-product-query&sk=_onKPRpM&aff_trace_key=cbd19955eae149ffaca815f329334e00-1781887469224-05611-_onKPRpM&terminal_id=9e5669d204254c5ab04439f61bb38a03&afSmartRedirect=y|
|15.| Resistor 100k|4|£0.07|£0.28|https://www.digikey.co.uk/en/products/detail/yageo/RC0402FR-07100KL/726526|
|16.| Resistor 10k| 7|£0.07|£0.49|https://www.digikey.co.uk/en/products/detail/yageo/RC0402FR-0710KL/726523|
|17.| Resistor 5.1k|2|£0.07|£0.14|https://www.digikey.co.uk/en/products/detail/yageo/RC0402FR-075KL/5917711?s=N4IgTCBcDaIEoGEAMAWJYBicC0SDsArANIAyIAugL5A|
|18.| Resistor 4.7k|2|£0.07|£0.14|https://www.digikey.co.uk/en/products/detail/yageo/RC0402FR-074K7L/2827563?s=N4IgTCBcDaIE4GMAMAWJYBmcC0SDsKA1ngDYgC6AvkA|
|19.| Resistor 1.2k|1|£0.07|£0.07|https://www.digikey.co.uk/en/products/detail/yageo/RC0402FR-071K2L/726517?s=N4IgTCBcDaIE4GMAMAWJYBmcC0SDsAjANZgA2IAugL5A|
|20.| Resistor 1k|2|£0.07|£0.14|https://www.digikey.co.uk/en/products/detail/yageo/RC0402FR-071KL/726513?s=N4IgTCBcDaIE4GMAMAWJYBmcC0SDsAjANYA2IAugL5A|
|21.| Capacitor 10u|6|£0.27|£1.62|https://www.digikey.co.uk/en/products/detail/murata-electronics/GRM155R61A106ME18D/26264983?gclsrc=aw.ds&gad_source=1&gad_campaignid=23428943411&gbraid=0AAAAADrbLlgWGEv27dhZWFi7DSW1z73GA&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTqvSOZSlstmrAEjrq3gS1yfg1YO956E60UKJHYAsPGcPTFWQ-4doWhoCHfYQAvD_BwE|
|22.| Capacitor 1u|1|£0.07|£0.07|https://www.digikey.co.uk/en/products/detail/taiyo-yuden/JMK105BJ105KV-F/930583|
|23.| Capacitor 100n|6|£0.07|£0.42|https://www.digikey.co.uk/en/products/detail/samsung-electro-mechanics/CL05B104KP5NNNC/3886660|
|24.| LED RED|1|£0.34|£0.34|https://www.digikey.co.uk/en/products/detail/lumex-opto-components-inc/SML-LXFM0603SIC-TR/411897|
|25.| LED GREEN|1|£0.25|£0.25|https://www.digikey.co.uk/en/products/detail/w%C3%BCrth-elektronik/150060GS73220/8557160|
|26.| 6mm Tactile Button|2|£0.87|£1.74|https://www.digikey.co.uk/en/products/detail/omron-electronics-inc-emc-div/B3U-1100P/1534339?gclsrc=aw.ds&gad_source=4&gad_campaignid=21679743037&gbraid=0AAAAADrbLliVdtEPbUuy9LFELut7DHDTH&gclid=CjwKCAjw0dPRBhAPEiwAE5vTTvYnbM4oHlGRfQNn_dntS3duTGOIw8Mnn3E9ZYJ9iPymQCv81zZk4RoCT6MQAvD_BwE|
|27.|PCB|1|£0.48|£2.4|JLCPCB|
|28.|Solder Paste Stencil|1|£5.37|£5.37|JLCPCB|
|29.|M3 Self Tapping Screws|4|£0.05|£2.47(50pack)|https://cpc.farnell.com/unbranded/m3x6-pan-pozi-stainl/m3x6-pan-pozi-stainless-screws/dp/FN00814?gross_price=true&mckv=sshopping_dc|pcrid|426684131423|kword||match||plid||slid||product|FN00814|pgrid|100371162718|ptaid|pla-2177230439981|&CMP=KNC-GUK-CPC-SHOPPING-9262013734-100371162718-FN00814&s_kwcid=AL!5616!3!426684131423!!!network}!2177230439981!&gad_source=1&gad_campaignid=9262013734&gbraid=0AAAAAD_m6B18mbvSishqdH_AlczsMH5Ge&gclid=CjwKCAjw0dPRBhAPEiwAE5vTToLz2cqZ-4VV0NWd0TadiM0KJ0ZQb9aNZPIKNwyf5dgqHOcgOcoShBoCqskQAvD_BwE
|30.|3D printed Case and Keycap|1 set|N/A (small)|£10.50 (1 Roll PETG HF)|https://uk.store.bambulab.com/products/petg-hf?id=42010450264124|
|31.|Thin Wire|1|~£0.5 (1m)|£4.99 (spool of 10m)|https://www.amazon.co.uk/sourcing-map-Stranded-Electrical-Connecting/dp/B0F6LRFJS6/ref=asc_df_B0F6LRFJS6?mcid=b5412eaed2b73ada95f26adff5a23573&tag=googshopuk-21&linkCode=df0&hvadid=744245591477&hvpos=&hvnetw=g&hvrand=16339553975944344858&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9045986&hvtargid=pla-2428586534065&hvocijid=16339553975944344858-B0F6LRFJS6-&hvexpln=0&gad_source=1&th=1|
|32.|Keychain|1|£0.13|£3.89 (pack of 30)|https://www.amazon.co.uk/YHYZ-Premium-Keychain-Suitable-Jewelry/dp/B08CMWFL8Y/ref=sr_1_1_sspa?dib=eyJ2IjoiMSJ9.fGkRdlsqd3AZ_iNoiR7zF35eZUd6fHiOCn_RnzR7vG0Dsa545q4wWuqMcmIT-IYOeXM9MwDFgkXlyeWz8jMrcc_tMue2nDkNHKqY9WsoGyH_8GPG7TQi2M0S8wCalJpa3Sym7tYFwX-vqYpmQUAKadWCtYKhZ1TgqDam371x7FiJaGl2wRj_T-UYzSTtC1hAXJ3cIsjkdFY4oScrln7F-ZkC-0hp9vfMWK_BnJqm5k8kiewMKxIDF1-szprBlbU6V8cEVpE91mFfO-X3o2D1GVEmsEcWy1zfVsUAdCABfNY.WjOZfGPOmoFyCkeD3UFRfQtdPHeSlY8Nv6DINSG97Os&dib_tag=se&keywords=Keyrings%2B%26%2BKeychains&qid=1781890914&sr=8-1-spons&aref=CwgZzk9sIl&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1&psc=1|
-
### Assembly:
 - Make sure you have all components listed available and casing 3D printed.
 - Solder all the components on the PCB as per the schematic
 - Connect the battery to the 2 pin connector (label in schematic file)
 - Place the PCB on top of the base and use M3 screws, preferably around 3-4mm
 - Flash firmware onto the ESP32 using the USB-C connector (If there is no output when flashing, hold the flash button to reset - forces chip into download mode)
 - Use plastic adhesive to adhere the the lid to the base - once everything works okay
 - Put on the keycap and enjoy!

### Design Notes:
- You could go with a different mcu but I chose the ESP-32 as this one has native USB, decent peripheral support and has 8MB of memory which makes it a suitable cost-effective solution in this case. The atenna is not used, but it could be used in future alterations with firmware but if you really wanted bluetooth or wifi you can use ur phone lol
- I reccomend you get a stencil which would make soldering alot easier
- The system switches and the rotary encoder is located under the keycap as they are designed to be set-once parameters, not designed to be constantly adjusted so this would make the keycap look better.
