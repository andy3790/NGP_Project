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
	virtual void Render(HDC hDC, HBITMAP hBitmap, RECT WndRect) = 0;
	virtual void Decode(ObjectData object_data) = 0;

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime, RECT WndRect) {};
	virtual ObjectData Encode() { return ObjectData{}; };
#endif

};

