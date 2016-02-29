#include <string.h>
#include <pthread.h>

class Mutex
{
public:
    Mutex(const char *name)
    {
        strncpy(name_, name, strlen(name));
        pthread_mutex_init(&m_, NULL);
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
};

