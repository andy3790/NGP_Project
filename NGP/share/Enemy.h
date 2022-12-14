#pragma once
#include"Creature.h"

class Enemy: Creature{
public:
	enum direction {
		E_LEFT,
		E_RIGHT
	};

	enum status {
		E_SEEK,
		E_MOVE,
		E_ATTACK,
		E_REST
	};

private:

protected:
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
	virtual void MakeEnemy(POINT location, int dir) = 0;
	virtual void DelelteEnemy() = 0;

	void SetType(int Type) { type = Type; }
	void SetAct(int Act) { act = Act; }
	void SetCount(int Count) { count = Count; }
	void SetLocaition(int x, int y) { loca.x = x; loca.y = y; }
	void SetStatus(int Status) { status = Status; }
	void SetMove(BOOL Move) { move = Move; }
	void SetDirect(int Dir) { direct = Dir; }
	void SetFloor(BOOL Floor) { floor = Floor; }

	void ChangeType(int i) { type += i; }
	void ChangeAct(int i) { act += i; }
	void ChangeCount(int i) { count += i; }
	void ChangeLocaition(int x, int y) { loca.x += x; loca.y += y; }
	void ChangeStatus(int i) { status += i; }
	void ChangeMove() { move = !move; }
	void ChangeDirect(int i) { direct += i; }
	void ChangeFloor() { floor = !floor; }

	POINT GetAnimation(int x, int y) { return animation[y][x]; }
	POINT GetNowAnimation() { return animation[act][count]; }
	POINT GetLocaition() { return loca; }
	int GetType() { return type; }
	int GetAct() { return act; }
	int GetCount() { return count; }
	int GetStatus() { return status; }
	int GetDirect() { return direct; }
	int GetAniSizeX() { return anisizex; }
	int GetAniSizeY() { return anisizey; }
	BOOL GetFloor() { return floor; }
	BOOL GetMove() { return move; }

	void SetAtkBuffer(BOOL Atk_buffer) { atk_buffer = Atk_buffer; }
	BOOL GetAtkBuffer() { return atk_buffer; }

	void SetAtkFinish(BOOL Atk_finish) { atk_finish = Atk_finish; }
	BOOL GetAtkFinish() { return atk_finish; }

	void SetRest(int Rest) { rest = Rest; }
	void ChangeRest(int i) { rest += i; }
	int GetRest() { return rest; }

	void SetHp(int Hp) { hp = Hp; }
	void ChangeHp(int i) { hp -= i; }
	int GetHp() { return hp; }

	void SetDamage(int Damage) { damage = Damage; }
	int GetDamege() { return damage; }

	int GetPrintSizeX() { return printsizex; }
	int GetPrintSizeY() { return printsizey; }

	void SetBall(POINT loca) { ball = loca; }
	POINT GetBall() { return ball; }

	int GetMaxHp() { return max_hp; }

	void SetAlive(BOOL live) { alive = live; }
	BOOL GetAlive() { return alive; }

	POINT** GetAnimationPointer() { return animation; }

#if CONSOL==CLIENT
public:
	virtual void Render(HDC hDC, HBITMAP hBitmap, RECT WndRect) = 0;
	virtual void Decode(ObjectData object_data) = 0;

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime, RECT WndRect);
	virtual ObjectData Encode();
	STATE IntToState_Enemey(int in, int dir);
#endif

};

