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

/// Set the motor speed
/// @param speedLeft 0..255
/// @param speedRight 0..255
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
