// ConsoleApplication1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Shape.h"
#include "Rectancle.h"
#include "Circle.h"

int main()
{
	CShape* shapes[5] = { NULL };
	shapes[0] = new CCircle(100, 100, 50); 
	shapes[1] = new CRectancle(300, 300, 100, 100); 
	shapes[2] = new CRectancle(200, 100, 50, 150); 
	shapes[3] = new CCircle(100, 300, 150); 
	shapes[4] = new CRectancle(200, 200, 200, 200);

	for (int i = 0; i < 5; ++i) shapes[i]->Draw();
	for (int i = 0; i < 5; ++i) { delete shapes[i]; shapes[i] = NULL; }
	return 0;
}

