#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include <sstream>
#include <exception>
using namespace std;

#ifndef UTIL_H
#define UTIL_H

namespace Util {
	void strSplit(string str, vector<string>& tokens, char delim);
	string currentTimeToString();

	class meCout {
	private:
		ostream& conOut;
		mutex& Lock;

	public:
		meCout(mutex& lock);
		meCout& operator<<(const char* s);
		meCout& operator<<(const int i);
		meCout& operator<<(const stringstream& ss);
	};
}

#endif