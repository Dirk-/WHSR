#include "WHSR.h"

#if defined(ARDUINO_ARDUINO_NANO33BLE)
#include <nrf_timer.h>
#endif

void WHSR::TimerSet(unsigned long ms, void (*isrfunction)())
{
	TimerISRfunction = isrfunction;
	TimerWaitTime = (ms == 0 ? 1 : ms);

#if defined(ARDUINO_AVR_NANO)
    TCCR2A = (0 << COM2A1) | (0 << COM2A0) | // Compare Output abschalten
             (0 << COM2B1) | (0 << COM2B0) |
             (0 << WGM21) | (0 << WGM20); // Modus 00 Einstellen
                                          // Normal Operation

    TCCR2B = (0<<FOC2A) | (0<<FOC2B) |		// ???
			 (0<<WGM22) |					// siehe oeben -> Normal Operation
			 (0<<CS22) | (0<<CS21) | (0<<CS20); // Clock Source Abschalten
	
	TIMSK2 = (0<<OCIE2B) | (0<<OCIE2A) | (0<<TOIE2) ; // Alle Interrupts abschalten

	
	#if F_CPU < 1000000UL
	
		TCCR2B |= (0<<CS22) | (1<<CS21) | (0<<CS20); // prescaler set to 8
		TimerTcnt2 = 256 - (int)((float)F_CPU * 0.001 / 8);
	
	#elif F_CPU <= 16000000UL
	
		TCCR2B |= (1<<CS22) | (0<<CS21) | (0<<CS20); // prescaler set to 64
		TimerTcnt2 = 256 - (int)((float)F_CPU * 0.001 / 64);
	
	#else
	
		TCCR2B |= (1<<CS22) | (0<<CS21) | (1<<CS20); // prescaler set to 128
		TimerTcnt2 = 256 - (int)((float)F_CPU * 0.001 / 64);

	#endif
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    nrf_timer_shorts_enable(NRF_TIMER2, TIMER_SHORTS_COMPARE1_CLEAR_Msk);
    nrf_timer_mode_set(NRF_TIMER2, NRF_TIMER_MODE_TIMER);
    nrf_timer_bit_width_set(NRF_TIMER2, NRF_TIMER_BIT_WIDTH_32);
    nrf_timer_frequency_set(NRF_TIMER2, NRF_TIMER_FREQ_1MHz);
    nrf_timer_cc_write(NRF_TIMER4, NRF_TIMER_CC_CHANNEL1,
                       ms * 1000);
    nrf_timer_int_enable(NRF_TIMER2, NRF_TIMER_INT_COMPARE1_MASK);
    nrf_timer_task_trigger(NRF_TIMER2, NRF_TIMER_TASK_START);
#endif
}

#if defined(ARDUINO_ARDUINO_NANO33BLE)
void TIMER2_IRQHandler(void)
{
    if (nrf_timer_event_check(NRF_TIMER2, NRF_TIMER_EVENT_COMPARE1))
    {
        nrf_timer_event_clear(NRF_TIMER2, NRF_TIMER_EVENT_COMPARE1);
        WHSR::TimerOverflowISR();
    }
}
#endif

void WHSR::TimerStart()
{
	TimerCount = 0;
#if defined(ARDUINO_AVR_NANO)
    TCNT2 = TimerTcnt2;
    TIMSK2 |= (1<<TOIE2);
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    NVIC_SetPriority(TIMER2_IRQn, 7);
    NVIC_EnableIRQ(TIMER2_IRQn);
#endif
}

void WHSR::TimerStop()
{
#if defined(ARDUINO_AVR_NANO)
    TIMSK2 &= ~(1 << TOIE2);
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    NVIC_DisableIRQ(TIMER2_IRQn);
#endif
}

void WHSR::TimerOverflow()
{
#if defined(ARDUINO_AVR_NANO)
    TCNT2 = TimerTcnt2;
    TimerCount += 1;

    if (TimerCount >= TimerWaitTime && !TimerOverflowCount)
    {
        TimerOverflowCount = 1;
        TimerCount = TimerCount - TimerWaitTime;

        (*TimerISRfunction)();
        TimerOverflowCount = 0;
    }
#elif defined(ARDUINO_ARDUINO_NANO33BLE)
    (*TimerISRfunction)();
#endif
}



