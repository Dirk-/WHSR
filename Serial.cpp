
#include "Robot.h"

//
//	Initialisiert die Serielle Schnittstelle
//	RobotSerial - Bluetooth Serial
//	DBSerial - Debug Serial
//
void Robot::InitSerial()
{
	RobotSerial.begin(BLUETOOTH_BAUDRATE);
	
	#if DBSerial != RobotSerial
		DBSerial.begin(BaudRate);
	#endif
	
	DBSerial_print(F("Init Kommunikation"));
	DBSerial_println(F(" - Finsihed"));
}

