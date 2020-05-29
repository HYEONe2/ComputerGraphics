#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_ColorShader = 0;
	m_TextureShader = 0;

	m_GnarModel = 0;
	m_MonokumaModel = 0;
	m_EvelynnModel = 0;
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
	
	// Create the Direct3D object.  
	m_D3D = new D3DClass;  
	if(!m_D3D) 
	{ 
		return false;
	} 
					 
	// Initialize the Direct3D object.  
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);  
	if(!result)  
	{   
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);   
		return false;  
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}
	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	// Create the model object.
	m_GnarModel = new ModelClass;
	if (!m_GnarModel)
	{
		return false;
	}
	m_MonokumaModel = new ModelClass;
	if (!m_MonokumaModel)
	{
		return false;
	}
	m_EvelynnModel = new ModelClass;
	if (!m_EvelynnModel)
	{
		return false;
	}

	////result = m_Model->Initialize(m_D3D->GetDevice());
	//// Create the color shader object.
	//m_ColorShader = new ColorShaderClass;
	//if (!m_ColorShader)
	//{
	//	return false;
	//}
	// Initialize the color shader object.
	//result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
	//	return false;
	//}

	// Initialize the model object.
	////result = m_Model->Initialize(m_D3D->GetDevice(), L"../Engine/data/seafloor.dds");
	//result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/Cube.txt", L"../Engine/data/seafloor.dds");

	result = m_GnarModel->Initialize(m_D3D->GetDevice(), L"../Engine/data/Gnar/Gnar Super Galaxy.obj", L"../Engine/data/Gnar/Gnar_Skin13_TX_CM.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_MonokumaModel->Initialize(m_D3D->GetDevice(), L"../Engine/data/Monokuma/Monokuma.obj", L"../Engine/data/Monokuma/kuma00_p4.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	result = m_EvelynnModel->Initialize(m_D3D->GetDevice(), L"../Engine/data/Evelynn/Evelynn KDA.obj", L"../Engine/data/Evelynn/Evelynn_Skin06_TX_CM.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	for (int i = 0; i < 125; ++i)
	{
		ModelClass* PlaneModel = new ModelClass;
		result = PlaneModel->InitializeForPlane(m_D3D->GetDevice(), L"../Engine/data/Plane/PlaneTexture.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

		m_vecPlane.push_back(PlaneModel);
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	//// Release the color shader object.
	//if (m_ColorShader)
	//{
	//	m_ColorShader->Shutdown();
	//	delete m_ColorShader;
	//	m_ColorShader = 0;
	//}
	
	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	if (m_GnarModel)
	{
		m_GnarModel->Shutdown();
		delete m_GnarModel;
		m_GnarModel = 0;
	}
	if (m_MonokumaModel)
	{
		m_MonokumaModel->Shutdown();
		delete m_MonokumaModel;
		m_MonokumaModel = 0;
	}	
	if (m_EvelynnModel)
	{
		m_EvelynnModel->Shutdown();
		delete m_EvelynnModel;
		m_EvelynnModel = 0;
	}
	if (m_vecPlane.size() != 0)
	{
		for (auto iter : m_vecPlane)
		{
			iter->Shutdown();
			delete iter;
			iter = 0;
		}
	}
	
	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	
	// Render the graphics scene. 
	//result = Render();  
	result = Render(rotation);
	if(!result)
	{ 
		return false; 
	} 
	
	return true;
}

bool GraphicsClass::Render()
{
	// Clear the buffers to begin the scene.  
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result = false;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// Render the model using the texture shader.
	//m_PlaneModel->Render(m_D3D->GetDeviceContext());
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_PlaneModel->GetIndexCount(),
	//	worldMatrix, viewMatrix, projectionMatrix, m_PlaneModel->GetTexture());
	if (!result)
	{
		return false;
	}

	//// Render the model using the color shader.
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix,
	//	viewMatrix, projectionMatrix);
	
	// Present the rendered scene to the screen.  
	m_D3D->EndScene(); 
	
	return true;
}

bool GraphicsClass::Render(float rotation) 
{
	// Clear the buffers to begin the scene.  
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;
	D3DXMATRIX matScale, matRot, matTrans;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->SetPosition(0, 0, -14.f);
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMatrixRotationX(&matRot, float(D3DXToRadian(80.f)));

	int iSize = m_vecPlane.size();
	iSize = int(sqrt(iSize));
	for (int i = 0; i < iSize; ++i)
	{
		for (int j = 0; j<iSize; ++j)
		{
			D3DXMatrixTranslation(&matTrans, j * 2.f - 10.f, -2.f + (0.34f* i), i*2.f -8.f);
			worldMatrix = matRot * matTrans;

			m_vecPlane[i]->Render(m_D3D->GetDeviceContext());
			result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_vecPlane[i]->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix, m_vecPlane[i]->GetTexture());
			if (!result)
			{
				return false;
			}
		}
	}
	
	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationY(&matRot, -rotation);
	D3DXMatrixTranslation(&matTrans, -2.5f, -1.5f, -5.f);
	worldMatrix = matScale * matRot * matTrans;

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//Render the model using the texture shader.
	m_GnarModel->Render(m_D3D->GetDeviceContext());
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_GnarModel->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_GnarModel->GetTexture());
	if (!result)
	{
		return false;
	}

	D3DXMatrixScaling(&matScale, 0.7f, 0.7f, 0.7f);
	D3DXMatrixRotationY(&matRot, -rotation);
	D3DXMatrixTranslation(&matTrans, 1.f, -1.f, -10.f);
	worldMatrix = matScale * matRot * matTrans;

	m_MonokumaModel->Render(m_D3D->GetDeviceContext());
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_MonokumaModel->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_MonokumaModel->GetTexture());
	if (!result)
	{
		return false;
	}

	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationY(&matRot, rotation * 2.f);
	D3DXMatrixTranslation(&matTrans, 0, 0, 1.f);
	worldMatrix = matScale * matRot * matTrans;

	m_EvelynnModel->Render(m_D3D->GetDeviceContext());
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_EvelynnModel->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_EvelynnModel->GetTexture());
	if (!result)
	{
		return false;
	}

	//// Render the model using the color shader.
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix,
	//	viewMatrix, projectionMatrix);

	// Present the rendered scene to the screen.  
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::Change_Filter(D3D11_FILTER eFilter)
{
	ID3D11SamplerState* pSamplerState;
	pSamplerState = m_TextureShader->Get_SamplerState();

	D3D11_SAMPLER_DESC samplerDesc;
	pSamplerState->GetDesc(&samplerDesc);

	samplerDesc.Filter = eFilter;
	if (eFilter == D3D11_FILTER_ANISOTROPIC)
		samplerDesc.MaxAnisotropy = 16;
	else
		samplerDesc.MaxAnisotropy = 1;

	m_D3D->GetDevice()->CreateSamplerState(&samplerDesc, &pSamplerState);
	m_TextureShader->Set_SamplerState(pSamplerState);
}