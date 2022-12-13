#include "BackGround.h"

void BackGround::MakeBackGroundObject(int MapX, int MapY)
{
	BITMAP bmp;
	hMapBitmap = (HBITMAP)LoadImage(NULL, TEXT("../Resorce/Image/Map/Background_1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	MapSizeX = MapX;
	MapSizeY = MapY;
	GetObject(hMapBitmap, sizeof(BITMAP), &bmp);
	bitmapWidth = bmp.bmWidth;
	bitmapHight = bmp.bmHeight;
}

void BackGround::Render(HDC hDC, HBITMAP hBitmap, RECT WndRect)
{
	HDC mem1DC_Map;
	HBITMAP oldMapBitmap;

	mem1DC_Map = CreateCompatibleDC(hDC);
	oldMapBitmap = (HBITMAP)SelectObject(mem1DC_Map, hMapBitmap);

	Rectangle(hDC, 0, 0, MapSizeX, MapSizeY);
	StretchBlt(hDC, 0, 0, MapSizeX, MapSizeY - 100, mem1DC_Map, 0, 0, bitmapWidth, bitmapHight, SRCCOPY);
	SelectObject(mem1DC_Map, oldMapBitmap);
	DeleteDC(mem1DC_Map);
}

void BackGround::Decode(ObjectData object_data)
{

}