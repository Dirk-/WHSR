
#include "WHSR.h"

//
//	Initialisiert die Serielle Schnittstelle
//	RobotSerial - Bluetooth Serial
//	DebugSerial - Debug Serial
//
void WHSR::InitSerial()
{
	RobotSerial.begin(REGULAR_BAUDRATE);
	
	#if DebugSerial != RobotSerial
		DebugSerial.begin(DEBUG_BAUDRATE);
	#endif
	
	DebugSerial_print(F("Init Kommunikation"));
	DebugSerial_println(F(" - Finished"));
}

