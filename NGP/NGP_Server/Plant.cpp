#include "Plant.h"

void Plant::MakeEnemy(POINT location, int dir)
{
	myImage.Load((LPCTSTR)L"../Resorce/Image/Enemy/plant.png");

	int aniSizeX = 128;
	int aniSizeY = 128;

	animation = (POINT**)malloc(sizeof(POINT*) * 1);
	animation[0] = (POINT*)malloc(sizeof(POINT) * 1);
	animation[0][0] = { 0, 0 };
	max_hp = 50;
	hp = 50;
	damage = 10;
	printsizex = aniSizeX;
	printsizey = aniSizeY;



	count = 0;
	act = 0;
	loca = location;
	direct = dir;
	status = E_SEEK;
	anisizex = aniSizeX;
	anisizey = aniSizeY;

	alive = true;
	move = false;
	atk_buffer = false;
	atk_finish = false;
	rest = 0;
}

void Plant::DelelteEnemy()
{
	free(animation[0]);
	free(animation);

	myImage.Destroy();
}

void Plant::Update(float eTime, RECT WndRect)
{

}

ObjectData Plant::Encode()
{
	ObjectData data;
	data.hp = GetHp();
	POINT p = GetLocaition();
	data.pos = { (short)p.x, (short)p.y };
	data.state = IntToState_Enemey(GetAct(), GetDirect());
	data.vel_1 = 0;

	return data;
}