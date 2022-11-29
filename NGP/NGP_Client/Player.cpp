#include "Player.h"

void Player::Render(HDC hDC, HBITMAP hBitmap, RECT WndRect)
{
	HDC memDC, mem2DC, mem3DC;
	HBITMAP tempBitmap, tempBitmap2;
	HBITMAP oldBitmap;
	HDC mem1DC_PL, mem2DC_PL;
	HBITMAP tempPLBitmap, oldtempPLBitmap, oldPLBitmap;
	HBRUSH hBrush, oldBrush;

	memDC = CreateCompatibleDC(hDC);
	oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

	mem2DC = CreateCompatibleDC(memDC);
	hBrush = CreateSolidBrush(RGB(255, 0, 255));
	oldBrush = (HBRUSH)SelectObject(mem2DC, hBrush);

	if (GetDamageTimer() % 2 == 0) { // Player
		if (UsingSkill) {
			mem1DC_PL = CreateCompatibleDC(memDC);
			tempPLBitmap = CreateCompatibleBitmap(hDC, GetSpriteSizeX(), GetSpriteSizeY());
			oldtempPLBitmap = (HBITMAP)SelectObject(mem1DC_PL, tempPLBitmap);
			mem2DC_PL = CreateCompatibleDC(mem1DC_PL);
			if (Getact() <= 1) {
				oldPLBitmap = (HBITMAP)SelectObject(mem2DC_PL, GethBitmap_move());
			}
			else {
				oldPLBitmap = (HBITMAP)SelectObject(mem2DC_PL, GethBitmap_attack());
			}
			for (int i = 0; i < 5; i++) {
				if (GetDashPt(i) > 0) {
					if (GetDirect() == P_RIGHT) { StretchBlt(mem1DC_PL, 0, 0, GetSpriteSizeX(), GetSpriteSizeY(), mem2DC_PL, GetNowanimation().x, GetNowanimation().y, GetSpriteSizeX(), GetSpriteSizeY(), SRCCOPY); }
					else { StretchBlt(mem1DC_PL, 0, 0, GetSpriteSizeX(), GetSpriteSizeY(), mem2DC_PL, GetNowanimation().x + GetSpriteSizeX() - 1, GetNowanimation().y, -GetSpriteSizeX(), GetSpriteSizeY(), SRCCOPY); }
					TransparentBlt(memDC, GetDashPp(i).x, GetDashPp(i).y, GetPrintSizeX(), GetPrintSizeY(), mem1DC_PL, 0, 0, GetSpriteSizeX(), GetSpriteSizeY(), RGB(255, 0, 255));
				}
			}
			if (Getact() <= 1) {
				if (GetDirect() == P_RIGHT) { StretchBlt(mem1DC_PL, 0, 0, GetSpriteSizeX(), GetSpriteSizeY(), mem2DC_PL, GetNowanimation().x, GetNowanimation().y, GetSpriteSizeX(), GetSpriteSizeY(), SRCCOPY); }
				else { StretchBlt(mem1DC_PL, 0, 0, GetSpriteSizeX(), GetSpriteSizeY(), mem2DC_PL, GetNowanimation().x + GetSpriteSizeX() - 1, GetNowanimation().y, -GetSpriteSizeX(), GetSpriteSizeY(), SRCCOPY); }
			}
			else if (Getact() >= 2 && Getact() <= 5) {
				if (GetDirect() == P_RIGHT) { StretchBlt(mem1DC_PL, 0, 0, GetSpriteSizeX(), GetSpriteSizeY(), mem2DC_PL, GetNowanimation().x + GetSpriteSizeX() - 1, GetNowanimation().y, -GetSpriteSizeX(), GetSpriteSizeY(), SRCCOPY); }
				else { StretchBlt(mem1DC_PL, 0, 0, GetSpriteSizeX(), GetSpriteSizeY(), mem2DC_PL, GetNowanimation().x, GetNowanimation().y, GetSpriteSizeX(), GetSpriteSizeY(), SRCCOPY); }
			}

			//if(Getact() >= 2 && Getact() <= 5 && GetDirect() == P_LEFT ) { TransparentBlt(memDC, GetPrintPos().x - GetPrintSizeX() + 80, GetPrintPos().y, GetPrintSizeX(), GetPrintSizeY(), mem1DC_PL, 0, 0, GetSpriteSizeX(), GetSpriteSizeY(), RGB(255, 0, 255)); }
			if (1) { TransparentBlt(memDC, GetPrintPos().x, GetPrintPos().y, GetPrintSizeX(), GetPrintSizeY(), mem1DC_PL, 0, 0, GetSpriteSizeX(), GetSpriteSizeY(), RGB(255, 0, 255)); }
			SelectObject(mem2DC_PL, oldPLBitmap);
			DeleteDC(mem2DC_PL);
			SelectObject(mem1DC_PL, oldtempPLBitmap);
			DeleteDC(mem1DC_PL);
			DeleteObject(tempPLBitmap);
		}
		else { // 스킬 사용 중 이라면
			if (skillSlot[UsingSkillNum].count < 0) { UsingSkill = UseSkill((UsingSkillNum)); }
			mem1DC_PL = CreateCompatibleDC(memDC);
			tempPLBitmap = CreateCompatibleBitmap(hDC, skillSlot[UsingSkillNum].SpriteSizeX[skillSlot[UsingSkillNum].act], skillSlot[UsingSkillNum].SpriteSizeY[skillSlot[UsingSkillNum].act]);
			oldtempPLBitmap = (HBITMAP)SelectObject(mem1DC_PL, tempPLBitmap);
			mem2DC_PL = CreateCompatibleDC(mem1DC_PL);
			oldPLBitmap = (HBITMAP)SelectObject(mem2DC_PL, skillSlot[UsingSkillNum].hBitmap);

			if (GetDirect() == P_LEFT) { StretchBlt(mem1DC_PL, 0, 0, skillSlot[UsingSkillNum].SpriteSizeX[skillSlot[UsingSkillNum].act], skillSlot[UsingSkillNum].SpriteSizeY[skillSlot[UsingSkillNum].act], mem2DC_PL, skillSlot[UsingSkillNum].animation[skillSlot[UsingSkillNum].act][skillSlot[UsingSkillNum].count].x, skillSlot[UsingSkillNum].animation[skillSlot[UsingSkillNum].act][skillSlot[UsingSkillNum].count].y, skillSlot[UsingSkillNum].SpriteSizeX[skillSlot[UsingSkillNum].act], skillSlot[UsingSkillNum].SpriteSizeY[skillSlot[UsingSkillNum].act], SRCCOPY); }
			else { StretchBlt(mem1DC_PL, 0, 0, skillSlot[UsingSkillNum].SpriteSizeX[skillSlot[UsingSkillNum].act], skillSlot[UsingSkillNum].SpriteSizeY[skillSlot[UsingSkillNum].act], mem2DC_PL, skillSlot[UsingSkillNum].animation[skillSlot[UsingSkillNum].act][skillSlot[UsingSkillNum].count].x + skillSlot[UsingSkillNum].SpriteSizeX[skillSlot[UsingSkillNum].act] - 1, skillSlot[UsingSkillNum].animation[skillSlot[UsingSkillNum].act][skillSlot[UsingSkillNum].count].y, -skillSlot[UsingSkillNum].SpriteSizeX[skillSlot[UsingSkillNum].act], skillSlot[UsingSkillNum].SpriteSizeY[skillSlot[UsingSkillNum].act], SRCCOPY); }

			if (1) { TransparentBlt(memDC, GetPrintPos().x, GetPrintPos().y, GetPrintSizeX(), GetPrintSizeY(), mem1DC_PL, 0, 0, skillSlot[UsingSkillNum].SpriteSizeX[skillSlot[UsingSkillNum].act], skillSlot[UsingSkillNum].SpriteSizeY[skillSlot[UsingSkillNum].act], RGB(255, 0, 255)); }
			SelectObject(mem2DC_PL, oldPLBitmap);
			DeleteDC(mem2DC_PL);
			SelectObject(mem1DC_PL, oldtempPLBitmap);
			DeleteDC(mem1DC_PL);
			DeleteObject(tempPLBitmap);

		}
	}

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
	if (GetDashCT() == DashTimer) { oldBrush = (HBRUSH)SelectObject(memIDC, IBrush); }
	else { oldBrush = (HBRUSH)SelectObject(memIDC, (HBRUSH)GetStockObject(BLACK_BRUSH)); }
	Rectangle(memIDC, 170, 50 - 40 * DashTimer / GetDashCT(), 210, 50); // 대시 쿨
	oldRIBitmap = (HBITMAP)SelectObject(memRIDC, I_hBitmap_DASH);
	GetObject(I_hBitmap_DASH, sizeof(BITMAP), &bmp);
	TransparentBlt(memIDC, 170, 10, 40, 40, memRIDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 0, 255));
	SelectObject(memRIDC, oldRIBitmap);
	SelectObject(memIDC, oldBrush);

	if (GetS1CT() == 0) { oldBrush = (HBRUSH)SelectObject(memIDC, IBrush); }
	else { oldBrush = (HBRUSH)SelectObject(memIDC, (HBRUSH)GetStockObject(BLACK_BRUSH)); }
	Rectangle(memIDC, 200, 60 + 50 * GetS1CT() / GetS1MCT(), 250, 110); // 스킬 1 쿨
	oldRIBitmap = (HBITMAP)SelectObject(memRIDC, I_hBitmap_SKILL1);
	GetObject(I_hBitmap_SKILL1, sizeof(BITMAP), &bmp);
	TransparentBlt(memIDC, 200, 60, 50, 50, memRIDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 0, 255));
	SelectObject(memRIDC, oldRIBitmap);
	SelectObject(memIDC, oldBrush);

	if (GetS2CT() == 0) { oldBrush = (HBRUSH)SelectObject(memIDC, IBrush); }
	else { oldBrush = (HBRUSH)SelectObject(memIDC, (HBRUSH)GetStockObject(BLACK_BRUSH)); }
	Rectangle(memIDC, 270, 60 + 50 * GetS2CT() / GetS2MCT(), 320, 110); // 스킬 2 쿨
	oldRIBitmap = (HBITMAP)SelectObject(memRIDC, I_hBitmap_SKILL2);
	GetObject(I_hBitmap_SKILL2, sizeof(BITMAP), &bmp);
	TransparentBlt(memIDC, 270, 60, 50, 50, memRIDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 0, 255));
	SelectObject(memRIDC, oldRIBitmap);
	SelectObject(memIDC, oldBrush);

	if (GetUltCT() == 0) { oldBrush = (HBRUSH)SelectObject(memIDC, IBrush); }
	else { oldBrush = (HBRUSH)SelectObject(memIDC, (HBRUSH)GetStockObject(BLACK_BRUSH)); }
	Rectangle(memIDC, 350, 30 + 80 * GetUltCT() / GetUltMCT(), 430, 110); // 궁 쿨
	oldRIBitmap = (HBITMAP)SelectObject(memRIDC, I_hBitmap_ULT);
	GetObject(I_hBitmap_ULT, sizeof(BITMAP), &bmp);
	TransparentBlt(memIDC, 350, 30, 80, 80, memRIDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 0, 255));
	SelectObject(memRIDC, oldRIBitmap);
	SelectObject(memIDC, oldBrush);

	DeleteObject(IBrush);
	IBrush = CreateSolidBrush(RGB(051, 051, 051));
	oldBrush = (HBRUSH)SelectObject(memIDC, IBrush);
	Rectangle(memIDC, 180, 130, GetMaxHp() * 3 + 180, 160); // 최대체력바
	SelectObject(memIDC, oldBrush);

	DeleteObject(IBrush);
	IBrush = CreateSolidBrush(RGB(204, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memIDC, IBrush);
	Rectangle(memIDC, 180, 130, GetHp() * 3 + 180, 160); // 현재체력바
	SelectObject(memIDC, oldBrush);

	SelectObject(memIDC, oldIBitmap);
	DeleteObject(hBitmap_Interface);
	DeleteObject(IBrush);
	DeleteDC(memIDC);
	DeleteDC(memRIDC);
}

