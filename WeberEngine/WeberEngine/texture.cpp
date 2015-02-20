#include "texture.h"

Texture::Texture(WCHAR* textureFilePath, ID3D11Device* device):
				textureFilePath(textureFilePath),
				device(device)
{
	textureResource = 0;
}


Texture::Texture(const Texture& other)
{
}


Texture::~Texture()
{
}

bool Texture::Initialize()
{
	HRESULT result;

	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, textureFilePath, NULL, NULL, &textureResource, NULL);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Texture::Shutdown()
{
	// Release the texture resource.
	if (textureResource)
	{
		textureResource->Release();
		textureResource = 0;
	}

	return;
}

ID3D11ShaderResourceView* Texture::GetTexture()
{
	return textureResource;
}
