#include "WHSR.h"

WHSR * WHSR::myRobot = NULL;

void WHSR::Init(void)
{
	myRobot = this;

    interrupts();   // Enable interrupts (probably unneccessary)

    // Init the WHSR parts
	initSerial();
	initADC();
	initSwitches();
	initLEDs();
	initSensors();
	initEngine();
}


// Attach the default Interrupt Service Routines to the interrupts
#if defined(ARDUINO_AVR_NANO)
ISR(ADC_vect) { WHSR::ADCInterruptISR(); }
ISR(TIMER1_OVF_vect) { WHSR::ADCInterruptBlockISR(); }
ISR(INT0_vect) { WHSR::RPMLeftISR(); }
ISR(INT1_vect) { WHSR::RPMRightISR(); }
ISR(TIMER2_OVF_vect) { WHSR::TimerOverflowISR(); }
ISR(PCINT1_vect) { WHSR::SwitchISR(); }
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
#endif

