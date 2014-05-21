////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include <string>
using namespace std;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "Texture.h"
#include "TextureArrayClass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class Model
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 binormal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VectorType
	{
		float x, y, z;
	};


public:
	Model();
	Model(string);
	Model(const Model&);
	~Model();

	bool Initialize(ID3D11Device*, char*, WCHAR*,WCHAR*);
	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void setNumVerts(int);
	string textureName,textureName2;
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	ID3D11ShaderResourceView** GetTextureArray();
	ModelType* m_model;

	void setDiffuseColor(float,float,float);
	void setAmbientColor(float,float,float);
	void setSpecularColor(float,float,float);
	void setColorType(float,float,float,float);

	D3DXVECTOR4 getDiffuseColor();
	D3DXVECTOR4 getAmbientColor();
	D3DXVECTOR4 getSpecularColor();
	D3DXVECTOR4	getColorType();

	void setTexture();
	void setDisplacement();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*,WCHAR*);
	bool LoadTexture(ID3D11Device*,string, string);
	void ReleaseTextures();

	bool LoadModel(char*);
	void ReleaseModel();

	void CalculateModelVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);
	void CalculateNormal(VectorType, VectorType, VectorType&);

	D3DXVECTOR4 ambientColor;
	D3DXVECTOR4 diffuseColor;
	D3DXVECTOR4 specularColor;

	D3DXVECTOR4 ColorType;  // use material? , use bump  ( diff text, bump text, material)

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureArrayClass* m_TextureArray;
	Texture* m_Texture;
};

#endif
