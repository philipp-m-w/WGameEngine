#include "graphicscontroller.h"
#include "options.h"

GraphicsController::GraphicsController()
{
	d3dClass = 0;
	m_camera = 0;
	m_lights = 0;
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

	//create Camera
	m_camera = new Camera(D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	//create light-vector
	m_lights = new std::vector<Light>();

}

void GraphicsController::ShutDown()
{
	if (d3dClass)
	{
		d3dClass->Shutdown();
		delete d3dClass;
		d3dClass = 0;
	}

	delete(m_camera);
	delete(m_lights);
}


/**
* This Method is executed in every cycle of the Display Run-Method. It produces one Frame 
* on the graphics card by rendering all models/texts etc on the graphics card.
*/
void GraphicsController::buildFrame()
{

}

void GraphicsController::addLight(D3DXVECTOR3 position, D3DXVECTOR3 direction, D3DXVECTOR4 color) {
	Light light = Light(position, direction, color);
	m_lights->push_back(light);
}