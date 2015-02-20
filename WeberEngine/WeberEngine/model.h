#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include "texture.h"
using namespace std;

class StandardModel
{
private:

	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 textureCoordinate;
		D3DXVECTOR3 normal;
	};

	struct ModelData
	{
		//position of vertex
		float px, py, pz;
		//texture coordinates of vertex
		float tu, tv;
		//normale of vertex
		float nx, ny, nz;
	};

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

	void LoadTexture();
	void ReleaseTexture();

	void LoadModel();
	void ReleaseModel();
	
public:
	StandardModel(char* modelFilePath, WCHAR* textureFilePath, ID3D11Device* device);
	StandardModel(const StandardModel&);
	~StandardModel();

	//This function loads the Model Data to the graphics card.
	//Afterwards the Shader can be executed on the graphics card, so the model is drawn.
	//!!Make sure this function is called before Shader-Rendering!!
	void LoadModelDataToGraphicsCard(ID3D11DeviceContext* deviceContext);

	bool InitializeBuffers();
	bool Initialize();
	void ShutDown();
	void ShutdownBuffers();

	//Getters for vertexCount, IndexCount and Texture
	int GetIndexCount();
	int GetVertexCount();
	ID3D11ShaderResourceView* GetTexture();

	//TODO: Model braucht getter für alle möglichen Zeichenoperationen?

};