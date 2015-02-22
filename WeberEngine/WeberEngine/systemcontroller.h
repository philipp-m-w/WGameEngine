#pragma once

#include "display.h"
#include "input.h"
#include "inputsenum.h"
#include "graphicscontroller.h"

class SystemController
{
private:
	Display* display;
	InputController* inputController;
	GraphicsController* graphicsController;

public:
	SystemController();
	SystemController(const SystemController&);
	~SystemController();

	bool Initialize();
	bool Shutdown();
	bool StartDisplaying();

	void buildFrame();


	//Input Funktionen
	void checkDeviceInputs();
	void processInputEvent(InputEvent event);
	std::vector<int>* getMouseLocation();
};
