#include "shadermanager.h"
#include "d3dclass.h"

ShaderManager::ShaderManager()
{
	phongShadering = 0;
	lightShader = 0;
}

ShaderManager::ShaderManager(const ShaderManager&)
{

}

ShaderManager::~ShaderManager()
{

}

bool ShaderManager::InitializeAll(ID3D11Device* device, HWND hwnd)
{
	bool result;

	phongShadering = new PhongShadering();
	result = phongShadering->Initialize(device, hwnd);
	if (!phongShadering) {
		return result;
	}
	lightShader = new LightShaderClass();
	result = lightShader->Initialize(device, hwnd);
	if (!lightShader) {
		return result;
	}

	return result;
}

bool ShaderManager::ShutDownAll()
{
	phongShadering->Shutdown();
	lightShader->Shutdown();

	return true;
}

bool ShaderManager::RenderLightShader(ID3D11DeviceContext* context, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
		D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, D3DXVECTOR4 lightColors[], D3DXVECTOR4 lightPositions[])
{
	return lightShader->Render(context, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightColors, lightPositions);
}

bool  ShaderManager::RenderPhongShader(RenderData* renderData)
{
	return phongShadering->Render(renderData);
}