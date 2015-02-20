#ifndef _INPUT_H_
#define _INPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include "keyboardinput.h"
#include "mouseinput.h"
#include "inputsenum.h"
#include <vector>


class InputController
{
public:
	InputController();
	InputController(const InputController&);
	~InputController();

	bool Initialize(HINSTANCE, HWND, int screenWidth, int screenHeight);
	void Shutdown();
	//this check is done in every Frame
	std::vector<InputEvent>* checkDeviceInputs();
	std::vector<int>* getMouseLocation();

private:
	IDirectInput8* m_directInput;
	KeyboardInput* keyboard;
	MouseInput* mouse;
	int m_screenWidth, m_screenHeight;
};

#endif