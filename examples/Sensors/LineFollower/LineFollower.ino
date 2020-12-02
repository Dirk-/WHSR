
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
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
        robo.readLinesensor(data, LED_ON);
        Serial.print("Left: ");
        Serial.print(data[SENSOR_LEFT]);
        Serial.print("  Right: ");
        Serial.println(data[SENSOR_RIGHT]);
        delay(500);
    }

    // Read line sensors, LEDs off
    Serial.println("Linefollower; Light Off ");
    for (int i = 0; i < 5; i++)
    {
        robo.readLinesensor(data, LED_OFF);
        Serial.print("Left: ");
        Serial.print(data[SENSOR_LEFT]);
        Serial.print("  Right: ");
        Serial.println(data[SENSOR_RIGHT]);
        delay(500);
    }
}
