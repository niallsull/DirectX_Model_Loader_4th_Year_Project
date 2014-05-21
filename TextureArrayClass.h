////////////////////////////////////////////////////////////////////////////////
// Filename: texturearrayclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTUREARRAYCLASS_H_
#define _TEXTUREARRAYCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx11tex.h>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: TextureArrayClass
////////////////////////////////////////////////////////////////////////////////
class TextureArrayClass
{
public:
	TextureArrayClass();
	TextureArrayClass(const TextureArrayClass&);
	~TextureArrayClass();

	bool Initialize(ID3D11Device*, WCHAR*, WCHAR*);
	bool Initialize(ID3D11Device*, string, string);
	void Shutdown();

	ID3D11ShaderResourceView** GetTextureArray();

private:


	ID3D11ShaderResourceView* m_textures[2];
};

#endif
