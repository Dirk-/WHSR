/*
  LineFollower

  This example for the Westphalian University's WHSR lerning robot shows how to
  read out the values of the line sensors of the robot.

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
	Serial.println("Linefollower Test");
}

void loop()
{
	// Array for sensor results (left, right)
	int data[2];
	
	// Read line sensors, LEDs on
    Serial.println("Linefollower; Light On ");
    for (int i = 0; i < 5; i++)
    {
        // Communicate results
        robo.readLinesensor(data, LED_ON);
        Serial.print("Left: ");
        Serial.print(data[SENSOR_LEFT]);
        Serial.print("  Right: ");
        Serial.println(data[SENSOR_RIGHT]);
        delay(500);                             // Pause for a half second
    }

    // Read line sensors, LEDs off
    Serial.println("Linefollower; Light Off ");
    for (int i = 0; i < 5; i++)
    {
        // Communicate results
        robo.readLinesensor(data, LED_OFF);
        Serial.print("Left: ");
        Serial.print(data[SENSOR_LEFT]);
        Serial.print("  Right: ");
        Serial.println(data[SENSOR_RIGHT]);
        delay(500);                             // Pause for a half second
    }
}
