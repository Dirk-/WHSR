
#include "Robot.h"

void Robot::TimerSet(unsigned long ms, void (*isrfunction)())
{
	TimerISRfunction = isrfunction;
	TimerWaitTime = (ms == 0 ? 1 : ms);
	
	TCCR2A = (0<<COM2A1) | (0<<COM2A0) |	// Compare Output abschalten
			 (0<<COM2B1) | (0<<COM2B0) | 	
			 (0<<WGM21)  | (0<<WGM20);		// Modus 00 Einstellen
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
}

void Robot::TimerStart()
{
	TimerCount = 0;
	TCNT2 = TimerTcnt2;
	TIMSK2 |= (1<<TOIE2);
}

void Robot::TimerStop()
{
	TIMSK2 &= ~(1<<TOIE2);
}

void Robot::TimerOverflow()
{
	TCNT2 = TimerTcnt2;
	TimerCount += 1;
	
	if (TimerCount >= TimerWaitTime && !TimerOverflowCount)
	{
		TimerOverflowCount = 1;
		TimerCount = TimerCount - TimerWaitTime;

		(*TimerISRfunction)();
		TimerOverflowCount = 0;
	}
}



