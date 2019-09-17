
#include "WHSR.h"

//
//	Initialisiert die Serielle Schnittstelle
//	RobotSerial - Bluetooth Serial
//	DBSerial - Debug Serial
//
void WHSR::InitSerial()
{
	RobotSerial.begin(BLUETOOTH_BAUDRATE);
	
	#if DBSerial != RobotSerial
		DBSerial.begin(USB_BAUDRATE);
	#endif
	
	DBSerial_print(F("Init Kommunikation"));
	DBSerial_println(F(" - Finsihed"));
}

