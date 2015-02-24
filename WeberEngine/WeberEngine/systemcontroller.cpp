#include "systemcontroller.h"

SystemController::SystemController()
{
	graphicsController = 0;
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
	case LEFT: graphicsController->getCamera()->moveLeft();
		break;
	case RIGHT: graphicsController->getCamera()->moveRight();
		break;
	case UP: graphicsController->getCamera()->moveForward();
		break;
	case DOWN: graphicsController->getCamera()->moveBackward();
		break;
	case ESCAPE: display->closeFrame();
		break;
	case ENTER:
		break;
	case SPACE: graphicsController->getCamera()->moveUp();
		break;
	case CTRL: graphicsController->getCamera()->moveDown();
		break;
	case MLEFTCLICK:
		break;
	case MRIGHTCLICK:
		break;
	case KEY_Q: graphicsController->getCamera()->rotateRightAroundUp();
		break;
	case KEY_E: graphicsController->getCamera()->rotateLeftAroundUp();
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
	graphicsController = new GraphicsController();
	result = graphicsController->Initialize(display->getScreenWidth(), display->getScreenHeight(), display->getHWND());
	if (!result)
	{
		return false;
	}

	return result;
}

bool SystemController::Shutdown()
{
	//Free everything
	
	if (inputController) {
		inputController->Shutdown();
		delete inputController;
		inputController = 0;
	}
	if (graphicsController) {
		graphicsController->ShutDown();
		delete graphicsController;
		graphicsController = 0;
	}

	if (display) {
		display->Shutdown();
		delete display;
		display = 0;
	}
	return true;
}

void SystemController::buildFrame()
{
	graphicsController->getCamera()->updateCamera();
	graphicsController->buildFrame();
}

bool SystemController::StartDisplaying()
{
	display->Run();
	return true;
}