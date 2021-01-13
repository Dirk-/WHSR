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
#if defined(ARDUINO_AVR_NANO)
	Serial.print("Vref: ");
	Serial.println(robo.readVref());				// Read reference voltage
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
	Serial.println("Vref nicht definiert");			// Not defined
#endif
	Serial.print("Vbat: ");
	Serial.println(robo.readBattery());				// Read battery voltage
	delay(1000);									// Pause for a second
}
