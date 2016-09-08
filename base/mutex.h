#ifndef MUTEX_H_
#define MUTEX_H_
#include <string.h>
#include <pthread.h>

class Mutex
{
public:
    Mutex(const char *name)
    {
        strncpy(name_, name, strlen(name));
		pthread_mutexattr_init(&attr_);
		pthread_mutexattr_settype(&attr_, PTHREAD_MUTEX_NORMAL);
        pthread_mutex_init(&m_, &attr_);
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&m_);
    }

    void Lock()
    {
        pthread_mutex_lock(&m_);
    }

    void Unlock()
    {
        pthread_mutex_unlock(&m_);
    }

	friend class Cond;

    class Locker
    {
    public:
        Locker(Mutex &m) : m_(m)
        {
            m_.Lock();
        }

        ~Locker()
        {
            m_.Unlock();
        }
        
    private:
        Mutex &m_;
    };

private:
    char name_[64];
    pthread_mutex_t m_;
	pthread_mutexattr_t attr_;
};

#endif

