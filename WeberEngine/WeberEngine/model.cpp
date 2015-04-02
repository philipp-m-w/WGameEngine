#include "model.h"

StandardModel::StandardModel(char* modelFilePath, WCHAR* textureFilePath, ID3D11Device* device) :
			modelFilePath(modelFilePath),
			textureFilePath(textureFilePath),
			device(device),
			vertexCount(0),
			indexCount(0)
{
	vertexBuffer = 0;
	indexBuffer = 0;	
	modelData = 0;
	m_minPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_maxPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


StandardModel::StandardModel(const StandardModel&)
{

}

StandardModel::~StandardModel()
{

}


bool StandardModel::Initialize()
{
	bool result;
	// Load in the model data,
	LoadModel();

	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers();
	if (!result)
	{
		return false;
	}
	

	// Load the texture for this model.
	LoadTexture();

	return true;
}


bool StandardModel::InitializeBuffers()
{
	//our vertex-data from the model files
	Vertex* vertices;
	//indices to vertices of model data
	unsigned long* indices;
	//descriptions for the buffer allocation on graphics card
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	vertices = new Vertex[vertexCount];
	indices = new unsigned long[indexCount];

	//Load vertex and index arrays with data from the loaded model
	int i;
	for (i = 0; i < vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(modelData[i].px, modelData[i].py, modelData[i].pz);
		vertices[i].textureCoordinate = D3DXVECTOR2(modelData[i].tu, modelData[i].tv);
		vertices[i].normal = D3DXVECTOR3(modelData[i].nx, modelData[i].ny, modelData[i].nz);

		indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void StandardModel::ShutDown()
{
	// Release the model texture.
	ReleaseTexture();

	// Release the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}

void StandardModel::LoadModel()
{
	ifstream fin;
	char input;
	int i;

	// Open the model file.
	fin.open(modelFilePath);

	// If it could not open the file then exit.
	if (fin.fail())
	{		
		return;
	}

	// Read up to the value of vertex count.
		fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> vertexCount;

	// Set the number of indices to be the same as the vertex count.
	indexCount = vertexCount;

	// Create the model using the vertex count that was read in.
	modelData = new ModelData[vertexCount];

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;

	// Read in the vertex data.
	for (i = 0; i < vertexCount; i++)
	{
		fin >> modelData[i].px >> modelData[i].py >> modelData[i].pz;
		fin >> modelData[i].tu >> modelData[i].tv;
		fin >> modelData[i].nx >> modelData[i].ny >> modelData[i].nz;

		//determine boundingBox
		if (modelData[i].px > maxX) { maxX = modelData[i].px; }
		if (modelData[i].py > maxY) { maxY = modelData[i].py; }
		if (modelData[i].pz > maxZ) { maxZ = modelData[i].pz; }
		if (modelData[i].px < minX) { minX = modelData[i].px; }
		if (modelData[i].py < minY) { minY = modelData[i].py; }
		if (modelData[i].pz < minZ) { minZ = modelData[i].pz; }

	}

	m_minPoint.x = minX;
	m_minPoint.y = minY;
	m_minPoint.z = minZ;
	m_maxPoint.x = maxX;
	m_maxPoint.y = maxY;
	m_maxPoint.z = maxZ;

	// Close the model file.
	fin.close();

}

void StandardModel::ReleaseModel()
{
	if (modelData)
	{
		delete[] modelData;
		modelData = 0;
	}
	return;
}

void StandardModel::LoadTexture()
{
	// Create the texture object.
	texture = new Texture(textureFilePath, device);
	if (!texture)
	{
		return;
	}

	// Initialize the texture object.
	bool result = texture->Initialize();
	if (!result)
	{
		return;
	}
}


void StandardModel::ReleaseTexture()
{
	// Release the texture object.
	if (texture)
	{
		texture->Shutdown();
		delete texture;
		texture = 0;
	}

	return;
}

void StandardModel::ShutdownBuffers()
{
	// Release the index buffer.
	if (indexBuffer)
	{
		indexBuffer->Release();
		indexBuffer = 0;
	}
	// Release the vertex buffer.
	if (vertexBuffer)
	{
		vertexBuffer->Release();
		vertexBuffer = 0;
	}

	return;
}

//This function loads the Model Data to the graphics card.
//Afterwards the Shader can be executed on the graphics card, so the model is drawn.
//!!Make sure this function is called before Shader-Rendering!!
void StandardModel::LoadModelDataToGraphicsCard(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(Vertex);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

int StandardModel::GetIndexCount()
{
	return indexCount;
}

int StandardModel::GetVertexCount()
{
	return vertexCount;
}


ID3D11ShaderResourceView* StandardModel::GetTexture()
{
	return texture->GetTexture();
}

void StandardModel::getBoundingBox(D3DXVECTOR3& minPoint, D3DXVECTOR3& maxPoint) {
	minPoint = m_minPoint;
	maxPoint = m_maxPoint;
	return;
}

void StandardModel::scaleModelSize(float xScale, float yScale, float zScale)
{

	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;

	for (int i = 0; i < vertexCount; i++) {
		modelData[i].px = modelData[i].px * xScale;
		modelData[i].py = modelData[i].py * yScale;
		modelData[i].pz = modelData[i].pz * zScale;

		//determine boundingBox
		if (modelData[i].px > maxX) { maxX = modelData[i].px; }
		if (modelData[i].py > maxY) { maxY = modelData[i].py; }
		if (modelData[i].pz > maxZ) { maxZ = modelData[i].pz; }
		if (modelData[i].px < minX) { minX = modelData[i].px; }
		if (modelData[i].py < minY) { minY = modelData[i].py; }
		if (modelData[i].pz < minZ) { minZ = modelData[i].pz; }
	}

	m_minPoint.x = minX;
	m_minPoint.y = minY;
	m_minPoint.z = minZ;
	m_maxPoint.x = maxX;
	m_maxPoint.y = maxY;
	m_maxPoint.z = maxZ;

	InitializeBuffers();
}

void StandardModel::translateModel(float xDiff, float yDiff, float zDiff)
{
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;

	for (int i = 0; i < vertexCount; i++) {
		modelData[i].px += xDiff;
		modelData[i].py += yDiff;
		modelData[i].pz += zDiff;

		//determine boundingBox
		if (modelData[i].px > maxX) { maxX = modelData[i].px; }
		if (modelData[i].py > maxY) { maxY = modelData[i].py; }
		if (modelData[i].pz > maxZ) { maxZ = modelData[i].pz; }
		if (modelData[i].px < minX) { minX = modelData[i].px; }
		if (modelData[i].py < minY) { minY = modelData[i].py; }
		if (modelData[i].pz < minZ) { minZ = modelData[i].pz; }
	}

	m_minPoint.x = minX;
	m_minPoint.y = minY;
	m_minPoint.z = minZ;
	m_maxPoint.x = maxX;
	m_maxPoint.y = maxY;
	m_maxPoint.z = maxZ;

	InitializeBuffers();
}

void StandardModel::scaleAndTranslateModel(float xScale, float yScale, float zScale, float xDiff, float yDiff, float zDiff)
{
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;

	for (int i = 0; i < vertexCount; i++) {
		modelData[i].px = modelData[i].px * xScale + xDiff;
		modelData[i].py = modelData[i].py * yScale + yDiff;
		modelData[i].pz = modelData[i].pz * zScale + zDiff;

		//determine boundingBox
		if (modelData[i].px > maxX) { maxX = modelData[i].px; }
		if (modelData[i].py > maxY) { maxY = modelData[i].py; }
		if (modelData[i].pz > maxZ) { maxZ = modelData[i].pz; }
		if (modelData[i].px < minX) { minX = modelData[i].px; }
		if (modelData[i].py < minY) { minY = modelData[i].py; }
		if (modelData[i].pz < minZ) { minZ = modelData[i].pz; }
	}

	m_minPoint.x = minX;
	m_minPoint.y = minY;
	m_minPoint.z = minZ;
	m_maxPoint.x = maxX;
	m_maxPoint.y = maxY;
	m_maxPoint.z = maxZ;

	InitializeBuffers();
}