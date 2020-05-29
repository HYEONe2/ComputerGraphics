#include "ModelClass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ModelClass::ModelClass(const ModelClass& other)
{
}

ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, SHAPE eShape)
{
	bool result;
	// Initialize the vertex and index buffer that hold the geometry for the triangle.

	m_eShape = eShape;

	switch (eShape)
	{
	case SHAPE_TRI:
		result = InitializeBuffers(device);
		break;
	case SHAPE_RECT:
		result = InitializeRectangle(device);
		break;
	case SHAPE_PENTAGON:
		result = InitializePentagon(device);
		break;
	case SHAPE_HEXAGON:
		result = InitializeHexagon(device);
		break;
	case SHAPE_END:
		result = InitializeBuffers(device);
		break;
	}
	if (!result)
	{
		return false;
	}
	return true;
}

void ModelClass::Shutdown()
{
	// Release the vertex and index buffers.
	ShutdownBuffers();
	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);
	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

D3DXMATRIX ModelClass::Get_WorldMatrix()
{
	return m_matWorld;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 3;
	// Set the number of indices in the index array.
	m_indexCount = 3;
	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); // Bottom left.
	vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // Top middle.
	vertices[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f); // Bottom right.
	vertices[2].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	// Load the index array with data.
	indices[0] = 0; // Bottom left.
	indices[1] = 1; // Top middle.
	indices[2] = 2; // Bottom right.

					// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;
	return true;
}

bool ModelClass::InitializeRectangle(ID3D11Device * device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 4;
	// Set the number of indices in the index array.
	m_indexCount = 6;
	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); // Bottom left.
	vertices[0].color = D3DXVECTOR4(1.f, 1.0f, 0.0f, 1.0f);
	vertices[1].position = D3DXVECTOR3(-1.f, 1.0f, 0.0f); // Top left.
	vertices[1].color = D3DXVECTOR4(1.f, 0.0f, 1.0f, 1.0f);
	vertices[2].position = D3DXVECTOR3(1.f, 1.0f, 0.0f); // Top right.
	vertices[2].color = D3DXVECTOR4(0.f, 1.0f, 1.0f, 1.0f);
	vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f); // Bottom right.
	vertices[3].color = D3DXVECTOR4(1.f, 1.0f, 1.0f, 1.0f);
	// Load the index array with data.
	indices[0] = 0; // Bottom left.
	indices[1] = 1; // Top middle.
	indices[2] = 2; // Bottom right.
	indices[3] = 0; // Bottom left.
	indices[4] = 2; // Top middle.
	indices[5] = 3; // Bottom right.

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;

	return true;
}

bool ModelClass::InitializePentagon(ID3D11Device * device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 6;
	// Set the number of indices in the index array.
	m_indexCount = 15;
	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(-0.85f, 0.0f, 0.0f);
	vertices[0].color = D3DXVECTOR4(1.f, 1.0f, 0.0f, 1.0f);
	vertices[1].position = D3DXVECTOR3(0.f, 0.75f, 0.0f); 
	vertices[1].color = D3DXVECTOR4(1.f, 0.0f, 1.0f, 1.0f);
	vertices[2].position = D3DXVECTOR3(0.f, 0.0f, 0.0f);
	vertices[2].color = D3DXVECTOR4(0.f, 1.0f, 1.0f, 1.0f);
	vertices[3].position = D3DXVECTOR3(0.85f, 0.0f, 0.0f); 
	vertices[3].color = D3DXVECTOR4(0.f, 1.0f, 1.0f, 1.0f);
	vertices[4].position = D3DXVECTOR3(0.45f, -0.825f, 0.0f);
	vertices[4].color = D3DXVECTOR4(0.f, 0.0f, 0.0f, 1.0f);
	vertices[5].position = D3DXVECTOR3(-0.45f, -0.825f, 0.0f);
	vertices[5].color = D3DXVECTOR4(1.f, 1.0f, 1.0f, 1.0f);

	// Load the index array with data.
	indices[0] = 0; 
	indices[1] = 1; 
	indices[2] = 2; 
	indices[3] = 2; 
	indices[4] = 1; 
	indices[5] = 3; 
	indices[6] = 4; 
	indices[7] = 2; 
	indices[8] = 3;
	indices[9] = 5;
	indices[10] = 2;
	indices[11] = 4;
	indices[12] = 0;
	indices[13] = 2;
	indices[14] = 5;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;

	return true;
}

