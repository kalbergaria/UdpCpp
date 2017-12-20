// System Files
#include "K_Time.h"

// External Libraries
#include <unistd.h>

#define THOUSAND 1000

//
//
//
void SleepRemainingIterationDuration(timespec* iterationStart, int usecIterationDuration, int usecSleepIntervals)
{
	struct timespec currentTime;
	clock_gettime(CLOCK_REALTIME, &currentTime);

	while (TimespecConcatTimeConvert2us(&currentTime) - TimespecConcatTimeConvert2us(iterationStart) < usecIterationDuration)
	{
		usleep(usecSleepIntervals);
		clock_gettime(CLOCK_REALTIME, &currentTime);
	}
}

//
// FOR TIMESPEC!!!
//
long long TimespecConcatTimeConvert2us(timespec* timeStruct)
{
	return (long long)(timeStruct->tv_sec * THOUSAND * THOUSAND + timeStruct->tv_nsec / THOUSAND);
}

//
// FOR TIMEVAL!!!
//
long long TimevalConcatTimeConvert2us(timeval* timeStruct)
{
	return (long long)(timeStruct->tv_sec * THOUSAND * THOUSAND + timeStruct->tv_usec);
}
