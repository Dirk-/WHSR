
#include <WHSR.h>

WHSR robo = WHSR();

volatile int color = COLOR_BLUE;

void timerISR()
{
    switch (color)
    {
    case COLOR_BLUE:
        color = COLOR_RED;
        break;
    case COLOR_RED:
        color = COLOR_GREEN;
        break;
    case COLOR_GREEN:
        color = COLOR_BLUE;
        break;

    default:
        color = COLOR_RED;
        break;
    }
}

void setup()
{
	robo.Init();
    robo.TimerSet(2000, timerISR);
    robo.TimerStart();

    Serial.println("Timer Test");
}


void loop()
{
    robo.setStatusLED(color);
    delay(300);
    robo.setStatusLED(COLOR_BLACK);
    delay(300);
}