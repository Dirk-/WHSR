
#include "WHSR.h"

/**
 * @brief Prepares the sensors of the WHSR
 * 
 */
void WHSR::InitSensors(void)
{
	pinMode(LineFollower_LED, OUTPUT);
	digitalWrite(LineFollower_LED, LED_Sensor_Pegel_Off);
	
	pinMode(ACS_IR_LED_PIN, OUTPUT);
	digitalWrite(ACS_IR_LED_PIN, LED_Sensor_Pegel_Off);
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
 * @param LightStatus LEDOn or LEDOff
 */
void WHSR::readLinesensor(int *data, unsigned char LightStatus)
{
	if(LightStatus == LEDOn)
	{
		setFrontLED(LightStatus);
		delay(1);
	}
	
	readLinesensor(data);

	setFrontLED(LEDOff);
}

/**
 * @brief Reads out the two line sensors at the bottom of the WHSR
 * 
 * @param data array with two elements, left and right sensor values (0..1023)
 */
void WHSR::readLinesensor(int *data)
{
	DoCheckADCMode(LineFollower_Left);
	DoCheckADCMode(LineFollower_Right);
	
	data[Sensor_Left] = mySensorValues[LineFollower_Left];
	data[Sensor_Right] = mySensorValues[LineFollower_Right];
}

/**
 * @brief Reads out the two distance sensors in the front of the WHSR, optionally turning on the IR LEDs
 * 
 * @param data array with two elements, left and right sensor values (0..1023)
 * @param LightStatus LEDOn or LEDOff
 */
void WHSR::readDistance(int *data, unsigned char LightStatus)
{
	if(LightStatus == LEDOn)
	{
		setIrLEDs(LightStatus);
		delay(100);
	}
	
	readDistance(data);
	
	setIrLEDs(LEDOff);
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
	
	data[Sensor_Left] = mySensorValues[ACS_LEFT_ADC];
	data[Sensor_Right] = mySensorValues[ACS_RIGHT_ADC];
}

/**
 * @brief Reads out the two photo cells in the front of the WHSR
 * 
 * @param data array with two elements, left and right sensor values (0..1023)
 */
void WHSR::readAmbientLight(int *data)
{
	DoCheckADCMode(LDR_Left);
	DoCheckADCMode(LDR_Right);
	
	data[Sensor_Left] = mySensorValues[LDR_Left];
	data[Sensor_Right] = mySensorValues[LDR_Right];
}

