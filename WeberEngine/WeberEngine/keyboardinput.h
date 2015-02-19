#ifndef _KEYBOARDINPUT_H_
#define _KEYBOARDINPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include "input.h";

class KeyboardInput
{
public:
	KeyboardInput(IDirectInput8* m_directInput, Input* input);
	KeyboardInput(const KeyboardInput&);
	~KeyboardInput();

	bool Initialize(HINSTANCE, HWND);
	void Shutdown();
	bool checkKeyboardInputs();

private:
	bool ReadKeyboard();

private:
	Input* listener;
	IDirectInput8* directInput;
	IDirectInputDevice8* m_keyboard;
	unsigned char m_keyboardState[256];
};

#endif