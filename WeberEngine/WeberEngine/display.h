#pragma once


#define WIN32_LEAN_AND_MEAN

#include <windows.h>

class SystemController;

class Display
{
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	SystemController* systemController;

	int screenWidth, screenHeight;

	void InitializeWindows();
	void ShutdownWindows();

public:

	Display(SystemController* systemController);
	Display(const Display&);
	~Display();
	bool Initialize();
	void Shutdown();
	void Run();
	HWND getHWND();
	HINSTANCE getHinstance();
	int getScreenWidth();
	int getScreenHeight();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
};

/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static Display* ApplicationHandle = 0;

