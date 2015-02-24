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

	//Lights !!MULTIPLE!!
	int light_count;
	D3DXVECTOR3* lightDirections;
	D3DXVECTOR3* lightPositions;
	D3DXVECTOR4* lightColors;

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

	struct LightBuffer
	{
		//specifies how many of the lights are really used
		int lightCount;

		D3DXVECTOR3 padding;

		//TODO: Achtung Reihenfolge ist später für Grafikkarte exctrem wichtig!!
		D3DXVECTOR4 lightColor1;
		//Position und Richtung des Lichts für PhongShading
		D3DXVECTOR3 lightDirection1;
		D3DXVECTOR3 lightPosition1;	

		D3DXVECTOR4 lightColor2;
		D3DXVECTOR3 lightDirection2;
		D3DXVECTOR3 lightPosition2;

		D3DXVECTOR4 lightColor3;
		D3DXVECTOR3 lightDirection3;
		D3DXVECTOR3 lightPosition3;

		D3DXVECTOR4 lightColor4;
		D3DXVECTOR3 lightDirection4;
		D3DXVECTOR3 lightPosition4;

		D3DXVECTOR4 lightColor5;
		D3DXVECTOR3 lightDirection5;
		D3DXVECTOR3 lightPosition5;

		D3DXVECTOR4 lightColor6;
		D3DXVECTOR3 lightDirection6;
		D3DXVECTOR3 lightPosition6;

		D3DXVECTOR4 lightColor7;
		D3DXVECTOR3 lightDirection7;
		D3DXVECTOR3 lightPosition7;

		D3DXVECTOR4 lightColor8;
		D3DXVECTOR3 lightDirection8;
		D3DXVECTOR3 lightPosition8;

		D3DXVECTOR4 lightColor9;
		D3DXVECTOR3 lightDirection9;
		D3DXVECTOR3 lightPosition9;

		D3DXVECTOR4 lightColor10;
		D3DXVECTOR3 lightDirection10;
		D3DXVECTOR3 lightPosition10;
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