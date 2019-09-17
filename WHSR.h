
#ifndef WHSR_H
#define WHSR_H

#include "WHSR_Pins.h"
#include "Config.h"
#include <Arduino.h>

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

// Robot Class
class WHSR
{
private:
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

public:
	static WHSR *myRobot;
	/* ************************************************************************************
	 *
	 *	Variablen
	 *
	 * ************************************************************************************ */

	long SwitchFactor = STANDARD_SWITCH_FACTOR;
	long InternalReferenceVoltage = STANDARD_INTERNAL_REFERENCE_VOLTAGE;

	double ResistorOben = STANDARD_RESISTOR_OBEN;
	double ResistorUnten = STANDARD_RESISTOR_UNTEN;

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
	volatile int mySensorValues[9];

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
			if (myRobot->ADCMode == ADCMode_Block)
				ADCSRA |= (1 << ADSC);
		}
	}

	/* ************************************************************************************
	 *
	 *	Sensors
	 *
	 * ************************************************************************************ */

	unsigned int readReferenz(void);
	float readBattery(void);
	float readVref(void);

	void readLinesensor(int *data, unsigned char LightStatus);
	void readLinesensor(int *data);
	unsigned int readLinesensor(char Side, unsigned char LightStatus);
	unsigned int readLinesensor(char Side);

	void readACS(int *data, unsigned char LightStatus);
	void readACS(int *data);
	unsigned int readACS(char Side, unsigned char LightStatus);
	unsigned int readACS(char Side);

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
	 *	Kompatibilität
	 *
	 * ************************************************************************************ */

	void readOdometry(int *data);
	unsigned long readOdometry(char Side);
};

#endif