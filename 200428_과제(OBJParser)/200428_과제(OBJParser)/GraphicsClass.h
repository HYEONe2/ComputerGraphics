#pragma once

#include <windows.h>
#include "D3DClass.h"
#include <vector>

#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"
#include "TextureShaderClass.h"

// Globals
const bool FULL_SCREEN = false;
// 주사율을 맞춰주는 것
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
	
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	void Change_Filter(D3D11_FILTER eFilter);
private:
	bool Render();
	bool Render(float);
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	
	ModelClass* m_GnarModel;
	ModelClass* m_MonokumaModel;
	ModelClass* m_EvelynnModel;
	vector<ModelClass*> m_vecPlane;
};