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

private:
	bool Render();
	bool Render(float);
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	TextClass* m_Text;
};