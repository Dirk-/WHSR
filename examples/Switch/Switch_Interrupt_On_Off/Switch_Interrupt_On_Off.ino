/*
  Switch_Interrupt_On_Off

  This example for the Westphalian University's WHSR lerning robot shows that 
  the PinChange interrupt is switched off when a switch is pressed. Afterwards 
  the Pinchange Intrrupt is switched on again. It does not work properly on the 
  Arduino Nano 33 BLE. 

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
	robo.switchInterruptOn();						   		// Turn On the PinChange Interrupt
	Serial.println("Switch Interrupt Test - On _ Off");
}

void loop()
{
	bool wait = false;
	if(robo.switchAvailable())
	{
		Serial.println(robo.readSwitches(), BIN);
		wait = true;
		
		robo.switchInterruptOff();							// Turn Off the PinChange Interrupt
		Serial.println("Interrupt - Turn Off");
	}
	
	if(wait)
	{
		delay(6000);										// Pause for six seconds 
		robo.switchInterruptOn();							// Turn On the PinChange Interrupt	
		Serial.println("Interrupt - Turn On");
	}
}