
/** 
 * WHSR.h
 * 
 * This file contains the declarations you need for using the WHSR library
 *  
 */
#ifndef WHSR_H
#define WHSR_H

#include <Arduino.h>

// _____________________________________ Library Defines _____________________________________
// Values that you can use when calling WHRS library functions

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

#define Color_Off       0b000
#define Color_On        0b111

#define Color_White     Color_On
#define Color_Black     Color_Off
#define Color_Red       0b100
#define Color_Green     0b010
#define Color_Blue      0b001
#define Color_Yellow    0b110
#define Color_Magenta   0b101
#define Color_Cyan      0b011

//
// Interrupt states of the switches
//
#define SwitchState_None    0b01 // 1
#define SwitchState_Idle    0b00 // 0
#define SwitchState_Wait    0b10 // 2
#define SwitchState_Do      0b11 // 3

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
#define RWD EngineDirBackward

#define MAX_SPEED 255

// _____________________________________ Serial Communication _____________________________________

// If we had a board with several Serial ports, we could redefine this to Serial1, Serial2, ...
#define RobotSerial Serial

// Set this to true if you want debug information from the library or if you want
// to use DebugSerial_print and DebugSerial_println in your own sketches.
// You can leave these calls in your final sketch, if you set DEBUG to false,
// they will not send anything.
#define DEBUG false

#if DEBUG == true
// Use the regular Serial port
#define DebugSerial Serial
#define DebugSerial_print(...) DebugSerial.print(__VA_ARGS__)
#define DebugSerial_println(...) DebugSerial.println(__VA_ARGS__)
#else
#define DebugSerial_print(...)
#define DebugSerial_println(...)
#endif

// Baud rate for debug comunication
#define DEBUG_BAUDRATE 9600

// Baud rate for regular communication, e.g. via USB or Bluetooth
#define REGULAR_BAUDRATE 115200

// _____________________________________ WHSR-board specific values _____________________________________

// Factor used in calculation of the switch value in order to get a binary
// representation of pressed switches
#define STANDARD_SWITCH_FACTOR 65L

// Resistor values for battery voltage devider
#define STANDARD_RESISTOR_OBEN 33000.0  // top resistor (R6)
#define STANDARD_RESISTOR_UNTEN 10000.0 // bottom resistor (R7)

//
// Internal Analog Referenz
//
#define STANDARD_INTERNAL_REFERENCE_VOLTAGE 4459L // in mV                           
                                                  // Kann gemessen/berechnet werden: 
                                                  //( Vcc / 1024 ) * Asuro::readVreference(void)

// _____________________________________ IO Pins _____________________________________

//
//	Bluetooth Komunikation
//
#define Serial_RX 0
#define Serial_TX 1

//
//	Engine, H-Bridge, Odometry
//
#define Revolution_Speed_Left 2
#define Revolution_Speed_Right 3

#define Engine_PWM_Left 9
#define Engine_PWM_Right 10

#define Engine_Dir_Left 13
#define Engine_Dir_Right 12

//
// LED-Ports
//
#define LED_Green   PD5
#define LED_Red     PD6
#define LED_Blue    PD7

//
// Sensors
//
#define BATTERY_ADC 7 // 7. ADC-Kanal

// Buttons
#define Switch_On_Interrupt 11
#define SWITCH_ADC 2        // 2. ADC-Kanal
#define SWITCH_PIN A2       // A2 = D16 = ADC[2]

// Anti Collision System
#define ACS_IR_LED_PIN PD4
#define ACS_LEFT_ADC 1 // 1. ADC-Kanal
#define ACS_RIGHT_ADC 6    // 6. ADC-Kanal

// LDR - Light Sensing
#define LDR_Left 3  // -> A7
#define LDR_Right 4 // -> A4

// Line Follower
#define LineFollower_LED 8
#define LineFollower_Right 5 // -> A1
#define LineFollower_Left 0  // -> A6

#define REFERENCE_PIN 8 // -> A14

// _____________________________________ Robot Class _____________________________________
class WHSR
{
public:
    /* ************************************************************************************
	 *
	 *	You can alter the values of these variables to suit your board
	 *
	 * ************************************************************************************ */

    long SwitchFactor = STANDARD_SWITCH_FACTOR;
    long InternalReferenceVoltage = STANDARD_INTERNAL_REFERENCE_VOLTAGE;

    double ResistorOben = STANDARD_RESISTOR_OBEN;       // R6
    double ResistorUnten = STANDARD_RESISTOR_UNTEN;     // R7

    /* ************************************************************************************
	 *
	 *	Initialisiert die Hardware des WHSR
	 *	(GPIO, ADC, PWM, Serial)
	 *
	 * ************************************************************************************ */
    void Init(void);

    /* ************************************************************************************
	 *
	 *	ADC - Batterie, Referenz, Temperatur
	 *
	 * ************************************************************************************ */

    char ADCMode = ADCMode_None;

    bool ADCWaitForBlock(void);

