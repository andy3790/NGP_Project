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

void BackGround::Update(float eTime, RECT WndRect)
{

}

ObjectData BackGround::Encode()
{
	ObjectData data;

	data.hp = 1;
	data.pos = { (short)0, (short)0 };
	data.state = STATE::idle;

	data.vel_1 = OBJECT_TYPE_BACKGROUND;

	return data;
}