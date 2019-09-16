
#include "WHSR.h"

void WHSR::readOdometry(int *data)
{
	GetRPMSensorCount(data);
}

unsigned long WHSR::readOdometry(char Side)
{
	return GetRPMSensorCount(Side);
}