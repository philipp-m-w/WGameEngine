#pragma once

#include "lightshaderclass.h"
#include "phongshadering.h"

class ShaderManager
{
private:
	PhongShadering* phongShadering;
	LightShaderClass* lightShader;

public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool InitializeAll(ID3D11Device* device, HWND hwnd);
	bool ShutDownAll();

	//Aufrufe der einzelnen Shader
	bool RenderPhongShader(RenderData* renderData);
	bool RenderLightShader(ID3D11DeviceContext* context, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix,
					ID3D11ShaderResourceView* texture, D3DXVECTOR4 lightColors[], D3DXVECTOR4 lightPositions[]);

};