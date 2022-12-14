#pragma once
#include"Enemy.h"
class Bird : Enemy {
private:
	CImage myImage;

public:
	Bird() {}
	Bird(POINT location, int dir) { MakeEnemy(location, dir); }

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

