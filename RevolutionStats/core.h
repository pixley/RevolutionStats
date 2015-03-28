#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <sstream>
#include "console.h"
#include "display.h"
#include "util.h"
#include "match.h"
using namespace std;
using namespace sf;

struct dex {
	string species;
	int num;

	dex(string spec, int no);
};

bool operator< (dex lhs, dex rhs);
bool operator< (string lhs, dex rhs);
bool operator> (dex lhs, dex rhs);
bool operator> (string lhs, dex rhs);

class Core
{
private:
	vector<dex> Dex;
	vector<statLine> Stats;

	match Match;

	mutex ConLock;
	string In;

	Con console;
	string InPokes;
	stringstream MessQueue;

	RenderWindow Win;
	Display Disp;

	bool PokeLoad();
	bool StatLoad();

	bool Input();
	void Display();

	unsigned int NameToNum(string Species);

public:
	Core();
	~Core();
	__declspec(noinline) bool Init();
	void Loop();
};