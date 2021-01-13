/*
  Distance

  This example for the Westphalian University's WHSR lerning robot shows how to
  read out the values of the distance sensors of the robot.

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
	Serial.println("Distance Test");
}

void loop()
{
	// Array for sensor results (left, right)
	int data[2];
	
	// Read distance sensors, IR LEDs on
	Serial.println("---------- Distance sensors, IR LEDs on -------------");
    for (int i = 0; i < 5; i++)
    {
        // Communicate results
        robo.readDistance(data, LED_ON);
        Serial.print("Left: ");
        Serial.print(data[SENSOR_LEFT]);
        Serial.print("  Right: ");
        Serial.println(data[SENSOR_RIGHT]);
        delay(500);                             // Pause for a half second
    }
	
	// Read distance sensors, IR LEDs off
    Serial.println("---------- Distance sensors, IR LEDs off -------------");
    for (int i = 0; i < 5; i++)
    {
        // Communicate results
        robo.readDistance(data, LED_OFF);
        Serial.print("Left: ");
        Serial.print(data[SENSOR_LEFT]);
        Serial.print("  Right: ");
        Serial.println(data[SENSOR_RIGHT]);
        delay(500);                             // Pause for a half second
    }
}
