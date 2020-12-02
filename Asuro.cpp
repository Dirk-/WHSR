
#include "WHSR.h"

void WHSR::readOdometry(int *data)
{
	getRPMSensorCount(data);
}

unsigned long WHSR::readOdometry(char Side)
{
	return getRPMSensorCount(Side);
}