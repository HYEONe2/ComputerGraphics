#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

class ModelClass
{
public:
	enum SHAPE {SHAPE_TRI, SHAPE_RECT, SHAPE_PENTAGON, SHAPE_HEXAGON, SHAPE_END};
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};
public:
	int GetIndexCount();
	D3DXMATRIX Get_WorldMatrix();

	void Make_RotateWorld();
	void Make_ParentRotateWorld(D3DXMATRIX*);
public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, SHAPE = SHAPE_END);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
private:
	bool InitializeBuffers(ID3D11Device*);
	bool InitializeRectangle(ID3D11Device*);
	bool InitializePentagon(ID3D11Device*);
	bool InitializeHexagon(ID3D11Device*);

	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	SHAPE m_eShape = SHAPE_END;
	D3DXMATRIX m_matWorld;
	D3DXVECTOR3 m_vecRotate;
};