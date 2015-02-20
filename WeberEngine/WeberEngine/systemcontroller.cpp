#include "systemcontroller.h"

SystemController::SystemController()
{
}

SystemController::SystemController(const SystemController& other)
{
}

SystemController::~SystemController()
{
}

//this check is done in every Frame
void SystemController::checkDeviceInputs()
{
	std::vector<InputEvent>* resultEvents = inputController->checkDeviceInputs();
	for each (InputEvent event in *resultEvents)
	{
		processInputEvent(event);
	}
	delete resultEvents;
}

void SystemController::processInputEvent(InputEvent event) {
	switch (event)
	{
	case LEFT:
		break;
	case RIGHT:
		break;
	case UP:
		break;
	case DOWN:
		break;
	case ESCAPE: display->closeFrame();
		break;
	case ENTER:
		break;
	case SPACE:
		break;
	case MLEFTCLICK: display->closeFrame();
		break;
	case MRIGHTCLICK: display->closeFrame();
		break;
	default:
		break;
	}
}

std::vector<int>* SystemController::getMouseLocation() {
	return inputController->getMouseLocation();
}

bool SystemController::Initialize()
{
	bool result = false;
	//Create Display class for visualizing everything on the screen
	display = new Display(this);
	if (display)
	{
		display->Initialize(); //if constructor doesnt work, everything else is pointless
		result = true;
	}
	if (result) {
		inputController = new InputController();
		if (inputController) {
			HINSTANCE hinst = display->getHinstance();
			HWND hwnd = display->getHWND();
			result = inputController->Initialize(hinst, hwnd, display->getScreenWidth(), display->getScreenHeight());
		}
	}
	return result;
}

bool SystemController::Shutdown()
{
	//Free everything
	if (display) {
		display->Shutdown();
		delete display;
		display = 0;
	}
	if (inputController) {
		inputController->Shutdown();
		delete inputController;
		inputController = 0;
	}
	return true;
}
bool SystemController::StartDisplaying()
{
	display->Run();
	return true;
}