#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

//all the data necessary to render using the PhongShadering
struct RenderData
{
	ID3D11DeviceContext* deviceContext;
	int indexCount;

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;

	ID3D11ShaderResourceView* texture;

	D3DXVECTOR3 lightDirection;
	D3DXVECTOR3 lightPosition;

	D3DXVECTOR4 ambientColor;
	D3DXVECTOR4 diffuseColor;
	D3DXVECTOR4 specularColor;
	float specularPower;

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

	struct LightBuffer
	{
		//TODO: Achtung Reihenfolge ist später für Grafikkarte exctrem wichtig!!
		D3DXVECTOR4 ambientColor;
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR4 specularColor;
		//Position und Richtung des Lichts für PhongShading
		D3DXVECTOR3 lightDirection;
		D3DXVECTOR3 lightPosition;
		float specularPower;
		
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
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_cameraBuffer;


	///////////////////
	//private functions
	///////////////////
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4,
		D3DXVECTOR3, D3DXVECTOR4, float);
	void RenderShader(ID3D11DeviceContext*, int);

public:
	PhongShadering();
	PhongShadering(const PhongShadering&);
	~PhongShadering();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(RenderData* renderData);
};