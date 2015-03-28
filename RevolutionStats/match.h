#include <string>
#include <vector>
#include "stdafx.h"
using namespace std;

#ifndef MATCH_H
#define MATCH_H
struct match {
	string redPokes[3];
	string bluePokes[3];
	int redStats[3][6];
	int blueStats[3][6];
};

struct statLine {
	int stats[6];

	int& operator[](unsigned int idx) { return stats[idx]; }
	statLine(int nums[6]) { for (int i = 0; i < 6; i++) { stats[i] = nums[i]; } }
};
#endif