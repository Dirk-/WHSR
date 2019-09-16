
#ifndef WHSRPINS_H
	#define WHSRPINS_H
	
	//
	//	Bluetooth Komunikation
	//
	#define Serial_RX 0
	#define Serial_TX 1

	//
	//	Engine, H-Bridge, Odometry
	//
	#define Revolution_Speed_Left  2
	#define Revolution_Speed_Right 3

	#define Engine_PWM_Left   9
	#define Engine_PWM_Right 10

	#define Engine_Dir_Left  13
	#define Engine_Dir_Right 12

	//
	// LED
	//
	#define LED_Blue  7
	#define LED_Green 5
	#define LED_Red   6

	//
	// Sensors
	//
	#define Batterie 7	// -> A2

	// Button
	#define Switch_On_Interrupt 11
	#define Switch 2 // -> A3
	#define SwitchISRPin A2 // -> A3

	// Anti Collision System
	#define ACS_IrLED  4
	#define ACS_Left  1 // -> A0
	#define ACS_Right 6 // -> A5

	// LDR - Light Sensing
	#define LDR_Left  3 // -> A7
	#define LDR_Right 4 // -> A4

	// Line Follower
	#define LineFollower_LED 8
	#define LineFollower_Right 5 // -> A1
	#define LineFollower_Left 0 // -> A6

	#define Referenz 8 // -> A14
#endif