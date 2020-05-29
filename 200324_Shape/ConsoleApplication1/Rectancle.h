#pragma once
#include "Shape.h"

class CRectancle 
	: public CShape
{
public:
	CRectancle();
	CRectancle(float fX, float fY, float fW, float fH);
	~CRectancle();

public:
	virtual void Draw() const;

private:
	float m_fW = 0;
	float m_fH = 0;
};

