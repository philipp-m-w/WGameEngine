#ifndef _INPUT_H_
#define _INPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include "keyboardinput.h"
#include "mouseinput.h"


class InputController
{
public:
	InputController();
	InputController(const InputController&);
	~InputController();

	bool Initialize(HINSTANCE, HWND, int screenWidth, int screenHeight);
	void Shutdown();
	//this check is done in every Frame
	bool checkDeviceInputs();
	void onEscapePressed();

private:
	IDirectInput8* m_directInput;
	KeyboardInput* keyboard;
	MouseInput* mouse;
	int m_screenWidth, m_screenHeight;
};

#endif