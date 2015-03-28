#include <iostream>
#include <string>
#include <mutex>
#include <sstream>
#include "util.h"
using namespace std;

#ifndef CONSOLE_H
#define CONSOLE_H
class Con
{
private:
	mutex& ConLock;
public:
	Con(mutex& conLock);
	void Input(string& inPokes);
	void Output(stringstream& messages);
};
#endif