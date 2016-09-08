#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <iostream>
#include <set>
#include <unistd.h>
#include "../../base/mutex.h"
#include "request.h"

using namespace std;

class Request;

class Inventory
{
public:
	Inventory() : mutex_("Inventory")
	{}

	void add(Request *req);
	void remove(Request *req);
	void printAll();
	
private:
	Mutex mutex_;
	set<Request*> requests_;
};

#endif

