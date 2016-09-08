#ifndef REQUEST_H_
#define REQUEST_H_

#include <iostream>
#include <string>
#include "../../base/mutex.h"

using namespace std;

class Request
{
public:

	Request(string name) : name_(name), mutex_("request")
	{}
	~Request();

	void process();
	void print();

private:
	Mutex  mutex_;
	string name_;
};

#endif

