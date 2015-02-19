#include "inputcontroller.h"

KeyboardInput::KeyboardInput(IDirectInput8* m_directInput, InputController* input)
{
	directInput = m_directInput;
	m_keyboard = 0;
	listener = input;
}

KeyboardInput::KeyboardInput(const KeyboardInput& other)
{
}

KeyboardInput::~KeyboardInput()
{
}

bool KeyboardInput::Initialize(HINSTANCE hinstance, HWND hwnd){
	HRESULT result;

	// Initialize the direct input interface for the keyboard.
	result = directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the keyboard to not share with other programs.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Now acquire the keyboard.
	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}
}
void KeyboardInput::Shutdown(){
	// Release the keyboard.
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	directInput = 0;
	listener = 0;

	return;
}
bool KeyboardInput::checkKeyboardInputs(){
	bool result;
	// Read the current state of the keyboard.
	result = ReadKeyboard();
	if (!result)
	{
		return false;
	}

	//check for events
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		//escape pressed
		listener->onEscapePressed();
	}

	return true;
}
bool KeyboardInput::ReadKeyboard(){
	HRESULT result;

	// Read the keyboard device.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}