void Player::Decode(ObjectData object_data)
{

}


BOOL Player::UseSkill(int Skill_Num) {
	skillSlot[Skill_Num].count++;
	if (skillSlot[Skill_Num].count == 0) {
		int Checker = -1;
		if (Skill_Num == P_USE_SKILL_1) { Checker = Skill_1; }
		else if (Skill_Num == P_USE_SKILL_2) { Checker = Skill_2; }
		else if (Skill_Num == P_USE_SKILL_3) { Checker = Ult; }

		if (Checker == P_SKILL_1) {
			if (skillSlot[Skill_Num].act == 0) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 150, PrintPos.y); }
				SetPrintSizeX(150);
				SetPrintSizeY(150);
			}
			else if (skillSlot[Skill_Num].act == 1) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 200, PrintPos.y); }
				SetPrintSizeX(200);
				SetPrintSizeY(160);
				if (GetDirect() == P_LEFT) { ChangePrintPos(-200, 0); }
				else { ChangePrintPos(200, 0); }
			}
			else if (skillSlot[Skill_Num].act == 2) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 160, PrintPos.y); }
				SetPrintSizeX(160);
				SetPrintSizeY(100);
			}
		}
		else if (Checker == P_SKILL_2) {
			if (skillSlot[Skill_Num].act == 0) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 120, PrintPos.y); }
				SetPrintSizeX(120);
				SetPrintSizeY(180);
			}
			else if (skillSlot[Skill_Num].act == 1) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 200, PrintPos.y); }
				SetPrintSizeX(200);
				SetPrintSizeY(160);
			}
			else if (skillSlot[Skill_Num].act == 2) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 240, PrintPos.y); }
				SetPrintSizeX(240);
				SetPrintSizeY(240);
				if (GetDirect() == P_LEFT) { ChangePrintPos(-150, 0); }
				else { ChangePrintPos(150, 0); }
			}
			else if (skillSlot[Skill_Num].act == 3) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 200, PrintPos.y); }
				SetPrintSizeX(200);
				SetPrintSizeY(200);
			}
		}
		else if (Checker == P_ULT_1) {
			if (skillSlot[Skill_Num].act == 0) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 200, PrintPos.y); }
				SetPrintSizeX(200);
				SetPrintSizeY(150);
			}
			else if (skillSlot[Skill_Num].act == 1) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 400, PrintPos.y); }
				SetPrintSizeX(400);
				SetPrintSizeY(170);
			}
			else if (skillSlot[Skill_Num].act == 2) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 180, PrintPos.y); }
				SetPrintSizeX(180);
				SetPrintSizeY(200);
			}
			else if (skillSlot[Skill_Num].act == 3) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 260, PrintPos.y); }
				SetPrintSizeX(260);
				SetPrintSizeY(170);
			}
			else if (skillSlot[Skill_Num].act == 4) {
				if (GetDirect() == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 1000, PrintPos.y); }
				SetPrintSizeX(1000);
				SetPrintSizeY(400);
			}
		}
	}
	if (skillSlot[Skill_Num].count >= skillSlot[Skill_Num].NumCount[skillSlot[Skill_Num].act]) {
		skillSlot[Skill_Num].act++;
		skillSlot[Skill_Num].count = -1;
	}
	if (skillSlot[Skill_Num].act >= skillSlot[Skill_Num].NumAct) {
		skillSlot[Skill_Num].act = 0;
		skillSlot[Skill_Num].count = -1;
		if (PrintSizeX != 80 && GetDirect() == P_LEFT) {
			SetPrintPos(PrintPos.x + PrintSizeX - 80, PrintPos.y);
		}
		SetPrintSizeX(80);
		SetPrintSizeY(100);
		return FALSE;
	}
	return TRUE;
}

void Player::MakePlayer(int actNum, int dir)
{
	return;
}