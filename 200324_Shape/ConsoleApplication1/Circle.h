#pragma once
#include "Shape.h"

class CCircle 
	: public CShape
{
public:
	CCircle();
	CCircle(float fX, float fY, float fRadius);
	~CCircle();

public:
	virtual void Draw() const;

private:
	float m_fRadius = 0;
};

