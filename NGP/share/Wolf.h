#pragma once
#include"Enemy.h"
class Wolf : Enemy{
private:


public:

#if CONSOL==CLIENT
public:
	void Render(HDC hDC, HBITMAP hBitmap, RECT WndRect);
	void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	void Update(float eTime);
	ObjectData Encode();
#endif

};

