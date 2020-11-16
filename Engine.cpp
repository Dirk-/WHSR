
#include "WHSR.h"

//
//	Initialisiert die beiden H-Brücken
//
void WHSR::InitEngine()
{
	DebugSerial_print(F("Init Motor"));
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
	pinMode(Engine_PWM_Left, OUTPUT);
	pinMode(Engine_PWM_Right, OUTPUT);
	InitEnginePWM();

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
#endif

    DebugSerial_println(F(" - Finsihed"));
}

//
//	Initialisiert die PWM
//		Frequenzeinstellung
//	
//	Wird auch für den ADC im Block Modus verwendet!!!
//
void WHSR::InitEnginePWM()
{
#if defined(ARDUINO_AVR_NANO)
    TIMSK1 &= ~(1 << OCIE1A); // Timer Interrupt abschalten

    TCCR1A = (1 << WGM10) |	// Timer 1 - 8bit PWM Mode

			 (1 << COM1A1) |// Clear OC1A/OC1B on Compare Match when up-counting.
			 (1 << COM1B1);	// Set OC1A/OC1B on Compare Match when down-counting.


	TCCR1B = (0 << CS12) |	// Setting   Divisor   Frequency
			 (1 << CS11) |	// 0x01          1     31372.55
			 (0 << CS10);	// 0x02          8     3921.16
							// 0x03         64     490.20   <--DEFAULT
							// 0x04        256     122.55
							// 0x05       1024     30.64

	OCR1A = 0;
	OCR1B = 0;
	
	TIMSK1 |= (1 << TOIE1);
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
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

/// Returns the rotational sensor count for both wheels
/// @param data int array which contains the two sensor values upon return
void WHSR::GetRPMSensorCount(int *data)
{
	data[SENSOR_LEFT] = RPMSensorCountLeft;
	data[SENSOR_RIGHT] = RPMSensorCountRight;

	RPMSensorCountLeft = 0;
	RPMSensorCountRight = 0;
}

/// Returns the rotational sensor count for the given wheel
/// @param Side SENSOR_LEFT or SENSOR_RIGHT
unsigned long WHSR::GetRPMSensorCount(char Side)
{
	unsigned long tmp;
	
	if(Side == SENSOR_LEFT)
	{
		tmp = RPMSensorCountLeft;
		RPMSensorCountLeft = 0;
	}
	else
	{
		tmp = RPMSensorCountRight;
		RPMSensorCountRight = 0;
	}
	
	return tmp;
}

/* ******************************************************************************************
 * 
 * Mit diesen Funkionen kann die Drehrichtung der Motoren gesetzt werden
 * 
 * ****************************************************************************************** */

void WHSR::setMotorDirectionLeft(char dir)
{
	if(dir == FWD)
		digitalWrite(MOTOR_LEFT_DIR_DPIN, LOW);
	else if (dir == BWD)
		digitalWrite(MOTOR_LEFT_DIR_DPIN, HIGH);
}

void WHSR::setMotorDirectionRight(char dir)
{
    if (dir == FWD)
        digitalWrite(MOTOR_RIGHT_DIR_DPIN, LOW);
    else if (dir == BWD)
        digitalWrite(MOTOR_RIGHT_DIR_DPIN, HIGH);
}


void WHSR::setMotorDirection (char left, char right)
{
	setMotorDirectionLeft(left);
	setMotorDirectionRight(right);
}

/* ******************************************************************************************
 * 
 * Mit diesen Funktionen kam man die Motorgeschwindigkeit einstellen
 * 
 * ****************************************************************************************** */

void WHSR::setMotorSpeedLeft(int pwm, bool ChangeDirection)
{
	char tmp = constrain(abs(pwm), 0, 255);
#if defined(ARDUINO_AVR_NANO)
    OCR1A = tmp;
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
#endif

    if(ChangeDirection)
	{
		if(pwm < 0)
			setMotorDirectionLeft(MOTOR_FORWARD);
		else
			setMotorDirectionLeft(MOTOR_BACKWARD);
			
	}
}

void WHSR::setMotorSpeedRight(int pwm, bool ChangeDirection)
{
	char tmp = constrain(abs(pwm), 0, 255);
#if defined(ARDUINO_AVR_NANO)
    OCR1B = tmp;
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
#endif

    if(ChangeDirection)
	{
		if(pwm < 0)
			setMotorDirectionRight(MOTOR_FORWARD);
		else
			setMotorDirectionRight(MOTOR_BACKWARD);
			
	}
}

void WHSR::setMotorSpeed (int left, int right, bool ChangeDirection)
{
	setMotorSpeedLeft(left, ChangeDirection);
	setMotorSpeedRight(right, ChangeDirection);
}

