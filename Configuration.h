#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "boards.h"
#include "macros.h"

// @section info

#if ENABLED(USE_AUTOMATIC_VERSIONING)
  #include "_Version.h"
#else
  #include "Default_Version.h"
#endif

// User-specified version info of this build to display in [Pronterface, etc] terminal window during
// startup. Implementation of an idea by Prof Braino to inform user that any changes made to this
// build by the user have been successfully uploaded into firmware.
#define STRING_CONFIG_H_AUTHOR ("Jon, Makerfarm Pegasus Dual 10\" 1.1.0 RC3") // Who made the changes.
#define SHOW_BOOTSCREEN
#define STRING_SPLASH_LINE1 SHORT_BUILD_VERSION // will be shown during bootup in line 1
//#define STRING_SPLASH_LINE2 STRING_DISTRIBUTION_DATE // will be shown during bootup in line 2

// @section machine

// SERIAL_PORT selects which serial port should be used for communication with the host.
// This allows the connection of wireless adapters (for instance) to non-default port pins.
// Serial port 0 is still used by the Arduino bootloader regardless of this setting.
// :[0,1,2,3,4,5,6,7]
#define SERIAL_PORT 0

// This determines the communication speed of the printer
// :[2400,9600,19200,38400,57600,115200,250000]
#define BAUDRATE 115200

// The following define selects which electronics board you have.
// Please choose the name from boards.h that matches your setup
#ifndef MOTHERBOARD
  #define MOTHERBOARD 44
#endif

// Optional custom name for your RepStrap or other custom machine
// Displayed in the LCD "Ready" message
#define CUSTOM_MACHINE_NAME "Pegasus"

// Define this to set a unique identifier for this printer, (Used by some programs to differentiate between machines)
// You can use an online service to generate a random UUID. (eg http://www.uuidgenerator.net/version4)
#define MACHINE_UUID "9831ee20-f544-40ec-9450-58e42773382e"

// This defines the number of extruders
// :[1,2,3,4]
#define EXTRUDERS 1

// Offset of the extruders (uncomment if using more than one and relying on firmware to position when changing).
// The offset has to be X=0, Y=0 for the extruder 0 hotend (default extruder).
// For the other hotends it is their distance from the extruder 0 hotend.
#define EXTRUDER_OFFSET_X {0.0, 25.30} // (in mm) for each extruder, offset of the hotend on the X axis
#define EXTRUDER_OFFSET_Y {0.0, -1.00}  // (in mm) for each extruder, offset of the hotend on the Y axis

#define POWER_SUPPLY 1

// @section temperature

//===========================================================================
//============================= Thermal Settings ============================
//===========================================================================
//
//--1kohm pullup on my ramps
//
//// Temperature sensor settings:
// 1 is 100k thermistor - best choice for EPCOS 100k (4.7k pullup)
// 5 is 100K thermistor - ATC Semitec 104GT-2 (Used in ParCan & J-Head) (4.7k pullup)

// 51 is 100k thermistor - EPCOS (1k pullup)
// 52 is 200k thermistor - ATC Semitec 204GT-2 (1k pullup)
// 55 is 100k thermistor - ATC Semitec 104GT-2 (Used in ParCan & J-Head) (1k pullup)

#define TEMP_SENSOR_0 52
#define TEMP_SENSOR_1 52
#define TEMP_SENSOR_2 0
#define TEMP_SENSOR_3 0
#define TEMP_SENSOR_BED 52

// This makes temp sensor 1 a redundant sensor for sensor 0. If the temperatures difference between these sensors is to high the print will be aborted.
//#define TEMP_SENSOR_1_AS_REDUNDANT
#define MAX_REDUNDANT_TEMP_SENSOR_DIFF 10

// Actual temperature must be close to target for this long before M109 returns success
#define TEMP_RESIDENCY_TIME 10  // (seconds)
#define TEMP_HYSTERESIS 3       // (degC) range of +/- temperatures considered "close" to the target one
#define TEMP_WINDOW     1       // (degC) Window around target to start the residency timer x degC early.

// The minimal temperature defines the temperature below which the heater will not be enabled It is used
// to check that the wiring to the thermistor is not broken.
// Otherwise this would lead to the heater being powered on all the time.
#define HEATER_0_MINTEMP 5
#define HEATER_1_MINTEMP 5
#define HEATER_2_MINTEMP 5
#define HEATER_3_MINTEMP 5
#define BED_MINTEMP 5

