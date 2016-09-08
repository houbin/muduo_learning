#include "thread.h"

using namespace std;

void* startThread(void *obj)
{
	ThreadData *data = static_cast<ThreadData*>(obj);
	data->runInThread();

	return NULL;
}

Thread::Thread(ThreadFunc fun, string name)
: t_id_(NULL), func_(fun), name_(name), started_(false), joined_(false), number_()
{
}

Thread::~Thread()
{
    if (started_ && !joined_)
    {
        pthread_detach(t_id_);
    }
}

void Thread::SetDefaultName()
{
    int num = number_.Inc();
    if (name_.empty())
    {
        char buffer[32] = {0};
        snprintf(buffer, sizeof(buffer), "thread_%d", num);
        name_ = buffer;
    }
}

void Thread::Start()
{
    started_ = true;

	ThreadData *data = new ThreadData(func_);
    if (pthread_create(&t_id_, NULL, &startThread, data))
    {
        started_ = false;
    }
}

void Thread::Join()
{
    joined_ = true;
    pthread_join(t_id_, NULL);

	return;
}


