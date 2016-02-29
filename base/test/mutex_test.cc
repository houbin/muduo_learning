#include "../mutex.h"
#include <iostream>

using namespace std;

int g_count = 0;

Mutex mutex("test");

void foo()
{
    Mutex::Locker lock(mutex);
    cout << "this is foo, and seq is " << ++g_count <<endl;
}

int main()
{
    int i = 0;
    for (; i < 10000; i++)
    {
        foo();
    }
    
    return 0;
}
