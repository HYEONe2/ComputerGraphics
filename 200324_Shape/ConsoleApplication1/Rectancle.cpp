#include "stdafx.h"
#include "Rectancle.h"


CRectancle::CRectancle()
{
}

CRectancle::CRectancle(float fX, float fY, float fW, float fH)
	:CShape(fX, fY), m_fW(fW), m_fH(fH)
{
}


CRectancle::~CRectancle()
{
}

void CRectancle::Draw() const
{
	cout << "[RECTANGLE] position = ( " << m_fX << ", " << m_fY << " ), size = ( " << m_fW << ",  " << m_fY << " )" << endl;

	//TCHAR st[1024];
	//wprintf(st, TEXT("[RECTNAGLE] position = (%d, %d), radius = %d"), (int)m_fX, (int)m_fY, (int)m_fW, m_fH);
	//DrawText(pDC, st, -1, &RECT, DT_LEFT | DT_VCENTER | DT_NOCLIP);
}
