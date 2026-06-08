/*
  Switch_Test.ino - Example for the WHSR library

  This example for the Westphalian University's WHSR lerning robot shows how to 
  read out the value of the switch of the robot. It is also used to check which 
  switch has been pressed. 

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

	// Wait a moment to let the user open the serial monitor
	delay(2000);
  Serial.println("Switch Test - Press a switch");
}

void loop()
{
  // Get joint value of all switches
  int switchvalue = robo.readSwitches();

  // Print switch input value in binary form, should show a 1 for each pressed switch
  Serial.print(switchvalue, BIN);

  // Print switch input value in decimal form
  Serial.print(" (");
  Serial.print(switchvalue);
  Serial.println(")");

  // Pause for 200 milliseconds
  delay(200);
}
