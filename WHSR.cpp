#include "WHSR.h"

WHSR * WHSR::myRobot = NULL;

void WHSR::Init(void)
{
	myRobot = this;

    interrupts();   // Enable interrupts (probably unneccessary)

    // Init the WHSR parts
	initSerial();
	initADC();
	initSwitches();
	initLEDs();
	initSensors();
	initEngine();
}


// Attach the default Interrupt Service Routines to the interrupts
#if defined(ARDUINO_AVR_NANO)
ISR(ADC_vect) { WHSR::ADCInterruptISR(); }
ISR(TIMER1_OVF_vect) { WHSR::ADCInterruptBlockISR(); }
ISR(INT0_vect) { WHSR::RPMLeftISR(); }
ISR(INT1_vect) { WHSR::RPMRightISR(); }
ISR(TIMER2_OVF_vect) { WHSR::TimerOverflowISR(); }
ISR(PCINT1_vect) { WHSR::SwitchISR(); }
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
#endif

// ----------------------------------------- Serial Port ------------------------------------------

//
//	Initialisiert die Serielle Schnittstelle
//	RobotSerial - Bluetooth Serial
//	DebugSerial - Debug Serial
//
void WHSR::initSerial()
{
    RobotSerial.begin(REGULAR_BAUDRATE);

#if DebugSerial != RobotSerial
    DebugSerial.begin(DEBUG_BAUDRATE);
#endif
}

// --------------------------------------------- LEDs ----------------------------------------------


//
//	Diese Funktion initialisiert die RGB-LED
//
void WHSR::initLEDs(void)
{
    pinMode(STATUSLED_BLUE_DPIN, OUTPUT);
    digitalWrite(STATUSLED_BLUE_DPIN, LOW);

    pinMode(STATUSLED_GREEN_DPIN, OUTPUT);
    digitalWrite(STATUSLED_GREEN_DPIN, LOW);

    pinMode(STATUSLED_RED_DPIN, OUTPUT);
    digitalWrite(STATUSLED_RED_DPIN, LOW);
}

//
//	MitHilfe dieser Funkion kan die Status-LED auf eine Farbe gesetzt werden
//
void WHSR::setStatusLED(unsigned char color)
{
    digitalWrite(STATUSLED_RED_DPIN, (color & COLOR_RED) > 0 ? HIGH : LOW);

    digitalWrite(STATUSLED_GREEN_DPIN, (color & COLOR_GREEN) > 0 ? HIGH : LOW);

    digitalWrite(STATUSLED_BLUE_DPIN, (color & COLOR_BLUE) > 0 ? HIGH : LOW);

    // Pin Map LED D5 - D7... PD5 - PD7
    //Write Port Alternative Moeglichkeit - schnellere Operation
    //PORTD = PORTD | color << 5; // B10101000;
}

//
//	Diese Funktion setzt die Status-LED auf die verschiedenen Farben
//	Feste Reihenfolge
//
void WHSR::shiftStatusLED(void)
{
    static unsigned char pos = 0;
    setStatusLED(pos++);
}

//
//	Diese Funktion schaltet die Front-LED (LED fuer den Linienfolger) ein oder aus
//
void WHSR::setFrontLED(unsigned char status)
{
    if (status == LED_ON)
        digitalWrite(LINE_FOLLOWER_LED_DPIN, HIGH);
    else
        digitalWrite(LINE_FOLLOWER_LED_DPIN, LOW);
}

//
//	Diese Funktion schaltet die ACS-LEDs (LED fuer die Fruehwarnung) ein oder aus
//
void WHSR::setIrLEDs(unsigned char status)
{
    if (status == LED_ON)
        digitalWrite(ACS_IR_LED_DPIN, HIGH);
    else
        digitalWrite(ACS_IR_LED_DPIN, LOW);
}


// ------------------------------------------------- Motors -------------------------------------------------


volatile unsigned long RPMSensorCountRight = 0;
volatile unsigned long RPMSensorCountLeft = 0;

//
//	Initialisiert die beiden H-Brücken
//
void WHSR::initEngine()
{
    //
    // Motor Dir Init
    //
    pinMode(MOTOR_RIGHT_DIR_DPIN, OUTPUT);
    digitalWrite(MOTOR_RIGHT_DIR_DPIN, LOW);

    pinMode(MOTOR_LEFT_DIR_DPIN, OUTPUT);
    digitalWrite(MOTOR_LEFT_DIR_DPIN, LOW);

    //
    //  Timer 1 PWM Init
    //
    pinMode(MOTOR_LEFT_PWM_DPIN, OUTPUT);
    pinMode(MOTOR_RIGHT_PWM_DPIN, OUTPUT);
    initEnginePWM();

    //
    // Init Drehzahl
    //

#if defined(ARDUINO_AVR_NANO)
    EICRA = (0 << ISC11) | // Interrupt 0 & 1
            (1 << ISC10) | // Trigger on any logical Change
            (0 << ISC01) |
            (1 << ISC00);

    EIMSK = (1 << INT1) | (1 << INT0); // Enable Interrupt
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    // Interrupts an die Odometrie-Pins hängen
    attachInterrupt(digitalPinToInterrupt(ROT_TICKS_LEFT_DPIN), WHSR::RPMLeftISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROT_TICKS_RIGHT_DPIN), WHSR::RPMRightISR, CHANGE);
