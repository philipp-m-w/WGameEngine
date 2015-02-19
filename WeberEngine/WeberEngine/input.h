#ifndef _INPUT_H_
#define _INPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include "mouseinput.h"
#include "keyboardinput.h"
#include "systemcontroller.h"

class Input
{
public:
	Input(SystemController* controller);
	Input(const Input&);
	~Input();

	bool Initialize(HINSTANCE, HWND, int screenWidth, int screenHeight);
	void Shutdown();
	//this check is done in every Frame
	bool checkDeviceInputs();
	void onEscapePressed();



private:

private:
	SystemController* systemController;
	IDirectInput8* m_directInput;
	KeyboardInput* keyboard;
	MouseInput* mouse;
	int m_screenWidth, m_screenHeight;
};

#endif