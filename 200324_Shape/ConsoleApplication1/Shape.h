#pragma once

class CShape
{
public:
	CShape();
	CShape(float fX, float fY);
	~CShape();

public:
	virtual void Draw() const;

protected:
	float m_fX = 0;
	float m_fY = 0;
};

