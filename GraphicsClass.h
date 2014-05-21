////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "Model.h"
#include "lightshaderclass.h"
#include "bumpmapshaderclass.h"
#include "MaterialShader.h"
#include "lightclass.h"
#include "ModelCollection.h"
#include "OBJParser.h"
#include "multitextureshaderclass.h"
#include "InputClass.h"
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(float,int,int,int&);
	ModelCollection models;

private:
	bool Render(float,int);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	Model* m_Model;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	MultiTextureShaderClass* m_MultiTextureShader;
	BumpMapShaderClass* m_BumpMapShader;
	MaterialShader* m_MaterialShader;
	InputClass* m_Input;
	
};

#endif
