#pragma once
#include"GameObject.h"

class Creature : GameObject {
private:
	int		m_maxHp;	// 최대 Hp
	int		m_hp;		// 현재 Hp
	bool	m_direct;	// 바라보는 방향

public:

#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif

};

