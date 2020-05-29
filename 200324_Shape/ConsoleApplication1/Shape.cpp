#include "stdafx.h"
#include "Shape.h"


CShape::CShape()
{
}

CShape::CShape(float fX, float fY)
	: m_fX(fX), m_fY(fY)
{
}


CShape::~CShape()
{
}

void CShape::Draw() const
{
	cout << "[SHAPE] position = ( " << m_fX << ", " << m_fY << " )" << endl;
}