// When temperature exceeds max temp, your heater will be switched off.
// This feature exists to protect your hotend from overheating accidentally, but *NOT* from thermistor short/failure!
// You should use MINTEMP for thermistor short/failure protection.
#define HEATER_0_MAXTEMP 275
#define HEATER_1_MAXTEMP 275
#define HEATER_2_MAXTEMP 275
#define HEATER_3_MAXTEMP 275
#define BED_MAXTEMP 150

//===========================================================================
//============================= PID Settings ================================
//===========================================================================
// PID Tuning Guide here: http://reprap.org/wiki/PID_Tuning

// Comment the following line to disable PID and enable bang-bang.
#define PIDTEMP
#define BANG_MAX 255 // limits current to nozzle while in bang-bang mode; 255=full current
#define PID_MAX BANG_MAX // limits current to nozzle while PID is active (see PID_FUNCTIONAL_RANGE below); 255=full current
#if ENABLED(PIDTEMP)
  //#define SLOW_PWM_HEATERS // PWM with very low frequency (roughly 0.125Hz=8s) and minimum state time of approximately 1s useful for heaters driven by a relay
  #define PID_PARAMS_PER_EXTRUDER // Uses separate PID parameters for each extruder (useful for mismatched extruders)
                                    // Set/get with gcode: M301 E[extruder number, 0-2]
  #define PID_FUNCTIONAL_RANGE 10 // If the temperature difference between the target temperature and the actual temperature
                                  // is more then PID_FUNCTIONAL_RANGE then the PID will be shut off and the heater will be set to min/max.
  #define PID_INTEGRAL_DRIVE_MAX PID_MAX  //limit for the integral term
  #define K1 0.95 //smoothing factor within the PID

    // Makerfarm Pegasus Dual e3dv6 (primary)
    //from pidautotune
  #define  DEFAULT_Kp 34.24
  #define  DEFAULT_Ki 3.80
  #define  DEFAULT_Kd 77.18

      // Makerfarm Pegasus Dual e3dv6 (secondary)
    //from pidautotune
 // #define  DEFAULT_Kp 35.97
 // #define  DEFAULT_Ki 4.44
 // #define  DEFAULT_Kd 72.81

#endif // PIDTEMP

//===========================================================================
//============================= PID > Bed Temperature Control ===============
//===========================================================================
// Select PID or bang-bang with PIDTEMPBED. If bang-bang, BED_LIMIT_SWITCHING will enable hysteresis
//
// Uncomment this to enable PID on the bed. It uses the same frequency PWM as the extruder.
// If your PID_dT is the default, and correct for your hardware/configuration, that means 7.689Hz,
// which is fine for driving a square wave into a resistive load and does not significantly impact you FET heating.
// This also works fine on a Fotek SSR-10DA Solid State Relay into a 250W heater.
// If your configuration is significantly different than this and you don't understand the issues involved, you probably
// shouldn't use bed PID until someone else verifies your hardware works.
// If this is enabled, find your own PID constants below.
#define PIDTEMPBED

//#define BED_LIMIT_SWITCHING

// This sets the max power delivered to the bed, and replaces the HEATER_BED_DUTY_CYCLE_DIVIDER option.
// all forms of bed control obey this (PID, bang-bang, bang-bang with hysteresis)
// setting this to anything other than 255 enables a form of PWM to the bed just like HEATER_BED_DUTY_CYCLE_DIVIDER did,
// so you shouldn't use it unless you are OK with PWM on your bed.  (see the comment on enabling PIDTEMPBED)
#define MAX_BED_POWER 255 // limits duty cycle to bed; 255=full current

#if ENABLED(PIDTEMPBED)

  #define PID_BED_INTEGRAL_DRIVE_MAX MAX_BED_POWER //limit for the integral term

  //Makerfarm 10" bed with 3mm borosilicate
  //pidautotune
  #define  DEFAULT_bedKp 209.84
  #define  DEFAULT_bedKi 41.05
  #define  DEFAULT_bedKd 268.18

  // FIND YOUR OWN: "M303 E-1 C8 S90" to run autotune on the bed at 90 degreesC for 8 cycles.
#endif // PIDTEMPBED

// @section extruder

