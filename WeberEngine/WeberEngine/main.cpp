#include "systemcontroller.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemController* System = 0;
	bool initializeSuccessful;	

	System = new SystemController();
	if (System)
	{
		System->Initialize();
	}
	else {
		return 0;
	}
	
	//Implement all functionality here
	System->StartDisplaying();

	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}


