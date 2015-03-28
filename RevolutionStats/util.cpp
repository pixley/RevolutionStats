#include "stdafx.h"
#include "util.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cwchar>
using namespace std;

void Util::strSplit(string str, vector<string>& tokens, char delim) {
	string buf; // Have a buffer string
	stringstream ss(str); // Insert the string into a stream

	while (getline(ss, buf, delim))
		tokens.emplace_back(buf);

	return;
}

string Util::currentTimeToString() {
	time_t time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	tm uTime;
	tm* utcTime = &uTime;
	gmtime_s(utcTime, &time);
	int m = utcTime->tm_mon;
	int d = utcTime->tm_mday;
	int h = utcTime->tm_hour;
	int min = utcTime->tm_min;

	char c_stamp[21];

	sprintf_s(c_stamp, "[%2d-%2d\t%2d:%2dZ]", m + 1, d, h, min);

	string stamp(c_stamp);

	replace(stamp.begin(), stamp.end(), ' ', '0');
	replace(stamp.begin(), stamp.end(), '\t', ' ');

	return stamp;
}

Util::meCout::meCout(mutex& lock) : conOut(cout), Lock(lock) {

}

Util::meCout& Util::meCout::operator<<(const char* s) {
	Lock.lock();
	conOut << s;
	Lock.unlock();
	return *this;
}

Util::meCout& Util::meCout::operator<<(const int i) {
	Lock.lock();
	conOut << i;
	Lock.unlock();
	return *this;
}

Util::meCout& Util::meCout::operator<<(const stringstream& ss) {
	Lock.lock();
	conOut << ss.str();
	Lock.unlock();
	return *this;
}