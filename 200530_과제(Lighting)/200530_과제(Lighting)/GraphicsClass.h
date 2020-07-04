#pragma once

#include <windows.h>
#include "D3DClass.h"

#include "TextClass.h"
#include "BitmapClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"
#include "TextureShaderClass.h"
#include "LightShaderClass.h"
#include "InputClass.h"
#include "LightClass.h"
// Globals
const bool FULL_SCREEN = false;
// 주사율을 맞춰주는 것
const bool VSYNC_ENABLED = false; 
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
	bool Frame(int, int, float);

	void SetInputClass(InputClass*);
	void MoveCamera(float);
	void TurnLightOnOff();

private:
	bool Render();
	bool Render(float);	bool RenderText();
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	TextClass* m_Text;
	InputClass* m_InputClass;

	ModelClass* m_Plane;
	ModelClass* m_GnarModel;
	ModelClass* m_MonokumaModel;
	ModelClass* m_EvelynnModel;

private:
	bool Light[3];
};