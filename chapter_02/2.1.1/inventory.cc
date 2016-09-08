#include "inventory.h"

using namespace std;

void Inventory::add(Request *req)
{
	Mutex::Locker lock(mutex_);
 	requests_.insert(req);
}

void Inventory::remove(Request *req)
{
	Mutex::Locker lock(mutex_);
	requests_.erase(req);
}

void Inventory::printAll()
{
	Mutex::Locker locker(mutex_);
	for(set<Request*>::iterator iter = requests_.begin();
		iter != requests_.end();
	   	iter++)
	{
		Request *temp = *iter;
		usleep(1000 * 1000);
		temp->print();
	}
}

