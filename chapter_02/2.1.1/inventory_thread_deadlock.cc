#include <iostream>
#include "inventory.h"
#include "request.h"
#include "unistd.h"
#include "../../base/thread.h"

using namespace std;

Inventory g_inventory;

void print()
{
	g_inventory.printAll();
}

int main()
{
	Request *r = new Request("houbin");
	r->process();

	Thread thread(print);
	thread.Start();

	usleep(500 * 1000);

	delete r;

	thread.Join();

	return 0;
}
