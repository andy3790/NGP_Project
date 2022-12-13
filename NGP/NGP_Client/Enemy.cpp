#include "Enemy.h"

void Enemy::SetAct(STATE Act)
{
	switch (Act)
	{
	case STATE::idle:
		act = 0;
	case STATE::left:
		act = 1;
		direct = 0;
	case STATE::right:
		act = 1;
		direct = 1;
	case STATE::att:
		act = 2;
	}
}


int Enemy::StateToInt_Enemey(STATE in, int dir)
{
	switch (in)
	{
	case STATE::idle:
		return 0;
	case STATE::left:
		if (dir == 0)
			return 1;
		else
			return 2;
	case STATE::att:
		return 3;
	}
}