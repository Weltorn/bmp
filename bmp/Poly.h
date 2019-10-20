#pragma once
#include "Subject.h"
#include "Util.h"
class Poly :
	public Subject
{
public:
	Poly();
	Poly::Poly(int* vx, int num);
	~Poly();

	 void draw(HDC hdc)override;
	 void draw(HDC hdc, COLORREF color);
	 bool isCollision(Subject* target)override;
};

