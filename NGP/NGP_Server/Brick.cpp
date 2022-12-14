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

void Brick::Update(float eTime, RECT WndRect)
{

}

ObjectData Brick::Encode()
{
	ObjectData data;

	data.hp = 1;
	data.pos = { (short)rect.right, (short)rect.bottom };
	data.state = STATE::idle;

	data.vel_1 = OBJECT_TYPE_BRICK;

	return data;
}