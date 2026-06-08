
/*
  CheckBatteryVoltage

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

  robo.ResistorOben = 33000.0;
  robo.ResistorUnten = 10000.0;
	robo.Init();

	// Wait a moment to let the user open the serial monitor
	delay(2000);
  Serial.println("Check battery and reference voltage");
}

void loop()
{
  Serial.print("Reference voltage: ");
  Serial.print(robo.readReferenceVoltage());
  Serial.println(" V");

  Serial.print("Battery voltage:   ");
  Serial.print(robo.readBatteryVoltage());
  Serial.println(" V");

  delay(1000);
}
