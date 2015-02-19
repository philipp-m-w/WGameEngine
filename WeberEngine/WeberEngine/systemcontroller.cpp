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

void SystemController::closeFrame(){

}
void SystemController::moveCamera(float left, float right, float top, float bottom){

}
void SystemController::rotateZ(float angle){

}

bool SystemController::Initialize()
{
	bool result = false;
	//Create Display class for visualizing everything on the screen
	display = new Display();
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