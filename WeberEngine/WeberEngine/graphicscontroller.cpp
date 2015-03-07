#include "graphicscontroller.h"
#include "options.h"

GraphicsController::GraphicsController()
{
	d3dClass = 0;
	m_camera = 0;
	m_lights = 0;
	phongShadering = 0;
	models = 0;
	m_Frustum = 0;
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
	m_camera = new Camera(D3DXVECTOR3(0.0f, 0.0f, -3.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	// Create the frustum object.
	m_Frustum = new Frustum();


	//create light-vector
	m_lights = new std::vector<Light>();

	addLight(D3DXVECTOR3(0.0, 0.5, -3.0), D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR4(1.0, 1.0, 1.0, 0.9));
	addLight(D3DXVECTOR3(-0.5, 1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR4(1.0, 1.0, 1.0, 0.9));
	addLight(D3DXVECTOR3(0.5, 1.0, -1.0), D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR4(1.0, 1.0, 1.0, 0.9));
	addLight(D3DXVECTOR3(0.0, 1.0, -5.0), D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR4(1.0, 1.0, 1.0, 0.9));

	//Create models
	models = new std::vector<StandardModel*>();

	//Add the first model
	StandardModel* catModel = new StandardModel("../WeberEngine/data/models/cat.txt", L"../WeberEngine/data/textures/cat.dds", d3dClass->GetDevice());
	models->push_back(catModel);

	//Add the second model
	StandardModel* appleModel = new StandardModel("../WeberEngine/data/models/apple.txt", L"../WeberEngine/data/textures/apple.dds", d3dClass->GetDevice());
	models->push_back(appleModel);

	//Add the cube model
	StandardModel* cubeModel = new StandardModel("../WeberEngine/data/models/cube.txt", L"../WeberEngine/data/textures/apple.dds", d3dClass->GetDevice());
	models->push_back(cubeModel);

	//Add the boden
	StandardModel* bodenModel = new StandardModel("../WeberEngine/data/models/boden.txt", L"../WeberEngine/data/textures/boden.dds", d3dClass->GetDevice());
	models->push_back(bodenModel);

	//Initialize all models
	for each (StandardModel* model in *models)
	{
		model->Initialize();
	}

	//Initialize Phong Shader
	phongShadering = new PhongShadering();
	result = phongShadering->Initialize(d3dClass->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the phong shader object.", L"Error", MB_OK);
		return false;
	}

}

void GraphicsController::ShutDown()
{
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	if (d3dClass)
	{
		d3dClass->Shutdown();
		delete d3dClass;
		d3dClass = 0;
	}

	delete(m_camera);

	m_lights->clear();
	delete(m_lights);

	for each (StandardModel* model in *models)
	{
		model->ShutDown();
	}
	delete(models);
}


/**
* This Method is executed in every cycle of the Display Run-Method. It produces one Frame 
* on the graphics card by rendering all models/texts etc on the graphics card.
*/
void GraphicsController::buildFrame()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

	viewMatrix = *m_camera->GetViewMatrix();
	d3dClass->GetWorldMatrix(worldMatrix);
	d3dClass->GetProjectionMatrix(projectionMatrix);
	d3dClass->GetOrthoMatrix(orthoMatrix);

	// Construct the frustum.
	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);

	//D3DXVECTOR4 lightColors[light_count];
	D3DXVECTOR4 lightColors[10];
	D3DXVECTOR3 lightPositions[10];
	D3DXVECTOR3 lightDirections[10];
	for (size_t i = 0; i < m_lights->size(); i++)
	{
		lightColors[i] = m_lights->at(i).getColor();
		lightPositions[i] = m_lights->at(i).getPosition();
		lightDirections[i] = m_lights->at(i).getDirection();
	}

	int modelIndex;

	RenderData renderData;
	renderData.cameraPosition = *m_camera->GetPosition();
	renderData.deviceContext = d3dClass->GetDeviceContext();	
	renderData.k_s = D3DXVECTOR3(0.2, 0.2, 0.2);
	renderData.light_count = m_lights->size();
	renderData.n = 80.0f;
	renderData.projectionMatrix = projectionMatrix;
	renderData.viewMatrix = viewMatrix;
	renderData.worldMatrix = worldMatrix;
	renderData.lightColors = lightColors;
	renderData.lightDirections = lightDirections;
	renderData.lightPositions = lightPositions;

	// Clear the buffers to begin the scene.
	d3dClass->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Turn off alpha blending after rendering the text.
	d3dClass->TurnOffAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	d3dClass->TurnZBufferOn();

	bool renderSuccessful = false;
	for (modelIndex = 0; modelIndex < models->size(); modelIndex++)
	{
		//check if the model lies in the frustum
		D3DXVECTOR3 minPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 maxPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		models->at(modelIndex)->getBoundingBox(minPoint, maxPoint);
		if (m_Frustum->CheckBB(minPoint, maxPoint))
		{
			//first load model data to graphics card, then render it
			models->at(modelIndex)->LoadModelDataToGraphicsCard(d3dClass->GetDeviceContext());

			//load model-internal data to RenderData
			renderData.indexCount = models->at(modelIndex)->GetIndexCount();
			renderData.texture = models->at(modelIndex)->GetTexture();
			renderSuccessful = phongShadering->Render(&renderData);
		}
	}
	d3dClass->EndScene();
}

void GraphicsController::addLight(D3DXVECTOR3 position, D3DXVECTOR3 direction, D3DXVECTOR4 color) {
	Light light = Light(position, direction, color);
	m_lights->push_back(light);
}

Camera* GraphicsController::getCamera() {
	return m_camera;
}