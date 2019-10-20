#include "Poly.h"



Poly::Poly(int* vx, int num):Subject(vx,num)
{
}
Poly::Poly()
{
}


Poly::~Poly()
{
}

void Poly::draw(HDC hdc)
{
	POINT* tempapt = (POINT*)malloc(sizeof(POINT)*icount);
	memcpy(tempapt, apt, sizeof(int)*icount * 2);
	for(int i = 0;i<icount;i++)
	{
		tempapt[i].x = tempapt[i].x + offset_x;
		tempapt[i].y = tempapt[i].y + offset_y;
		Util::myprintf(L"temp[%d].x:%d,temp[%d].x:%d\n", i, tempapt[i].x, i, tempapt[i].y);
	}
	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	HPEN oldpen = (HPEN)SelectObject(hdc, pen);
	Polygon(hdc, tempapt, icount);
	DeleteObject(SelectObject(hdc, oldbrush));
	DeleteObject(SelectObject(hdc, oldpen));
	delete tempapt;
}
void Poly::draw(HDC hdc,COLORREF color)
{
	POINT* tempapt = (POINT*)malloc(sizeof(POINT)*icount);
	memcpy(tempapt, apt, sizeof(int)*icount * 2);
	for (int i = 0; i<icount; i++)
	{
		tempapt[i].x = tempapt[i].x + offset_x;
		tempapt[i].y = tempapt[i].y + offset_y;
		Util::myprintf(L"temp[%d].x:%d,temp[%d].x:%d\n", i, tempapt[i].x,i, tempapt[i].y);
	}
	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);
	HPEN pen = CreatePen(PS_SOLID,1,color);
	HPEN oldpen = (HPEN)SelectObject(hdc, pen);
	Polygon(hdc, tempapt, icount);
	DeleteObject(SelectObject(hdc, oldbrush));
	DeleteObject(SelectObject(hdc, oldpen));
	delete tempapt;
}
bool Poly::isCollision(Subject* target)
{
	return false;
}