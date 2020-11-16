
#include "WHSR.h"

/**
 * @brief Prepares the sensors of the WHSR
 * 
 */
void WHSR::InitSensors(void)
{
	pinMode(LINE_FOLLOWER_LED_PIN, OUTPUT);
	digitalWrite(LINE_FOLLOWER_LED_PIN, LOW);
	
	pinMode(ACS_IR_LED_PIN, OUTPUT);
	digitalWrite(ACS_IR_LED_PIN, LOW);
}

/**
 * @brief Reads the raw adc value of the reference voltage
 * 
 * @return reference voltage (0..1023)
 */
unsigned int WHSR::readVreference(void)
{
	DoCheckADCMode(REFERENCE_PIN);
	return mySensorValues[REFERENCE_PIN];
}

/**
 * @brief Reads the reference voltage in Volt
 * 
 * @return reference voltage [V]
 */
float WHSR::readVref(void)
{
	float result = (InternalReferenceVoltage * (readVreference() / 1023.0)) / 1000;
	
	DebugSerial_print(" Vref: ");
	DebugSerial_print(result);
	DebugSerial_print(F("; "));
	
	return result;
}

/**
 * @brief Reads the battery voltage
 * 
 * @return battery voltage [V] 
 */
float WHSR::readBattery(void)
{
	float vref = readVref();
	
	DoCheckADCMode(BATTERY_ADC);
	float VAdc = (vref/1023) * mySensorValues[BATTERY_ADC];
	float result = VAdc * ((ResistorOben + ResistorUnten)/ResistorUnten); 
	
	DebugSerial_print(F(" B1: "));
	DebugSerial_print(mySensorValues[BATTERY_ADC]);
	DebugSerial_print(F(" B2: "));
	DebugSerial_print(VAdc);
	DebugSerial_print(F(" ->: "));
	DebugSerial_print(result);
	DebugSerial_print(F("; "));
	
	return (result);
}

/**
 * @brief Reads out the two line sensors at the bottom of the WHSR, optionally turning on the IR LED
 * 
 * @param data array with two elements, left and right sensor values (0..1023)
 * @param LightStatus LED_ON or LED_OFF
 */
void WHSR::readLinesensor(int *data, unsigned char LightStatus)
{
	if(LightStatus == LED_ON)
	{
		setFrontLED(LightStatus);
		delay(1);
	}
	
	readLinesensor(data);

	setFrontLED(LED_OFF);
}

/**
 * @brief Reads out the two line sensors at the bottom of the WHSR
 * 
 * @param data array with two elements, left and right sensor values (0..1023)
 */
void WHSR::readLinesensor(int *data)
{
	DoCheckADCMode(LINE_FOLLOWER_LEFT_ADC);
	DoCheckADCMode(LINE_FOLLOWER_RIGHT_ADC);
	
	data[SENSOR_LEFT] = mySensorValues[LINE_FOLLOWER_LEFT_ADC];
	data[SENSOR_RIGHT] = mySensorValues[LINE_FOLLOWER_RIGHT_ADC];
}

/**
 * @brief Reads out the two distance sensors in the front of the WHSR, optionally turning on the IR LEDs
 * 
 * @param data array with two elements, left and right sensor values (0..1023)
 * @param LightStatus LED_ON or LED_OFF
 */
void WHSR::readDistance(int *data, unsigned char LightStatus)
{
	if(LightStatus == LED_ON)
	{
		setIrLEDs(LightStatus);
		delay(100);
	}
	
	readDistance(data);
	
	setIrLEDs(LED_OFF);
}

/**
 * @brief Reads out the two distance sensors in the front of the WHSR
 * 
 * @param data array with two elements, left and right sensor values (0..1023)
 */
void WHSR::readDistance(int *data)
{	
	DoCheckADCMode(ACS_LEFT_ADC);
	DoCheckADCMode(ACS_RIGHT_ADC);
	
	data[SENSOR_LEFT] = mySensorValues[ACS_LEFT_ADC];
	data[SENSOR_RIGHT] = mySensorValues[ACS_RIGHT_ADC];
}

/**
 * @brief Reads out the two photo cells in the front of the WHSR
 * 
 * @param data array with two elements, left and right sensor values (0..1023)
 */
void WHSR::readAmbientLight(int *data)
{
	DoCheckADCMode(LDR_LEFT_ADC);
	DoCheckADCMode(LDR_RIGHT_ADC);
	
	data[SENSOR_LEFT] = mySensorValues[LDR_LEFT_ADC];
	data[SENSOR_RIGHT] = mySensorValues[LDR_RIGHT_ADC];
}

