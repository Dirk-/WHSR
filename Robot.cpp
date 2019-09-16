
#include "Robot.h"

Robot * Robot::MyRobot = NULL;

void Robot::Init(void)
{
	MyRobot = this;
	
	sei();
	
	InitSerial();
	InitADC();
	
	InitSwitches();
	InitLeds();
	InitSensors();
	InitEngine();
}


ISR(ADC_vect) { Robot::ADCInterruptISR(); }
ISR(TIMER1_OVF_vect) { Robot::ADCInterruptBlockISR(); }

ISR(INT0_vect) { Robot::RPMLeftISR(); }
ISR(INT1_vect) { Robot::RPMRightISR(); }

ISR(TIMER2_OVF_vect) { Robot::TimerOverflowISR(); }

ISR (PCINT1_vect) { Robot::SwitchISR(); }




