/*
  Switch_Interrupt

  This example for the Westphalian University's WHSR lerning robot shows how to 
  read out the value of the switch of the robot. It is also used to check which 
  switch has been pressed. It does not work properly on the Arduino Nano 33 BLE. 

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
	Serial.println("Switch Test");
}

void loop()
{
  // Communicate value
  int switchvalue = robo.readSwitches();

  //Print switch input value in binary form, should show a 1 for each pressed switch
  // This is not compatible with the Arduino Nano 33 BLE.
  Serial.print(switchvalue, BIN);
  Serial.print(" (");
  Serial.print(switchvalue);
  Serial.println(")");
  
  delay(100);                            // Pause for 100 milliseconds
}
