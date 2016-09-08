#include "../../base/mutex.h"
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

Mutex mutex("deadlock_mutex");

class Foo
{
private:
	string name_;
public:
	Foo(string name) : name_(name) {}
    void doit()
    {
//		Mutex::Locker lock(mutex);
        cout << "just do it, name " << name_ << endl;
    }
};
vector<Foo*> foos;

void post(Foo* f)
{
    Mutex::Locker lock(mutex);
    foos.push_back(f);
}

void traverse()
{
    Mutex::Locker lock(mutex);
    vector<Foo*>::iterator iter = foos.begin();
    for (; iter != foos.end(); iter++)
    {
        Foo *temp = *iter;
		temp->doit();
    }
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		char buffer[32] = {0};
		snprintf(buffer, 31, "name_%d", i);
		Foo *foo = new Foo(string(buffer));
		post(foo);
	}

    traverse();

	return 0;
}
