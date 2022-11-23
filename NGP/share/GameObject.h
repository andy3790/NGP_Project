#pragma once
#include"NGP_struct.h"

class GameObject{
private:
	enum dir {
		left,
		right
	};

	int ��ġ_x;
	int ��ġ_y;

	int ũ��_x;
	int ũ��_y;
public:


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

