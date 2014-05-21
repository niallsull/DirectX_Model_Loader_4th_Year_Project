#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>
#include <d3dx11tex.h>
#include <string>
using namespace std;

class Texture
{
public:
	Texture(void);
	~Texture(void);
	bool Initialize(ID3D11Device*, WCHAR*);
	bool Initialize(ID3D11Device*, string);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

	ID3D11ShaderResourceView* m_texture;
};

#endif
