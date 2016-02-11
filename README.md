# MFMarlin
Marlin 1.1.0 RC3 for Makerfarm Pegasus

**in this configuration software endstops are turned off; as a result you will be able to crash the head very easily if you manually move the print head or incorrectly set offsets. If you do not want it to act this way edit line 404 of configuration.h to be true instead of false**

newest changes: speed has been changed because I changed my stepper drivers. I blew out the stepsticks that came with it because I am dumb and replaced with DRV8825 - trying out 1/32nd stepping for now

added a ferrite core to the servo signal line and powered with a 7805 rather than using the arduino. Jitter is improved quite a bit but still present unfortunately. Considering building a [noise trap](http://www.sentex.ca/~mec1995/gadgets/noiserx.htm) because I found a hex-schmitt IC in my parts bin; also might add caps to the power and signal lines (see arduino_servo_filters.jpg)

https://github.com/MarlinFirmware/Marlin - I didn't fork because I'm dumb but all the real work is from here; mine is merely a configuration for a 10" Makerfarm pegasus, figured I would share to help anyone else that has a similar setup. I'm also using this document as a collection of what I've done so I can keep track.

This is typically going to be configured for my setup (described below). I'll try to maintain it for as long as possible but no guarantees on that front. I would suggest that if you download this you read over configuration.h at least once - you'll likely at least need to change the bed size and would probably benefit from adding your own PID tunings. If you are using auto bed level you will need to enter the measurements for your machine and if not you should disable it and turn software endstops on.

I have a 10" Pegasus dual extruder with E3Dv6 extruders, graphical LCD, a servo for auto bed leveling (abl), 3mm Borosilicate over bed, SSR on bed for PID control, new bed clips, and some other mods that don't impact the firmware (octopi, cooling for Ramps, lighting, etc). Working fine for me however I do not take any responsibility for you destroying your machine or whatever and no warranty is expressed or implied. Also - I tend to err on the side of slower printing so you may need to play with that a bit for your preferences.

see /mods for images and a brief description of mods I've done as well as some troubleshooting for problems that were a pain to solve and some ideas for new mods. 

my current slicer settings posted in /slicer as an fff file for simplify3d. If you don't use S3D you can just open it on github; it's basically an XML file. I typically end up messing with the standard stuff, infill/raft/layer height/temperature/etc but the rest is mostly locked in at this point.

Change notes for MFMarlin:
configuration.h

line 73: MB type; I have it set to BOARD_RAMPS_14_EEB - extruder, extruder, bed. Single extruder may want EFB at the end (extruder, fan, bed) or something else depending on what you have connected to D10/9/8, see 

line 78: custom machine name if you want to change the "pegasus ready" text

line 86: define # of extruders. set to 1 currently because I broke my secondary thermistor. D'oh!

thermal settings should be the same unless you've changed thermistors. On that note I've read Makerfarm uses custom thermistor tables but I compared his versus the one in this release and they were essentially identical so thermistortables.h is unchanged; unsure if what I heard was wrong or if this only applies to the prusa i3v

lines 175-178 may have to change for E3Dv6 lite? 

PID:
lines 218-20 are the settings from my extruder with pidautotune, would probably be beneficial to run your own and put in your own values (M303 E0 C8 S210, where E is device (e0 ext 1, e1 ext 2, e-1 bed), C is # cycles, and S is target temp). I see that RC3 has the option to use seperate PID for each extruder, I will likely play with this some more when my replacement thermistor comes

line 246 (#define PIDTEMPBED) - comment this out if you do not use PID for the bed (if you are using the default relay from the kit you should comment this out, I use a Fotek SSR)

lines 270-72 are my bed settings from pidautotune, again suggest you grab your own (M303 E-1 C8 S100)

thermal runaway is on, settings for this have moved to configuration_adv.h - I upped the protection period to 60s because I found myself getting false positives with the PID bed. Consider changing configuration_adv.h line 21 to 40 if you are not. 

back to configuration.h:
346-52: endstop inverting. I have them all as false, colin's has x_max inverted which shouldn't matter as the machine doesn't have max endstops - on that note line 353 is not commented out, comment out to add max endstops 

404 - set to false, set to true if you aren't using abl/are using abl with a second endstop wired in series.

410-415 - my bed limits. If you have the 8" machine this will definitely need to be changed. If you have the default 10 with binder clips you'll probably have to pull it in a bit; I've modified how my glass clamps to the bed to maximize build area. I also place my x and y endstops at x0 y0

420 - filament runout sensor is commented out, not using.

430-50 manual bed leveling is commented out because I'm using abl, uncomment line 434 to add it back into the menu

auto bed level section

457 - comment out to disable ABL

480-83 - box, if you've changed the bed size you'll likely need to change this

489 - # of probe points x 3, set to 3 (probes 9 points)

506-08 - z probe offsets from extruder - [you will need to measure these on your own] (http://zennmaster.com/random-things/auto-bed-leveling-for-the-makerfarm-prusa-i3-part-3-final-setup)

510-517 - z probe behavior, customize to your preference

602-613 - copied from Colin's release. Ensure these values match the ones in your machines config, especially axis_steps_per_unit!

640 - eeprom storage enabled

654-61 - preheat settings. Mine are probably a touch high but they work for my primary filament brand (inland)

LCD - 
if you're using no LCD comment out line 725 (#define REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER). If you're using the graphic LCD leave as is and install the [u8glib arduino library](https://github.com/olikraus/u8glib)

if you're using the other LCD comment out 725 as above and I believe you uncomment line 715: #define REPRAP_DISCOUNT_SMART_CONTROLLER

RC servo stuff:
comment out line 816 to disable servos

if you are using a servo for abl ensure you set #define SERVO_ENDSTOP_ANGLES on line 826 for your setup

if the servo is unable to complete moves increase servo_activation_delay on line 837, I'm using a towerpro 9g servo so I had to up it a bit. If you notice the servo jerking a bit after it's finished you might need to decrease it. 

other changes:
ultralcd.cpp line 1669 - changed incrementor to += to invert direction of rotary knob on LCD display

bugs found:
random reboot - appears to be a function of using too much at once (e.g. ramping heat WAY up on both extruders and bed while having the carriage move around) and is most likely an issue with my power supply, but still trying to see if I can reproduce it. 
SD sometimes not detected after reboot - every time this has happened reseating the card has fixed the issue. again, trying to reproduce consistently. 

to do - enable second extruder when new thermistor comes; play with extruder offsets in firmware to replace M218 commands in slicer starting gcode. 

msg me if you find a bug or have questions although I do not guarantee I can help or will respond in a timely manner. 




