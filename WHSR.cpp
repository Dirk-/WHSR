
#include "WHSR.h"

WHSR * WHSR::myRobot = NULL;

void WHSR::Init(void)
{
	myRobot = this;
	
	sei();
	
	InitSerial();
	InitADC();
	
	InitSwitches();
	InitLeds();
	InitSensors();
	InitEngine();
}


ISR(ADC_vect) { WHSR::ADCInterruptISR(); }
ISR(TIMER1_OVF_vect) { WHSR::ADCInterruptBlockISR(); }

ISR(INT0_vect) { WHSR::RPMLeftISR(); }
ISR(INT1_vect) { WHSR::RPMRightISR(); }

ISR(TIMER2_OVF_vect) { WHSR::TimerOverflowISR(); }

ISR (PCINT1_vect) { WHSR::SwitchISR(); }




