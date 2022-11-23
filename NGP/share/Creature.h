#pragma once
#include"GameObject.h"

class Creature : GameObject {
private:
	int		m_maxHp;	// 최대 Hp
	int		m_hp;		// 현재 Hp
	bool	m_direct;	// 바라보는 방향

public:
	// set()
	void SetHp(int vel) { m_hp = vel; }
	void SetMaxHp(int vel) { m_maxHp = vel; }
	void SetDirect(bool vel) { m_direct = vel; }

	// get()
	int GetHp() { return m_hp; }
	int GetMaxHp() { return m_maxHp; }
	bool GetDirect() { return m_direct; }

	// chagne()
	void ChangeHp(int vel) { m_hp += vel; }
	void ChangeMaxHp(int vel) { m_hp += vel; }
	void ChangeDirect() { m_direct = !m_direct; }


#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime) {};
	virtual ObjectData Encode() { return ObjectData{}; };
#endif

};

