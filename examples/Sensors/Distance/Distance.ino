
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
	robo.readDistance(data, LEDOn);

	Serial.println("---------- Distance sensors, IR LEDs on -------------");
	Serial.print("Left: ");
	Serial.println(data[Sensor_Left]);
	Serial.print("Right: ");
	Serial.println(data[Sensor_Right]);
	delay(1000);
	
	// Read distance sensors, IR LEDs off
	robo.readDistance(data, LEDOff); 

	Serial.println("---------- Distance sensors, IR LEDs off -------------");
	Serial.print("Left: ");
	Serial.println(data[Sensor_Left]);
	Serial.print("Right: ");
	Serial.println(data[Sensor_Right]);
	delay(1000);
}
