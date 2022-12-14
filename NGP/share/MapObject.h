#pragma once
#include"GameObject.h"

class MapObject : GameObject{
private:


public:

#if CONSOL==CLIENT
public:
	virtual void Render(HDC hDC, HBITMAP hBitmap, RECT WndRect) = 0;
	virtual void Decode(ObjectData object_data) = 0;

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime) = 0;
	virtual ObjectData Encode() = 0;
#endif

};

