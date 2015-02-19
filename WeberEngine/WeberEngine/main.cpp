#include "systemcontroller.h"
#include "display.h"


bool Initialize(SystemController* System, Display* display)
{
	bool result = true;
	// Create the systemController object which is the facade class of the controller.
	System = new SystemController();
	if (!System)
	{
		return 0; //if constructor doesnt work, everything else is pointless
	}

	//Create Display class for visualizing everything on the screen
	display = new Display();
	if (!display)
	{
		return 0; //if constructor doesnt work, everything else is pointless
	}
	display->Initialize();

	return result;
}

bool Shutdown(SystemController* System, Display* display)
{
	//Free everything
	if (display) {
		display->Shutdown();
		delete display;
		display = 0;
	}

	if (System)
	{
		delete System;
		System = 0;
	}

	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemController* System = 0;
	Display* display = 0;
	bool initializeSuccessful;	

	//Initialize all facade classes and so forth
	initializeSuccessful = Initialize(System, display);

	if (initializeSuccessful)
	{
		//Implement all functionality here
		display->Run();

		
	}

	//free all created objects
	Shutdown(System, display);

	return 0;
}