//this prevents dangerous Extruder moves, i.e. if the temperature is under the limit
//can be software-disabled for whatever purposes by
#define PREVENT_DANGEROUS_EXTRUDE
//if PREVENT_DANGEROUS_EXTRUDE is on, you can still disable (uncomment) very long bits of extrusion separately.
#define PREVENT_LENGTHY_EXTRUDE

#define EXTRUDE_MINTEMP 170
#define EXTRUDE_MAXLENGTH (X_MAX_LENGTH+Y_MAX_LENGTH) //prevent extrusion of very large distances.

//===========================================================================
//======================== Thermal Runaway Protection =======================
//===========================================================================

#define THERMAL_PROTECTION_HOTENDS // Enable thermal protection for all extruders
#define THERMAL_PROTECTION_BED     // Enable thermal protection for the heated bed

//===========================================================================
//============================= Mechanical Settings =========================
//===========================================================================

// @section homing

// coarse Endstop Settings
#define ENDSTOPPULLUPS // Comment this out (using // at the start of the line) to disable the endstop pullup resistors

#if DISABLED(ENDSTOPPULLUPS)
  // fine endstop settings: Individual pullups. will be ignored if ENDSTOPPULLUPS is defined
  //#define ENDSTOPPULLUP_XMAX
  //#define ENDSTOPPULLUP_YMAX
  //#define ENDSTOPPULLUP_ZMAX
  //#define ENDSTOPPULLUP_XMIN
  //#define ENDSTOPPULLUP_YMIN
  //#define ENDSTOPPULLUP_ZMIN
  //#define ENDSTOPPULLUP_ZMIN_PROBE
#endif

// Mechanical endstop with COM to ground and NC to Signal uses "false" here (most common setup).
const bool X_MIN_ENDSTOP_INVERTING = false; // set to true to invert the logic of the endstop.
const bool Y_MIN_ENDSTOP_INVERTING = false; // set to true to invert the logic of the endstop.
const bool Z_MIN_ENDSTOP_INVERTING = false; // set to true to invert the logic of the endstop.
const bool X_MAX_ENDSTOP_INVERTING = false; // set to true to invert the logic of the endstop.
const bool Y_MAX_ENDSTOP_INVERTING = false; // set to true to invert the logic of the endstop.
const bool Z_MAX_ENDSTOP_INVERTING = false; // set to true to invert the logic of the endstop.
const bool Z_MIN_PROBE_ENDSTOP_INVERTING = false; // set to true to invert the logic of the endstop.
#define DISABLE_MAX_ENDSTOPS

// For Inverting Stepper Enable Pins (Active Low) use 0, Non Inverting (Active High) use 1
// :{0:'Low',1:'High'}
#define X_ENABLE_ON 0
#define Y_ENABLE_ON 0
#define Z_ENABLE_ON 0
#define E_ENABLE_ON 0 // For all extruders

// Disables axis when it's not being used.
// WARNING: When motors turn off there is a chance of losing position accuracy!
#define DISABLE_X false
#define DISABLE_Y false
#define DISABLE_Z false

// @section extruder

#define DISABLE_E false // For all extruders
#define DISABLE_INACTIVE_EXTRUDER true //disable only inactive extruders and keep active extruder enabled

// @section machine

// Invert the stepper direction. Change (or reverse the motor connector) if an axis goes the wrong way.
#define INVERT_X_DIR true
#define INVERT_Y_DIR false
#define INVERT_Z_DIR false

// @section extruder

// For direct drive extruder v9 set to true, for geared extruder set to false.
#define INVERT_E0_DIR false
#define INVERT_E1_DIR false
#define INVERT_E2_DIR false
#define INVERT_E3_DIR false

// @section homing

// ENDSTOP SETTINGS:
// Sets direction of endstops when homing; 1=MAX, -1=MIN
// :[-1,1]
#define X_HOME_DIR -1
#define Y_HOME_DIR -1
#define Z_HOME_DIR -1

#define min_software_endstops false // If true, axis won't move to coordinates less than HOME_POS.
#define max_software_endstops true  // If true, axis won't move to coordinates greater than the defined lengths below.

// @section machine

// Travel limits after homing (units are in mm)
#define X_MIN_POS 0
#define Y_MIN_POS 0
#define Z_MIN_POS 0
#define X_MAX_POS 205
#define Y_MAX_POS 234
#define Z_MAX_POS 240

