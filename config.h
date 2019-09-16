
#ifndef WHSRCONFIG_H
	#define WHSRCONFIG_H

	//
	// Serial 
	//
	#define BAUDRATE 115200				// BaudRate für die Debug Komunikation
	#define BLUETOOTH_BAUDRATE 115200	// BaudRate für das Bluetooth Modul
										// Muss mit dem eingesteltem übereinpassen
		
	//
	// Switch 
	//
	#define STANDARD_SWITCH_FACTOR 65L
	
	//
	//	Batterie
	//
	#define STANDARD_RESISTOR_OBEN  33000.0	// Verbaute Widerstände
	#define STANDARD_RESISTOR_UNTEN 10000.0	// um die Batterie spannung herunterzuteilen
	
	//
	// Internal Analog Referenz
	//
	#define STANDARD_INTERNAL_REFERENCE_VOLTAGE 1069L 	// in mV
											// Kann gemessen/berechnet werden:
											//( Vcc / 1024 ) * Asuro::readReferenz(void)
	
	
	/* ####################################################################################
	 *
	 * Ab hier nix mehr Ändern
	 *
	 * #################################################################################### */
	
	//
	// ADC
	//
	#define MaxADCChannels 9
	#define ADCMode_None 0
	#define ADCMode_Block 1
	
	//
	// LED States
	//
	#define LED_Status_Pegel_On  HIGH
	#define LED_Status_Pegel_Off LOW
	
	#define Color_Off		0b000
	#define Color_On		0b111
	
	#define Color_White		Color_On
	#define Color_Black		Color_Off
	#define Color_Red		0b100
	#define Color_Green		0b010
	#define Color_Blue		0b001
	#define Color_Yellow	0b110
	#define Color_Magenta	0b101
	#define Color_Cyan		0b011
	
	//
	// Switch
	//
	#define SwitchState_None 0b01 // 0x1
	#define SwitchState_Idle 0x00 // 0x0
	#define SwitchState_Wait 0x10 // 0x2
	#define SwitchState_Do   0x11 // 0x3
	
	//
	// Sensor
	//
	#define LED_Sensor_Pegel_On  HIGH
	#define LED_Sensor_Pegel_Off LOW
	#define Sensor_Left 0
	#define Sensor_Right 1
	#define LEDOn LED_Sensor_Pegel_On
	#define LEDOff LED_Sensor_Pegel_Off
	
	//
	// Directions
	//
	#define EngineDirForward_Pegel  LOW
	#define EngineDirBackward_Pegel  HIGH
		
	#define EngineDirForward 1
	#define FWD EngineDirForward
	
	#define EngineDirBackward -1
	#define BWD EngineDirBackward
	#define EngineDirReward EngineDirBackward
	#define RWD EngineDirBackward
	
	#define MAX_SPEED 255
	
#endif