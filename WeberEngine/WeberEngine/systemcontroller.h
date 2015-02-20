#pragma once

#include "display.h"
#include "input.h"
#include "inputsenum.h"

class SystemController
{
private:
	Display* display;
	InputController* inputController;

public:
	SystemController();
	SystemController(const SystemController&);
	~SystemController();

	bool Initialize();
	bool Shutdown();
	bool StartDisplaying();


	//Input Funktionen
	void checkDeviceInputs();
	void processInputEvent(InputEvent event);
	std::vector<int>* getMouseLocation();
};