bool ModelClass::InitializeHexagon(ID3D11Device * device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 7;
	// Set the number of indices in the index array.
	m_indexCount = 18;
	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // Bottom left.
	vertices[0].color = D3DXVECTOR4(1.f, 1.0f, 1.0f, 1.0f);
	vertices[1].position = D3DXVECTOR3(-1.f, 0.0f, 0.0f); // Top left.
	vertices[1].color = D3DXVECTOR4(1.f, 1.0f, 1.0f, 1.0f);
	vertices[2].position = D3DXVECTOR3(-0.5f, 0.87f, 0.0f); // Top right.
	vertices[2].color = D3DXVECTOR4(1.f, 1.0f, 1.0f, 1.0f);
	vertices[3].position = D3DXVECTOR3(0.5f, 0.87f, 0.0f); // Bottom right.
	vertices[3].color = D3DXVECTOR4(1.f, 1.0f, 1.0f, 1.0f);
	vertices[4].position = D3DXVECTOR3(1.f, 0.0f, 0.0f); // Bottom right.
	vertices[4].color = D3DXVECTOR4(1.f, 1.0f, 1.0f, 1.0f);
	vertices[5].position = D3DXVECTOR3(0.5f, -0.87f, 0.0f); // Bottom right.
	vertices[5].color = D3DXVECTOR4(1.f, 1.0f, 1.0f, 1.0f);
	vertices[6].position = D3DXVECTOR3(-0.5f, -0.87f, 0.0f); // Bottom right.
	vertices[6].color = D3DXVECTOR4(1.f, 1.0f, 1.0f, 1.0f);
	// Load the index array with data.
	indices[0] = 0; // Bottom left.
	indices[1] = 1; // Top middle.
	indices[2] = 2; // Bottom right.
	indices[3] = 0; // Bottom left.
	indices[4] = 2; // Top middle.
	indices[5] = 3; // Bottom right.
	indices[6] = 0; // Bottom left.
	indices[7] = 3; // Top middle.
	indices[8] = 4; // Bottom right.
	indices[9] = 0; // Bottom left.
	indices[10] = 4; // Top middle.
	indices[11] = 5; // Bottom right.
	indices[12] = 0; // Bottom left.
	indices[13] = 5; // Top middle.
	indices[14] = 6; // Bottom right.
	indices[15] = 0; // Bottom left.
	indices[16] = 6; // Top middle.
	indices[17] = 1; // Bottom right.
// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;

	return true;
}

void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;
	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

void ModelClass::Make_RotateWorld()
{
	m_vecRotate.x += 0.05f;
	m_vecRotate.y += 0.05f;
	m_vecRotate.z += 0.05f;

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixRotationX(&m_matWorld, m_vecRotate.x);
	D3DXMatrixRotationY(&m_matWorld, m_vecRotate.y);
	D3DXMatrixRotationZ(&m_matWorld, m_vecRotate.z);
	
	switch (m_eShape)
	{
	case ModelClass::SHAPE_TRI:
		break;
	case ModelClass::SHAPE_RECT:
		break;
	case ModelClass::SHAPE_PENTAGON:
		m_matWorld._41 = -2.f;
		m_matWorld._42 = -1.5f;
		break;
	case ModelClass::SHAPE_HEXAGON:
		m_matWorld._41 = 2.f;
		m_matWorld._42 = -1.5f;
		break;
	case ModelClass::SHAPE_END:
		break;
	default:
		break;
	}
}

void ModelClass::Make_ParentRotateWorld(D3DXMATRIX * matParent)
{
	m_matWorld *= *matParent;
}
