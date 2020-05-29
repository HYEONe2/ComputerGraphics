#include "GraphicsClass.h"

void GraphicsClass::Set_BackColor(D3DXVECTOR4 vColor)
{
	m_vBackColor = vColor;
}

void GraphicsClass::Move_CameraPos(D3DXVECTOR3 vPos)
{
	D3DXVECTOR3 vOriginPos = m_Camera->GetPosition();
	m_Camera->SetPosition(vOriginPos.x + vPos.x, vOriginPos.y + vPos.y, vOriginPos.z + vPos.z);
}

void GraphicsClass::SetRenderState(bool bIsSolid)
{
	ID3D11RasterizerState* pRasterState;
	m_D3D->GetDeviceContext()->RSGetState(&pRasterState);
	
	D3D11_RASTERIZER_DESC rasterDesc;
	pRasterState->GetDesc(&rasterDesc);

	if (bIsSolid)
		rasterDesc.FillMode = D3D11_FILL_SOLID;
	else
		rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
	
	m_D3D->GetDevice()->CreateRasterizerState(&rasterDesc, &pRasterState);
	m_D3D->GetDeviceContext()->RSSetState(pRasterState);
}

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_ColorShader = 0;
	m_vBackColor = { 0.f,0.f,0.f,1.f };
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
		MessageBox(hwnd, "Could not initialize Direct3D", "Error", MB_OK);   
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
	//m_Model = new ModelClass;
	//if (!m_Model)
	//{
	//	return false;
	//}
	m_RectModel = new ModelClass;
	if (!m_RectModel)
	{
		return false;
	}
	m_PentagonModel = new ModelClass;
	if (!m_PentagonModel)
	{
		return false;
	}
	m_HexagonModel = new ModelClass;
	if (!m_HexagonModel)
	{
		return false;
	}
	// Initialize the model object.
	//result = m_Model->Initialize(m_D3D->GetDevice());
	//if (!result)
	//{
	//	MessageBox(hwnd, "Could not initialize the model object.", "Error", MB_OK);
	//	return false;
	//}
	result = m_RectModel->Initialize(m_D3D->GetDevice(), ModelClass::SHAPE_RECT);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize the model object.", "Error", MB_OK);
		return false;
	}
	result = m_PentagonModel->Initialize(m_D3D->GetDevice(), ModelClass::SHAPE_PENTAGON);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize the model object.", "Error", MB_OK);
		return false;
	}
	result = m_HexagonModel->Initialize(m_D3D->GetDevice(), ModelClass::SHAPE_HEXAGON);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize the model object.", "Error", MB_OK);
		return false;
	}
	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}
	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize the color shader object.", "Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	if (m_D3D)
	{
		m_D3D->Shutdown();  
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}
	// Release the model object.
	//if (m_Model)
	//{
	//	m_Model->Shutdown();
	//	delete m_Model;
	//	m_Model = 0;
	//}
	if (m_RectModel)
	{
		m_RectModel->Shutdown();
		delete m_RectModel;
		m_RectModel = 0;
	}
	if (m_PentagonModel)
	{
		m_PentagonModel->Shutdown();
		delete m_PentagonModel;
		m_PentagonModel = 0;
	}
	if (m_HexagonModel)
	{
		m_HexagonModel->Shutdown();
		delete m_HexagonModel;
		m_HexagonModel = 0;
	}
	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	
	return;
}

bool GraphicsClass::Frame()
{
	bool result;
	
	// Render the graphics scene. 
	result = Render();  
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
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(m_vBackColor.x, m_vBackColor.y, m_vBackColor.z, m_vBackColor.w);
	
	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
	
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	//m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the color shader.
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix,
	//	viewMatrix, projectionMatrix);

	m_RectModel->Make_RotateWorld();
	worldMatrix = m_RectModel->Get_WorldMatrix();
	m_RectModel->Render(m_D3D->GetDeviceContext());
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_RectModel->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix);

	m_PentagonModel->Make_RotateWorld();
	m_PentagonModel->Make_ParentRotateWorld(&worldMatrix);
	worldMatrix = m_PentagonModel->Get_WorldMatrix();
	m_PentagonModel->Render(m_D3D->GetDeviceContext());
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_PentagonModel->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix);
	
	m_HexagonModel->Make_RotateWorld();
	m_HexagonModel->Make_ParentRotateWorld(&worldMatrix);
	worldMatrix = m_HexagonModel->Get_WorldMatrix();
	m_HexagonModel->Render(m_D3D->GetDeviceContext());
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_HexagonModel->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix);

	if (!result)
	{
		return false;
	}
	// Present the rendered scene to the screen.  
	m_D3D->EndScene(); 
	
	return true;
}