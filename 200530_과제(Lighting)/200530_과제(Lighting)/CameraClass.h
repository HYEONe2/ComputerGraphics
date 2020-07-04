#pragma once

#include <d3dx10math.h>

class CameraClass
{
public:
	enum MOVE{MOVE_FORWARD, MOVE_BACKWARD, MOVE_LEFT, MOVE_RIGHT, MOVE_MOUSEX, MOVE_MOUSEY, MOVE_END};

public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void SetLookAt(float, float, float);
	void SetUp(float, float, float);
	void SetRight(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	void GetViewMatrix(D3DXMATRIX&);

	void MoveCamera(MOVE, float, signed long = 0);

	void Render();

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	float m_lookAtX, m_lookAtY, m_lookAtZ;
	float m_upX, m_upY, m_upZ;
	float m_rightX, m_rightY, m_rightZ;

	D3DXMATRIX m_viewMatrix;
};