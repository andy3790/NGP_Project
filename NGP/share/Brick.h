#pragma once
#include"MapObject.h"
class Brick : MapObject{
public:
	enum Type : int {
		Ground,
		Wall,
		Shelf
	};

private:
	CImage image;
	RECT rect;
	Type type;

public:
	Brick();
	Brick(RECT input, Type type) {
		MakeBrickObject(input, type);
	}

	void MakeBrickObject(RECT input, Type type);

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

