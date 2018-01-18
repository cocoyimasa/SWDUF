#ifndef __ARGUMENT_H__
#define __ARGUMENT_H__
#include "Basic.h"
#include <vector>
using namespace std;
using namespace swd;
class Argument : public Object{
public:
	Argument();
	Argument(const Argument& args);
	Object* Get(int index);
	void Push(Object* obj);
	bool Clear();
	int Size();
protected:
	vector<Object*> args;
};

#endif