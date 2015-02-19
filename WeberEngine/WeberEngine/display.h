#ifndef _DISPLAY_H_
#define _DISPLAY_H_


#define WIN32_LEAN_AND_MEAN

#include <windows.h>

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Display
{
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	void InitializeWindows(int& width, int& height);
	void ShutdownWindows();

public:

	Display();
	Display(const Display&);
	~Display();
	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
};

/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static Display* ApplicationHandle = 0;

#endif