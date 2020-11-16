
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
	robo.readDistance(data, LED_ON);

	Serial.println("---------- Distance sensors, IR LEDs on -------------");
	Serial.print("Left: ");
	Serial.println(data[SENSOR_LEFT]);
	Serial.print("Right: ");
	Serial.println(data[SENSOR_RIGHT]);
	delay(1000);
	
	// Read distance sensors, IR LEDs off
	robo.readDistance(data, LED_OFF); 

	Serial.println("---------- Distance sensors, IR LEDs off -------------");
	Serial.print("Left: ");
	Serial.println(data[SENSOR_LEFT]);
	Serial.print("Right: ");
	Serial.println(data[SENSOR_RIGHT]);
	delay(1000);
}
