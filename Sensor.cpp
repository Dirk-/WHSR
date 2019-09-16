
#include "Robot.h"

void Robot::InitSensors(void)
{
	pinMode(LineFollower_LED, OUTPUT);
	digitalWrite(LineFollower_LED, LED_Sensor_Pegel_Off);
	
	pinMode(ACS_IrLed, OUTPUT);
	digitalWrite(ACS_IrLed, LED_Sensor_Pegel_Off);
}

/* ******************************************************************************************
 * 
 * Diese Funktionen beschäftigen sich mit dem Einlesen
 * der Batteriespannung und der Referenzspannung
 * 
 * ****************************************************************************************** */

unsigned int Robot::readReferenz(void)
{
	DoCheckADCMode(Referenz);
	return mySensorValues[Referenz];
}

float Robot::readVref(void)
{
	float result = (InternalReferenceVoltage * (1023.0 / readReferenz())) / 1000;
	
	DBSerial_print(" Vref: ");
	DBSerial_print(result);
	DBSerial_print(F("; "));
	
	return result;
}

float Robot::readBattery(void)
{
	float vref = readVref();
	
	DoCheckADCMode(Batterie);
	float VAdc = (vref/1023) * mySensorValues[Batterie];
	float result = VAdc * ((ResistorOben + ResistorUnten)/ResistorUnten); 
	
	DBSerial_print(F(" B1: "));
	DBSerial_print(mySensorValues[Batterie]);
	DBSerial_print(F(" B2: "));
	DBSerial_print(VAdc);
	DBSerial_print(F(" ->: "));
	DBSerial_print(result);
	DBSerial_print(F("; "));
	
	return (result);
}

/* ******************************************************************************************
 * 
 * Diese Funktionen lesen den Lienienfolger aus
 * 
 * ****************************************************************************************** */

void Robot::readLinesensor(int *data, unsigned char LightStatus)
{
	if(LightStatus == LEDOn)
	{
		setFrontLED(LightStatus);
		delay(1);
	}
	
	readLinesensor(data);

	setFrontLED(LEDOff);
}
void Robot::readLinesensor(int *data)
{
	DoCheckADCMode(LineFollower_Left);
	DoCheckADCMode(LineFollower_Right);
	
	data[Sensor_Left] = mySensorValues[LineFollower_Left];
	data[Sensor_Right] = mySensorValues[LineFollower_Right];
}

unsigned int Robot::readLinesensor(char Side, unsigned char LightStatus)
{
	int data[2];
	readLinesensor(*data, LightStatus);
		
	if(Side == Sensor_Left)
		return mySensorValues[LineFollower_Left];
	else
		return mySensorValues[LineFollower_Right];
}

unsigned int Robot::readLinesensor(char Side)
{
	int data[2];
	readLinesensor(*data);
		
	if(Side == Sensor_Left)
		return mySensorValues[LineFollower_Left];
	else
		return mySensorValues[LineFollower_Right];
}

/* ******************************************************************************************
 * 
 * Diese Funktionen lesen den ACS aus (Kolisionsfrühwarnung)
 * 
 * ****************************************************************************************** */

void Robot::readACS(int *data, unsigned char LightStatus)
{
	if(LightStatus == LEDOn)
	{
		setIRLeds(LightStatus);
		delay(100);
	}
	
	readACS(data);
	
	setIRLeds(LEDOff);
}

void Robot::readACS(int *data)
{	
	DoCheckADCMode(ACS_Left);
	DoCheckADCMode(ACS_Right);
	
	data[Sensor_Left] = mySensorValues[ACS_Left];
	data[Sensor_Right] = mySensorValues[ACS_Right];
}


unsigned int Robot::readACS(char Side, unsigned char LightStatus)
{
	int data[2];
	readACS(*data, LightStatus);
		
	if(Side == Sensor_Left)
		return mySensorValues[ACS_Left];
	else
		return mySensorValues[ACS_Right];
}

unsigned int Robot::readACS(char Side)
{	
	int data[2];
	readACS(*data);
		
	if(Side == Sensor_Left)
		return mySensorValues[ACS_Left];
	else
		return mySensorValues[ACS_Right];
}


/* ******************************************************************************************
 * 
 * Diese Funktionen lesen die beiden Lichtsensoren aus
 * 
 * ****************************************************************************************** */

void Robot::readLDR(int *data)
{
	DoCheckADCMode(LDR_Left);
	DoCheckADCMode(LDR_Right);
	
	data[Sensor_Left] = mySensorValues[LDR_Left];
	data[Sensor_Right] = mySensorValues[LDR_Right];
}

unsigned int Robot::readLDR(char Side)
{
	if(Side == Sensor_Left)
	{
		DoCheckADCMode(LDR_Left);
		return mySensorValues[LDR_Left];
	}
	else
	{
		DoCheckADCMode(LDR_Right);
		return mySensorValues[LDR_Right];
	}
}
