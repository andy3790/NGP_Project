#pragma once
#include"GameObject.h"

class Creature : GameObject {
private:
	int		m_maxHp;	// 최대 Hp
	int		m_hp;		// 현재 Hp
	bool	m_direct;	// 바라보는 방향

	float	m_age;		// 애니메이션 용 시간 저장 변수

public:
	// set()
	void SetHp(int vel) { m_hp = vel; }
	void SetMaxHp(int vel) { m_maxHp = vel; }
	void SetDirect(bool vel) { m_direct = vel; }
	void SetAge(float vel) { m_age = vel; }

	// get()
	int GetHp() { return m_hp; }
	int GetMaxHp() { return m_maxHp; }
	bool GetDirect() { return m_direct; }
	float GetAge() { return m_age; }

	// chagne()
	void ChangeHp(int vel) { m_hp += vel; }
	void ChangeMaxHp(int vel) { m_hp += vel; }
	void ChangeDirect() { m_direct = !m_direct; }
	void ChangeAge(float vel) { m_age += vel; }


#if CONSOL==CLIENT
public:
	virtual void Render(HDC hDC, HBITMAP hBitmap, RECT WndRect) = 0;
	virtual void Decode(ObjectData object_data) = 0;

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime) {};
	virtual ObjectData Encode() { return ObjectData{}; };
#endif

};

