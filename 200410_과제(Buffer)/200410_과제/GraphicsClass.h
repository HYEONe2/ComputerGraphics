#pragma once

#include <windows.h>
#include "D3DClass.h"

#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	void Set_BackColor(D3DXVECTOR4 vColor);
	void Move_CameraPos(D3DXVECTOR3 vPos);
	void SetRenderState(bool);

public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
private:
	bool Render();
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ModelClass* m_RectModel;
	ModelClass* m_PentagonModel;
	ModelClass* m_HexagonModel;
	ColorShaderClass* m_ColorShader;

	D3DXVECTOR4 m_vBackColor;
};