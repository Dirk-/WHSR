
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
	pinMode(Engine_Dir_Right, OUTPUT);
	digitalWrite(Engine_Dir_Right, LOW);
	
	pinMode(Engine_Dir_Left, OUTPUT);
	digitalWrite(Engine_Dir_Left, LOW);

	//
	//  Timer 1 PWM Init
	//
	pinMode(Engine_PWM_Left, OUTPUT);
	pinMode(Engine_PWM_Right, OUTPUT);
	InitEnginePWM();

	//
	// Init Drehzahl
	//
	
	EICRA = (0 << ISC11) | // Interrupt 0 & 1
			(1 << ISC10) | // Trigger on any logical Change
			(0 << ISC01) |
			(1 << ISC00);
	
	EIMSK = (1 << INT1) | (1 << INT0); // Enable Interrupt
	
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
	TIMSK1 &= ~(1<<OCIE1A);	// Timer Interrupt abschalten

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

/* ******************************************************************************************
 * 
 * Diese Funktionen geben den aktuellen RPM Sensorwert zurück
 * Im Anschluss werden diese beiden wieder zurückgesetzt
 * 
 * ****************************************************************************************** */


void WHSR::GetRPMSensorCount(int *data)
{
	data[Sensor_Left] = RPMSensorCountLeft;
	data[Sensor_Right] = RPMSensorCountRight;

	RPMSensorCountLeft = 0;
	RPMSensorCountRight = 0;
}

unsigned long WHSR::GetRPMSensorCount(char Side)
{
	unsigned long tmp;
	
	if(Side == Sensor_Left)
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
	if(dir == 1)
		digitalWrite(Engine_Dir_Left, EngineDirForward_Pegel);
	else if (dir == -1)
		digitalWrite(Engine_Dir_Left, EngineDirBackward_Pegel);
}

void WHSR::setMotorDirectionRight(char dir)
{
	if(dir == 1)
		digitalWrite(Engine_Dir_Right, EngineDirForward_Pegel);
	else if (dir == -1)
		digitalWrite(Engine_Dir_Right, EngineDirBackward_Pegel);
}


void WHSR::setMotorDirection (char left, char right)
{
	setMotorDirectionLeft(left);
	setMotorDirectionRight(right);
}

/* ******************************************************************************************
 * 
 * Mit diesen Funktionen kam man die Motorengeschwindigkeit einstellen
 * 
 * ****************************************************************************************** */

void WHSR::setMotorSpeedLeft(int pwm, bool ChangeDirection = false)
{
	char tmp = constrain(abs(pwm), 0, 255);
	OCR1A = tmp;
	
	if(ChangeDirection)
	{
		if(pwm < 0)
			setMotorDirectionLeft(EngineDirForward);
		else
			setMotorDirectionLeft(EngineDirBackward);
			
	}
}

void WHSR::setMotorSpeedRight(int pwm, bool ChangeDirection = false)
{
	char tmp = constrain(abs(pwm), 0, 255);
	OCR1B = tmp;
	
	if(ChangeDirection)
	{
		if(pwm < 0)
			setMotorDirectionRight(EngineDirForward);
		else
			setMotorDirectionRight(EngineDirBackward);
			
	}
}

void WHSR::setMotorSpeed (int left, int right, bool ChangeDirection = false)
{
	setMotorSpeedLeft(left, ChangeDirection);
	setMotorSpeedRight(right, ChangeDirection);
}

