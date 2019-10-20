#pragma once
#include "T_Config.h"
#include <vector>
using namespace std;


class Subject
{
protected:
	POINT* apt;
	int icount;
	int offset_x, offset_y;

	COLORREF color;
public:
	Subject(int* vx, int num, COLORREF color = RGB(255, 255, 255));
	Subject(POINT* vx, int num,COLORREF color = RGB(255,255,255));
	Subject();
	~Subject();

	void setApt(int*, int num);
	void setApt(POINT*, int num);
	int getApt(POINT*);
	int getIcount();
	void setColor(COLORREF color);
	COLORREF getColor();
	void setOffset(int px,int py);
	POINT getOffset();
	virtual void draw(HDC hdc) = 0;
	virtual bool isCollision(Subject* target) = 0;
};

