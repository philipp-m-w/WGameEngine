#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include "texture.h"
using namespace std;

class StandardModel
{
private:

	//Datentyp f�r Grafikkarte
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 textureCoordinate;
		D3DXVECTOR3 normal;
	};

	//datentyp, mit dessen hilfe die Daten aus model.txt gelesen werden
	//diese Daten werden sp�ter w�rs Rendern in den Vertex-Datentyp konvertiert
	struct ModelData
	{
		//position of vertex
		float px, py, pz;
		//texture coordinates of vertex
		float tu, tv;
		//normale of vertex
		float nx, ny, nz;
	};

	bool scaling;
	float scalingX, scalingY, scalingZ;

	char* modelFilePath;
	WCHAR* textureFilePath;
	ID3D11Device* device;	

	//information about model data
	int vertexCount;
	int indexCount;
	ModelData* modelData;

	//Texture object
	Texture* texture;

	//These are the model-buffers which will be loaded to graphics card
	ID3D11Buffer *vertexBuffer, *indexBuffer;

	//cube-BoundingBox
	D3DXVECTOR3 m_minPoint;
	D3DXVECTOR3 m_maxPoint;

	void LoadTexture();
	void ReleaseTexture();

	void LoadModel();
	void ReleaseModel();
	void ShutdownBuffers();
	bool InitializeBuffers();

	/* Initializes the buffer, but scales the model in its size according to the scaling values */
	bool InitializeBuffers(float scalingX, float scalingY, float scalingZ);
	
public:
	StandardModel(char* modelFilePath, WCHAR* textureFilePath, ID3D11Device* device);
	//Constructor for scaled models
	StandardModel(char* modelFilePath, WCHAR* textureFilePath, ID3D11Device* device, float scalingX, float scalingY, float scalingZ);
	StandardModel(const StandardModel&);
	~StandardModel();

	//This function loads the Model Data to the graphics card.
	//Afterwards the Shader can be executed on the graphics card, so the model is drawn.
	//!!Make sure this function is called before Shader-Rendering!!
	void LoadModelDataToGraphicsCard(ID3D11DeviceContext* deviceContext);
	void getBoundingBox(D3DXVECTOR3& minPoint, D3DXVECTOR3& maxPoint);
	
	bool hasToBeScaled();

	bool Initialize();
	
	/* Initializes the model the same as Initialize(), but scales the model in its size according to the scaling values */
	bool InitializeScaling(float scalingX, float scalingY, float scalingZ);
	void ShutDown();
	

	//Getters for vertexCount, IndexCount and Texture
	int GetIndexCount();
	int GetVertexCount();
	ID3D11ShaderResourceView* GetTexture();

	//TODO: Model braucht getter f�r alle m�glichen Zeichenoperationen?

};