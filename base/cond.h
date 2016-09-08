#ifndef COND_H_
#define COND_H_

#include <pthread.h>
#include "mutex.h"

class Cond
{
private:
	pthread_cond_t cond_;

public:
	Cond()
	{
		pthread_cond_init(&cond_, NULL);
	}

	~Cond()
	{
		pthread_cond_destroy(&cond_);
	}

	void Wait(Mutex &mutex)
	{
		pthread_cond_wait(&cond_, &(mutex.m_));
	}

	void Notify()
	{
		pthread_cond_signal(&cond_);
	}

	void NofifyAll()
	{
		pthread_cond_broadcast(&cond_);
	}
};

#endif

