#include "graphicscontroller.h"
#include "options.h"

GraphicsController::GraphicsController()
{
	d3dClass = 0;
}

GraphicsController::GraphicsController(const GraphicsController&)
{
}

GraphicsController::~GraphicsController()
{

}

bool GraphicsController::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	// Create the Direct3D object.
	d3dClass = new D3DClass;
	if (!d3dClass)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = d3dClass->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

}

void GraphicsController::ShutDown()
{
	if (d3dClass)
	{
		d3dClass->Shutdown();
		delete d3dClass;
		d3dClass = 0;
	}
}


/**
* This Method is executed in every cycle of the Display Run-Method. It produces one Frame 
* on the graphics card by rendering all models/texts etc on the graphics card.
*/
void GraphicsController::buildFrame()
{

}