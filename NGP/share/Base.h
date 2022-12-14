#pragma once
#include"Enemy.h"

class Base : Enemy{
private:
	CImage myImage;

public:
	Base() {}
	Base(POINT location, int dir) { MakeEnemy(location, dir); }

	void MakeEnemy(POINT location, int dir);
	void DelelteEnemy();

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

