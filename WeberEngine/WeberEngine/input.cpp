#include "input.h"

InputController::InputController(SystemController* controller)
{
	m_directInput = 0;
	mouse = 0;
	keyboard = 0;
	systemController = controller;
}

InputController::InputController(const InputController& other)
{
}

InputController::~InputController()
{
}

bool InputController::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	//initialize all device inputs
	mouse = new MouseInput(m_directInput);
	if (FAILED(mouse))
	{
		return false;
	}
	mouse->Initialize(hinstance, hwnd, screenWidth, screenHeight);

	keyboard = new KeyboardInput(m_directInput);
	if (FAILED(keyboard))
	{
		return false;
	}
	keyboard->Initialize(hinstance, hwnd);

	return true;
}

void InputController::Shutdown()
{
	// Release the mouse.
	if (mouse)
	{
		mouse->Shutdown();
	}
	free(mouse);

	// Release the keyboard.
	if (keyboard)
	{
		keyboard->Shutdown();
	}
	free(keyboard);

	// Release the main interface to direct input.
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	systemController = 0;

	return;
}

//this check is done in every Frame
bool InputController::checkDeviceInputs()
{
	bool result;

	// Read the current state of the keyboard.
	result = keyboard->checkKeyboardInputs();
	if (!result)
	{
		return false;
	}

	// Read the current state of the mouse.
	result = mouse->checkMouseInputs();
	if (!result)
	{
		return false;
	}

	// update the mouse-location
	mouse->UpdateMouseLocation();

	return true;
}

void InputController::onEscapePressed() {
	//systemController->
}
