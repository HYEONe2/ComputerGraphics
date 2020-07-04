#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

#include "TextureClass.h"

class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		//D3DXVECTOR4 color;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct ModelCount
	{
		int vertexCount;
		int textureCount;
		int normalCount;
		int faceCount;
	};
	struct OBJType
	{
		float x, y, z;
	};
	struct FaceType
	{
		int x, y, z;
		int tu, tv, tz;
		int nx, ny, nz;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*);
	bool Initialize(ID3D11Device*, WCHAR*);
	bool Initialize(ID3D11Device*, char*, WCHAR*); 
	// obj model
	bool Initialize(ID3D11Device*, WCHAR*, WCHAR*);
	// Terrain model
	bool InitializeForPlane(ID3D11Device*, WCHAR*);

	ID3D11ShaderResourceView* GetTexture();
	int GetVertexCount();
	int GetIndexCount();

private:
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();
	bool LoadModel(char*);
	void ReleaseModel(); 

public:
	void Shutdown();
	void Render(ID3D11DeviceContext*);

private:
	bool InitializeBuffers(ID3D11Device*);
	bool InitializeBuffersForPlane(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	bool LoadOBJModel(WCHAR*);
	bool ReadFileCounts(WCHAR*, ModelCount&);
	bool LoadDataStructures(WCHAR*, ModelCount);


private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

private:
	TextureClass* m_Texture;
	ModelType* m_model;
};