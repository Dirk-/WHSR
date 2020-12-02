
#include "WHSR.h"


// For copy & paste
#if defined(ARDUINO_AVR_NANO)
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
#endif



/**
 * @brief Prepares the sensors of the WHSR
 * 
 */
void WHSR::initSensors(void)
{
	pinMode(LINE_FOLLOWER_LED_DPIN, OUTPUT);
	digitalWrite(LINE_FOLLOWER_LED_DPIN, LOW);
	
	pinMode(ACS_IR_LED_DPIN, OUTPUT);
	digitalWrite(ACS_IR_LED_DPIN, LOW);

#if defined(ARDUINO_AVR_NANO)
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    // Set the analog reference to 3.3V (default)
    // analogReference(AR_VDD);
#endif
}

/**
 * @brief Reads the raw adc value of the reference voltage
 * 
 * @return reference voltage (0..1023)
 */
unsigned int WHSR::readVreference(void)
{
#if defined(ARDUINO_AVR_NANO)
    DoCheckADCMode(REFERENCE_PIN);
    return mySensorValues[REFERENCE_PIN];
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    // TODO: REFERENCE_PIN gibt es nicht beim 33 BLE
    //return analogRead(REFERENCE_PIN);
    return 0;
#endif
}

/**
 * @brief Reads the reference voltage in Volt
 * 
 * @return reference voltage [V]
 */
float WHSR::readVref(void)
{
	float result = (InternalReferenceVoltage * (readVreference() / 1023.0)) / 1000;

    DebugSerial_print(" readVreference: ");
    DebugSerial_print(readVreference());
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
#if defined(ARDUINO_AVR_NANO)
    float vref = readVref();

    DoCheckADCMode(BATTERY_ADC);
    float VAdc = (vref / 1023) * mySensorValues[BATTERY_ADC];
    float result = VAdc * ((ResistorOben + ResistorUnten) / ResistorUnten);

    DebugSerial_print(F(" B1: "));
    DebugSerial_print(mySensorValues[BATTERY_ADC]);
    DebugSerial_print(F(" B2: "));
    DebugSerial_print(VAdc);
    DebugSerial_print(F(" ->: "));
    DebugSerial_print(result);
    DebugSerial_print(F("; "));
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    DebugSerial_print(F(" AR_VDD: "));
    DebugSerial_print(analogRead(AR_VDD));
    DebugSerial_print(F(" Battery: "));
    DebugSerial_print(analogRead(BATTERY_ADC));
    DebugSerial_print(F("; "));
    float VAdc = (3.3 / 1023) * analogRead(BATTERY_ADC);
    float result = VAdc * ((ResistorOben + ResistorUnten) / ResistorUnten);
#endif

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
#if defined(ARDUINO_AVR_NANO)
    DoCheckADCMode(LINE_FOLLOWER_LEFT_ADC);
    DoCheckADCMode(LINE_FOLLOWER_RIGHT_ADC);

    data[SENSOR_LEFT] = mySensorValues[LINE_FOLLOWER_LEFT_ADC];
    data[SENSOR_RIGHT] = mySensorValues[LINE_FOLLOWER_RIGHT_ADC];
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    data[SENSOR_LEFT] = analogRead(LINE_FOLLOWER_LEFT_ADC);
    data[SENSOR_RIGHT] = analogRead(LINE_FOLLOWER_RIGHT_ADC);
#endif
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
#if defined(ARDUINO_AVR_NANO)
    DoCheckADCMode(ACS_LEFT_ADC);
    DoCheckADCMode(ACS_RIGHT_ADC);

    data[SENSOR_LEFT] = mySensorValues[ACS_LEFT_ADC];
    data[SENSOR_RIGHT] = mySensorValues[ACS_RIGHT_ADC];
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    data[SENSOR_LEFT] = analogRead(ACS_LEFT_ADC);
    data[SENSOR_RIGHT] = analogRead(ACS_RIGHT_ADC);
#endif
}

/**
 * @brief Reads out the two photo cells in the front of the WHSR
 * 
 * @param data array with two elements, left and right sensor values (0..1023)
 */
void WHSR::readAmbientLight(int *data)
{
#if defined(ARDUINO_AVR_NANO)
    DoCheckADCMode(LDR_LEFT_ADC);
    DoCheckADCMode(LDR_RIGHT_ADC);

    data[SENSOR_LEFT] = mySensorValues[LDR_LEFT_ADC];
    data[SENSOR_RIGHT] = mySensorValues[LDR_RIGHT_ADC];
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    data[SENSOR_LEFT] = analogRead(LDR_LEFT_ADC);
    data[SENSOR_RIGHT] = analogRead(LDR_RIGHT_ADC);
#endif
}

