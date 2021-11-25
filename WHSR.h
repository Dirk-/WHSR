
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
// Values you can use when calling WHRS library functions

//
// ADC
//
#define MAX_ADC_CHANNELS 8
#define ADC_MODE_NONE 0
#define ADC_MODE_BLOCK 1
#define SWITCH_ADC 2 // 2. ADC-Kanal für Switches

//
// LED Colors
//
#define COLOR_OFF       0b000
#define COLOR_ON        0b111

#define COLOR_WHITE     COLOR_ON
#define COLOR_BLACK     COLOR_OFF
#define COLOR_RED       0b100
#define COLOR_GREEN     0b010
#define COLOR_BLUE      0b001
#define COLOR_YELLOW    0b110
#define COLOR_MAGENTA   0b101
#define COLOR_CYAN      0b011

//
// Interrupt states of the collision switches
//
#define SWITCH_INTERRUPT_NONE    0b01 // 1, do not use interrupt, use polling
#define SWITCH_INTERRUPT_IDLE    0b00 // 0, nothing to do
#define SWITCH_INTERRUPT_WAIT    0b10 // 2, wait for ADC conversion to finish
#define SWITCH_INTERRUPT_DO      0b11 // 3, start ADC conversion

//
// Sensor constants
//
#define SENSOR_LEFT     0   // Index for left sensor value in data array
#define SENSOR_RIGHT    1   // Index for right sensor value in data array
#define LED_ON HIGH
#define LED_OFF LOW

//
// Motor
//
#define MOTOR_FORWARD 1
#define FWD MOTOR_FORWARD

#define MOTOR_BACKWARD -1
#define BWD MOTOR_BACKWARD
#define RWD MOTOR_BACKWARD

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
#define REGULAR_BAUDRATE 9600 // 115200

// _____________________________________ WHSR-board specific values _____________________________________

// Factor used in calculation of the switch value in order to get a binary
// representation of pressed switches
#define STANDARD_SWITCH_FACTOR 65L

// Resistor values for battery voltage devider
#define STANDARD_RESISTOR_TOP 33000.0  // top resistor (R6)
#define STANDARD_RESISTOR_BOTTOM 10000.0 // bottom resistor (R7)

//
// Internal Analog Referenz
//
#define STANDARD_INTERNAL_REFERENCE_VOLTAGE 4459L // in mV                           
                                                  // Kann gemessen/berechnet werden: 
                                                  //( Vcc / 1024 ) * Asuro::readVreference(void)


// _____________________________________ IO Pins _____________________________________

/*
Werte der Arduino-Konstanten:
A2: 16
A3: 17
A7: 21
D8/PB0: 8
D12/PB4: 12
D4/PD4: 4
D5/PD5: 5
D6/PD6: 6
D7/PD7: 7

"Pin x" im Kommentar gibt Pin-Nummer des Arduino-Boards
*/

//
//	Bluetooth Komunikation
//
#define SERIAL_RX_DPIN 0    // Pin 2
#define SERIAL_TX_DPIN 1    // Pin 1

//
//	Engine, H-Bridge, Odometry
//
#define ROT_TICKS_LEFT_DPIN 2 // Pin 5
#define ROT_TICKS_RIGHT_DPIN 3 // Pin 6

#define MOTOR_LEFT_PWM_DPIN 10 // Pin 13
#define MOTOR_RIGHT_PWM_DPIN 9 // Pin 12

#define MOTOR_LEFT_DIR_DPIN 13  // Pin 16
#define MOTOR_RIGHT_DIR_DPIN 12 // Pin 15

//
// LED-Ports
//
#define STATUSLED_GREEN_DPIN   5  // Pin 8
#define STATUSLED_RED_DPIN     6  // Pin 9
#define STATUSLED_BLUE_DPIN    7  // Pin 10

//
// Sensors
//
#define BATTERY_ADC 7 // 7. ADC-Kanal

// Anti Collision System
#define ACS_IR_LED_DPIN 4   // Pin 7
#define ACS_LEFT_ADC 1      // 1. ADC-Kanal
#define ACS_RIGHT_ADC 6     // 6. ADC-Kanal

// LDR - Light Sensing
#define LDR_LEFT_ADC 3  // 3. ADC-Kanal
#define LDR_RIGHT_ADC 4 // 4. ADC-Kanal

// Line Follower
#define LINE_FOLLOWER_LED_DPIN 8 // Pin 11
#define LINE_FOLLOWER_RIGHT_ADC 5 // 5. ADC-Kanal
#define LINE_FOLLOWER_LEFT_ADC 0  // 0. ADC-Kanal

#define REFERENCE_PIN 8 // -> A14????

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

    double ResistorOben = STANDARD_RESISTOR_TOP;       // R6
    double ResistorUnten = STANDARD_RESISTOR_BOTTOM;     // R7

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

    char ADCMode = ADC_MODE_NONE;

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
            if (myRobot->ADCMode == ADC_MODE_BLOCK)
                ADCSRA |= (1 << ADSC);  // Start conversation
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
            if (myRobot->ADCMode == ADC_MODE_BLOCK)
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

    void setMotorDirection(char dirLeft, char dirRight);

    void setMotorSpeed(int speedLeft, int speedRight);

    void getRPMSensorCount(unsigned long *data);

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


private:
    static WHSR *myRobot;
    volatile int mySensorValues[9];

    /* ************************************************************************************
	 *
	 *	Init-Funktionen für die
	 *	einzelnen Teilbereiche
	 *
	 * ************************************************************************************ */

    void initSerial(void);
    void initLEDs(void);
    void initADC(void);
    void initEngine(void);
    void initEnginePWM(void);

    void initSwitches(void);
    void initSensors(void);

    /* ************************************************************************************
	 *
	 *	Switches
	 *
	 * ************************************************************************************ */

    volatile unsigned char SWITCH_INTERRUPT_STATE = SWITCH_INTERRUPT_NONE;
    volatile unsigned char switchValue = 0;
    
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

    volatile byte ADCPos = 0;
    volatile bool ADCBlockPassed = false;

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
