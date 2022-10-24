#include "main.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"

// 타입 추가
void Enemy::MakeEnemy(int e_type, int aniSizeX, int aniSizeY, int dir, const TCHAR name[]) {
	monster.Load((LPCTSTR)name);
	// swich 로 변환
<<<<<<< HEAD
	switch (type)
	{
	case E_BASE:
		animation = (POINT**)malloc(sizeof(POINT*) * 3);
		for (int i = 0; i < 3; i++) {
			animation[i] = (POINT*)malloc(sizeof(POINT) * 24);
		}
=======
	animation = (POINT**)malloc(sizeof(POINT*) * aniNumX);
	for (int i = 0; i < aniNumY; i++) {
		animation[i] = (POINT*)malloc(sizeof(POINT) * aniNumY);
	}
>>>>>>> origin/monster

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 24; j++) {
				animation[i][j] = { aniSizeX * i, aniSizeY * j };
			}
		}
		break;
	case E_WOLF:
		break;
	case E_PLANT:
		break;
	case E_BIRD:
		break;
	}
	
	count = 0;
	act = 0;
	loca = { 500,440 };
	direct = dir;
	status = E_SEEK;
	anisizex = aniSizeX;
	anisizey = aniSizeY;
	type = E_BASE; // 수정

	move = false;
	atk_buffer = false;
	atk_finish = false;
	rest = 0;
}

void Enemy::DelelteEnemy() {
	switch (type)
	{
	case E_BASE:
		for (int i = 0; i < 3; i++) { free(animation[i]); }
		free(animation);
		break;
	case E_WOLF:
		for (int i = 0; i < 3; i++) { free(animation[i]); }
		free(animation);
		break;
	case E_PLANT:
		for (int i = 0; i < 3; i++) { free(animation[i]); }
		free(animation);
		break;
	case E_BIRD:
		for (int i = 0; i < 3; i++) { free(animation[i]); }
		free(animation);
		break;
	}
}

void Enemy::SetType(int Type) { type = Type; }
void Enemy::SetAct(int Act) { act = Act; }
void Enemy::SetCount(int Count) { count = Count; }
void Enemy::SetLocaition(int x, int y) { loca.x = x; loca.y = y; }
void Enemy::SetStatus(int Status) { status = Status; }
void Enemy::SetMove(BOOL Move) { move = Move; }
void Enemy::SetDirect(int Dir) { direct = Dir; }
void Enemy::SetFloor(BOOL Floor) { floor = Floor; }

void Enemy::ChangeType(int i) { type += i; }
void Enemy::ChangeAct(int i) { act += i; }
void Enemy::ChangeCount(int i) { count += i; }
void Enemy::ChangeLocaition(int x, int y) { loca.x += x; loca.y += y; }
void Enemy::ChangeStatus(int i) { status += i; }
void Enemy::ChangeMove() { move = !move; }
void Enemy::ChangeDirect(int i) { direct += i; }
void Enemy::ChangeFloor() { floor = !floor; }

POINT Enemy::GetAnimation(int x, int y) { return animation[y][x]; }
POINT Enemy::GetNowAnimation() { return animation[act][count]; }
POINT Enemy::GetLocaition() { return loca; }
int Enemy::GetType() { return type; }
int Enemy::GetAct() { return act; }
int Enemy::GetCount() { return count; }
int Enemy::GetStatus() { return status; }
int Enemy::GetDirect() { return direct; }
int Enemy::GetAniSizeX() { return anisizex; }
int Enemy::GetAniSizeY() { return anisizey; }
BOOL Enemy::GetFloor() { return floor; }
BOOL Enemy::GetMove() { return move; }

void Enemy::SetAtkBuffer(BOOL Atk_buffer) { atk_buffer = Atk_buffer; }
BOOL Enemy::GetAtkBuffer() { return atk_buffer; }
void Enemy::SetAtkFinish(BOOL Atk_finish) { atk_finish = Atk_finish; }
BOOL Enemy::GetAtkFinish() { return atk_finish; }
void Enemy::SetRest(int Rest) { rest = Rest; }
void Enemy::ChangeRest(int i) { rest += i; }
int Enemy::GetRest() { return rest; }
void Enemy::SetHp(int Hp) { hp = Hp; }
void Enemy::ChangeHp(int i) { hp -= i; }
int Enemy::GetHp() { return hp; }
void Enemy::SetDamage(int Damage) { damage = Damage; }
int Enemy::GetDamege() { return damage; }


