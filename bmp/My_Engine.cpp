#include "My_Engine.h"
#include "Util.h"
#include "resource.h"

using namespace std;



My_Engine::My_Engine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
	WORD Icon, WORD SmIcon,
	int iWidth, int iHeight,
	COLORREF bkColor) :T_Engine(hInstance, szWindowClass, szTitle,
		Icon, SmIcon, iWidth, iHeight, bkColor)
{
	wnd_width = iWidth;
	wnd_height = iHeight;

	alpha = 0;
	HDC hdc = ::GetDC(m_hWnd);
	layerDC = ::CreateCompatibleDC(hdc);
	::ReleaseDC(m_hWnd, hdc);
}


My_Engine::~My_Engine()
{
	delete randCell;
}



void My_Engine::GameInit()
{	
	//��ֹͼƬ��Сʱʧ��
	SetStretchBltMode(bufferDC, HALFTONE);

	Bitmap* pBmp = NULL;
	/*pBmp = Bitmap::FromResource(m_hInstance, MAKEINTRESOURCE(IDB_SUNRISE));
	Status status = pBmp->GetHBITMAP(NULL, &hbitmap);
	if(status != S_OK)hbitmap = NULL;
	delete pBmp;*/
	mousePT.x = 0;
	mousePT.y = 0;
	rows = 5;
	cols = 5;
	cell_width = wnd_width / cols;
	cell_height = wnd_height / rows;
	startTime = GetTickCount();
	randCell = new int[rows *cols];
	ratio = 20;
	enlarge = true;	
}
// ��Ϸ�߼�����
void My_Engine::GameLogic()
{
	
}
// ��Ϸ��������
void My_Engine::GameEnd()
{
	
}
// ����GAME_STATEֵ��ʾ��Ϸ����
void My_Engine::GamePaint(HDC hdc)
{
	int nWidth = 400;
	int nHeight = 400;
	BYTE* picData = new BYTE[nWidth*nHeight * 4];
	memset(picData, 0, nWidth*nHeight * 4);
	Bitmap bm(nWidth, nHeight, nWidth * 4, PixelFormat32bppARGB, picData);
	for (int row = 0; row<nHeight; ++row)
	{
		for (int col = 0; col<nWidth; ++col)
		{		
			picData[row*nWidth * 4 + col * 4 + 2] = 255;	//Red
			picData[row*nWidth * 4 + col * 4 + 3] = 255;	//Alpha			
		}
	}

	//HBITMAP redbmp = CreateBlankBMP(250,250, RGB(255, 0, 0));
	HBITMAP redbmp = NULL;
	bm.GetHBITMAP(Color(0,0,0,0),&redbmp);
	SelectObject(hdc, redbmp);

	HBITMAP bluebmp = CreateBlankBMP(250, 250, RGB(0, 0, 255));
	SelectObject(layerDC, bluebmp);

	BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0, 100, 0 };
	AlphaBlend(hdc,
		0, 0, 200, 200,
		layerDC,
		0, 0, 200, 200,
		blendfunc);



	
		
}
// ����KM_ACTIONֵ��������Ϊ
void My_Engine::GameKeyAction(int ActionType)
{
	//if(ActionType == KEY_DOWN) PostQuitMessage(0); // ���������˳�����
}
// ����KM_ACTIONֵ���������Ϊ
 void My_Engine::GameMouseAction(int x, int y, int ActionType)
{ 
	 if(ActionType = MOUSE_MOVE)
	 {
		 if(mousePT.x == 0 && mousePT.y == 0) // ��¼������D ������λ��
		 {
			 mousePT.x = x; mousePT.y = y;
		 }
		// �����ǰ���λ���봰������ʱ�����겻һ��
		// ��ʾ����Ѿ��ƶ��� �����˳��������Ϣ
		 //if (mousePT.x != x && mousePT.y != y) PostQuitMessage(0);
	 }
 }

 
 HBITMAP My_Engine::CreateBlankBMP(HDC hDC, int ibWidth, int ibHeight, COLORREF crColor)
 {
	 //����һ���յ�λͼ
	 HBITMAP bitmap = CreateCompatibleBitmap(hDC, ibWidth, ibHeight);
	 if (bitmap == NULL) return FALSE;
	 //����һ���ڴ��豸��������λͼ
	 HDC memDC = CreateCompatibleDC(hDC);
	 //����һ����ɫ��ˢ����������������Ŀ�λͼ
	 HBRUSH hBrush = CreateSolidBrush(crColor);
	 //�������Ŀ�λͼ�滻�ڴ��豸�е�ԭ������
	 HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, bitmap);
	 //���ƶ�����ɫ���λͼ
	 RECT rcBitmap = { 0, 0, ibWidth, ibHeight };
	 FillRect(memDC, &rcBitmap, hBrush);
	 //��ԭ��ʹ��ԭ�������滻�ڴ��豸�е�λͼ����
	 SelectObject(memDC, hOldBitmap);
	 //ɾ���ڴ��豸
	 DeleteDC(memDC);
	 //ɾ����ˢ
	 DeleteObject(hBrush);
	 return bitmap;
 }
 BOOL My_Engine::LoadBmp(LPTSTR path, HBITMAP& hBitmap)
 {
	 hBitmap = (HBITMAP)LoadImage(GetModuleHandle(0), path,
		 IMAGE_BITMAP, 0, 0,
		 LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	 if (!hBitmap)
	 {
		 Util::myprintf(L"λͼ����ʧ��\n");
		 return FALSE;  // ���λͼ����ʧ��
	 }
	 DIBSECTION dib;
	 // ���λͼ��Ϣ��ȡʧ��
	 if (GetObject(hBitmap, sizeof(DIBSECTION), &dib) != sizeof(DIBSECTION))
	 {
		 DeleteObject(hBitmap);
		 hBitmap = 0;
		 return FALSE;
	 }
	 bmpWidth = dib.dsBmih.biWidth;
	 bmpHeight = dib.dsBmih.biHeight;
	 return TRUE;
 }

 HBITMAP My_Engine::CreateBlankBMP(int ibWidth, int ibHeight, COLORREF crColor)
 {
	 void* Bits;				// ָ�򱣴�λͼλֵ�ĵ�ַ
	 BITMAPINFOHEADER Header;	// λͼͷ��Ϣ
	 Header.biSize = sizeof(BITMAPINFOHEADER);
	 Header.biWidth = ibWidth;
	 Header.biHeight = ibHeight;
	 Header.biBitCount = 24;
	 Header.biPlanes = 1;
	 Header.biCompression = BI_RGB;
	 HBITMAP hbmp = CreateDIBSection(
		 NULL, (BITMAPINFO*)&Header, DIB_RGB_COLORS, &Bits, NULL, 0);
	 if (hbmp != NULL) //ʹ��ָ����ɫ���հ�λͼ
	 {
		 //����һ���ڴ��豸��������λͼ
		 HDC memDC = CreateCompatibleDC(GetDC(NULL));
		 //����һ����ɫ��ˢ����������������Ŀ�λͼ
		 HBRUSH hBrush = CreateSolidBrush(crColor);
		 //�������Ŀ�λͼ�滻�ڴ��豸�е�ԭ������
		 HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, hbmp);
		 //��ָ������ɫ���λͼ
		 RECT rcBitmap = { 0, 0, ibWidth, ibHeight };
		 FillRect(memDC, &rcBitmap, hBrush);
		 // �ָ�ԭ�е�λͼ����
		 SelectObject(memDC, hOldBitmap);
		 DeleteDC(memDC); //ɾ���ڴ��豸
		 DeleteObject(hBrush); //ɾ����ˢ
		 DeleteObject(Bits);
		 Bits = NULL;
	 }
	 return hbmp;
 }
 Bitmap* My_Engine::HBITMAP_To_Bitmap(HBITMAP hbmp, HDC hdc)
 {
	 BITMAP bmp;
	 int width, height;
	 // ����λͼ�����ȡBITMAP�ṹ����������
	 memset((void*)&bmp, 0, sizeof(BITMAP));
	 GetObject(hbmp, sizeof(BITMAP), (void*)&bmp);
	 width = bmp.bmWidth;
	 height = bmp.bmHeight;
	 byte* bmpBytes = (byte*)bmp.bmBits;
	 if (width <= 0 && height <= 0) return NULL;

	 // ����λͼ����½�һ��PixelFormat32bppPARGB��ʽ��Bitmap����
	 Bitmap* BmpCpy = new Bitmap(width, height, PixelFormat32bppPARGB);
	 // ����LockBits����Ϊλͼ�������ݿ���׼���ڴ滺����
	 BitmapData bmpData;
	 Rect rect(0, 0, width, height);
	 BmpCpy->LockBits(&rect, ImageLockModeWrite, PixelFormat32bppPARGB, &bmpData);
	 // �����λͼÿ��������������ָ��ָ������
	 int lineSize = width * 4;
	 byte* cpyBytes = (byte*)(bmpData.Scan0);
	 // ����λͼ�ĸ����п�������������������
	 for (int y = 0; y < height; y++)
	 {
		 memcpy((y * lineSize) + cpyBytes, ((height - y - 1) * lineSize) + bmpBytes, lineSize);
	 }
	 // �����ڴ滺����
	 BmpCpy->UnlockBits(&bmpData);
	 return BmpCpy;
 }
 void My_Engine::PaintRegion(HDC destDC, int destX, int destY,
	 int srcX, int srcY, int regionWidth, int regionHeight,
	 float ratio, int rotType, BYTE alpha)
 {
	 int width = (int)(regionWidth*ratio);
	 int height = (int)(regionHeight*ratio);

	 BYTE* pBits = NULL;
	 BITMAPINFO bmi;
	 bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	 bmi.bmiHeader.biWidth = width;
	 bmi.bmiHeader.biHeight = height;
	 bmi.bmiHeader.biPlanes = 1;
	 bmi.bmiHeader.biBitCount = 32;
	 bmi.bmiHeader.biCompression = BI_RGB;
	 bmi.bmiHeader.biSizeImage = width * height * 4;

	 HDC frameDC = ::CreateCompatibleDC(NULL);
	 HBITMAP hbitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pBits, NULL, NULL);
	 HBITMAP OldFrameBmp = (HBITMAP)SelectObject(frameDC, hbitmap);

	 BLENDFUNCTION frame_bf;
	 frame_bf.BlendOp = AC_SRC_OVER;
	 frame_bf.BlendFlags = 0;
	 frame_bf.SourceConstantAlpha = 255;
	 frame_bf.AlphaFormat = AC_SRC_ALPHA;

	 HDC memDC = CreateCompatibleDC(destDC);
	 HBITMAP OldMemBmp = (HBITMAP)SelectObject(memDC, GetBmpHandle());

	 AlphaBlend(frameDC, 0, 0, (int)(regionWidth*ratio), (int)(regionHeight*ratio),
		 memDC, srcX, srcY, regionWidth, regionHeight, frame_bf);

	 Bitmap* nowFrameBmp = HBITMAP_To_Bitmap(hbitmap, destDC);

	 //��ԭ��ʹ��ԭ�������滻�ڴ��豸�е�λͼ����
	 SelectObject(frameDC, OldFrameBmp);
	 DeleteDC(frameDC);//ɾ���ڴ��豸
	 DeleteObject(OldFrameBmp);//ɾ��λͼ����
	 DeleteObject(hbitmap);//ɾ��λͼ����

	//��ԭ��ʹ��ԭ�������滻�ڴ��豸�е�λͼ����
	 SelectObject(memDC, OldMemBmp);
	 DeleteDC(memDC);//ɾ���ڴ��豸
	 DeleteObject(OldMemBmp);//ɾ��λͼ����

							 //��ת֡ͼ
	 int framew = (int)(regionWidth*ratio);
	 int frameh = (int)(regionHeight*ratio);
	 switch (rotType)
	 {
	 case TRANS_NONE:
		 break;
	 case TRANS_NOFLIP_ROT90:
		 nowFrameBmp->RotateFlip(Rotate90FlipNone);
		 framew = (int)(regionHeight*ratio);
		 frameh = (int)(regionWidth*ratio);
		 break;
	 case TRANS_NOFLIP_ROT180:
		 nowFrameBmp->RotateFlip(Rotate180FlipNone);
		 framew = (int)(regionWidth*ratio);
		 frameh = (int)(regionHeight*ratio);
		 break;
	 case TRANS_NOFLIP_ROT270:
		 nowFrameBmp->RotateFlip(Rotate270FlipNone);
		 framew = (int)(regionHeight*ratio);
		 frameh = (int)(regionWidth*ratio);
		 break;
	 case TRANS_VFLIP_NOROT:
		 nowFrameBmp->RotateFlip(RotateNoneFlipY);
		 framew = (int)(regionWidth*ratio);
		 frameh = (int)(regionHeight*ratio);
		 break;
	 case TRANS_VFLIP_ROT90:
		 nowFrameBmp->RotateFlip(Rotate90FlipY);
		 framew = (int)(regionHeight*ratio);
		 frameh = (int)(regionWidth*ratio);
		 break;
	 case TRANS_VFLIP_ROT180:
		 nowFrameBmp->RotateFlip(Rotate180FlipY);
		 framew = (int)(regionWidth*ratio);
		 frameh = (int)(regionHeight*ratio);
		 break;
	 case TRANS_VFLIP_ROT270:
		 nowFrameBmp->RotateFlip(Rotate270FlipY);
		 framew = (int)(regionHeight*ratio);
		 frameh = (int)(regionWidth*ratio);
		 break;
	 case TRANS_HFLIP_NOROT:
		 nowFrameBmp->RotateFlip(RotateNoneFlipX);
		 framew = (int)(regionWidth*ratio);
		 frameh = (int)(regionHeight*ratio);
		 break;
	 case TRANS_HFLIP_ROT90:
		 nowFrameBmp->RotateFlip(Rotate90FlipX);
		 framew = (int)(regionHeight*ratio);
		 frameh = (int)(regionWidth*ratio);
		 break;
	 case TRANS_HFLIP_ROT180:
		 nowFrameBmp->RotateFlip(Rotate180FlipX);
		 framew = (int)(regionWidth*ratio);
		 frameh = (int)(regionHeight*ratio);
		 break;
	 case TRANS_HFLIP_ROT270:
		 nowFrameBmp->RotateFlip(Rotate270FlipX);
		 framew = (int)(regionHeight*ratio);
		 frameh = (int)(regionWidth*ratio);
		 break;
	 }

	 HDC bufDC = CreateCompatibleDC(destDC);
	 HBITMAP hbmp = NULL;
	 nowFrameBmp->GetHBITMAP(Color(0, 0, 0, 0), &hbmp);
	 HBITMAP OldbufBmp = (HBITMAP)SelectObject(bufDC, hbmp);

	 BLENDFUNCTION buf_bf;
	 buf_bf.BlendOp = AC_SRC_OVER;
	 buf_bf.BlendFlags = 0;
	 buf_bf.SourceConstantAlpha = alpha;
	 buf_bf.AlphaFormat = AC_SRC_ALPHA;
	 AlphaBlend(destDC, destX, destY, framew, frameh,
		 bufDC, 0, 0, framew, frameh, buf_bf);

	 //��ԭ��ʹ��ԭ�������滻�ڴ��豸�е�λͼ����
	 SelectObject(bufDC, OldbufBmp);
	 DeleteDC(bufDC);//ɾ���ڴ��豸
	 DeleteObject(OldbufBmp);//ɾ��λͼ����
	 DeleteObject(hbmp);//ɾ��λͼ����
	 DeleteObject(nowFrameBmp);//ɾ��λͼ����
	 delete nowFrameBmp;//ɾ��λͼ����
 }

 void My_Engine::PaintText(HDC hdc, RectF fontRect, LPCTSTR text, REAL fontSize,
	 LPCTSTR fontName, Color fontColor, FontStyle style,
	 StringAlignment align)
 {
	 //ʹ��GDI�������л���
	 Graphics graph(hdc);
	 FontFamily fontFamily(fontName);
	 Font font(&fontFamily, fontSize, style, UnitPoint);

	 StringFormat format;
	 format.SetLineAlignment(StringAlignmentCenter);
	 format.SetAlignment(align);
	 SolidBrush solidBrush1(fontColor);

	 graph.SetTextRenderingHint(TextRenderingHintAntiAlias);
	 graph.DrawString(text, (INT)wcslen(text), &font, fontRect, &format, &solidBrush1);
	 graph.ReleaseHDC(hdc);
 }

 // ��������range ָ����Χ�ĵȶ������
 // ����iArray Ϊ�ĳ�������ĵĳ��������������ȶ���ΪԪ����������range ������
 void My_Engine::GetRandomNum(int range, int* iArray)
 {
	 int i;
	 srand((unsigned)time(NULL)); // ��ʼ�������
	 for (i = 0; i<range; ++i)
	 {
		 iArray[i] = i;
	 }
	 for (i = range; i>0; --i)
	 {
		 int r = rand() % i;
		 swap(iArray[i - 1], iArray[r]);
	 }
 }