//===========================================================================
//========================= Filament Runout Sensor ==========================
//===========================================================================
//#define FILAMENT_RUNOUT_SENSOR // Uncomment for defining a filament runout sensor such as a mechanical or opto endstop to check the existence of filament
                                 // In RAMPS uses servo pin 2. Can be changed in pins file. For other boards pin definition should be made.
                                 // It is assumed that when logic high = filament available
                                 //                    when logic  low = filament ran out
#if ENABLED(FILAMENT_RUNOUT_SENSOR)
  const bool FIL_RUNOUT_INVERTING = true;  // Should be uncommented and true or false should assigned
  #define ENDSTOPPULLUP_FIL_RUNOUT // Uncomment to use internal pullup for filament runout pins if the sensor is defined.
  #define FILAMENT_RUNOUT_SCRIPT "M600"
#endif

//===========================================================================
//============================ Bed Auto Leveling ============================
//===========================================================================

// @section bedlevel

#define AUTO_BED_LEVELING_FEATURE // Delete the comment to enable (remove // at the start of the line)
#define Z_MIN_PROBE_REPEATABILITY_TEST  // If not commented out, Z-Probe Repeatability test will be included if Auto Bed Leveling is Enabled.

#if ENABLED(AUTO_BED_LEVELING_FEATURE)

  // There are 2 different ways to specify probing locations:
  //
  // - "grid" mode
  //   Probe several points in a rectangular grid.
  //   You specify the rectangle and the density of sample points.
  //   This mode is preferred because there are more measurements.
  //
  // - "3-point" mode
  //   Probe 3 arbitrary points on the bed (that aren't colinear)
  //   You specify the XY coordinates of all 3 points.

  // Enable this to sample the bed in a grid (least squares solution).
  // Note: this feature generates 10KB extra code size.
  #define AUTO_BED_LEVELING_GRID

  #if ENABLED(AUTO_BED_LEVELING_GRID)

    #define LEFT_PROBE_BED_POSITION 20
    #define RIGHT_PROBE_BED_POSITION 161
    #define FRONT_PROBE_BED_POSITION 20
    #define BACK_PROBE_BED_POSITION 200

    #define MIN_PROBE_EDGE 5 // The Z probe minimum square sides can be no smaller than this.

    // Set the number of grid points per dimension.
    // You probably don't need more than 3 (squared=9).
    #define AUTO_BED_LEVELING_GRID_POINTS 3

  #else  // !AUTO_BED_LEVELING_GRID

      // Arbitrary points to probe.
      // A simple cross-product is used to estimate the plane of the bed.
      #define ABL_PROBE_PT_1_X 15
      #define ABL_PROBE_PT_1_Y 180
      #define ABL_PROBE_PT_2_X 15
      #define ABL_PROBE_PT_2_Y 20
      #define ABL_PROBE_PT_3_X 170
      #define ABL_PROBE_PT_3_Y 20

  #endif // AUTO_BED_LEVELING_GRID

  // Offsets to the Z probe relative to the nozzle tip.
  // X and Y offsets must be integers.
  #define X_PROBE_OFFSET_FROM_EXTRUDER -44     // Z probe to nozzle X offset: -left  +right
  #define Y_PROBE_OFFSET_FROM_EXTRUDER -12    // Z probe to nozzle Y offset: -front +behind
  #define Z_PROBE_OFFSET_FROM_EXTRUDER -7.8  // Z probe to nozzle Z offset: -below (always!)

  #define Z_RAISE_BEFORE_HOMING 15     // (in mm) Raise Z axis before homing (G28) for Z probe clearance.
                                        // Be sure you have this distance over your Z_MAX_POS in case.

  #define XY_TRAVEL_SPEED 3000         // X and Y axis travel speed between probes, in mm/min.

  #define Z_RAISE_BEFORE_PROBING 20  // How much the Z axis will be raised before traveling to the first probing point.
  #define Z_RAISE_BETWEEN_PROBINGS 20 // How much the Z axis will be raised when traveling from between next probing points.
  #define Z_RAISE_AFTER_PROBING 20   // How much the Z axis will be raised after the last probing point.

