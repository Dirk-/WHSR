/*
  Battery_Vref

  This example for the Westphalian University's WHSR lerning robot shows how to
  read out the battery voltage and the reference voltage of the robot.

  This example code is in the public domain. For more information, see
  https://github.com/Dirk-/WHSR
*/

#include <WHSR.h>

// We need one instance of the WHSR class to handle the robot
WHSR robo = WHSR();

void setup()
{
	// Initialize all functional modules of the robot
	robo.Init();
	Serial.println("Battery & Vref Test");
}

void loop()
{
	Serial.print("Vref: ");
	Serial.println(robo.readReferenceVoltage());

	Serial.print("Vbat: ");
	Serial.println(robo.readBatteryVoltage());

	delay(1000);	// Pause for a second
}
