#pragma once
#include"GameObject.h"
class Projectile : GameObject {
private:


public:

#if CONSOL==CLIENT
public:
	void Render(HDC hDC, HBITMAP hBitmap, RECT WndRect);
	void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	void Update(float eTime, RECT WndRect);
	ObjectData Encode();
#endif

};

