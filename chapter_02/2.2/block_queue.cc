#include <iostream>
#include "../../base/thread.h"
#include "../../base/cond.h"
#include "../../base/mutex.h"
#include <list>

using namespace std;

Mutex mutex("BlockQueue");
Cond cond;
list<int> queue;

int dequeue()
{
	Mutex::Locker lock(mutex);
	while(queue.empty())
	{
		cond.Wait(mutex);
	}

	int temp = queue.front();
	queue.pop_front();

	cout << "dequeue: " << temp << endl;
	return 0;
}

int equeue(int item)
{
	Mutex::Locker lock(mutex);

	queue.push_back(item);
	cout << "equeue: " << item << endl;
	cond.Notify();
}

void producer()
{
	int i = 0;
	while (true)
	{
		equeue(i++);
		usleep(500*1000);
	}
}

void consumer()
{
	while(true)
	{
		dequeue();
	}
}

int main()
{
	Thread t(producer);
	t.Start();

	consumer();

	t.Join();
	return 0;
}

