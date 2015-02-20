#pragma once

#include "d3dclass.h"


class GraphicsController
{
private:
	D3DClass* d3dClass;
public:
	GraphicsController();
	GraphicsController(const GraphicsController&);
	~GraphicsController();

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void ShutDown();

	void buildFrame();
};