#include "Brick.h"

void Brick::MakeBrickObject(RECT input, Type t)
{
	type = t;
	if (type == Type::Ground)
		image.Load(L"../Resorce/Image/Map/brick2.jpg");
	else if (type == Type::Wall)
		image.Load(L"../Resorce/Image/Map/brick1.jpg");
	else if (type == Type::Shelf)
		image.Load(L"../Resorce/Image/Map/brick1.jpg");
	else
		image.Load(L"../Resorce/Image/Map/brick1.jpg");

	rect = input;
}

void Brick::Render(HDC hDC, HBITMAP hBitmap, RECT WndRect)
{
	if(type == Type::Ground)
		image.StretchBlt(hDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 740, 200);
	else
		image.StretchBlt(hDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 626, 417);
}

void Brick::Decode(ObjectData object_data)
{
	int a, b;
	a = object_data.pos.x;
	b = object_data.pos.y;
	if (type == Brick::Ground || type == Brick::Wall || type == Brick::Shelf)
		return;


	if (a == 3900 && b == 1080) {
		MakeBrickObject(RECT{ 0,900,3900,1080 }, Brick::Ground);
	}
	else if (a == 2360 && b == 900) {
		MakeBrickObject(RECT{ 1760,600,2360,900 }, Brick::Wall);
	}
	else if (a == 2600 && b == 900) {
		MakeBrickObject(RECT{ 2360,700,2600,900 }, Brick::Wall);
	}
	else if (a == 3300 && b == 900) {
		MakeBrickObject(RECT{ 2600,800,3300,900 }, Brick::Wall);
	}
	else if (a == 860 && b == 900) {
		MakeBrickObject(RECT{ 400,750,860,900 }, Brick::Wall);
	}
	else if (a == 1540 && b == 700) {
		MakeBrickObject(RECT{ 1020,680,1540,700 }, Brick::Shelf);
	}
	else if (a == 1540 && b == 700) {
		MakeBrickObject(RECT{ 660,470,1540,490 }, Brick::Shelf);
	}
}