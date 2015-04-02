#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

/////////////
// GLOBALS //
/////////////
const int NUMBER_OF_LIGHTS = 4;

//all the data necessary to render using the PhongShadering
struct RenderData
{
	ID3D11DeviceContext* deviceContext;
	int indexCount;

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;

	ID3D11ShaderResourceView* texture;

	D3DXVECTOR4* lightPositions;

	//material info
	float n;
	D3DXVECTOR3 k_s;

	D3DXVECTOR3 cameraPosition;
};

class PhongShadering
{
private:
	struct MatrixBuffer
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct CameraBuffer
	{
		D3DXVECTOR3 cameraPosition;
		float padding;
	};

	struct MaterialBuffer
	{
		float n;
		D3DXVECTOR3 k_s;		
	};

	struct LightPositionBuffer
	{
		D3DXVECTOR4 lightPosition[NUMBER_OF_LIGHTS];
	};

	//////////////
	//Attributes
	//////////////

	//Pixel- and Vertex-Shaders
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;

	//other Graphicscard-Render-Descriptions
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;

	//Buffers for rendering-data
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_materialBuffer;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_cameraBuffer;


	///////////////////
	//private functions
	///////////////////
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);

	//bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, D3DXVECTOR3 lightDirection, D3DXVECTOR3 lightPosition, D3DXVECTOR4 lightColor,
	//	D3DXVECTOR3 cameraPosition, float specularPower);
	bool SetShaderParameters(RenderData* renderData);

	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

public:
	PhongShadering();
	PhongShadering(const PhongShadering&);
	~PhongShadering();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(RenderData* renderData);
};