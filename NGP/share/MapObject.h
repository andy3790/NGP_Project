#pragma once
#include"GameObject.h"

class MapObject : GameObject{
private:


public:

#if CONSOL==CLIENT
public:
	virtual void Render(HDC hDC, HBITMAP hBitmap, RECT WndRect);
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif

};

