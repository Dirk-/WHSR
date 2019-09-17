
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
	robo.readLinesensor(data, LEDOn);
	Serial.print("Linefollower; Light On ");
	Serial.print("Left: ");
	Serial.println(data[Sensor_Left]);
	Serial.print("Right: ");
	Serial.println(data[Sensor_Right]);
	delay(1000);
	
	// Read line sensors, LEDs off
	robo.readLinesensor(data, LEDOff);
	Serial.print("Linefollower; Light Off ");
	Serial.print("Left: ");
	Serial.println(data[Sensor_Left]);
	Serial.print("Right: ");
	Serial.println(data[Sensor_Right]);
	delay(1000);
}
