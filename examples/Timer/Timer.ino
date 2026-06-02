/*
  Timer

  This example for the Westphalian University's WHSR lerning robot shows how to 
  change the color of the LED with the help of a timer. The timer is called again 
  after the specified time has elapsed. 

  This example code is in the public domain. For more information, see
  https://github.com/Dirk-/WHSR
*/

#include <WHSR.h>

// We need one instance of the WHSR class to handle the robot
WHSR robo = WHSR();

// This variable gets changed in the timer ISR, so you have to signal the compiler that it is volatile, 
// otherwise the compiler might optimize it away and your timer will not work as expected.
volatile int color = COLOR_BLUE;

// This is your timer Interrupt service routine. It is called every time the timer overflows, 
// in this case every 3000 ms.
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
    // Initialize all functional modules of the robot
    robo.Init();
    robo.TimerSet(3000, timerISR);              // Set timer to three seconds
    robo.TimerStart();

    Serial.println("Timer Test");
}


void loop()
{
    robo.setStatusLED(color);
    delay(300);                                 // Pause for 300 milliseconds
    robo.setStatusLED(COLOR_BLACK);             // LED turn off
    delay(300);                                 // Pause for 300 milliseconds
}