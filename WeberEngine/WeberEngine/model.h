#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include "texture.h"
using namespace std;

class StandardModel
{
private:

	//Datentyp für Grafikkarte
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 textureCoordinate;
		D3DXVECTOR3 normal;
	};

	//datentyp, mit dessen hilfe die Daten aus model.txt gelesen werden
	//diese Daten werden später würs Rendern in den Vertex-Datentyp konvertiert
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

	//cube-BoundingBox
	D3DXVECTOR3 m_minPoint;
	D3DXVECTOR3 m_maxPoint;

	void LoadTexture();
	void ReleaseTexture();

	void LoadModel();
	void ReleaseModel();
	void ShutdownBuffers();
	bool InitializeBuffers();
	
public:
	StandardModel(char* modelFilePath, WCHAR* textureFilePath, ID3D11Device* device);
	StandardModel(const StandardModel&);
	~StandardModel();

	//This function loads the Model Data to the graphics card.
	//Afterwards the Shader can be executed on the graphics card, so the model is drawn.
	//!!Make sure this function is called before Shader-Rendering!!
	void LoadModelDataToGraphicsCard(ID3D11DeviceContext* deviceContext);
	void getBoundingBox(D3DXVECTOR3& minPoint, D3DXVECTOR3& maxPoint);
	
	bool Initialize();
	void ShutDown();
	

	//Getters for vertexCount, IndexCount and Texture
	int GetIndexCount();
	int GetVertexCount();
	ID3D11ShaderResourceView* GetTexture();

	//TODO: Model braucht getter für alle möglichen Zeichenoperationen?

};