void Enemy_AI(HWND hWnd, Player* player, Enemy* enemy, RECT WndRect, Wall* wall, int WallCount) {
	switch (enemy->GetType())
	{
	case E_BASE:
		enemy->ChangeCount(1);
		if (enemy->GetAtkBuffer() && enemy->GetStatus() != E_REST)
		{
			if (enemy->GetCount() == 24)
			{
				enemy->SetAtkFinish(true);
			}
		}
		enemy->SetCount(enemy->GetCount() % 24);
		if (!enemy->GetAtkBuffer())
		{
			// SEEK
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) > 300 || (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) < -300)
			{
				enemy->SetStatus(E_SEEK);
			}
			// FOLLOW
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) <= 300 && (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) >= -300)
			{
				enemy->SetStatus(E_MOVE);
			}
			// ATTACK
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) <= 48 && (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) >= -48 && (player->GetMidPos().y - (enemy->GetLocaition().y + 64)) <= 56 && (player->GetMidPos().y - (enemy->GetLocaition().y + 64)) >= -56)
			{
				enemy->SetAtkBuffer(true);
				enemy->SetCount(0);
				enemy->SetStatus(E_ATTACK);
			}
		}
		// 바닥 체크
		for (int i = 0; i < WallCount; ++i)
		{
			if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2 - 40,enemy->GetLocaition().y + enemy->GetAniSizeY() - 18 }))
			{
				enemy->SetLocaition(enemy->GetLocaition().x, wall[i].rect.top - enemy->GetAniSizeY() + 18);
				enemy->SetFloor(true);
				break;
			}
			if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2 + 40,enemy->GetLocaition().y + enemy->GetAniSizeY() - 18 }))
			{
				enemy->SetLocaition(enemy->GetLocaition().x, wall[i].rect.top - enemy->GetAniSizeY() + 18);
				enemy->SetFloor(true);
				break;
			}
		}
		switch (enemy->GetStatus())
		{
		case E_SEEK:
			if (enemy->GetCount() == 0)
			{
				if (rand() % 2 == 0)
				{
					enemy->SetMove(FALSE);
					enemy->SetAct(0);
				}
				else
				{
					enemy->SetMove(TRUE);
					enemy->SetAct(1);
					if (rand() % 2 == 0)
					{
						enemy->SetDirect(E_LEFT);
					}
					else
					{
						enemy->SetDirect(E_RIGHT);
					}
				}
			}
			if (enemy->GetMove())
			{
				if (enemy->GetDirect() == E_LEFT)
				{
					enemy->ChangeLocaition(-10, 0);
					if (enemy->GetLocaition().x < 0)
					{
						enemy->ChangeLocaition(10, 0);
					}
					//벽이랑 충돌체크
					for (int i = 0; i < WallCount; ++i)
					{
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 30 }))
						{
							enemy->ChangeLocaition(10, 0);
							break;
						}
					}
				}
				else
				{
					enemy->ChangeLocaition(10, 0);
					if (enemy->GetLocaition().x + enemy->GetAniSizeX() > WndRect.right * 2)
					{
						enemy->ChangeLocaition(-10, 0);
					}
					//벽이랑 충돌체크
					for (int i = 0; i < WallCount; ++i)
					{
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 30 }))
						{
							enemy->ChangeLocaition(-10, 0);
							break;
						}
					}
				}
			}
			break;
		case E_MOVE:
			enemy->SetAct(1);
			if (player->GetMidPos().x < (enemy->GetLocaition().x + 64))
			{
				enemy->SetDirect(E_LEFT);
			}
			else
			{
				enemy->SetDirect(E_RIGHT);
			}
			if (enemy->GetDirect() == E_LEFT)
			{
				enemy->ChangeLocaition(-10, 0);
				if (enemy->GetLocaition().x < 0)
				{
					enemy->ChangeLocaition(10, 0);
				}
				//벽이랑 충돌체크
				for (int i = 0; i < WallCount; ++i)
				{
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 30 }))
					{
						enemy->ChangeLocaition(10, 0);
						break;
					}
				}
			}
			else
			{
				enemy->ChangeLocaition(10, 0);
				if (enemy->GetLocaition().x + enemy->GetAniSizeX() > WndRect.right)
				{
					enemy->ChangeLocaition(-10, 0);
				}
				//벽이랑 충돌체크
				for (int i = 0; i < WallCount; ++i)
				{
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 30 }))
					{
						enemy->ChangeLocaition(-10, 0);
						break;
					}
				}
			}
			enemy->SetAct(1);
			break;
		case E_ATTACK:
			if (enemy->GetFloor())
			{
				if (enemy->GetCount() == 0)
				{
					if (player->GetMidPos().x < (enemy->GetLocaition().x + enemy->GetAniSizeX() / 2))
					{
						enemy->SetDirect(E_LEFT);
					}
					else
					{
						enemy->SetDirect(E_RIGHT);
					}
				}
				// 공격 함수
				if (enemy->GetCount() > 7 && enemy->GetCount() < 23)
				{
					RECT temp;
					if (enemy->GetDirect() == E_LEFT)
					{
						temp = { enemy->GetLocaition().x + 20,enemy->GetLocaition().y + 30,enemy->GetLocaition().x + enemy->GetAniSizeX() - 40,enemy->GetLocaition().y + enemy->GetAniSizeY() - 30 };
					}
					if (enemy->GetDirect() == E_RIGHT)
					{
						temp = { enemy->GetLocaition().x + 40,enemy->GetLocaition().y + 30,enemy->GetLocaition().x + enemy->GetAniSizeX() - 20,enemy->GetLocaition().y + enemy->GetAniSizeY() - 30 };
					}
					RECT player_box = { player->GetMidPos().x - 30,player->GetMidPos().y - 40,player->GetMidPos().x + 30,player->GetMidPos().y + 40 };
					if (IntersectRect(&temp, &player_box, &temp))
					{
						player->Damage2PL(enemy->GetDamege());
					}
				}
				if (enemy->GetAtkFinish())
				{
					enemy->SetAtkFinish(false);
					enemy->SetStatus(E_REST);
				}
				enemy->SetAct(2);
			}
			break;
		case E_REST:
			enemy->ChangeRest(1);
			if (enemy->GetRest() == 24)
			{
				enemy->SetAtkBuffer(false);
				enemy->SetRest(0);
			}
			enemy->SetAct(0);
			break;
		}
		if (!enemy->GetFloor())
		{
			enemy->ChangeLocaition(0, 25);
		}
		enemy->SetFloor(false);
		break;
	case E_WOLF:
		enemy->ChangeCount(1);
		if (enemy->GetAtkBuffer() && enemy->GetStatus() != E_REST)
		{
			if (enemy->GetCount() == 15)
			{
				enemy->SetAtkFinish(true);
			}
		}
		enemy->SetCount(enemy->GetCount() % 15);
		if (!enemy->GetAtkBuffer())
		{
			// SEEK
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) > 300 || (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) < -300)
			{
				enemy->SetStatus(E_SEEK);
			}
			// FOLLOW
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) <= 300 && (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) >= -300)
			{
				enemy->SetStatus(E_MOVE);
			}
			// ATTACK
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) <= 48 && (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) >= -48 && (player->GetMidPos().y - (enemy->GetLocaition().y + 64)) <= 56 && (player->GetMidPos().y - (enemy->GetLocaition().y + 64)) >= -56)
			{
				enemy->SetAtkBuffer(true);
				enemy->SetCount(8);
				enemy->SetStatus(E_ATTACK);
			}
		}
		// 바닥 체크
		for (int i = 0; i < WallCount; ++i)
		{
			if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2 - 40,enemy->GetLocaition().y + enemy->GetAniSizeY() - 2 }))
			{
				enemy->SetLocaition(enemy->GetLocaition().x, wall[i].rect.top - enemy->GetAniSizeY() + 18);
				enemy->SetFloor(true);
				break;
			}
			if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2 + 40,enemy->GetLocaition().y + enemy->GetAniSizeY() - 2 }))
			{
				enemy->SetLocaition(enemy->GetLocaition().x, wall[i].rect.top - enemy->GetAniSizeY() + 18);
				enemy->SetFloor(true);
				break;
			}
		}
		switch (enemy->GetStatus())
		{
		case E_SEEK:
			if (enemy->GetCount() == 0)
			{
				if (rand() % 2 == 0)
				{
					enemy->SetMove(FALSE);
					enemy->SetCount(0);
				}
				else
				{
					enemy->SetMove(TRUE);
					enemy->SetAct(1);
					if (rand() % 2 == 0)
					{
						enemy->SetDirect(E_LEFT);
					}
					else
					{
						enemy->SetDirect(E_RIGHT);
					}
					enemy->SetCount(enemy->GetCount() % 8);
				}
			}
			if (enemy->GetMove())
			{
				if (enemy->GetDirect() == E_LEFT)
				{
					enemy->ChangeLocaition(-10, 0);
					if (enemy->GetLocaition().x < 0)
					{
						enemy->ChangeLocaition(10, 0);
					}
					//벽이랑 충돌체크
					for (int i = 0; i < WallCount; ++i)
					{
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 10 }))
						{
							enemy->ChangeLocaition(10, 0);
							break;
						}
					}
				}
				else
				{
					enemy->ChangeLocaition(10, 0);
					if (enemy->GetLocaition().x + enemy->GetAniSizeX() > WndRect.right * 2)
					{
						enemy->ChangeLocaition(-10, 0);
					}
					//벽이랑 충돌체크
					for (int i = 0; i < WallCount; ++i)
					{
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 10 }))
						{
							enemy->ChangeLocaition(-10, 0);
							break;
						}
					}
				}
			}
			break;
		case E_MOVE:
			enemy->SetAct(1);
			if (player->GetMidPos().x < (enemy->GetLocaition().x + 64))
			{
				enemy->SetDirect(E_LEFT);
			}
			else
			{
				enemy->SetDirect(E_RIGHT);
			}
			if (enemy->GetDirect() == E_LEFT)
			{
				enemy->ChangeLocaition(-10, 0);
				if (enemy->GetLocaition().x < 0)
				{
					enemy->ChangeLocaition(10, 0);
				}
				//벽이랑 충돌체크
				for (int i = 0; i < WallCount; ++i)
				{
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 10 }))
					{
						enemy->ChangeLocaition(10, 0);
						break;
					}
				}
			}
			else
			{
				enemy->ChangeLocaition(10, 0);
				if (enemy->GetLocaition().x + enemy->GetAniSizeX() > WndRect.right)
				{
					enemy->ChangeLocaition(-10, 0);
				}
				//벽이랑 충돌체크
				for (int i = 0; i < WallCount; ++i)
				{
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 10 }))
					{
						enemy->ChangeLocaition(-10, 0);
						break;
					}
				}
			}
			enemy->SetCount(enemy->GetCount() % 8);
			enemy->SetAct(1);
			break;
		case E_ATTACK:
			if (enemy->GetFloor())
			{
<<<<<<< HEAD
				if (enemy->GetCount() == 0)
				{
					if (player->GetMidPos().x < (enemy->GetLocaition().x + enemy->GetAniSizeX() / 2))
					{
						enemy->SetDirect(E_LEFT);
					}
					else
					{
						enemy->SetDirect(E_RIGHT);
					}
=======
				if (player->GetMidPos().x < (enemy->GetLocaition().x + 64))
				{
					enemy->SetDirect(E_LEFT);
				}
				else
				{
					enemy->SetDirect(E_RIGHT);
>>>>>>> origin/monster
				}
				if (enemy->GetAtkFinish())
				{
					enemy->SetAtkFinish(false);
					enemy->SetStatus(E_REST);
				}
				enemy->SetAct(2);
			}
			break;
		case E_REST:
			enemy->ChangeRest(1);
			if (enemy->GetRest() == 15)
			{
				enemy->SetAtkBuffer(false);
				enemy->SetRest(0);
			}
			enemy->SetCount(0);
			break;
		}
		if (!enemy->GetFloor())
		{
			enemy->ChangeLocaition(0, 25);
		}
		enemy->SetFloor(false);
		break;
	case E_PLANT:
		enemy->ChangeCount(1);
		if (enemy->GetAtkBuffer() && enemy->GetStatus() != E_REST)
		{
			if (enemy->GetCount() == 24)
			{
				enemy->SetAtkFinish(true);
			}
		}
		enemy->SetCount(enemy->GetCount() % 24);
		if (!enemy->GetAtkBuffer())
		{
			// SEEK
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) > 300 || (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) < -300)
			{
				enemy->SetStatus(E_SEEK);
			}
			// ATTACK
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) <= 300 && (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) >= -300 && (player->GetMidPos().y - (enemy->GetLocaition().y + 64)) <= 56 && (player->GetMidPos().y - (enemy->GetLocaition().y + 64)) >= -56)
			{
				enemy->SetAtkBuffer(true);
				enemy->SetCount(0);
				enemy->SetStatus(E_ATTACK);
			}
		}
		switch (enemy->GetStatus())
		{
		case E_SEEK:
			if (enemy->GetCount() == 0)
			{
				if (rand() % 2 == 0)
				{
					enemy->SetDirect(E_LEFT);
					enemy->SetMove(FALSE);
					enemy->SetAct(0);
				}
			}
			break;
		case E_ATTACK:
			if (enemy->GetFloor())
			{
				if (enemy->GetCount() == 0)
				{
					if (player->GetMidPos().x < (enemy->GetLocaition().x + enemy->GetAniSizeX() / 2))
					{
						enemy->SetDirect(E_LEFT);
					}
					else
					{
						enemy->SetDirect(E_RIGHT);
					}
				}
				if (enemy->GetAtkFinish())
				{
					enemy->SetAtkFinish(false);
					enemy->SetStatus(E_REST);
				}
				enemy->SetAct(0);
			}
			break;
		case E_REST:
			enemy->ChangeRest(1);
			if (enemy->GetRest() == 24)
			{
				enemy->SetAtkBuffer(false);
				enemy->SetRest(0);
			}
			enemy->SetAct(0);
			break;
		}
		break;
	case E_BIRD:
		enemy->ChangeCount(1);
		if (enemy->GetAtkBuffer() && enemy->GetStatus() != E_REST)
		{
			if (enemy->GetCount() == 3)
			{
				enemy->SetAtkFinish(true);
			}
		}
		enemy->SetCount(enemy->GetCount() % 3);
		if (!enemy->GetAtkBuffer())
		{
			// SEEK
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) > 300 || (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) < -300)
			{
				enemy->SetStatus(E_SEEK);
			}
			// FOLLOW
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) <= 300 && (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) >= -300)
			{
				enemy->SetStatus(E_MOVE);
			}
			// ATTACK
			if ((player->GetMidPos().x - (enemy->GetLocaition().x + 64)) <= 12 && (player->GetMidPos().x - (enemy->GetLocaition().x + 64)) >= -12 && (player->GetMidPos().y - (enemy->GetLocaition().y + 64)) <= 12 && (player->GetMidPos().y - (enemy->GetLocaition().y + 64)) >= -12)
			{
				enemy->SetAtkBuffer(true);
				enemy->SetCount(0);
				enemy->SetStatus(E_ATTACK);
			}
		}
		switch (enemy->GetStatus())
		{
		case E_SEEK:
			if (enemy->GetCount() == 0)
			{
				if (rand() % 2 == 0)
				{
					enemy->SetMove(FALSE);
					enemy->SetAct(0);
				}
				else
				{
					enemy->SetMove(TRUE);
					enemy->SetAct(1);
					if (rand() % 2 == 0)
					{
						enemy->SetDirect(E_LEFT);
					}
					else
					{
						enemy->SetDirect(E_RIGHT);
					}
				}
			}
			if (enemy->GetMove())
			{
				enemy->SetAct(1);
				if (enemy->GetDirect() == E_LEFT)
				{
					enemy->ChangeLocaition(-10, 0);
					if (enemy->GetLocaition().x < 0)
					{
						enemy->ChangeLocaition(10, 0);
					}
					//벽이랑 충돌체크
					for (int i = 0; i < WallCount; ++i)
					{
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 4 }))
						{
							enemy->ChangeLocaition(10, 0);
							break;
						}
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + 4 }))
						{
							enemy->ChangeLocaition(10, 0);
							break;
						}
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() - 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
						{
							enemy->ChangeLocaition(10, 0);
							break;
						}
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
						{
							enemy->ChangeLocaition(10, 0);
							break;
						}
					}
				}
				else
				{
					enemy->ChangeLocaition(10, 0);
					if (enemy->GetLocaition().x < 0)
					{
						enemy->ChangeLocaition(-10, 0);
					}
					//벽이랑 충돌체크
					for (int i = 0; i < WallCount; ++i)
					{
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 4 }))
						{
							enemy->ChangeLocaition(-10, 0);
							break;
						}
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + 4 }))
						{
							enemy->ChangeLocaition(-10, 0);
							break;
						}
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() - 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
						{
							enemy->ChangeLocaition(-10, 0);
							break;
						}
						if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
						{
							enemy->ChangeLocaition(-10, 0);
							break;
						}
					}
				}
			}
			break;
		case E_MOVE:
			enemy->SetAct(1);
			if (player->GetMidPos().x < (enemy->GetLocaition().x + enemy->GetAniSizeX() / 2))
			{
				enemy->SetDirect(E_LEFT);
			}
			else
			{
				enemy->SetDirect(E_RIGHT);
			}
			if (enemy->GetDirect() == E_LEFT)
			{
				enemy->ChangeLocaition(-10, 0);
				if (enemy->GetLocaition().x < 0)
				{
					enemy->ChangeLocaition(10, 0);
				}
				//벽이랑 충돌체크
				for (int i = 0; i < WallCount; ++i)
				{
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 4 }))
					{
						enemy->ChangeLocaition(10, 0);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + 4 }))
					{
						enemy->ChangeLocaition(10, 0);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() - 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
					{
						enemy->ChangeLocaition(10, 0);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
					{
						enemy->ChangeLocaition(10, 0);
						break;
					}
				}
			}
			else
			{
				enemy->ChangeLocaition(10, 0);
				if (enemy->GetLocaition().x < 0)
				{
					enemy->ChangeLocaition(-10, 0);
				}
				//벽이랑 충돌체크
				for (int i = 0; i < WallCount; ++i)
				{
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 4 }))
					{
						enemy->ChangeLocaition(-10, 0);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + 4 }))
					{
						enemy->ChangeLocaition(-10, 0);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() - 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
					{
						enemy->ChangeLocaition(-10, 0);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
					{
						enemy->ChangeLocaition(-10, 0);
						break;
					}
				}
			}
			if (player->GetMidPos().y < (enemy->GetLocaition().y + enemy->GetAniSizeY() / 2))
			{
				enemy->ChangeLocaition(0, -10);
				if (enemy->GetLocaition().x < 0)
				{
					enemy->ChangeLocaition(0, 10);
				}
				//벽이랑 충돌체크
				for (int i = 0; i < WallCount; ++i)
				{
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 4 }))
					{
						enemy->ChangeLocaition(0, 10);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + 4 }))
					{
						enemy->ChangeLocaition(0, 10);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() - 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
					{
						enemy->ChangeLocaition(0, 10);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
					{
						enemy->ChangeLocaition(0, 10);
						break;
					}
				}
			}
			else
			{
				enemy->ChangeLocaition(0, 10);
				if (enemy->GetLocaition().x < 0)
				{
					enemy->ChangeLocaition(0, -10);
				}
				//벽이랑 충돌체크
				for (int i = 0; i < WallCount; ++i)
				{
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + enemy->GetAniSizeY() - 4 }))
					{
						enemy->ChangeLocaition(0, -10);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() / 2,enemy->GetLocaition().y + 4 }))
					{
						enemy->ChangeLocaition(0, -10);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + enemy->GetAniSizeX() - 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
					{
						enemy->ChangeLocaition(0, -10);
						break;
					}
					if (PtInRect(&wall[i].rect, { enemy->GetLocaition().x + 4,enemy->GetLocaition().y + enemy->GetAniSizeY() / 2 }))
					{
						enemy->ChangeLocaition(0, -10);
						break;
					}
				}
			}
			// 공격 함수
			break;
		case E_ATTACK:
<<<<<<< HEAD
			if (enemy->GetCount() == 0)
			{
				if (player->GetMidPos().x < (enemy->GetLocaition().x + enemy->GetAniSizeX() / 2))
				{
					enemy->SetDirect(E_LEFT);
				}
				else
				{
					enemy->SetDirect(E_RIGHT);
				}
=======
			if (player->GetMidPos().x < (enemy->GetLocaition().x + 64))
			{
				enemy->SetDirect(E_LEFT);
			}
			else
			{
				enemy->SetDirect(E_RIGHT);
>>>>>>> origin/monster
			}
			if (enemy->GetAtkFinish())
			{
				enemy->SetAtkFinish(false);
				enemy->SetStatus(E_REST);
			}
			enemy->SetAct(1);
			// 공격 함수
			break;
		case E_REST:
			enemy->ChangeRest(1);
			if (enemy->GetRest() == 12)
			{
				enemy->SetAtkBuffer(false);
				enemy->SetRest(0);
			}
			enemy->SetAct(0);
			break;
		}
		break;
	case E_FAR:
		// 추가해야됨
		break;
	}
	
}