#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "InputClass.h"
#include "graphicsclass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();
	bool Initialize();
	void Shutdown();
	void Run();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	bool KeyInput();

private:
	LPCSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	InputClass* m_Input;
	GraphicsClass* m_Graphics;
};// Function prototypes
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// Globals
static SystemClass* ApplicationHandle = 0;