
/** 
 * config.h
 * 
 * This file contains defines you can change in your code as well as internal defines
 *  
 */
#ifndef WHSRCONFIG_H
#define WHSRCONFIG_H

// Baud rate for debug comunication
#define DEBUG_BAUDRATE 9600	

// Baud rate for regular communication, e.g. via USB or Bluetooth
#define REGULAR_BAUDRATE 115200 		

// Factor used in calculation of the switch value in order to get a binary 
// representation of pressed switches
#define STANDARD_SWITCH_FACTOR 65L

// Resistor values for battery voltage devider
#define STANDARD_RESISTOR_OBEN 33000.0  // top resistor
#define STANDARD_RESISTOR_UNTEN 10000.0 // bottom resistor

//
// Internal Analog Referenz
//
#define STANDARD_INTERNAL_REFERENCE_VOLTAGE 1069L // in mV
												  // Kann gemessen/berechnet werden:
												  //( Vcc / 1024 ) * Asuro::readVreference(void)


/* ####################################################################################
 *
 * Don't change any values from here on
 *
 * #################################################################################### */

//
// ADC
//
#define MaxADCChannels 9
#define ADCMode_None 0
#define ADCMode_Block 1

//
// LED States
//
#define LED_Status_Pegel_On HIGH
#define LED_Status_Pegel_Off LOW

#define Color_Off 0b000
#define Color_On 0b111

#define Color_White Color_On
#define Color_Black Color_Off
#define Color_Red 0b100
#define Color_Green 0b010
#define Color_Blue 0b001
#define Color_Yellow 0b110
#define Color_Magenta 0b101
#define Color_Cyan 0b011

//
// Interrupt states of the switches
//
#define SwitchState_None 0b01 // 1
#define SwitchState_Idle 0b00 // 0
#define SwitchState_Wait 0b10 // 2
#define SwitchState_Do 0b11   // 3

//
// Sensor
//
#define LED_Sensor_Pegel_On HIGH
#define LED_Sensor_Pegel_Off LOW
#define Sensor_Left 0
#define Sensor_Right 1
#define LEDOn LED_Sensor_Pegel_On
#define LEDOff LED_Sensor_Pegel_Off

//
// Directions
//
#define EngineDirForward_Pegel LOW
#define EngineDirBackward_Pegel HIGH

#define EngineDirForward 1
#define FWD EngineDirForward

#define EngineDirBackward -1
#define BWD EngineDirBackward
#define EngineDirReward EngineDirBackward
#define RWD EngineDirBackward

#define MAX_SPEED 255

#endif