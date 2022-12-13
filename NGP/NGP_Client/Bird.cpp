#include "Bird.h"

void Bird::MakeEnemy(POINT location, int dir)
{
	myImage.Load((LPCTSTR)L"../Resorce/Image/Enemy/bat.png");

	int aniSizeX = 32;
	int aniSizeY = 32;

	animation = (POINT**)malloc(sizeof(POINT*) * 2);
	for (int i = 0; i < 2; i++) {
		animation[i] = (POINT*)malloc(sizeof(POINT) * 3);
	}

	for (int j = 0; j < 3; ++j)
	{
		animation[0][j] = { 32 * j + 32,aniSizeY * 0 };
	}
	for (int j = 0; j < 3; ++j)
	{
		animation[1][j] = { 32 * j + 32,aniSizeY * 3 };
	}
	max_hp = 40;
	hp = 40;
	damage = 5;
	printsizex = 3 * aniSizeX;
	printsizey = 3 * aniSizeY;



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

void Bird::DelelteEnemy()
{
	for (int i = 0; i < 2; i++) { free(animation[i]); }
	free(animation);

	myImage.Destroy();
}

void Bird::Render(HDC hDC, HBITMAP hBitmap, RECT WndRect)
{
	HDC memDC, mem2DC, mem3DC;
	HBITMAP tempBitmap, tempBitmap2;
	HBITMAP oldBitmap, oldtempBitmap, oldtempBitmap2;
	HDC mem1DC_Map;
	HBITMAP oldMapBitmap;
	HBRUSH hBrush, oldBrush, hRed, hGray;

	memDC = CreateCompatibleDC(hDC);
	oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

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
		TransparentBlt(memDC, GetLocaition().x, GetLocaition().y, GetPrintSizeX(), GetPrintSizeY(), mem2DC, 0, 0, GetAniSizeX(), GetAniSizeY(), RGB(255, 0, 255));

		SelectObject(memDC, hGray);
		Rectangle(memDC, GetLocaition().x + 10, GetLocaition().y - 30, GetLocaition().x + GetPrintSizeX() - 10, GetLocaition().y - 10);
		SelectObject(memDC, hRed);
		Rectangle(memDC, GetLocaition().x + 10, GetLocaition().y - 30, GetLocaition().x + 10 + ((GetPrintSizeX() - 20) * ((float)GetHp() / (float)GetMaxHp())), GetLocaition().y - 10);
		SelectObject(memDC, GetStockObject(WHITE_BRUSH));
		SelectObject(mem2DC, oldtempBitmap);
		DeleteObject(tempBitmap);
	}

	DeleteObject(hRed);
	DeleteObject(hGray);
}

void Bird::Decode(ObjectData object_data)
{

}