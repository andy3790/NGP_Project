#pragma once
#include"MapObject.h"

class BackGround : MapObject {
private:
	HBITMAP hMapBitmap;
	int bitmapWidth;
	int bitmapHight;

	int MapSizeX;
	int MapSizeY;
public:
	BackGround() {};
	BackGround(int MapX, int MapY) {
		MakeBackGroundObject(MapX, MapY);
	}

	void MakeBackGroundObject(int MapX, int MapY);

#if CONSOL==CLIENT
public:
	void Render(HDC hDC, HBITMAP hBitmap, RECT WndRect);
	void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	void Update(float eTime, RECT WndRect);
	ObjectData Encode();
#endif

};

