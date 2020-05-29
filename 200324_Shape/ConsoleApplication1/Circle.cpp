#include "stdafx.h"
#include "Circle.h"


CCircle::CCircle()
{
}

CCircle::CCircle(float fX, float fY, float fRadius)
	:CShape(fX, fY), m_fRadius(fRadius)
{
}


CCircle::~CCircle()
{
}

void CCircle::Draw() const
{
	cout << "[CIRCLE] position = ( " << m_fX << ", " << m_fY << " ), radius = " << m_fRadius << endl;
}
