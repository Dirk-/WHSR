
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	robo.switchInterruptOn();
	Serial.println("Switch Interrupt Test");
}

void loop()
{
	// Simulate busy behaviour (but interrupt will be registered)
	delay(2000);

	if (robo.switchAvailable())
	{	
		Serial.print("Switches pressed: ");
		// Print switch input value in binary form, should show a 1 for each pressed switch 
		Serial.println(robo.readSwitches(), BIN);
	} else
	{
		Serial.println("Nothing detected.");
	}
	

}