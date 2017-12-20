#ifndef THREAD_BASE_H
#define THREAD_BASE_H

// External Files
#include <pthread.h>

class ThreadBase
{
	public:
		ThreadBase();
		bool StartThread();
        virtual void ThreadMethod() = 0;

	protected:
		pthread_t threadHandle;
};

#endif