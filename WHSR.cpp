#include "WHSR.h"

WHSR * WHSR::myRobot = NULL;

void WHSR::Init(void)
{
	myRobot = this;

#if defined(ARDUINO_AVR_NANO)
    sei(); // Start Interrupts
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
#endif

    // Init the WHSR parts
	InitSerial();
	InitADC();
	InitSwitches();
	InitLEDs();
	InitSensors();
	InitEngine();
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