    void ADCInterrupt(void);

    static void ADCInterruptISR(void)
    {
        if (myRobot != NULL)
            myRobot->ADCInterrupt();
    }

    static void ADCInterruptBlockISR(void)
    {
        if (myRobot != NULL)
        {
#if defined(ARDUINO_AVR_NANO)
            if (myRobot->ADCMode == ADCMode_Block)
                ADCSRA |= (1 << ADSC);  // Start conversation
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
            if (myRobot->ADCMode == ADCMode_Block)
            {
                ; // TODO
            }
#endif
        }
    }

    /* ************************************************************************************
	 *
	 *	Sensors
	 *
	 * ************************************************************************************ */

    unsigned int readVreference(void);
    float readBattery(void);
    float readVref(void);

    void readLinesensor(int *data, unsigned char LightStatus);
    void readLinesensor(int *data);

    void readDistance(int *data, unsigned char LightStatus);
    void readDistance(int *data);

    void readAmbientLight(int *data);
    unsigned int readAmbientLight(char Side);

    /* ************************************************************************************
	 *
	 *	StatusLED
	 *
	 * ************************************************************************************ */

    void setStatusLED(unsigned char color);
    void shiftStatusLED(void);
    void setFrontLED(unsigned char status);
    void setIrLEDs(unsigned char status);

    /* ************************************************************************************
	 *
	 *	Engine
	 *
	 * ************************************************************************************ */

    void RPMLeft(void);
    static void RPMLeftISR(void)
    {
        if (myRobot != NULL)
            myRobot->RPMLeft();
    }

    void RPMRight(void);
    static void RPMRightISR(void)
    {
        if (myRobot != NULL)
            myRobot->RPMRight();
    }

    void setMotorDirectionLeft(char dir);
    void setMotorDirectionRight(char dir);
    void setMotorDirection(char left, char right);

    void setMotorSpeedLeft(int pwm, bool ChangeDirection = false);
    void setMotorSpeedRight(int pwm, bool ChangeDirection = false);
    void setMotorSpeed(int left, int right, bool ChangeDirection = false);

    void GetRPMSensorCount(int *data);
    unsigned long GetRPMSensorCount(char Side);

    /* ************************************************************************************
	 *
	 *	Switches
	 *
	 * ************************************************************************************ */

    //
    // Read Out Switches
    //
    unsigned char readSwitches(void);

    //
    //
    //
    bool switchAvailable(void);
    void switchInterruptOn(void);
    void switchInterruptOff(void);
    void switchInterrupt(void);

    static void SwitchISR(void)
    {
        if (myRobot != NULL)
            myRobot->switchInterrupt();
    }

    /* ************************************************************************************
	 *
	 *	Timer
	 *
	 * ************************************************************************************ */

    static void TimerOverflowISR(void)
    {
        if (myRobot != NULL)
            myRobot->TimerOverflow();
    }

    void TimerSet(unsigned long ms, void (*isrfunction)());
    void TimerStart();
    void TimerStop();
    void TimerOverflow();

    /* ************************************************************************************
	 *
	 *	Kompatibilität mit dem ASURO
	 *
	 * ************************************************************************************ */

    void readOdometry(int *data);
    unsigned long readOdometry(char Side);

private:
    static WHSR *myRobot;
    volatile int mySensorValues[9];

    /* ************************************************************************************
	 *
	 *	Init-Funktionen für die
	 *	einzelnen Teilbereiche
	 *
	 * ************************************************************************************ */

    void InitSerial(void);
    void InitLEDs(void);
    void InitADC(void);
    void InitEngine(void);
    void InitEnginePWM(void);

    void InitSwitches(void);
    void InitSensors(void);

    /* ************************************************************************************
	 *
	 *	Switches
	 *
	 * ************************************************************************************ */

    volatile unsigned char SwitchStateInterrupt = SwitchState_None;
    volatile unsigned char switchValue = 0;
    volatile unsigned char switchInterruptAktiv = 0;

    /* ************************************************************************************
	 *
	 *	Battery, ADC
	 *
	 * ************************************************************************************ */

    void SetADMUX(char pin);

    void ADCStartNext(void);
    void ADCStart(char Channel);
    void ADCWaitForConversion(void);

    void DoCheckADCMode(char channel);

    volatile char ADCPos = 0;
    volatile bool ADCBlockPassed = false;

    /* ************************************************************************************
	 *
	 *	Motor
	 *
	 * ************************************************************************************ */

    volatile unsigned long RPMSensorCountRight = 0;
    volatile unsigned long RPMSensorCountLeft = 0;

    /* ************************************************************************************
	 *
	 *	Timer
	 *
	 * ************************************************************************************ */

    volatile unsigned long TimerCount = 0;
    volatile unsigned int TimerOverflowCount = 0;
    volatile unsigned int TimerTcnt2 = 0;
    unsigned long TimerWaitTime = 0;

    void (*TimerISRfunction)();
};

#endif