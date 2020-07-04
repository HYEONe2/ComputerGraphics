#include "CameraClass.h"

CameraClass::CameraClass()
{
	m_positionX = 0.f;
	m_positionY = 0.f;
	m_positionZ = 0.f;
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
	m_lookAtX = 0.0;
	m_lookAtY = 0.0;
	m_lookAtZ = 1.0;
	m_upX = 0.0f;
	m_upY = 1.0f;
	m_upZ = 0.0f;
}

CameraClass::CameraClass(const CameraClass& other)
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}
void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

void CameraClass::SetLookAt(float x, float y, float z)
{
	m_lookAtX = x;
	m_lookAtY = y;
	m_lookAtZ = z;
}

void CameraClass::SetUp(float x, float y, float z)
{
	m_upX = x;
	m_upY = y;
	m_upZ = z;
}

void CameraClass::SetRight(float x, float y, float z)
{
	m_rightX = x;
	m_rightY = y;
	m_rightZ = z;
}

D3DXVECTOR3 CameraClass::GetPosition()
{
	return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
}
D3DXVECTOR3 CameraClass::GetRotation()
{
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraClass::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = m_upX;
	up.y = m_upY;
	up.z = m_upZ;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;
	
	// Setup where the camera is looking by default.
	lookAt.x = m_lookAtX;
	lookAt.y = m_lookAtY;
	lookAt.z = m_lookAtZ;
	
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;
	
	D3DXVECTOR3 vRight;
	D3DXVec3Cross(&vRight, &D3DXVECTOR3(m_upX, m_upY, m_upZ), &D3DXVECTOR3(m_lookAtX, m_lookAtY, m_lookAtZ));
	m_rightX = vRight.x;
	m_rightY = vRight.y;
	m_rightZ = vRight.z;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	
	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;
	
	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);
	return;
}

void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

void CameraClass::MoveCamera(MOVE eMove, float frametime, signed long MouseMove)
{
	switch (eMove)
	{
	case MOVE_FORWARD:
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
		D3DXVECTOR3 vLook = D3DXVECTOR3(m_lookAtX, m_lookAtY, m_lookAtZ);

		vPos += *D3DXVec3Normalize(&vLook, &vLook) * frametime * 0.01f;

		SetPosition(vPos.x, vPos.y, vPos.z);
	}
		break;
	case MOVE_BACKWARD:
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
		D3DXVECTOR3 vLook = D3DXVECTOR3(m_lookAtX, m_lookAtY, m_lookAtZ);

		vPos -= *D3DXVec3Normalize(&vLook, &vLook) * frametime * 0.01f;

		SetPosition(vPos.x, vPos.y, vPos.z);
	}
		break;
	case MOVE_LEFT:
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
		D3DXVECTOR3 vRight = D3DXVECTOR3(m_rightX, m_rightY, m_rightZ);

		vPos -= *D3DXVec3Normalize(&vRight, &vRight) * frametime * 0.01f;

		SetPosition(vPos.x, vPos.y, vPos.z);
	}
		break;
	case MOVE_RIGHT:
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
		D3DXVECTOR3 vRight = D3DXVECTOR3(m_rightX, m_rightY, m_rightZ);

		vPos += *D3DXVec3Normalize(&vRight, &vRight) * frametime * 0.01f;

		SetPosition(vPos.x, vPos.y, vPos.z);
	}
		break;
	case MOVE_MOUSEX:
	{
		D3DXMATRIX	RotationMatrix;
		D3DXMatrixRotationAxis(&RotationMatrix, &D3DXVECTOR3(0, 1.f, 0), 0.005f * frametime * MouseMove);

		D3DXVECTOR3 vRight = D3DXVECTOR3(m_rightX, m_rightY, m_rightZ);
		D3DXVECTOR3	vUp = D3DXVECTOR3(m_upX, m_upY, m_upZ);
		D3DXVECTOR3	vLook = D3DXVECTOR3(m_lookAtX, m_lookAtY, m_lookAtZ);

		D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
		D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
		D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

		SetRight(vRight.x, vRight.y, vRight.z);
		SetUp(vUp.x, vUp.y, vUp.z);
		SetLookAt(vLook.x, vLook.y, vLook.z);
	}
		break;
	case MOVE_MOUSEY:
	{
		D3DXVECTOR3 vRight = D3DXVECTOR3(m_rightX, m_rightY, m_rightZ);

		D3DXMATRIX	RotationMatrix;
		D3DXMatrixRotationAxis(&RotationMatrix, &vRight, 0.005f * frametime * MouseMove);

		D3DXVECTOR3	vUp = D3DXVECTOR3(m_upX, m_upY, m_upZ);
		D3DXVECTOR3	vLook = D3DXVECTOR3(m_lookAtX, m_lookAtY, m_lookAtZ);

		D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
		D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
		D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

		SetRight(vRight.x, vRight.y, vRight.z);
		SetUp(vUp.x, vUp.y, vUp.z);
		SetLookAt(vLook.x, vLook.y, vLook.z);
	}
		break;
	}
}
