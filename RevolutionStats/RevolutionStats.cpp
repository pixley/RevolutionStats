// RevolutionStats.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "core.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Core* core = new Core();
	if (core->Init())
	{
		core->Loop();
	}

	delete core;

	return 0;
}

