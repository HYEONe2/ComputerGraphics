#include "inputclass.h"

InputClass::InputClass()
{
	m_InputSDK = 0;
	m_KeyBoard = 0;
	m_Mouse = 0;
}

InputClass::InputClass(const InputClass& other)
{
}

InputClass::~InputClass()
{
}

void InputClass::Initialize()
{
	int i;
	// Initialize all the keys to being released and not pressed.
	for (i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}
	return;
}

bool InputClass::ReadyInputDevice(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	m_screenWidth = screenWidth; 
	m_screenHeight = screenHeight;
	
	m_mouseX = 0; 
	m_mouseY = 0;

	if (DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_InputSDK,	NULL))
		return false;

	if (m_InputSDK->CreateDevice(GUID_SysKeyboard, &m_KeyBoard, nullptr))
		return false;

	m_KeyBoard->SetDataFormat(&c_dfDIKeyboard);

	m_KeyBoard->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	m_KeyBoard->Acquire();

	if (m_InputSDK->CreateDevice(GUID_SysMouse, &m_Mouse, nullptr))
		return false;

	m_Mouse->SetDataFormat(&c_dfDIMouse);

	m_Mouse->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	m_Mouse->Acquire();

	return true;
}

void InputClass::SetInputDev(void)
{
	if (nullptr == m_KeyBoard ||
		nullptr == m_Mouse)
		return;

	m_KeyBoard->GetDeviceState(256, m_byKeyState);
	m_Mouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}

void InputClass::ShutDown()
{
	if (m_Mouse)
	{
		m_Mouse->Unacquire();
		m_Mouse->Release();
		m_Mouse = 0;
	}

	if (m_KeyBoard)
	{
		m_KeyBoard->Unacquire();
		m_KeyBoard->Release();
		m_KeyBoard = 0;
	}
	
	if(m_InputSDK) 
	{
		m_InputSDK->Release();
		m_InputSDK = 0;
	} 
	
	return;
}

bool InputClass::GetDIKeyState(unsigned char byKeyID)
{
	if (m_byKeyState[byKeyID] & 0x8000)
		return true;

	return false;
}

bool InputClass::OnceKeyDown(unsigned char byKeyID)
{
	if (m_byKeyState[byKeyID] & 0x8000)
	{
		if (m_bKeyDown[byKeyID] == false)
		{
			m_bKeyDown[byKeyID] = true;
			return true;
		}
	}

	else
	{
		m_bKeyDown[byKeyID] = false;
	}

	return false;
}

signed char InputClass::GetDIMouseState(MOUSEKEYSTATE eMouse)
{
	return m_tMouseState.rgbButtons[eMouse];
}

long InputClass::GetDIMouseMove(MOUSEMOVESTATE eMouseState)
{
	return *(((signed long*)&m_tMouseState) + eMouseState);
}

void InputClass::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
	return;
}

void InputClass::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
	return;
}

bool InputClass::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
}