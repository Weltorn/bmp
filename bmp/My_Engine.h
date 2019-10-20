#pragma once
#include "T_Engine.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <AtlBase.h>
#include "Poly.h"
#include "CollisionManager.h"


#ifdef WIN32
#include <direct.h>
#include <io.h>
#endif
using namespace std;

class My_Engine :
	public T_Engine
{
private:
	HDC layerDC;
	HBITMAP hbitmap;

	int wnd_width, wnd_height;
	POINT mousePT;

	Poly triangle, triangle1;
	int triangle_x = 0, triangle_y = 0;
	int triangle1_x = 0, triangle1_y = 0;
	CollisionManager collisionManager;
public:
	My_Engine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT,
		COLORREF bkColor = WIN_BKCLR);
	~My_Engine();

	HBITMAP CreateBlankBMP(int ibWidth, int ibHeight, COLORREF crColor);
	BOOL LoadBmp(LPTSTR path, HBITMAP& hBitmap);
	HBITMAP CreateBlankBMP(HDC hDC, int ibWidth, int ibHeight, COLORREF crColor);
	Bitmap* HBITMAP_To_Bitmap(HBITMAP hbmp, HDC hdc);
	void PaintRegion(HDC destDC, int destX, int destY,
		int srcX, int srcY, int regionWidth, int regionHeight,
		float ratio, int rotType = 0, BYTE alpha = 255);
	void PaintText(HDC hdc, RectF fontRect, LPCTSTR text, REAL fontSize,
		LPCTSTR fontName, Color fontColor, FontStyle style = FontStyleBold,
		StringAlignment align = StringAlignmentCenter);

	HBITMAP GetBmpHandle() { return hbitmap; }
	void GetRandomNum(int range, int* iArray);

	void GameInit();
	// 游戏逻辑处理
	void GameLogic();
	// 游戏结束处理
	void GameEnd();
	// 根据GAME_STATE值显示游戏界面
	void GamePaint(HDC hdc);
	// 根据KM_ACTION值处理按键行为
	void GameKeyAction(int ActionType = KEY_SYS_NONE);
	// 根据KM_ACTION值处理鼠标行为
	void GameMouseAction(int x, int y, int ActionType);
};



