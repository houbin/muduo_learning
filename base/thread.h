#ifndef THREAD_T_
#define THREAD_T_

#include "atomic.h"
#include <string>
#include <boost/function.hpp>
#include <stdio.h>

using namespace std;

class Thread
{
public:
    typedef boost::function<void ()> ThreadFunc;

    Thread(ThreadFunc fun, string name = "");
    ~Thread();

    void SetDefaultName();
    void Start();
    void Join();
    
private:
    pthread_t t_id_;
    ThreadFunc func_;
    string name_;

    bool started_;
    bool joined_;

    AtomicInt32 number_;
};

class ThreadData
{
private:
	typedef Thread::ThreadFunc ThreadFunc;
	
	ThreadFunc func_;

public:
	ThreadData(const ThreadFunc& func) : func_(func)
	{ }

	void runInThread()
	{
		func_();
	}
};

#endif

