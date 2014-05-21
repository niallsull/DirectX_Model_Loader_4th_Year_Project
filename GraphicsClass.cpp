////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_MultiTextureShader = 0;
	m_BumpMapShader = 0;
	m_MaterialShader=0;
	m_Input=0;

}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	OBJParser parser=OBJParser("SkyTownTrees");
	
	string model;
	model=parser.Parse();

	models=ModelCollection(model);

	models.ParseModelData();

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	m_Input->Initialize();

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, false, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	//m_Model = new Model;
	//if(!m_Model)
	//{
	//	return false;
	//}

	////// Initialize the model object.
	//result = m_Model->Initialize(m_D3D->GetDevice(), "realTest.txt", L"boxTextured.dds");
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 3.0f, -40.0f);
	m_Camera->SetPosition(0.0f, 3.0f, -50.0f);
	m_Camera->SetLookAt(0.0f,0.0f,1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);
	

	for(int i=0;i<models.modelMeshes.size();i++)
	{
		result=models.modelMeshes.at(i)->Initialize(m_D3D->GetDevice());
		if(!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}

	

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}
//

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	//m_Light->SetDiffuseColor(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light->SetDiffuseColor(0.7f, 0.7f, 0.7f, 1.0f);
	m_Light->SetAmbientColor(0.7f, 0.7f, 0.7f, 1.0f);
	m_Light->SetDirection(0.0f, 1.0f, -1.0f);


	// Create the bump map shader object.
	m_BumpMapShader = new BumpMapShaderClass;
	if(!m_BumpMapShader)
	{
		return false;
	}

	// Initialize the bump map shader object.
	result = m_BumpMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}


	m_MaterialShader = new MaterialShader;
	if(!m_MaterialShader)
	{
		return false;
	}

	// Initialize the bump map shader object.
	result = m_MaterialShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}
	/*
	// Create the multitexture shader object.
	m_MultiTextureShader = new MultiTextureShaderClass;
	if(!m_MultiTextureShader)
	{
		return false;
	}

	// Initialize the multitexture shader object.
	result = m_MultiTextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the multitexture shader object.", L"Error", MB_OK);
		return false;
	}
	*/
	return true;
}


void GraphicsClass::Shutdown()
{

	if(m_MaterialShader)
	{
		m_MaterialShader->Shutdown();
		delete m_MaterialShader;
		m_MaterialShader = 0;
	}

	// Release the bump map shader object.
	if(m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	// Release the multitexture shader object.
	if(m_MultiTextureShader)
	{
		m_MultiTextureShader->Shutdown();
		delete m_MultiTextureShader;
		m_MultiTextureShader = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	for(int i=0;i<models.modelMeshes.size();i++)
	{
		models.modelMeshes.at(i)->Shutdown();
		delete models.modelMeshes.at(i);
		models.modelMeshes.at(i)=0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}


	if(m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}


	return;
}


bool GraphicsClass::Frame(float r,int s,int view,int& change)
{
	bool result;
	if(change==1)
	{
		if(view==0)
		{
			m_Camera->SetPosition(0.0f,3.0f,-40.0f);
			m_Camera->SetLookAt(0.0f,0.0f,1.0f);
		}

		if(view==1)
		{
			m_Camera->SetPosition(-10.0f,3.0f,10.0f);
			m_Camera->SetLookAt(1.0f,0.0f,-1.0f);
		}

		if(view==2)
		{
			m_Camera->SetPosition(-70.0f,40.0f,-70.0f);
			m_Camera->SetLookAt(1.0f,-0.5f,1.0f);
		}

		if(view==3)
		{
			m_Camera->SetPosition(20.0f,1.0f,0.0f);
			m_Camera->SetLookAt(-1.0f,0.0f,0.0f);
		}

		
		if(view==4)
		{
			m_Camera->SetPosition(100.0f,100.0f,-100.0f);
			m_Camera->SetLookAt(-1.0f,-1.0f,1.0f);
		}


		if(view==5)
		{
			m_Camera->SetPosition(20.0f,1.5f,-20.0f);
			m_Camera->SetLookAt(-1.0f,0.0f,1.0f);
		}
		change=0;
	}

	
	// Update the rotation variable each frame.
	//rotation += (float)D3DX_PI * 0.001f;
	if(r > 360.0f)
	{
		r -= 360.0f;
	}
	
	// Render the graphics scene.
	result = Render(r,s);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation,int shader)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMatrixRotationY(&worldMatrix, rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model->Render(m_D3D->GetDeviceContext());
	
	//models.modelMeshes.at(1)->Render(m_D3D->GetDeviceContext());
	
	if(shader==0){
	for(int i=0;i<models.modelMeshes.size();i++)
	{
		models.modelMeshes.at(i)->Render(m_D3D->GetDeviceContext());
		m_BumpMapShader->Render(m_D3D->GetDeviceContext(), models.modelMeshes.at(i)->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			models.modelMeshes.at(i)->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(),m_Light->GetAmbientColor());
	}
	}

	if(shader==1){
	for(int i=0;i<models.modelMeshes.size();i++)
	{
		models.modelMeshes.at(i)->Render(m_D3D->GetDeviceContext());
		m_LightShader->Render(m_D3D->GetDeviceContext(),models.modelMeshes.at(i)->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
								   models.modelMeshes.at(i)->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	}
	}

	if(shader==2){
	for(int i=0;i<models.modelMeshes.size();i++)
	{
		models.modelMeshes.at(i)->Render(m_D3D->GetDeviceContext());
		m_MaterialShader->Render(m_D3D->GetDeviceContext(),models.modelMeshes.at(i)->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
			models.modelMeshes.at(i)->getDiffuseColor(),models.modelMeshes.at(i)->getAmbientColor(),models.modelMeshes.at(i)->getSpecularColor());
	}
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
