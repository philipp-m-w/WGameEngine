#ifndef _MOUSEINPUT_H_
#define _MOUSEINPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include "inputsenum.h"
#include <vector>

class MouseInput
{
public:
	MouseInput(IDirectInput8* m_directInput);
	MouseInput(const MouseInput&);
	~MouseInput();

	bool Initialize(HINSTANCE, HWND, int screenWidth, int screenHeight);
	void Shutdown();
	std::vector<InputEvent>* checkMouseInputs();
	void UpdateMouseLocation();
	std::vector<int>* getMouseLocation();

private:
	void ReadMouse();

private:
	IDirectInput8* directInput;
	IDirectInputDevice8* m_mouse;
	DIMOUSESTATE m_mouseState;
	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

#endif;