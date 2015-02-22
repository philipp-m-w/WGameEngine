#pragma once

#include "d3dclass.h"
#include "camera.h"
#include "light.h"
#include "phongshadering.h"
#include <vector>


class GraphicsController
{
private:
	D3DClass* d3dClass;
	Camera* m_camera;
	std::vector<Light>* m_lights;

public:
	GraphicsController();
	GraphicsController(const GraphicsController&);
	~GraphicsController();

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void ShutDown();
	void addLight(D3DXVECTOR3 position, D3DXVECTOR3 direction, D3DXVECTOR4 color);

	void buildFrame();
};