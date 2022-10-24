#pragma once
#define E_LEFT 0
#define E_RIGHT 1

#define E_SEEK 0
#define E_MOVE 1
#define E_ATTACK 2
#define E_REST 3

#define E_BASE 0
#define E_WOLF 1
#define E_PLANT 2
#define E_BIRD 3
#define E_FAR 4

class Enemy {
private:
	POINT** animation; // act count
	POINT loca;
	int type; //
	int act; // 0 hold 1 move 2 attack
	int count;
	int status; // seek(hold, roam) follow(move) attack(attack)
	int direct;
	int anisizex;
	int anisizey;
	int printsizex;
	int printsizey;
	BOOL move;
	BOOL floor; //
	BOOL atk_buffer;
	BOOL atk_finish;
	int rest;
	int max_hp;
	int hp;
	int damage;
	POINT ball;
	BOOL alive;
public:
	CImage monster; // 128 128

	Enemy& operator= (Enemy&& other)
	{
		monster.Destroy();
		monster.Attach(other.monster.Detach());
		return *this;
	}

	void MakeEnemy(int e_type, POINT location, int aniSizeX, int aniSizeY, int dir, const TCHAR name[]);
	void DelelteEnemy();
	void SetType(int Type);
	void SetAct(int Act);
	void SetCount(int Count);
	void SetLocaition(int x, int y);
	void SetStatus(int Status);
	void SetMove(BOOL Move);
	void SetDirect(int Dir);
	void SetFloor(BOOL Floor);

	void ChangeType(int i);
	void ChangeAct(int i);
	void ChangeCount(int i);
	void ChangeLocaition(int x, int y);
	void ChangeStatus(int i);
	void ChangeMove();
	void ChangeDirect(int i);
	void ChangeFloor();

	POINT GetAnimation(int x, int y);
	POINT GetNowAnimation();
	POINT GetLocaition();
	int GetType();
	int GetAct();
	int GetCount();
	int GetStatus();
	int GetDirect();
	int GetAniSizeX();
	int GetAniSizeY();
	BOOL GetMove();
	BOOL GetFloor();

	void SetAtkBuffer(BOOL Atk_buffer);
	BOOL GetAtkBuffer();
	void SetAtkFinish(BOOL Atk_finish);
	BOOL GetAtkFinish();
	void SetRest(int Rest);
	void ChangeRest(int i);
	int GetRest();
	void SetHp(int Hp);
	void ChangeHp(int i);
	int GetHp();
	void SetDamage(int Damage);
	int GetDamege();
	int GetPrintSizeX();
	int GetPrintSizeY();
	void SetBall(POINT loca);
	POINT GetBall();
	int GetMaxHp();
	void SetAlive(BOOL live);
	BOOL GetAlive();
};

void Enemy_AI(HWND hWnd, Player* player, Enemy* enemy, RECT WndRect, Wall* wall, int WallCount, int* score);