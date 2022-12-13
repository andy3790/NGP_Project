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

}