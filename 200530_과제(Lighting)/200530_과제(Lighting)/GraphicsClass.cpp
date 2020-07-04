#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_TextureShader = 0;
	m_Bitmap = 0; 
	m_LightShader = 0;
	m_Light = 0;
	m_Text = 0;

	m_Plane = 0;
	m_GnarModel = 0;
	m_MonokumaModel = 0;
	m_EvelynnModel = 0;

	for (int i = 0; i < 3; ++i)
		Light[i] = false;
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
	int iPolyCnt = 0;

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
	m_Camera->SetPosition(0.0f, 1.5f, -15.0f);

	D3DXMATRIX baseViewMatrix;
	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the plane object.
	m_Plane = new ModelClass;
	result = m_Plane->InitializeForPlane(m_D3D->GetDevice(), L"../Engine/data/Plane/PlaneTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	// Create the model object.
	m_GnarModel = new ModelClass;
	if (!m_GnarModel)
	{
		return false;
	}
	result = m_GnarModel->Initialize(m_D3D->GetDevice(), L"../Engine/data/Gnar/Gnar Super Galaxy.obj", L"../Engine/data/Gnar/Gnar_Skin13_TX_CM.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	m_MonokumaModel = new ModelClass;
	if (!m_MonokumaModel)
	{
		return false;
	}
	
	result = m_MonokumaModel->Initialize(m_D3D->GetDevice(), L"../Engine/data/Monokuma/Monokuma.obj", L"../Engine/data/Monokuma/kuma00_p4.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_EvelynnModel = new ModelClass;
	if (!m_EvelynnModel)
	{
		return false;
	}
	result = m_EvelynnModel->Initialize(m_D3D->GetDevice(), L"../Engine/data/Evelynn/Evelynn KDA.obj", L"../Engine/data/Evelynn/Evelynn_Skin06_TX_CM.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	iPolyCnt += (m_Plane->GetVertexCount() / 3);
	iPolyCnt += (m_GnarModel->GetVertexCount() / 3);
	iPolyCnt += (m_MonokumaModel->GetVertexCount() / 3);
	iPolyCnt += (m_EvelynnModel->GetVertexCount() / 3);

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

	//// Create the bitmap object.
	//m_Bitmap = new BitmapClass;
	//if (!m_Bitmap)
	//{
	//	return false;
	//}
	//// Initialize the bitmap object.
	//result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
	//	L"../Engine/data/seafloor.dds", 256, 256);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}
	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth,
		screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}
	// Set the Vertex .
	result = m_Text->SetSentence(iPolyCnt, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}
	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	m_Light->SetDirection(0.f, -1.f, 0.f);
	m_Light->SetAmbientColor(0, 0, 0, 0);
	m_Light->SetDiffuseColor(0, 0, 0, 0);
	m_Light->SetSpecularColor(0, 0, 0, 0);
	m_Light->SetSpecularPower(99999999.f);

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

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if (m_Plane)
	{
		m_Plane->Shutdown();
		delete m_Plane;
		m_Plane = 0;
	}
	if (m_GnarModel)
	{
		m_GnarModel->Shutdown();
		delete m_GnarModel;
		m_GnarModel = 0;
	}
	// Release the model object.
	if (m_MonokumaModel)
	{
		m_MonokumaModel->Shutdown();
		delete m_MonokumaModel;
		m_MonokumaModel = 0;
	}
	// Release the model object.
	if (m_EvelynnModel)
	{
		m_EvelynnModel->Shutdown();
		delete m_EvelynnModel;
		m_EvelynnModel = 0;
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

	//if (m_InputClass)
	//{
	//	m_InputClass->ShutDown();
	//	delete m_InputClass;
	//	m_InputClass = 0;
	//}

	return;
}

bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;

	static float rotation = 0.0f;
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.0005f * frameTime;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	
	result = m_Text->SetAmbient(Light[0], m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	result = m_Text->SetDiffuse(Light[1], m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	result = m_Text->SetSpecular(Light[2], m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
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

void GraphicsClass::SetInputClass(InputClass * InputClass)
{
	m_InputClass = InputClass;
}

void GraphicsClass::MoveCamera(float frametime)
{
	if (!m_InputClass)
		return;

	if (m_InputClass->GetDIKeyState(DIK_W))
	{
		m_Camera->MoveCamera(CameraClass::MOVE_FORWARD, frametime);
	}
	
	if (m_InputClass->GetDIKeyState(DIK_S))
	{
		m_Camera->MoveCamera(CameraClass::MOVE_BACKWARD, frametime);
	}

	if (m_InputClass->GetDIKeyState(DIK_A))
	{
		m_Camera->MoveCamera(CameraClass::MOVE_LEFT, frametime);
	}

	if (m_InputClass->GetDIKeyState(DIK_D))
	{
		m_Camera->MoveCamera(CameraClass::MOVE_RIGHT, frametime);
	}

	signed long	MouseMove = 0;

	if (MouseMove = m_InputClass->GetDIMouseMove(InputClass::DIMM_X))
	{
		m_Camera->MoveCamera(CameraClass::MOVE_MOUSEX, frametime, MouseMove);
	}

	if (MouseMove = m_InputClass->GetDIMouseMove(InputClass::DIMM_Y))
	{
		m_Camera->MoveCamera(CameraClass::MOVE_MOUSEY, frametime, MouseMove);
	}

}

void GraphicsClass::TurnLightOnOff()
{
	if (m_InputClass->OnceKeyDown(DIK_1))
	{
		if (Light[0])
			m_Light->SetAmbientColor(0.f, 0.f, 0.f, 0.f);
		
		else if (!Light[0])
			m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.f);
		
		Light[0] = !Light[0];
	}

	if (m_InputClass->OnceKeyDown(DIK_2))
	{
		if (Light[1])
			m_Light->SetDiffuseColor(0.f, 0.f, 0.f, 0.f);

		else if (!Light[1])
			m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
		
		Light[1] = !Light[1];
	}

	if (m_InputClass->OnceKeyDown(DIK_3))
	{
		if (Light[2])
		{
			m_Light->SetSpecularColor(0.f, 0.f, 0.f, 0.f);
			m_Light->SetSpecularPower(99999999.f);
		}

		else if (!Light[2])
		{
			m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_Light->SetSpecularPower(32.f);
		}
		Light[2] = !Light[2];
	}
}

bool GraphicsClass::Render()
{
	// Clear the buffers to begin the scene.  
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, orthoMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 200, 200);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
		worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_GnarModel->Render(m_D3D->GetDeviceContext());
	m_MonokumaModel->Render(m_D3D->GetDeviceContext());
	m_EvelynnModel->Render(m_D3D->GetDeviceContext());

	//// Render the model using the color shader.
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix,
	//	viewMatrix, projectionMatrix);

	//// Render the model using the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(),
	//	worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_GnarModel->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_GnarModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_MonokumaModel->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_MonokumaModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_EvelynnModel->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_EvelynnModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.  
	m_D3D->EndScene(); 
	
	return true;
}

bool GraphicsClass::Render(float rotation) 
{
	// Clear the buffers to begin the scene.  
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, orthoMatrix, planeMatrix;
	D3DXMATRIX matScale, matRot, matTrans;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	D3DXMatrixScaling(&matScale, 20.f, 20.f, 20.f);
	D3DXMatrixRotationX(&matRot, float(D3DXToRadian(90.f)));
	planeMatrix = matScale * matRot;

	m_Plane->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Plane->GetIndexCount(), planeMatrix,
		viewMatrix, projectionMatrix, m_Plane->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationY(&matRot, -rotation);
	D3DXMatrixTranslation(&matTrans, -2.5f, 0.f, -5.f);
	worldMatrix = matScale * matRot * matTrans;

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_GnarModel->Render(m_D3D->GetDeviceContext());
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_GnarModel->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_GnarModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	D3DXMatrixScaling(&matScale, 0.7f, 0.7f, 0.7f);
	D3DXMatrixRotationY(&matRot, -rotation);
	D3DXMatrixTranslation(&matTrans, 1.f, 0.f, -10.f);
	worldMatrix = matScale * matRot * matTrans;

	m_MonokumaModel->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_MonokumaModel->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_MonokumaModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}
	
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationY(&matRot, rotation * 2.f);
	D3DXMatrixTranslation(&matTrans, 0, 0.f, 1.f);
	worldMatrix = matScale * matRot * matTrans;

	m_EvelynnModel->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_EvelynnModel->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_EvelynnModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	RenderText();

	// Present the rendered scene to the screen.  
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderText()
{
	bool result;

	D3DXMATRIX worldMatrix, orthoMatrix;
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();
	
	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	return true;
}
