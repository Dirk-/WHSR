
#include <Robot.h>

Robot robo = Robot();

void setup()
{
	robo.Init();
	Serial.println(F("Linefollower Test"));
}

void loop()
{
	int data[2];
	
	// Get Sensor Werte, Light On
	robo.readLinesensor(data, LEDOn);
	Serial.print(F("Linefollower; Light On "));
	Serial.print(F("Left: "));
	Serial.println(data[Sensor_Left]);
	Serial.print(F("Right: "));
	Serial.println(data[Sensor_Right]);
	delay(1000);
	
	// Get Sensor Werte, Light Off
	//robo.readLinesensor(data, LEDOff); // Je nachdem ob die IRLed an
	robo.readLinesensor(data);			 // ist oder nicht
	Serial.print(F("Linefollower; Light Off "));
	Serial.print(F("Left: "));
	Serial.println(data[Sensor_Left]);
	Serial.print(F("Right: "));
	Serial.println(data[Sensor_Right]);
	delay(1000);
	
	/*
	// Get Sensor Werte, Light On
	Serial.print(F("Linefollower Light On: "));
	Serial.print(F("Left: "));
	Serial.println(robo.readLinesensor(Sensor_Left, LEDOn));
	Serial.print(F("Right: "));
	Serial.println(robo.readLinesensor(Sensor_Right, LEDOn));
	delay(1000);
	
	// Get Sensor Werte, Light Off
	Serial.print(F("Linefollower Light On: "));
	Serial.print(F("Left: "));
	//Serial.println(robo.readLinesensor(Sensor_Left, LEDOff)); // Siehe oben
	Serial.println(robo.readLinesensor(Sensor_Left));
	Serial.print(F("Right: "));
	//Serial.println(robo.readLinesensor(Sensor_Right, LEDOff)); // Siehe oben
	Serial.println(robo.readLinesensor(Sensor_Right));
	delay(1000);
	
	*/
}
