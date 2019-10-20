#include "Subject.h"


Subject::Subject(int* vx,int num, COLORREF color)
{
	this->apt = (POINT*)malloc(sizeof(int)*num*2);
	memcpy(apt, vx, sizeof(int)*num * 2);
	icount = num;
	this->color = color;
}
Subject::Subject(POINT* vx, int num, COLORREF color)
{
	this->apt = (POINT*)malloc(sizeof(int)*num );
	memcpy(apt, vx, sizeof(int)*num * 2);
	icount = num;
	this->color = color;
}


Subject::Subject()
{
}


Subject::~Subject()
{
}

void Subject::setApt(int* vx, int num)
{
	delete apt;
	this->apt = (POINT*)malloc(sizeof(int)*num * 2);
	memcpy(apt, vx, sizeof(int)*num * 2);
	icount = num;
}

void Subject::setApt(POINT* vx, int num)
{
	delete apt;
	this->apt = (POINT*)malloc(sizeof(int)*num * 2);
	memcpy(apt, vx, sizeof(int)*num * 2);
	icount = num;
}
void  Subject::getApt(POINT* outapt)
{
	memcpy(outapt, apt, sizeof(int)*icount * 2);
}
void Subject::setColor(COLORREF color)
{
	this->color = color;
}
COLORREF Subject::getColor()
{
	return color;
}
void Subject::setOffset(int px, int py)
{
	offset_x = px;
	offset_y = py;
}
POINT Subject::getOffset()
{
	POINT pt = { offset_x, offset_y };
	return pt;
}