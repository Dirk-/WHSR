
#include <WHSR.h>

WHSR robo = WHSR();

int speed;           // Current speed of the motors (0 <= speed <= MAX_SPEED)
int directionSwitch; // +1 or -1 to flip direction

void setup()
{
    robo.Init();

    // Wait some time to give the user a chance to program the robot before it starts moving
    robo.setStatusLED(COLOR_RED);
    delay(1000);
    robo.setStatusLED(COLOR_YELLOW);
    delay(1000);
    robo.setStatusLED(COLOR_GREEN);
    delay(1000);

    // Start with minimum speed of 100, so that the motors actually turn the wheels
    speed = 100;
    directionSwitch = 1;

    // One wheel forward, the other one backward
    robo.setMotorDirection(FWD, RWD);

    Serial.println("Spin around");
}

void loop()
{
    if (speed < MAX_SPEED) // Accellerate
    {
        robo.setMotorSpeed(speed, speed);
        delay(25);
        speed++;
    }
    else // Switch direction
    {
        robo.setMotorSpeed(0, 0);
        Serial.println("Aaand the other way round!");

        // Read the odometry count
        unsigned long data[2];
        robo.getRPMSensorCount(data);
        Serial.print("Left odometry count: ");
        Serial.println(data[LEFT]);
        Serial.print("Right odometry count: ");
        Serial.println(data[RIGHT]);

        delay(250);
        speed = 100;
        directionSwitch = directionSwitch * (-1);
        robo.setMotorDirection(FWD * directionSwitch, RWD * directionSwitch);
    }
}