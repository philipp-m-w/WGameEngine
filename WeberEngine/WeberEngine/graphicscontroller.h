#pragma once

#include "d3dclass.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "frustum.h"
#include "shadermanager.h"
#include <vector>


class GraphicsController
{
private:
	D3DClass* d3dClass;
	Camera* m_camera;
	Frustum* m_Frustum;
	std::vector<Light>* m_lights;
	std::vector<StandardModel*>* models;
	ShaderManager* shaderManager;

public:
	GraphicsController();
	GraphicsController(const GraphicsController&);
	~GraphicsController();

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void ShutDown();
	void addLight(D3DXVECTOR3 position, D3DXVECTOR3 direction, D3DXVECTOR4 color);

	Camera* getCamera();

	void buildFrame();
};