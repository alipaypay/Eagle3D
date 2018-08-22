#ifndef TIMECONTROL_H
#define TIMECONTROL_H

#include <time.h>
#include <sys/time.h>
#include "EagleLog.h"
class TimeControl{
public:
	//static double DELTA_TIME;
	static long GetCurrentTimeMillis();
	static double GetTime();
//	static double GetDelta();
//
//	static void SetDelta(double delta);


private:
	static long GetNanoTime();
	static bool IS_BIGGER_HALF;
	static double SECOND_PART;
	static double SECOND_RESULT;
	static const long SECONDS;
};


#endif
