
#include "Robot.h"

void Robot::readOdometry(int *data)
{
	GetRPMSensorCount(data);
}

unsigned long Robot::readOdometry(char Side)
{
	return GetRPMSensorCount(Side);
}