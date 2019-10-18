#pragma once
#include "T_Engine.h"
#include "Util.h"

class testGDI//:public T_Display
{
private:
		



	static const long T_LENGTH = 4500;
	int wnd_width, wnd_height;
	HBITMAP hbitmap;
	int cell_width, cell_height;
	int rows, cols;
		
	long startTime;
	POINT mousePT;
	int* randCell;
	int ratio;
	bool enlarge;
public:
	testGDI();
	~testGDI();
	HBITMAP testGDI::CreateBlankBMP(int ibWidth, int ibHeight, COLORREF crColor);
	BOOL testGDI::LoadBmp(LPTSTR path, HBITMAP& hBitmap);
	HBITMAP testGDI::CreateBlankBMP(HDC hDC, int ibWidth, int ibHeight, COLORREF crColor);
	Bitmap* testGDI::HBITMAP_To_Bitmap(HBITMAP hbmp, HDC hdc);
	void testGDI::PaintRegion(HDC destDC, int destX, int destY,
		int srcX, int srcY, int regionWidth, int regionHeight,
		float ratio, int rotType, BYTE alpha);
	void testGDI::PaintText(HDC hdc, RectF fontRect, LPCTSTR text, REAL fontSize,
		LPCTSTR fontName, Color fontColor, FontStyle style,
		StringAlignment align);

	HBITMAP GetBmpHandle() { return hbitmap; }
	void GetRandomNum(int range, int* iArray);
};