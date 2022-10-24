#include "main.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"

// 타입 추가
void Enemy::MakeEnemy(int aniNumX, int aniNumY, int aniSizeX, int aniSizeY, int dir, const TCHAR name[]) {
	monster.Load((LPCTSTR)name);
	animation = (POINT**)malloc(sizeof(POINT*) * aniNumX);
	for (int i = 0; i < aniNumY; i++) {
		animation[i] = (POINT*)malloc(sizeof(POINT) * aniNumY);
	}

	for (int i = 0; i < aniNumX; i++) {
		for (int j = 0; j < aniNumY; j++) {
			animation[i][j] = { aniSizeX * i, aniSizeY * j };
		}
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
				if (player->GetMidPos().x < (enemy->GetLocaition().x + 64))
				{
					enemy->SetDirect(E_LEFT);
				}
				else
				{
					enemy->SetDirect(E_RIGHT);
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
				if (player->GetMidPos().x < (enemy->GetLocaition().x + 64))
				{
					enemy->SetDirect(E_LEFT);
				}
				else
				{
					enemy->SetDirect(E_RIGHT);
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
		break;
	case E_FAR:
		break;
	}
	
}