//#define Z_PROBE_END_SCRIPT "G1 Z10 F12000\nG1 X15 Y330\nG1 Z0.5\nG1 Z10" // These commands will be executed in the end of G29 routine.
                                                                            // Useful to retract a deployable Z probe.

  //#define Z_PROBE_SLED // Turn on if you have a Z probe mounted on a sled like those designed by Charles Bell.
  //#define SLED_DOCKING_OFFSET 5 // The extra distance the X axis must travel to pickup the sled. 0 should be fine but you can push it further if you'd like.


  //If you have enabled the Bed Auto Leveling and are using the same Z Probe for Z Homing,
  //it is highly recommended you let this Z_SAFE_HOMING enabled!!!

  #define Z_SAFE_HOMING   // This feature is meant to avoid Z homing with Z probe outside the bed area.
                          // When defined, it will:
                          // - Allow Z homing only after X and Y homing AND stepper drivers still enabled.
                          // - If stepper drivers timeout, it will need X and Y homing again before Z homing.
                          // - Position the Z probe in a defined XY point before Z Homing when homing all axis (G28).
                          // - Block Z homing only when the Z probe is outside bed area.

  #if ENABLED(Z_SAFE_HOMING)

    #define Z_SAFE_HOMING_X_POINT ((X_MIN_POS + X_MAX_POS) / 2)    // X point for Z homing when homing all axis (G28).
    #define Z_SAFE_HOMING_Y_POINT ((Y_MIN_POS + Y_MAX_POS) / 2)    // Y point for Z homing when homing all axis (G28).

  #endif

  // Support for a dedicated Z probe endstop separate from the Z min endstop.
  // If you would like to use both a Z probe and a Z min endstop together,
  // uncomment #define Z_MIN_PROBE_ENDSTOP and read the instructions below.
  // If you still want to use the Z min endstop for homing, disable Z_SAFE_HOMING above.
  // Example: To park the head outside the bed area when homing with G28.
  //
  // WARNING:
  // The Z min endstop will need to set properly as it would without a Z probe
  // to prevent head crashes and premature stopping during a print.
  //
  // To use a separate Z probe endstop, you must have a Z_MIN_PROBE_PIN
  // defined in the pins_XXXXX.h file for your control board.
  // If you are using a servo based Z probe, you will need to enable NUM_SERVOS,
  // Z_ENDSTOP_SERVO_NR and SERVO_ENDSTOP_ANGLES in the R/C SERVO support below.
  // RAMPS 1.3/1.4 boards may be able to use the 5V, Ground and the D32 pin
  // in the Aux 4 section of the RAMPS board. Use 5V for powered sensors,
  // otherwise connect to ground and D32 for normally closed configuration
  // and 5V and D32 for normally open configurations.
  // Normally closed configuration is advised and assumed.
  // The D32 pin in Aux 4 on RAMPS maps to the Arduino D32 pin.
  // Z_MIN_PROBE_PIN is setting the pin to use on the Arduino.
  // Since the D32 pin on the RAMPS maps to D32 on Arduino, this works.
  // D32 is currently selected in the RAMPS 1.3/1.4 pin file.
  // All other boards will need changes to the respective pins_XXXXX.h file.
  //
  // WARNING:
  // Setting the wrong pin may have unexpected and potentially disastrous outcomes.
  // Use with caution and do your homework.
  //
  //#define Z_MIN_PROBE_ENDSTOP

#endif // AUTO_BED_LEVELING_FEATURE


// @section homing

// The position of the homing switches
//#define MANUAL_HOME_POSITIONS  // If defined, MANUAL_*_HOME_POS below will be used
//#define BED_CENTER_AT_0_0  // If defined, the center of the bed is at (X=0, Y=0)

// Manual homing switch locations:
// For deltabots this means top and center of the Cartesian print volume.
#if ENABLED(MANUAL_HOME_POSITIONS)
  #define MANUAL_X_HOME_POS 0
  #define MANUAL_Y_HOME_POS 0
  #define MANUAL_Z_HOME_POS 0
  //#define MANUAL_Z_HOME_POS 402 // For delta: Distance between nozzle and print surface after homing.
#endif

// @section movement

/**
 * MOVEMENT SETTINGS
 */

#define HOMING_FEEDRATE {50*60, 50*60, 200, 0}  // set the homing speeds (mm/min)

// default settings

