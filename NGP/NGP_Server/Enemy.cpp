#include "Enemy.h"

STATE Enemy::IntToState_Enemey(int in, int dir)
{
	switch (in)
	{
	case 0:
		return STATE::idle;
	case 1:
		if (dir == 0)
			return STATE::left;
		else
			return STATE::right;
	case 2:
		return STATE::att;
	}
}