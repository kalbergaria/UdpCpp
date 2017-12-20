#ifndef K_TIME_H
#define K_TIME_H

#include <time.h>

void SleepRemainingIterationDuration(timespec* iterationStart, int usecIterationDuration, int usecSleepIntervals);
long long TimespecConcatTimeConvert2us(timespec* timeStruct);
long long TimevalConcatTimeConvert2us(timeval* timeStruct);

#endif
