#pragma once
#include"Creature.h"
class Player : Creature {
private:


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
