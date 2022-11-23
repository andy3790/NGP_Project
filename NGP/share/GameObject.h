#pragma once
#include"NGP_struct.h"

class GameObject{
private:
	enum dir {
		left,
		right
	};

	int 위치_x;
	int 위치_y;

	int 크기_x;
	int 크기_y;
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

