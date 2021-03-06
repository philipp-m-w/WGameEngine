#include "mouseinput.h"

MouseInput::MouseInput(IDirectInput8* m_directInput)
{
	directInput = m_directInput;
	m_mouse = 0;
}

MouseInput::MouseInput(const MouseInput& other)
{
}

MouseInput::~MouseInput()
{
}

bool MouseInput::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight) {
	HRESULT result;

	// Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize the location of the mouse on the screen.
	m_mouseX = 0;
	m_mouseY = 0;

	// Initialize the direct input interface for the mouse.
	result = directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the mouse to share with other programs.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Acquire the mouse.
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}
	return true;
}
void MouseInput::Shutdown(){
	// Release the mouse.
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	directInput = 0;
	return;
}
std::vector<InputEvent>* MouseInput::checkMouseInputs(){
	std::vector<InputEvent> *resultEvents = new std::vector<InputEvent>();

	// Read the current state of the mouse.
	ReadMouse();

	// Update the changes in the mouse.
	UpdateMouseLocation();

	//check Mouse Events

	// has a single-click occured?
	if (m_mouseState.rgbButtons[0]) {
		//leftClick ?
		resultEvents->push_back(InputEvent::MLEFTCLICK);
	}
	if (m_mouseState.rgbButtons[1]) {
		//leftClick ?
		resultEvents->push_back(InputEvent::MRIGHTCLICK);
	}

	return resultEvents;
}
void MouseInput::UpdateMouseLocation(){
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (m_mouseX < 0)  { m_mouseX = 0; }
	if (m_mouseY < 0)  { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth)  { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }

	return;
}
void MouseInput::ReadMouse(){
	HRESULT result;

	// Read the mouse device.
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}

	}
}

std::vector<int>* MouseInput::getMouseLocation()
{
	std::vector<int>* location = new std::vector<int>();
	location->push_back(m_mouseX);
	location->push_back(m_mouseY);
	return location;
}