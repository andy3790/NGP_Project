#include "Base.h"

void Base::Update(float eTime)
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