#include "Wolf.h"

void Wolf::MakeEnemy(POINT location, int dir)
{
	myImage.Load((LPCTSTR)L"../Resorce/Image/Enemy/wolf.png");

	int aniSizeX = 64;
	int aniSizeY = 32;

	animation = (POINT**)malloc(sizeof(POINT*) * 1);
	for (int i = 0; i < 1; i++) {
		animation[i] = (POINT*)malloc(sizeof(POINT) * 15);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			animation[0][j + i * 5] = { aniSizeX * j + 320, aniSizeY * i + 288 };
		}
	}
	max_hp = 70;
	hp = 70;
	damage = 8;
	printsizex = 2 * aniSizeX;
	printsizey = 2 * aniSizeY;



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

void Wolf::DelelteEnemy()
{
	free(animation[0]);
	free(animation);

	myImage.Destroy();
}

void Wolf::Update(float eTime, RECT WndRect)
{

}

ObjectData Wolf::Encode()
{
	ObjectData data;
	data.hp = GetHp();
	POINT p = GetLocaition();
	data.pos = { (short)p.x, (short)p.y };
	data.state = IntToState_Enemey(GetAct(), GetDirect());
	data.vel_1 = 0;

	return data;
}