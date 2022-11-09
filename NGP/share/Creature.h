#pragma once
#include"GameObject.h"

class Creature : GameObject {
private:
	int		m_maxHp;	// �ִ� Hp
	int		m_hp;		// ���� Hp
	bool	m_direct;	// �ٶ󺸴� ����

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

