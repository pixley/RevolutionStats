#include "stdafx.h"
#include "core.h"
#include <algorithm>
#include <Windows.h>
#include <WinUser.h>

dex::dex(string spec, int no)
{
	species = spec;
	num = no;
}

bool operator< (dex lhs, dex rhs) {
	return lhs.species < rhs.species;
}

bool operator>(dex lhs, dex rhs) {
	return lhs.species > rhs.species;
}

bool operator< (string lhs, dex rhs) {
	return lhs < rhs.species;
}

bool operator>(string lhs, dex rhs) {
	return lhs > rhs.species;
}

int binary_search(const vector<dex>& sorted_vec, string key) {
	size_t mid, left = 0;
	size_t right = sorted_vec.size(); // one position passed the right end
	while (left < right) {
		mid = left + (right - left) / 2;
		if (key > sorted_vec[mid]){
			left = mid + 1;
		}
		else if (key < sorted_vec[mid]){
			right = mid;
		}
		else {
			return sorted_vec[mid].num;
		}
	}

	return 0;
}

Core::Core() : console(ConLock), Win(VideoMode(1385, 305), "RevolutionStats Display", Style::Titlebar), Disp(Match, Win)
{
	Dex.reserve(524);
	Stats.reserve(524);

	Win.setPosition(Vector2i(0, 0));
	Win.setFramerateLimit(60);
}

Core::~Core() {}

bool Core::PokeLoad()
{
	ifstream pokes("pokelist.txt");

	if (!pokes.is_open())
		return false;

	string line;
	unsigned int i = 1;
	getline(pokes, line);
	while (!pokes.eof())
	{
		getline(pokes, line, '\n');
		Dex.emplace_back(dex(line, i));
		i += 1;
	}

	//sort the dex entries into alphabetical order for faster search
	sort(Dex.begin(), Dex.end());

	return true;
}

bool Core::StatLoad()
{
	ifstream stats("statlist.txt");

	if (!stats.is_open())
		return false;

	string line;
	getline(stats, line);
	while (!stats.eof())
	{
		getline(stats, line, '\n');
		vector<string> nums;
		Util::strSplit(line, nums, ' ');
		int buf[] = { stoi(nums[0]), stoi(nums[1]), stoi(nums[2]), stoi(nums[3]), stoi(nums[4]), stoi(nums[5]) };
		Stats.emplace_back(buf);
	}

	return true;
}

unsigned int Core::NameToNum(string species)
{
	return binary_search(Dex, species);
}

__declspec(noinline) bool Core::Init()
{
	bool load = PokeLoad() && StatLoad();
	return load;
}

void Core::Loop()
{
	thread conThread(&Con::Input, ref(console), ref(InPokes));
	while (Input())
	{
		Display();
	}

	conThread.join();
}

bool Core::Input() {
	bool out = true;
	
	if (ConLock.try_lock())
	{
		if (InPokes != "N/A" && InPokes != "exit")
		{
			vector<string> pokes;
			pokes.reserve(6);
			Util::strSplit(InPokes, pokes, '\t');

			for (int i = 0; i < pokes.size() / 2; i++)
			{
				Match.redPokes[i].assign(pokes[2 * i + 1]);
				Match.bluePokes[i].assign(pokes[2 * i]);

				unsigned int redPoke = NameToNum(pokes[2 * i + 1]);
				unsigned int bluePoke = NameToNum(pokes[2 * i]);

				for (int j = 0; j < 6; j++)
				{
					Match.redStats[i][j] = Stats[redPoke][j];
					Match.blueStats[i][j] = Stats[bluePoke][j];
				}
			}

			InPokes = "N/A";
		}
		else if (InPokes == "exit")
		{
			ConLock.unlock();
			return false;
		}
		ConLock.unlock();

	}
	return true;
}

void Core::Display()
{
	//this method is also used for the event loop, which is required, else the window
	//becomes unresponsive; RevolutionStats doesn't use the window for any input
	Event event;
	while (Win.pollEvent(event)) {
		//nothing here; just polling events
	}

	Disp.Draw();
}