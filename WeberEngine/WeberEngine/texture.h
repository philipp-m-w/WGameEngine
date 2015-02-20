#pragma once

#include <d3d11.h>
#include <d3dx11tex.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: TextureClass
////////////////////////////////////////////////////////////////////////////////
class Texture
{
public:
	Texture(WCHAR* textureFilePath, ID3D11Device* device);
	Texture(const Texture&);
	~Texture();

	bool Initialize();
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* textureResource;
	ID3D11Device* device;
	WCHAR* textureFilePath;
};