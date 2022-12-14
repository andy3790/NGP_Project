#include "Bird.h"

void Bird::MakeEnemy(POINT location, int dir)
{
	myImage.Load((LPCTSTR)L"../Resorce/Image/Enemy/bat.png");

	int aniSizeX = 32;
	int aniSizeY = 32;

	animation = (POINT**)malloc(sizeof(POINT*) * 2);
	for (int i = 0; i < 2; i++) {
		animation[i] = (POINT*)malloc(sizeof(POINT) * 3);
	}

	for (int j = 0; j < 3; ++j)
	{
		animation[0][j] = { 32 * j + 32,aniSizeY * 0 };
	}
	for (int j = 0; j < 3; ++j)
	{
		animation[1][j] = { 32 * j + 32,aniSizeY * 3 };
	}
	max_hp = 40;
	hp = 40;
	damage = 5;
	printsizex = 3 * aniSizeX;
	printsizey = 3 * aniSizeY;



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

void Bird::DelelteEnemy()
{
	for (int i = 0; i < 2; i++) { free(animation[i]); }
	free(animation);

	myImage.Destroy();
}

void Bird::Update(float eTime, RECT WndRect)
{

}

ObjectData Bird::Encode()
{
	ObjectData data;
	data.hp = GetHp();
	POINT p = GetLocaition();
	data.pos = { (short)p.x, (short)p.y };
	data.state = IntToState_Enemey(GetAct(), GetDirect());
	data.vel_1 = OBJECT_TYPE_BIRD;

	return data;
}