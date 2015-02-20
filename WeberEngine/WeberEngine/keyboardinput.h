#ifndef _KEYBOARDINPUT_H_
#define _KEYBOARDINPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include <vector>
#include "inputsenum.h"


class KeyboardInput
{
public:
	KeyboardInput(IDirectInput8* m_directInput);
	KeyboardInput(const KeyboardInput&);
	~KeyboardInput();

	bool Initialize(HINSTANCE, HWND);
	void Shutdown();
	std::vector<InputEvent>* checkKeyboardInputs();

private:
	void ReadKeyboard();

private:
	IDirectInput8* directInput;
	IDirectInputDevice8* m_keyboard;
	unsigned char m_keyboardState[256];
};

#endif