#endif
}

//
//	Initialisiert die PWM
//		Frequenzeinstellung
//
//	Wird auch für den ADC im Block Modus verwendet!!!
//
void WHSR::initEnginePWM()
{
#if defined(ARDUINO_AVR_NANO)
    TIMSK1 &= ~(1 << OCIE1A); // Timer Interrupt abschalten

    TCCR1A = (1 << WGM10) | // Timer 1 - 8bit PWM Mode

             (1 << COM1A1) | // Clear OC1A/OC1B on Compare Match when up-counting.
             (1 << COM1B1);  // Set OC1A/OC1B on Compare Match when down-counting.

    TCCR1B = (0 << CS12) | // Setting   Divisor   Frequency
             (1 << CS11) | // 0x01          1     31372.55
             (0 << CS10);  // 0x02          8     3921.16
                           // 0x03         64     490.20   <--DEFAULT
                           // 0x04        256     122.55
                           // 0x05       1024     30.64

    OCR1A = 0;
    OCR1B = 0;

    TIMSK1 |= (1 << TOIE1);
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    // Nichts nötig
#endif
}

//
//	Funktion für die Abhandlung der ISR
//
void WHSR::RPMLeft(void)
{
    ++RPMSensorCountLeft;
}

//
//	Funktion für die Abhandlung der ISR
//
void WHSR::RPMRight(void)
{
    ++RPMSensorCountRight;
}

/// Returns the rotational sensor count for both wheels.
/// @param data int array which contains the two sensor values upon return
void WHSR::getRPMSensorCount(unsigned long *data)
{
    data[SENSOR_LEFT] = RPMSensorCountLeft;
    data[SENSOR_RIGHT] = RPMSensorCountRight;
}

/// Set the direction of rotation of the motors
/// @param dirLeft FWD or BWD
/// @param dirRight FWD or BWD
void WHSR::setMotorDirection(char dirLeft, char dirRight)
{
    if (dirLeft == FWD)
        digitalWrite(MOTOR_LEFT_DIR_DPIN, LOW);
    else
        digitalWrite(MOTOR_LEFT_DIR_DPIN, HIGH);

    if (dirRight == FWD)
        digitalWrite(MOTOR_RIGHT_DIR_DPIN, LOW);
    else
        digitalWrite(MOTOR_RIGHT_DIR_DPIN, HIGH);
}

void WHSR::setMotorSpeed(int speedLeft, int speedRight)
{
    char tmp = constrain(abs(speedLeft), 0, 255);
#if defined(ARDUINO_AVR_NANO)
    //OCR1A = tmp;
    analogWrite(MOTOR_LEFT_PWM_DPIN, tmp);
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    analogWrite(MOTOR_LEFT_PWM_DPIN, tmp);
#endif

    tmp = constrain(abs(speedRight), 0, 255);
#if defined(ARDUINO_AVR_NANO)
    //OCR1B = tmp;
    analogWrite(MOTOR_RIGHT_PWM_DPIN, tmp);
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    analogWrite(MOTOR_RIGHT_PWM_DPIN, tmp);
#endif
}

// ------------------------------------------------- Sensors -------------------------------------------------

/**
 * @brief Prepares the sensors of the WHSR
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
    DebugSerial_print("; ");

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

    DebugSerial_print(" B1: ");
    DebugSerial_print(mySensorValues[BATTERY_ADC]);
    DebugSerial_print(" B2: ");
    DebugSerial_print(VAdc);
    DebugSerial_print(" ->: ");
    DebugSerial_print(result);
    DebugSerial_print("; ");
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    DebugSerial_print("AR_VDD: ");
    DebugSerial_println(AR_VDD);
    DebugSerial_print(" BATTERY_ADC: ");
    DebugSerial_println(analogRead(BATTERY_ADC));

  // Voltage calulation with measurements:
  // 4.69 V => BATTERY_ADC = 978
  // 8.12 V => BATTERY_ADC = 782
  float result = -0.0175 * analogRead(BATTERY_ADC) + 21.805;
  DebugSerial_print(" Result: ");
  DebugSerial_println(result);
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
    if (LightStatus == LED_ON)
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
    if (LightStatus == LED_ON)
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
