#include "TimeControl.h"
//double TimeControl::DELTA_TIME=0.0;
const long TimeControl::SECONDS=1000000000L;
bool TimeControl::IS_BIGGER_HALF=false;
double TimeControl::SECOND_RESULT=0.0;
double TimeControl::SECOND_PART=0.0;
 double TimeControl::GetTime(){
	 double nano=((double)GetNanoTime()/(double)TimeControl::SECONDS);

	 if(!TimeControl::IS_BIGGER_HALF && nano>=0.5){
		 TimeControl::IS_BIGGER_HALF=true;
	 }else if(TimeControl::IS_BIGGER_HALF &&  nano<0.5){
		 TimeControl::IS_BIGGER_HALF=false;
		 TimeControl::SECOND_PART+=1.0;

	 }
	 TimeControl::SECOND_RESULT=TimeControl::SECOND_PART+nano;
	return TimeControl::SECOND_RESULT;

}
 long TimeControl::GetNanoTime(){
	timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	//now.tv_sec * 1000000000L +
	return  now.tv_nsec;
}
// double TimeControl::GetDelta(){
//
//	return DELTA_TIME;
//}
// void TimeControl::SetDelta(double delta){
//
//	 DELTA_TIME=delta;
//}
 //获取当前时间（毫秒）
 long TimeControl::GetCurrentTimeMillis(){
	 struct timeval tv;
	 gettimeofday(&tv,NULL);
	 return tv.tv_sec * 1000 + tv.tv_usec / 1000;

}
