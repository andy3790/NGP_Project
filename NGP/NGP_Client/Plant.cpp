#include "Plant.h"

void Plant::MakeEnemy(POINT location, int dir)
{
	myImage.Load((LPCTSTR)L"../Resorce/Image/Enemy/plant.png");

	int aniSizeX = 128;
	int aniSizeY = 128;

	animation = (POINT**)malloc(sizeof(POINT*) * 1);
	animation[0] = (POINT*)malloc(sizeof(POINT) * 1);
	animation[0][0] = { 0, 0 };
	max_hp = 50;
	hp = 50;
	damage = 10;
	printsizex = aniSizeX;
	printsizey = aniSizeY;



	count = 0;
	act = 0;
	loca = location;
	direct = dir;
	status = E_SEEK;
	anisizex = aniSizeX;
	anisizey = aniSizeY;

	alive = true;
	move = false;
	atk_buffer = false;
	atk_finish = false;
	rest = 0;
}

void Plant::DelelteEnemy()
{
	free(animation[0]);
	free(animation);

	myImage.Destroy();
}

void Plant::Render(HDC hDC, HBITMAP hBitmap, RECT WndRect)
{
	HDC memDC, mem2DC, mem3DC;
	HBITMAP tempBitmap0, tempBitmap, tempBitmap2;
	HBITMAP oldBitmap, oldtempBitmap, oldtempBitmap2;
	HDC mem1DC_Map;
	HBITMAP oldMapBitmap;
	HBRUSH hBrush, oldBrush, hRed, hGray;

	memDC = CreateCompatibleDC(hDC);
	tempBitmap0 = CreateCompatibleBitmap(hDC, GetAniSizeX(), GetAniSizeY());
	oldBitmap = (HBITMAP)SelectObject(memDC, tempBitmap0);

	mem2DC = CreateCompatibleDC(memDC);
	hBrush = CreateSolidBrush(RGB(255, 0, 255));
	oldBrush = (HBRUSH)SelectObject(mem2DC, hBrush);

	hRed = CreateSolidBrush(RGB(255, 0, 0));
	hGray = CreateSolidBrush(RGB(102, 102, 102));
	if (GetHp() > 0)
	{
		tempBitmap = CreateCompatibleBitmap(hDC, GetAniSizeX(), GetAniSizeY());
		oldtempBitmap = (HBITMAP)SelectObject(mem2DC, tempBitmap);
		Rectangle(mem2DC, -1, -1, GetAniSizeX() + 1, GetAniSizeY() + 1);

		myImage.Draw(mem2DC, 0, 0, GetAniSizeX(), GetAniSizeY(), GetNowAnimation().x, GetNowAnimation().y, GetAniSizeX(), GetAniSizeY());
		if (GetDirect() == E_LEFT) {
		}
		else {
			mem3DC = CreateCompatibleDC(mem2DC);
			tempBitmap2 = CreateCompatibleBitmap(hDC, GetAniSizeX(), GetAniSizeY());
			oldtempBitmap2 = (HBITMAP)SelectObject(mem3DC, tempBitmap2);
			StretchBlt(mem3DC, 0, 0, GetAniSizeX(), GetAniSizeY(), mem2DC, GetAniSizeX() - 1, 0, -GetAniSizeX(), GetAniSizeY(), SRCCOPY);
			BitBlt(mem2DC, 0, 0, GetAniSizeX(), GetAniSizeY(), mem3DC, 0, 0, SRCCOPY);
			SelectObject(mem3DC, tempBitmap2);
			DeleteObject(tempBitmap2);
			DeleteDC(mem3DC);
		}
		
		BitBlt(memDC, 0, 0, GetAniSizeX(), GetAniSizeY(), mem2DC, 0, 0, SRCCOPY);
		TransparentBlt(hDC, GetLocaition().x, GetLocaition().y, GetPrintSizeX(), GetPrintSizeY(), memDC, 0, 0, GetAniSizeX(), GetAniSizeY(), RGB(255, 0, 255));
		
		if (GetStatus() == E_REST)
		{
			Ellipse(hDC, GetBall().x - 10, GetBall().y - 10, GetBall().x + 10, GetBall().y + 10);
		}

		SelectObject(hDC, hGray);
		Rectangle(hDC, GetLocaition().x + 10, GetLocaition().y - 30, GetLocaition().x + GetPrintSizeX() - 10, GetLocaition().y - 10);
		SelectObject(hDC, hRed);
		Rectangle(hDC, GetLocaition().x + 10, GetLocaition().y - 30, GetLocaition().x + 10 + ((GetPrintSizeX() - 20) * ((float)GetHp() / (float)GetMaxHp())), GetLocaition().y - 10);
		SelectObject(hDC, GetStockObject(WHITE_BRUSH));
		SelectObject(mem2DC, oldtempBitmap);
		DeleteObject(tempBitmap);
	}

	DeleteObject(hRed);
	DeleteObject(hGray);

	SelectObject(mem2DC, oldBrush);
	DeleteObject(hBrush);
	DeleteDC(mem2DC);

	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
}

void Plant::Decode(ObjectData object_data)
{
	Enemy::SetLocaition((int)object_data.pos.x, (int)object_data.pos.y);
	Enemy::SetHp((int)object_data.hp);
	Enemy::SetAct((int)object_data.state);
}