#define DEFAULT_AXIS_STEPS_PER_UNIT   {160.38,160.38,5120,180}  // default steps per unit for Ultimaker
#define DEFAULT_MAX_FEEDRATE          {500, 500, 2, 50}    // (mm/sec)
#define DEFAULT_MAX_ACCELERATION      {3000,3000,5,3000}    // X, Y, Z, E maximum start speed for accelerated moves. E default values are good for Skeinforge 40+, for older versions raise them a lot.

#define DEFAULT_ACCELERATION          500    // X, Y, Z and E acceleration in mm/s^2 for printing moves
#define DEFAULT_RETRACT_ACCELERATION  500    // E acceleration in mm/s^2 for retracts
#define DEFAULT_TRAVEL_ACCELERATION   500    // X, Y, Z acceleration in mm/s^2 for travel (non printing) moves

// The speed change that does not require acceleration (i.e. the software might assume it can be done instantaneously)
#define DEFAULT_XYJERK                20.0    // (mm/sec)
#define DEFAULT_ZJERK                 0.4     // (mm/sec)
#define DEFAULT_EJERK                 5.0    // (mm/sec)


//=============================================================================
//============================= Additional Features ===========================
//=============================================================================

// @section more

// Custom M code points
#define CUSTOM_M_CODES
#if ENABLED(CUSTOM_M_CODES)
  #if ENABLED(AUTO_BED_LEVELING_FEATURE)
    #define CUSTOM_M_CODE_SET_Z_PROBE_OFFSET 851
    #define Z_PROBE_OFFSET_RANGE_MIN -20
    #define Z_PROBE_OFFSET_RANGE_MAX 20
  #endif
#endif

// @section extras

// EEPROM
// The microcontroller can store settings in the EEPROM, e.g. max velocity...
// M500 - stores parameters in EEPROM
// M501 - reads parameters from EEPROM (if you need reset them after you changed them temporarily).
// M502 - reverts to the default "factory settings".  You still need to store them in EEPROM afterwards if you want to.
//define this to enable EEPROM support
#define EEPROM_SETTINGS

#if ENABLED(EEPROM_SETTINGS)
  // To disable EEPROM Serial responses and decrease program space by ~1700 byte: comment this out:
  #define EEPROM_CHITCHAT // Please keep turned on if you can.
#endif

//
// M100 Free Memory Watcher
//
//#define M100_FREE_MEMORY_WATCHER // uncomment to add the M100 Free Memory Watcher for debug purpose

// @section temperature

// Preheat Constants
#define PLA_PREHEAT_HOTEND_TEMP 205
#define PLA_PREHEAT_HPB_TEMP 45
#define PLA_PREHEAT_FAN_SPEED 0   // Insert Value between 0 and 255

#define ABS_PREHEAT_HOTEND_TEMP 250
#define ABS_PREHEAT_HPB_TEMP 100
#define ABS_PREHEAT_FAN_SPEED 0   // Insert Value between 0 and 255

//==============================LCD and SD support=============================
// @section lcd

// Define your display language below. Replace (en) with your language code and uncomment.
// en, pl, fr, de, es, ru, bg, it, pt, pt-br, fi, an, nl, ca, eu, kana, kana_utf8, cn, test
// See also language.h
#define LANGUAGE_INCLUDE GENERATE_LANGUAGE_INCLUDE(en)

// Choose ONE of these 3 charsets. This has to match your hardware. Ignored for full graphic display.
// To find out what type you have - compile with (test) - upload - click to get the menu. You'll see two typical lines from the upper half of the charset.
// See also documentation/LCDLanguageFont.md
  #define DISPLAY_CHARSET_HD44780_JAPAN        // this is the most common hardware

#define SDSUPPORT // Enable SD Card Support in Hardware Console
// Changed behaviour! If you need SDSUPPORT uncomment it!

// ==> REMEMBER TO INSTALL U8glib to your ARDUINO library folder: http://code.google.com/p/u8glib/wiki/u8glib
#define REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER

// @section extras

// Increase the FAN pwm frequency. Removes the PWM noise but increases heating in the FET/Arduino
//#define FAST_PWM_FAN

// Use software PWM to drive the fan, as for the heaters. This uses a very low frequency
// which is not as annoying as with the hardware PWM. On the other hand, if this frequency
// is too low, you should also increment SOFT_PWM_SCALE.
//#define FAN_SOFT_PWM

// Incrementing this by 1 will double the software PWM frequency,
// affecting heaters, and the fan if FAN_SOFT_PWM is enabled.
// However, control resolution will be halved for each increment;
// at zero value, there are 128 effective control positions.
#define SOFT_PWM_SCALE 0


