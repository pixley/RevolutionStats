#include "stdafx.h"
#include <vector>
#include "console.h"
#include <Windows.h>
using namespace std;

Con::Con(mutex& conLock) : ConLock(conLock) {}

void Con::Input(string& inPokes)
{
	//greeting messages
	ConLock.lock();
	cout << "Welcome to RevolutionStats, as used in Pixley Commentates Twitch!" << endl;
	cout << "This window is used for input of participating Pokemon." << endl;
	cout << "The stat display is the other window in this program." << endl;
	cout << endl;
	ConLock.unlock();

	//main console loop
	while (true)
	{
		//instructions
		ConLock.lock();
		cout << "For the following inputs, one Pokemon will be accepted at a time." << endl;
		cout << "Please check your spelling.  The TPP stream has them written for you" << endl;
		cout << "Names must have the first letter capitalized." << endl;
		cout << "Just in case, these are the valid forms for the following Pokemon:" << endl;
		cout << "  Nidoran-F, Nidoran-M, Farfetch'd, Mr. Mime, Porygon2, Deoxys-N/A/D/S,\n  Burmy/Wormadam-D/S/T, Shellos/Gastrodon-E/W, Mime Jr., Porygon-Z" << endl;
		cout << "Shiny Pokemon are handled using the following format: \"*XXXX\"\n" << endl;
		cout << endl;

		stringstream pokes;
		string buf;

		cout << "Input 1st Pokemon on the Blue Team: ";
		cin >> buf;
		pokes << buf << '\t';

		cout << "Input 1st Pokemon on the Red Team:  ";
		cin >> buf;
		pokes << buf << '\t';

		cout << "Input 2nd Pokemon on the Blue Team: ";
		cin >> buf;
		pokes << buf << '\t';

		cout << "Input 2nd Pokemon on the Red Team:  ";
		cin >> buf;
		pokes << buf << '\t';

		cout << "Input 3rd Pokemon on the Blue Team: ";
		cin >> buf;
		pokes << buf << '\t';

		cout << "Input 3rd Pokemon on the Red Team:  ";
		cin >> buf;
		pokes << buf;

		inPokes = pokes.str();

		ConLock.unlock();

		Sleep(1000);

		ConLock.lock();

		cout << "Stats are now being displayed on the display window." << endl;
		cout << "Type \"new\" to start the next match, or type \"exit\" to end your session." << endl;

		cin >> buf;

		ConLock.unlock();

		if (buf == "exit") {
			inPokes = buf;
			break;
		}
	}
}