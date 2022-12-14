#include "Base.h"

void Base::MakeEnemy(POINT location, int dir)
{
	myImage.Load((LPCTSTR)L"../Resorce/Image/Enemy/enemy.png");

	int aniSizeX = 128;
	int aniSizeY = 128;

	animation = (POINT**)malloc(sizeof(POINT*) * 3);
	for (int i = 0; i < 3; i++) {
		animation[i] = (POINT*)malloc(sizeof(POINT) * 24);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 24; j++) {
			animation[i][j] = { aniSizeX * i, aniSizeY * j };
		}
	}
	max_hp = 100;
	hp = 100;
	damage = 12;
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

void Base::DelelteEnemy()
{
	for (int i = 0; i < 3; i++) { free(animation[i]); }
	free(animation);

	myImage.Destroy();
}

void Base::Update(float eTime, RECT WndRect)
{

}

ObjectData Base::Encode()
{
	ObjectData data;
	data.hp = GetHp();
	POINT p = GetLocaition();
	data.pos = { (short)p.x, (short)p.y };
	data.state = IntToState_Enemey(GetAct(), GetDirect());
	data.vel_1 = 0;

	return data;
}