/*********************************************************************\
* R/C SERVO support
* Sponsored by TrinityLabs, Reworked by codexmas
**********************************************************************/

// Number of servos
//
// If you select a configuration below, this will receive a default value and does not need to be set manually
// set it manually if you have more servos than extruders and wish to manually control some
// leaving it undefined or defining as 0 will disable the servo subsystem
// If unsure, leave commented / disabled
//
#define NUM_SERVOS 3 // Servo index starts with 0 for M280 command

// Servo Endstops
//
// This allows for servo actuated endstops, primary usage is for the Z Axis to eliminate calibration or bed height changes.
// Use M851 to set the Z probe vertical offset from the nozzle. Store that setting with M500.
//
#define X_ENDSTOP_SERVO_NR -1
#define Y_ENDSTOP_SERVO_NR -1
#define Z_ENDSTOP_SERVO_NR 0
#define SERVO_ENDSTOP_ANGLES {{0,0}, {0,0}, {93,0}} // X,Y,Z Axis Extend and Retract angles

// Servo deactivation
//
// With this option servos are powered only during movement, then turned off to prevent jitter.
#define DEACTIVATE_SERVOS_AFTER_MOVE

#if ENABLED(DEACTIVATE_SERVOS_AFTER_MOVE)
  // Delay (in microseconds) before turning the servo off. This depends on the servo speed.
  // 300ms is a good value but you can try less delay.
  // If the servo can't reach the requested position, increase it.
  #define SERVO_DEACTIVATION_DELAY 500
#endif

/**********************************************************************\
 * Support for a filament diameter sensor
 * Also allows adjustment of diameter at print time (vs  at slicing)
 * Single extruder only at this point (extruder 0)
 *
 * Motherboards
 * 34 - RAMPS1.4 - uses Analog input 5 on the AUX2 connector
 * 81 - Printrboard - Uses Analog input 2 on the Exp1 connector (version B,C,D,E)
 * 301 - Rambo  - uses Analog input 3
 * Note may require analog pins to be defined for different motherboards
 **********************************************************************/
// Uncomment below to enable
//#define FILAMENT_SENSOR

#define FILAMENT_SENSOR_EXTRUDER_NUM 0   //The number of the extruder that has the filament sensor (0,1,2)
#define MEASUREMENT_DELAY_CM        14   //measurement delay in cm.  This is the distance from filament sensor to middle of barrel

#define DEFAULT_NOMINAL_FILAMENT_DIA 3.00  //Enter the diameter (in mm) of the filament generally used (3.0 mm or 1.75 mm) - this is then used in the slicer software.  Used for sensor reading validation
#define MEASURED_UPPER_LIMIT         3.30  //upper limit factor used for sensor reading validation in mm
#define MEASURED_LOWER_LIMIT         1.90  //lower limit factor for sensor reading validation in mm
#define MAX_MEASUREMENT_DELAY       20     //delay buffer size in bytes (1 byte = 1cm)- limits maximum measurement delay allowable (must be larger than MEASUREMENT_DELAY_CM  and lower number saves RAM)

//defines used in the code
#define DEFAULT_MEASURED_FILAMENT_DIA  DEFAULT_NOMINAL_FILAMENT_DIA  //set measured to nominal initially

//When using an LCD, uncomment the line below to display the Filament sensor data on the last line instead of status.  Status will appear for 5 sec.
//#define FILAMENT_LCD_DISPLAY

 /**
  * "Mixing Extruder" extension.
  *   - Extends G0/G1 with mixing factors ABCDHI for up to 6 steppers.
  *   - Adds a new code, M165, to set the current mix factors.
  *   - Optional support for Repetier Host M163, M164, and virtual extruder.
  *   - Extends the stepping routines to move multiple steppers in proportion to the mix.
  *   - This implementation supports only a single extruder.
  */
// #define MIXING_EXTRUDER_FEATURE
 #ifdef MIXING_EXTRUDER_FEATURE
   #define MIXING_STEPPERS 3        // Number of steppers in your mixing extruder
   #define MIXING_VIRTUAL_TOOLS 16  // Use the Virtual Tool method with M163 and M164
 #endif
 

#include "Configuration_adv.h"
#include "thermistortables.h"

#endif //CONFIGURATION_H
