#include "main.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"

void MapObject::ResetMapObject(HDC hDC, int MapX, int MapY) {
	BITMAP bmp;
	hBitmap = CreateCompatibleBitmap(hDC, MapX, MapY);
	hMapBitmap1 = (HBITMAP)LoadImage(NULL, TEXT("Map/Background_1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap_GAMEOVER = (HBITMAP)LoadImage(NULL, TEXT("Map/GameOver.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	I_hBitmap_FACE = (HBITMAP)LoadImage(NULL, TEXT("icon/Face.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	I_hBitmap_SKILL1 = (HBITMAP)LoadImage(NULL, TEXT("icon/S_Skill1_icon.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	I_hBitmap_SKILL2 = (HBITMAP)LoadImage(NULL, TEXT("icon/S_Skill2_icon.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	I_hBitmap_ULT = (HBITMAP)LoadImage(NULL, TEXT("icon/Ult1_icon.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	I_hBitmap_DASH = (HBITMAP)LoadImage(NULL, TEXT("icon/dodge.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	MapSizeX = MapX;
	MapSizeY = MapY;
	GetObject(hMapBitmap1, sizeof(BITMAP), &bmp);
	bmW = bmp.bmWidth;
	bmH = bmp.bmHeight;
}
void MapObject::ChangeMapObject(HDC hDC, int MapX, int MapY) {
	DeleteObject(hBitmap);
	hBitmap = CreateCompatibleBitmap(hDC, MapX, MapY);
	MapSizeX = MapX;
	MapSizeY = MapY;
}

void MapObject::Print2Map(HDC hDC, Player* PL, Enemy* E, int EnemyCount, Wall* wall, int WallCount, RECT WndRect, int* StartPrintX, int Score) { // 맵에 오브젝트 그리기
	HDC memDC, mem2DC, mem3DC;
	HBITMAP tempBitmap, tempBitmap2;
	HBITMAP oldBitmap, oldtempBitmap, oldtempBitmap2;
	HDC mem1DC_PL, mem2DC_PL;
	HBITMAP tempPLBitmap, oldtempPLBitmap, oldPLBitmap;
	HDC mem1DC_Map;
	HBITMAP oldMapBitmap;
	HBRUSH hBrush, oldBrush, hRed, hGray;

	memDC = CreateCompatibleDC(hDC);
	oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

	mem2DC = CreateCompatibleDC(memDC);
	hBrush = CreateSolidBrush(RGB(255, 0, 255));
	oldBrush = (HBRUSH)SelectObject(mem2DC, hBrush);

	mem1DC_Map = CreateCompatibleDC(memDC);
	oldMapBitmap = (HBITMAP)SelectObject(mem1DC_Map, hMapBitmap1);
	
	Rectangle(memDC, 0, 0, MapSizeX, MapSizeY);
	StretchBlt(memDC, 0, 0, MapSizeX, MapSizeY - 100, mem1DC_Map, 0, 0, bmW, bmH, SRCCOPY);
	SelectObject(mem1DC_Map, oldMapBitmap);
	DeleteDC(mem1DC_Map);

	brick2.StretchBlt(memDC, wall[0].rect.left, wall[0].rect.top, wall[0].rect.right - wall[0].rect.left, wall[0].rect.bottom - wall[0].rect.top, 0, 0, 740, 200);;
	for (int i = 1; i < WallCount; i++) {
		brick1.StretchBlt(memDC, wall[i].rect.left, wall[i].rect.top, wall[i].rect.right - wall[i].rect.left, wall[i].rect.bottom - wall[i].rect.top, 0, 0, 626, 417);
	}

	if ((*PL).GetDamageTimer() % 2 == 0) { // Player
		if (!(*PL).UsingSkill) {
			mem1DC_PL = CreateCompatibleDC(memDC);
			tempPLBitmap = CreateCompatibleBitmap(hDC, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY());
			oldtempPLBitmap = (HBITMAP)SelectObject(mem1DC_PL, tempPLBitmap);
			mem2DC_PL = CreateCompatibleDC(mem1DC_PL);
			if ((*PL).Getact() <= 1) {
				oldPLBitmap = (HBITMAP)SelectObject(mem2DC_PL, (*PL).GethBitmap_move());
			}
			else /*if ((*PL).Getact() >= 2 && (*PL).Getact() <= 6)*/ {
				oldPLBitmap = (HBITMAP)SelectObject(mem2DC_PL, (*PL).GethBitmap_attack());
			}
			for (int i = 0; i < 5; i++) {
				if ((*PL).GetDashPt(i) > 0) {
					if ((*PL).GetDirect() == P_RIGHT) { StretchBlt(mem1DC_PL, 0, 0, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), mem2DC_PL, (*PL).GetNowanimation().x, (*PL).GetNowanimation().y, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), SRCCOPY); }
					else { StretchBlt(mem1DC_PL, 0, 0, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), mem2DC_PL, (*PL).GetNowanimation().x + (*PL).GetSpriteSizeX() - 1, (*PL).GetNowanimation().y, -(*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), SRCCOPY); }
					TransparentBlt(memDC, (*PL).GetDashPp(i).x, (*PL).GetDashPp(i).y, (*PL).GetPrintSizeX(), (*PL).GetPrintSizeY(), mem1DC_PL, 0, 0, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), RGB(255, 0, 255));
				}
			}
			if ((*PL).Getact() <= 1) {
				if ((*PL).GetDirect() == P_RIGHT) { StretchBlt(mem1DC_PL, 0, 0, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), mem2DC_PL, (*PL).GetNowanimation().x, (*PL).GetNowanimation().y, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), SRCCOPY); }
				else { StretchBlt(mem1DC_PL, 0, 0, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), mem2DC_PL, (*PL).GetNowanimation().x + (*PL).GetSpriteSizeX() - 1, (*PL).GetNowanimation().y, -(*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), SRCCOPY); }
			}
			else if ((*PL).Getact() >= 2 && (*PL).Getact() <= 5) {
				if ((*PL).GetDirect() == P_RIGHT) { StretchBlt(mem1DC_PL, 0, 0, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), mem2DC_PL, (*PL).GetNowanimation().x + (*PL).GetSpriteSizeX() - 1, (*PL).GetNowanimation().y, -(*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), SRCCOPY); }
				else { StretchBlt(mem1DC_PL, 0, 0, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), mem2DC_PL, (*PL).GetNowanimation().x, (*PL).GetNowanimation().y, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), SRCCOPY); }
			}

			//if((*PL).Getact() >= 2 && (*PL).Getact() <= 5 && (*PL).GetDirect() == P_LEFT ) { TransparentBlt(memDC, (*PL).GetPrintPos().x - (*PL).GetPrintSizeX() + 80, (*PL).GetPrintPos().y, (*PL).GetPrintSizeX(), (*PL).GetPrintSizeY(), mem1DC_PL, 0, 0, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), RGB(255, 0, 255)); }
			if (1) { TransparentBlt(memDC, (*PL).GetPrintPos().x, (*PL).GetPrintPos().y, (*PL).GetPrintSizeX(), (*PL).GetPrintSizeY(), mem1DC_PL, 0, 0, (*PL).GetSpriteSizeX(), (*PL).GetSpriteSizeY(), RGB(255, 0, 255)); }
			SelectObject(mem2DC_PL, oldPLBitmap);
			DeleteDC(mem2DC_PL);
			SelectObject(mem1DC_PL, oldtempPLBitmap);
			DeleteDC(mem1DC_PL);
			DeleteObject(tempPLBitmap);
		}
		else { // 스킬 사용 중 이라면
			if ((*PL).skillSlot[(*PL).UsingSkillNum].count < 0) { (*PL).UsingSkill = (*PL).UseSkill(((*PL).UsingSkillNum)); }
			mem1DC_PL = CreateCompatibleDC(memDC);
			tempPLBitmap = CreateCompatibleBitmap(hDC, (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeX[(*PL).skillSlot[(*PL).UsingSkillNum].act], (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeY[(*PL).skillSlot[(*PL).UsingSkillNum].act]);
			oldtempPLBitmap = (HBITMAP)SelectObject(mem1DC_PL, tempPLBitmap);
			mem2DC_PL = CreateCompatibleDC(mem1DC_PL);
			oldPLBitmap = (HBITMAP)SelectObject(mem2DC_PL, (*PL).skillSlot[(*PL).UsingSkillNum].hBitmap);

			if ((*PL).GetDirect() == P_LEFT) { StretchBlt(mem1DC_PL, 0, 0, (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeX[(*PL).skillSlot[(*PL).UsingSkillNum].act], (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeY[(*PL).skillSlot[(*PL).UsingSkillNum].act], mem2DC_PL, (*PL).skillSlot[(*PL).UsingSkillNum].animation[(*PL).skillSlot[(*PL).UsingSkillNum].act][(*PL).skillSlot[(*PL).UsingSkillNum].count].x, (*PL).skillSlot[(*PL).UsingSkillNum].animation[(*PL).skillSlot[(*PL).UsingSkillNum].act][(*PL).skillSlot[(*PL).UsingSkillNum].count].y, (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeX[(*PL).skillSlot[(*PL).UsingSkillNum].act], (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeY[(*PL).skillSlot[(*PL).UsingSkillNum].act], SRCCOPY); }
			else { StretchBlt(mem1DC_PL, 0, 0, (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeX[(*PL).skillSlot[(*PL).UsingSkillNum].act], (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeY[(*PL).skillSlot[(*PL).UsingSkillNum].act], mem2DC_PL, (*PL).skillSlot[(*PL).UsingSkillNum].animation[(*PL).skillSlot[(*PL).UsingSkillNum].act][(*PL).skillSlot[(*PL).UsingSkillNum].count].x + (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeX[(*PL).skillSlot[(*PL).UsingSkillNum].act] - 1, (*PL).skillSlot[(*PL).UsingSkillNum].animation[(*PL).skillSlot[(*PL).UsingSkillNum].act][(*PL).skillSlot[(*PL).UsingSkillNum].count].y, -(*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeX[(*PL).skillSlot[(*PL).UsingSkillNum].act], (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeY[(*PL).skillSlot[(*PL).UsingSkillNum].act], SRCCOPY); }

			if (1) { TransparentBlt(memDC, (*PL).GetPrintPos().x, (*PL).GetPrintPos().y, (*PL).GetPrintSizeX(), (*PL).GetPrintSizeY(), mem1DC_PL, 0, 0, (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeX[(*PL).skillSlot[(*PL).UsingSkillNum].act], (*PL).skillSlot[(*PL).UsingSkillNum].SpriteSizeY[(*PL).skillSlot[(*PL).UsingSkillNum].act], RGB(255, 0, 255)); }
			SelectObject(mem2DC_PL, oldPLBitmap);
			DeleteDC(mem2DC_PL);
			SelectObject(mem1DC_PL, oldtempPLBitmap);
			DeleteDC(mem1DC_PL);
			DeleteObject(tempPLBitmap);

		}
	}

	hRed = CreateSolidBrush(RGB(255, 0, 0));
	hGray = CreateSolidBrush(RGB(102, 102, 102));
	for (int i = 0; i < EnemyCount; i++) {
		if (E[i].GetHp() > 0)
		{
			tempBitmap = CreateCompatibleBitmap(hDC, E[i].GetAniSizeX(), E[i].GetAniSizeY());
			oldtempBitmap = (HBITMAP)SelectObject(mem2DC, tempBitmap);
			Rectangle(mem2DC, -1, -1, E[i].GetAniSizeX() + 1, E[i].GetAniSizeY() + 1);

			E[i].monster.Draw(mem2DC, 0, 0, E[i].GetAniSizeX(), E[i].GetAniSizeY(), E[i].GetNowAnimation().x, E[i].GetNowAnimation().y, E[i].GetAniSizeX(), E[i].GetAniSizeY());
			if (E[i].GetDirect() == E_LEFT) {
			}
			else {
				mem3DC = CreateCompatibleDC(mem2DC);
				tempBitmap2 = CreateCompatibleBitmap(hDC, E[i].GetAniSizeX(), E[i].GetAniSizeY());
				oldtempBitmap2 = (HBITMAP)SelectObject(mem3DC, tempBitmap2);
				StretchBlt(mem3DC, 0, 0, E[i].GetAniSizeX(), E[i].GetAniSizeY(), mem2DC, E[i].GetAniSizeX() - 1, 0, -E[i].GetAniSizeX(), E[i].GetAniSizeY(), SRCCOPY);
				BitBlt(mem2DC, 0, 0, E[i].GetAniSizeX(), E[i].GetAniSizeY(), mem3DC, 0, 0, SRCCOPY);
				SelectObject(mem3DC, tempBitmap2);
				DeleteObject(tempBitmap2);
				DeleteDC(mem3DC);
			}
			TransparentBlt(memDC, E[i].GetLocaition().x, E[i].GetLocaition().y, E[i].GetPrintSizeX(), E[i].GetPrintSizeY(), mem2DC, 0, 0, E[i].GetAniSizeX(), E[i].GetAniSizeY(), RGB(255, 0, 255));
			if (E[i].GetType() == E_PLANT && E[i].GetStatus() == E_REST)
			{
				Ellipse(memDC, E[i].GetBall().x - 10, E[i].GetBall().y - 10, E[i].GetBall().x + 10, E[i].GetBall().y + 10);
			}
			SelectObject(memDC, hGray);
			Rectangle(memDC, E[i].GetLocaition().x + 10, E[i].GetLocaition().y - 30, E[i].GetLocaition().x + E[i].GetPrintSizeX() - 10, E[i].GetLocaition().y - 10);
			SelectObject(memDC, hRed);
			Rectangle(memDC, E[i].GetLocaition().x + 10, E[i].GetLocaition().y - 30, E[i].GetLocaition().x + 10 + ((E[i].GetPrintSizeX() - 20) * ((float)E[i].GetHp() / (float)E[i].GetMaxHp())), E[i].GetLocaition().y - 10);
			SelectObject(memDC, GetStockObject(WHITE_BRUSH));
			SelectObject(mem2DC, oldtempBitmap);
			DeleteObject(tempBitmap);
		}
	}
	DeleteObject(hRed);
	DeleteObject(hGray);
	if (*StartPrintX + WndRect.right > MapSizeX) { *StartPrintX = MapSizeX - WndRect.right; }
	else if (*StartPrintX < WndRect.left) { *StartPrintX = WndRect.left; }

	HDC memIDC, memRIDC;
	HBITMAP oldIBitmap, oldRIBitmap;
	BITMAP bmp;
	HBRUSH IBrush, oldIBrush;
	HFONT hFont, oldFont;
	memIDC = CreateCompatibleDC(memDC);
	memRIDC = CreateCompatibleDC(memIDC);
	hBitmap_Interface = CreateCompatibleBitmap(hDC, WndRect.right, WndRect.bottom / 6);
	oldBrush = (HBRUSH)SelectObject(memIDC, hBrush);
	oldIBitmap = (HBITMAP)SelectObject(memIDC, hBitmap_Interface);
	oldRIBitmap = (HBITMAP)SelectObject(memRIDC, I_hBitmap_FACE);
	GetObject(I_hBitmap_FACE, sizeof(BITMAP), &bmp);
	Rectangle(memIDC, 0, 0, WndRect.right, WndRect.bottom / 6);
	TransparentBlt(memIDC, 50, 20, 140, 140, memRIDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 0, 255));
	SelectObject(memRIDC, oldRIBitmap);
	//IBrush = (HBRUSH)CreateSolidBrush(RGB(102, 102, 255));
	IBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	SelectObject(memIDC, oldBrush);
	//사용 가능 스킬들
	if ((*PL).GetDashCT() == (*PL).DashTimer) { oldBrush = (HBRUSH)SelectObject(memIDC, IBrush); }
	else { oldBrush = (HBRUSH)SelectObject(memIDC, (HBRUSH)GetStockObject(BLACK_BRUSH)); }
	Rectangle(memIDC, 170, 50 - 40 * (*PL).DashTimer / (*PL).GetDashCT(), 210, 50); // 대시 쿨
	oldRIBitmap = (HBITMAP)SelectObject(memRIDC, I_hBitmap_DASH);
	GetObject(I_hBitmap_DASH, sizeof(BITMAP), &bmp);
	TransparentBlt(memIDC, 170, 10, 40, 40, memRIDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 0, 255));
	SelectObject(memRIDC, oldRIBitmap);
	SelectObject(memIDC, oldBrush);

	if ((*PL).GetS1CT() == 0) { oldBrush = (HBRUSH)SelectObject(memIDC, IBrush); }
	else { oldBrush = (HBRUSH)SelectObject(memIDC, (HBRUSH)GetStockObject(BLACK_BRUSH)); }
	Rectangle(memIDC, 200, 60 + 50 * (*PL).GetS1CT() / (*PL).GetS1MCT(), 250, 110); // 스킬 1 쿨
	oldRIBitmap = (HBITMAP)SelectObject(memRIDC, I_hBitmap_SKILL1);
	GetObject(I_hBitmap_SKILL1, sizeof(BITMAP), &bmp);
	TransparentBlt(memIDC, 200, 60, 50, 50, memRIDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 0, 255));
	SelectObject(memRIDC, oldRIBitmap);
	SelectObject(memIDC, oldBrush);

	if ((*PL).GetS2CT() == 0) { oldBrush = (HBRUSH)SelectObject(memIDC, IBrush); }
	else { oldBrush = (HBRUSH)SelectObject(memIDC, (HBRUSH)GetStockObject(BLACK_BRUSH)); }
	Rectangle(memIDC, 270, 60 + 50 * (*PL).GetS2CT() / (*PL).GetS2MCT(), 320, 110); // 스킬 2 쿨
	oldRIBitmap = (HBITMAP)SelectObject(memRIDC, I_hBitmap_SKILL2);
	GetObject(I_hBitmap_SKILL2, sizeof(BITMAP), &bmp);
	TransparentBlt(memIDC, 270, 60, 50, 50, memRIDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 0, 255));
	SelectObject(memRIDC, oldRIBitmap);
	SelectObject(memIDC, oldBrush);

	if ((*PL).GetUltCT() == 0) { oldBrush = (HBRUSH)SelectObject(memIDC, IBrush); }
	else { oldBrush = (HBRUSH)SelectObject(memIDC, (HBRUSH)GetStockObject(BLACK_BRUSH)); }
	Rectangle(memIDC, 350, 30 + 80 * (*PL).GetUltCT() / (*PL).GetUltMCT(), 430, 110); // 궁 쿨
	oldRIBitmap = (HBITMAP)SelectObject(memRIDC, I_hBitmap_ULT);
	GetObject(I_hBitmap_ULT, sizeof(BITMAP), &bmp);
	TransparentBlt(memIDC, 350, 30, 80, 80, memRIDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 0, 255));
	SelectObject(memRIDC, oldRIBitmap);
	SelectObject(memIDC, oldBrush);

	DeleteObject(IBrush);
	IBrush = CreateSolidBrush(RGB(051, 051, 051));
	oldBrush = (HBRUSH)SelectObject(memIDC, IBrush);
	Rectangle(memIDC, 180, 130, (*PL).GetMaxHp() * 3 + 180, 160); // 최대체력바
	SelectObject(memIDC, oldBrush);

	DeleteObject(IBrush);
	IBrush = CreateSolidBrush(RGB(204, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memIDC, IBrush);
	Rectangle(memIDC, 180, 130, (*PL).GetNowHp() * 3 + 180, 160); // 현재체력바
	SelectObject(memIDC, oldBrush);

	SetBkMode(memIDC, TRANSPARENT);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memIDC, RGB(255, 255, 255));
	SetTextColor(memDC, RGB(255, 255, 255));

	hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
	oldFont = (HFONT)SelectObject(memIDC, hFont);

	TCHAR str[20];
	wsprintf(str, L"%d / %d", (*PL).GetNowHp(), (*PL).GetMaxHp());
	TextOut(memIDC, (*PL).GetMaxHp() * 3 / 2 - 40 + 180, 135, str, _tcslen(str));
	SelectObject(memIDC, oldFont);


	oldFont = (HFONT)SelectObject(memDC, hFont);
	wsprintf(str, L"Score : %d", Score);
	TextOut(memDC, WndRect.right - 150 + *StartPrintX, WndRect.top + 50, str, _tcslen(str));

	SelectObject(memDC, oldFont);
	DeleteObject(hFont);

	TransparentBlt(memDC, *StartPrintX, WndRect.bottom / 6 * 5, WndRect.right, WndRect.bottom / 6, memIDC, 0, 0, WndRect.right, WndRect.bottom / 6, RGB(255, 0, 255));

	SelectObject(memIDC, oldIBitmap);
	DeleteObject(hBitmap_Interface);
	DeleteObject(IBrush);
	DeleteDC(memIDC);
	DeleteDC(memRIDC);

	static int GameOverTimer = 0;
	if ((*PL).GetNowHp() <= 0) {
		//BlackOut
		HDC memEndDC;
		BLENDFUNCTION bf;
		HBITMAP Black_Bg, oldtempbhBitmap;
		HBRUSH htempBrush;
		HFONT hFont, oldFont;
		SetBkMode(memDC, TRANSPARENT);
		SetTextColor(memDC, RGB(255, 255, 255));
		hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
		oldFont = (HFONT)SelectObject(memDC, hFont);

		if (GameOverTimer < 255) { GameOverTimer++; }

		memEndDC = CreateCompatibleDC(hDC);
		Black_Bg = (HBITMAP)CreateCompatibleBitmap(hDC, WndRect.right, WndRect.bottom);
		oldtempbhBitmap = (HBITMAP)SelectObject(memEndDC, Black_Bg);
		htempBrush = (HBRUSH)SelectObject(memEndDC, (HBRUSH)GetStockObject(BLACK_BRUSH));
		Rectangle(memEndDC, WndRect.left, WndRect.top, WndRect.right, WndRect.bottom);
		SelectObject(memEndDC, oldtempbhBitmap);

		bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
		bf.BlendFlags = 0; // 무조건 0이어야 한다
		bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
		bf.SourceConstantAlpha = GameOverTimer; // 투명도(투명 0 - 불투명 255)
		oldtempbhBitmap = (HBITMAP)SelectObject(memEndDC, Black_Bg);
		AlphaBlend(memDC, *StartPrintX, WndRect.top, WndRect.right, WndRect.bottom, memEndDC, WndRect.left, WndRect.top, WndRect.right, WndRect.bottom, bf);
		//StretchBlt(hDC, *StartPrintX, WndRect.top, WndRect.right, WndRect.bottom, memDC, WndRect.left, WndRect.top, WndRect.right, WndRect.bottom, SRCCOPY);
		SelectObject(memEndDC, oldtempbhBitmap);
		DeleteObject(htempBrush);
		DeleteDC(memEndDC);

		//Game Over
		mem3DC = CreateCompatibleDC(hDC);
		oldtempBitmap = (HBITMAP)SelectObject(mem3DC, hBitmap_GAMEOVER);
		BITMAP bmp;
		GetObject(hBitmap_GAMEOVER, sizeof(BITMAP), &bmp);
		TransparentBlt(memDC, *StartPrintX, WndRect.top, WndRect.right, WndRect.bottom, mem3DC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 0, 255));
		SelectObject(mem3DC, oldtempBitmap);
		DeleteDC(mem3DC);

		TCHAR str[20];
		wsprintf(str, L"Score : %d", Score);
		TextOut(memDC, (WndRect.right + WndRect.left) / 2 - 150 + *StartPrintX, (WndRect.top + WndRect.bottom) / 2 + 400, str, _tcslen(str));

		wsprintf(str, L"아무키나 눌러 게임을 종료합니다.");
		TextOut(memDC, (WndRect.right + WndRect.left) / 2 - 350 + *StartPrintX, (WndRect.top + WndRect.bottom) / 2 - 400, str, _tcslen(str));


		SelectObject(memDC, oldFont);
		DeleteObject(hFont);

	}
	else { GameOverTimer = 0; }
	BitBlt(hDC, WndRect.left, WndRect.top, WndRect.right, WndRect.bottom, memDC, *StartPrintX, 0, SRCCOPY);

	SelectObject(mem2DC, oldBrush);
	DeleteObject(hBrush);
	DeleteDC(mem2DC);

	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);

}

//E1.MakeEnemy(E_BIRD, { 500,440 }, 32, 32, E_LEFT, L"bat.png");
//E1.MakeEnemy(E_WOLF, { 500,440 }, 64, 32, E_LEFT, L"wolf.png");
//E1.MakeEnemy(E_BASE, { 500,440 }, 128, 128, E_LEFT, L"enemy.png");
//E1.MakeEnemy(E_PLANT, { 500,650 }, 128, 128, E_LEFT, L"plant.png");

void MapObject::StartMapObject(int* map_num, Enemy E[10], int* enemy_num) {
	*map_num = rand() % 3;
	switch (*map_num)
	{
	case MAP1:
		E[0].MakeEnemy(E_BASE, { 500,600 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		E[1].MakeEnemy(E_WOLF, { 1300,500 }, 64, 32, E_LEFT, L"Enemy/wolf.png");
		E[2].MakeEnemy(E_BIRD, { 600,300 }, 32, 32, E_LEFT, L"Enemy/bat.png");
		E[3].MakeEnemy(E_PLANT, { 800,370 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[4].MakeEnemy(E_BASE, { 2000,400 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		E[5].MakeEnemy(E_WOLF, { 2900,500 }, 64, 32, E_LEFT, L"Enemy/wolf.png");
		*enemy_num = 6;
		break;
	case MAP2:
		E[0].MakeEnemy(E_PLANT, { 1856,300 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[1].MakeEnemy(E_PLANT, { 400,500 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[2].MakeEnemy(E_PLANT, { 3300,500 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[3].MakeEnemy(E_BASE, { 1100,600 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		E[4].MakeEnemy(E_BIRD, { 2200,550 }, 32, 32, E_LEFT, L"Enemy/bat.png");
		E[5].MakeEnemy(E_WOLF, { 1300,200 }, 64, 32, E_LEFT, L"Enemy/wolf.png");
		E[6].MakeEnemy(E_BASE, { 2300,200 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		*enemy_num = 7;
		break;
	case MAP3:
		E[0].MakeEnemy(E_PLANT, { 1100,500 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[1].MakeEnemy(E_PLANT, { 1900,800 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[2].MakeEnemy(E_BIRD, { 1872,200 }, 32, 32, E_LEFT, L"Enemy/bat.png");
		E[3].MakeEnemy(E_BASE, { 2000,450 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		E[4].MakeEnemy(E_BASE, { 3100,550 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		E[5].MakeEnemy(E_WOLF, { 2550,400 }, 64, 32, E_LEFT, L"Enemy/wolf.png");
		*enemy_num = 6;
		break;
	}
}

void MapObject::ClearMapObject(int* map_num, Enemy E[10], int* enemy_num) {
	for (int i = 0; i < *enemy_num; ++i)
	{
		E[i].DelelteEnemy();
	}
	switch (*map_num)
	{
	case MAP1:
		if (rand() % 2 == 0)
		{
			*map_num = MAP2;
		}
		else
		{
			*map_num = MAP3;
		}
		break;
	case MAP2:
		if (rand() % 2 == 0)
		{
			*map_num = MAP1;
		}
		else
		{
			*map_num = MAP3;
		}
		break;
	case MAP3:
		if (rand() % 2 == 0)
		{
			*map_num = MAP1;
		}
		else
		{
			*map_num = MAP2;
		}
		break;
	}
	
	switch (*map_num)
	{
	case MAP1:
		E[0].MakeEnemy(E_BASE, { 500,600 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		E[1].MakeEnemy(E_WOLF, { 1300,500 }, 64, 32, E_LEFT, L"Enemy/wolf.png");
		E[2].MakeEnemy(E_BIRD, { 600,300 }, 32, 32, E_LEFT, L"Enemy/bat.png");
		E[3].MakeEnemy(E_PLANT, { 800,370 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[4].MakeEnemy(E_BASE, { 2000,400 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		E[5].MakeEnemy(E_WOLF, { 2900,500 }, 64, 32, E_LEFT, L"Enemy/wolf.png");
		*enemy_num = 6;
		break;
	case MAP2:
		E[0].MakeEnemy(E_PLANT, { 1856,300 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[1].MakeEnemy(E_PLANT, { 400,500 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[2].MakeEnemy(E_PLANT, { 3300,500 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[3].MakeEnemy(E_BASE, { 1100,600 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		E[4].MakeEnemy(E_BIRD, { 2200,550 }, 32, 32, E_LEFT, L"Enemy/bat.png");
		E[5].MakeEnemy(E_WOLF, { 1300,200 }, 64, 32, E_LEFT, L"Enemy/wolf.png");
		E[6].MakeEnemy(E_BASE, { 2300,200 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		*enemy_num = 7;
		break;
	case MAP3:
		E[0].MakeEnemy(E_PLANT, { 1100,500 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[1].MakeEnemy(E_PLANT, { 1900,800 }, 128, 128, E_LEFT, L"Enemy/plant.png");
		E[2].MakeEnemy(E_BIRD, { 1872,200 }, 32, 32, E_LEFT, L"Enemy/bat.png");
		E[3].MakeEnemy(E_BASE, { 2000,450 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		E[4].MakeEnemy(E_BASE, { 3100,550 }, 128, 128, E_LEFT, L"Enemy/enemy.png");
		E[5].MakeEnemy(E_WOLF, { 2550,400 }, 64, 32, E_LEFT, L"Enemy/wolf.png");
		*enemy_num = 6;
		break;
	}
}

int MapObject::GetMapX() { return MapSizeX; }
int MapObject::GetMapY() { return MapSizeY; }