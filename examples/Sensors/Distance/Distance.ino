
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
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
        robo.readDistance(data, LED_ON);
        Serial.print("Left: ");
        Serial.print(data[SENSOR_LEFT]);
        Serial.print("  Right: ");
        Serial.println(data[SENSOR_RIGHT]);
        delay(500);
    }
	
	// Read distance sensors, IR LEDs off
    Serial.println("---------- Distance sensors, IR LEDs off -------------");
    for (int i = 0; i < 5; i++)
    {
        robo.readDistance(data, LED_OFF);
        Serial.print("Left: ");
        Serial.print(data[SENSOR_LEFT]);
        Serial.print("  Right: ");
        Serial.println(data[SENSOR_RIGHT]);
        delay(500);
    }
}
