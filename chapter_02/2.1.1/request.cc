#include "request.h"
#include "inventory.h"
#include "global.h"

using namespace std;

void Request::process()
{
	Mutex::Locker lock(mutex_);
	g_inventory.add(this);
}

void Request::print()
{
	Mutex::Locker lock(mutex_);
	cout << "request name is " << name_ << endl;
}

Request::~Request()
{
	Mutex::Locker lock(mutex_);
	g_inventory.remove(this);
}


