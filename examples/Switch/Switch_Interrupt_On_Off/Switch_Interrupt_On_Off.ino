/*
  Switch_Interrupt_On_Off

  This example for the Westphalian University's WHSR lerning robot shows that 
  the switch pin interrupt is turned off when a switch is pressed. Afterwards 
  the switch pin interrupt is turned on again.

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

	// Turn on the switch pin interrupt, use internal callback function
	// Trigger on a falling edge, when a switch is pressed
	robo.switchInterruptOn(NULL, FALLING);	
	
	// Wait a moment to let the user open the serial monitor
	delay(2000);
	Serial.println("Switch Interrupt Test - Press a switch");
}

void loop()
{
	if(robo.switchAvailable())
	{
		Serial.println(robo.readSwitches(), BIN);
		
		// Pause interrupts for six seconds
		robo.switchInterruptOff();
		Serial.println("Interrupt - Deactivated for 6 seconds");
		delay(6000);
										
		// Turn on the switch pin interrupt again
		robo.switchInterruptOn(NULL, FALLING);	
		Serial.println("Interrupt - Activated");
	}
}