#include "main.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"


void SKILL::MakeSkill(int Select) {
	if (Select == P_SKILL_1) {
		hBitmap = (HBITMAP)LoadImage(NULL, TEXT("Player/SK1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		act = 0;
		count = -1;
		NumAct = 3;
		NumCount = (int*)malloc(sizeof(int) * NumAct);
		SpriteSizeX = (int*)malloc(sizeof(int) * NumAct);
		SpriteSizeY = (int*)malloc(sizeof(int) * NumAct);

		NumCount[0] = 5;
		NumCount[1] = 1;
		NumCount[2] = 5;
		SpriteSizeX[0] = 60;
		SpriteSizeY[0] = 60;
		SpriteSizeX[1] = 100;
		SpriteSizeY[1] = 80;
		SpriteSizeX[2] = 75;
		SpriteSizeY[2] = 40;

		animation = (POINT**)malloc(sizeof(POINT*) * NumAct);
		for (int i = 0; i < NumAct; i++) {
			animation[i] = (POINT*)malloc(sizeof(POINT) * NumCount[i]);
		}
		for (int j = 0; j < NumCount[0]; j++) { animation[0][j] = { SpriteSizeX[0] * j, 0 }; }
		for (int j = 0; j < NumCount[1]; j++) { animation[1][j] = { SpriteSizeX[1] * j, SpriteSizeY[0] }; }
		for (int j = 0; j < NumCount[2]; j++) { animation[2][j] = { SpriteSizeX[2] * j, SpriteSizeY[0] + SpriteSizeY[1] }; }
	}
	else if (Select == P_SKILL_2) {
		hBitmap = (HBITMAP)LoadImage(NULL, TEXT("Player/SK2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		act = 0;
		count = -1;
		NumAct = 4;
		NumCount = (int*)malloc(sizeof(int) * NumAct);
		SpriteSizeX = (int*)malloc(sizeof(int) * NumAct);
		SpriteSizeY = (int*)malloc(sizeof(int) * NumAct);

		NumCount[0] = 8;
		NumCount[1] = 7;
		NumCount[2] = 6;
		NumCount[3] = 4;
		SpriteSizeX[0] = 45;
		SpriteSizeY[0] = 70;
		SpriteSizeX[1] = 80;
		SpriteSizeY[1] = 60;
		SpriteSizeX[2] = 90;
		SpriteSizeY[2] = 90;
		SpriteSizeX[3] = 80;
		SpriteSizeY[3] = 80;

		animation = (POINT**)malloc(sizeof(POINT*) * NumAct);
		for (int i = 0; i < NumAct; i++) {
			animation[i] = (POINT*)malloc(sizeof(POINT) * NumCount[i]);
		}
		for (int j = 0; j < NumCount[0]; j++) { animation[0][j] = { SpriteSizeX[0] * j, 0 }; }
		for (int j = 0; j < NumCount[1]; j++) { animation[1][j] = { SpriteSizeX[1] * j, SpriteSizeY[0] }; }
		for (int j = 0; j < NumCount[2]; j++) { animation[2][j] = { SpriteSizeX[2] * j, SpriteSizeY[0] + SpriteSizeY[1] }; }
		for (int j = 0; j < NumCount[3]; j++) { animation[3][j] = { SpriteSizeX[3] * j, SpriteSizeY[0] + SpriteSizeY[1] + SpriteSizeY[2] }; }
	}
	else if (Select == P_ULT_1) {
		hBitmap = (HBITMAP)LoadImage(NULL, TEXT("Player/Ult.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		act = 0;
		count = -1;
		NumAct = 5;
		NumCount = (int*)malloc(sizeof(int) * NumAct);
		SpriteSizeX = (int*)malloc(sizeof(int) * NumAct);
		SpriteSizeY = (int*)malloc(sizeof(int) * NumAct);

		NumCount[0] = 6;
		NumCount[1] = 4;
		NumCount[2] = 6;
		NumCount[3] = 8;
		NumCount[4] = 5;
		SpriteSizeX[0] = 135;
		SpriteSizeY[0] = 100;
		SpriteSizeX[1] = 300;
		SpriteSizeY[1] = 120;
		SpriteSizeX[2] = 125;
		SpriteSizeY[2] = 150;
		SpriteSizeX[3] = 180;
		SpriteSizeY[3] = 120;
		SpriteSizeX[4] = 400;
		SpriteSizeY[4] = 180;

		animation = (POINT**)malloc(sizeof(POINT*) * NumAct);
		for (int i = 0; i < NumAct; i++) {
			animation[i] = (POINT*)malloc(sizeof(POINT) * NumCount[i]);
		}
		for (int j = 0; j < NumCount[0]; j++) { animation[0][j] = { SpriteSizeX[0] * j, 0 }; }
		for (int j = 0; j < NumCount[1]; j++) { animation[1][j] = { SpriteSizeX[1] * j, SpriteSizeY[0] }; }
		for (int j = 0; j < NumCount[2]; j++) { animation[2][j] = { SpriteSizeX[2] * j, SpriteSizeY[0] + SpriteSizeY[1] }; }
		for (int j = 0; j < NumCount[3]; j++) { animation[3][j] = { SpriteSizeX[3] * j, SpriteSizeY[0] + SpriteSizeY[1] + SpriteSizeY[2] }; }
		for (int j = 0; j < NumCount[4]; j++) { animation[4][j] = { SpriteSizeX[4] * j, SpriteSizeY[0] + SpriteSizeY[1] + SpriteSizeY[2] + SpriteSizeY[3] }; }

	}
}

void Player::MakePlayer(int actNum, int dir) {
	hBitmap_move = (HBITMAP)LoadImage(NULL, TEXT("Player/Player_move.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap_attack = (HBITMAP)LoadImage(NULL, TEXT("Player/Player_attack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	animation = (POINT**)malloc(sizeof(POINT*) * actNum);

	act = 0;
	Nextact = 0;
	count = 0;
	PrintPos = { 100,500 };
	PrintSizeX = 80;
	PrintSizeY = 100;
	MidPos.x = PrintPos.x + PrintSizeX / 2;
	MidPos.y = PrintPos.y + PrintSizeY / 2;
	LBPos = { PrintPos.x,PrintPos.y + PrintSizeY };
	NumAct = actNum;
	NumCount = (int*)malloc(sizeof(int) * NumAct);
	NumCount[0] = 3; // ´ë±â
	NumCount[1] = 4; // ÀÌµ¿
	NumCount[2] = 4; // °ø°Ý 1-1
	NumCount[3] = 3; // °ø°Ý 1-2
	NumCount[4] = 2; // °ø°Ý 2-1
	NumCount[5] = 3; // °ø°Ý 2-2

	for (int i = 0; i < actNum; i++) {
		animation[i] = (POINT*)malloc(sizeof(POINT) * NumCount[i]);
	}
	SpriteSizeX = (int*)malloc(sizeof(int) * NumAct);
	SpriteSizeY = (int*)malloc(sizeof(int) * NumAct);
	SpriteSizeX[0] = 67; SpriteSizeY[0] = 75;
	SpriteSizeX[1] = 104; SpriteSizeY[1] = 76;
	SpriteSizeX[2] = 37; SpriteSizeY[2] = 34;
	SpriteSizeX[3] = 71; SpriteSizeY[3] = 39;
	SpriteSizeX[4] = 32; SpriteSizeY[4] = 56;
	SpriteSizeX[5] = 52; SpriteSizeY[5] = 53;

	for (int j = 0; j < NumCount[0]; ++j) { animation[0][j] = { SpriteSizeX[0] * j, 0 }; }
	for (int j = 0; j < NumCount[1]; ++j) { animation[1][j] = { SpriteSizeX[1] * j, SpriteSizeY[0] }; }
	for (int j = 0; j < NumCount[2]; ++j) { animation[2][j] = { SpriteSizeX[2] * j, 0 }; }
	for (int j = 0; j < NumCount[3]; ++j) { animation[3][j] = { SpriteSizeX[3] * j, SpriteSizeY[2] }; }
	for (int j = 0; j < NumCount[4]; ++j) { animation[4][j] = { SpriteSizeX[4] * j, SpriteSizeY[2] + SpriteSizeY[3] }; }
	for (int j = 0; j < NumCount[5]; ++j) { animation[5][j] = { SpriteSizeX[5] * j, SpriteSizeY[2] + SpriteSizeY[3] + SpriteSizeY[4] }; }

	Direct = dir;

	MaxHp = 100;
	NowHp = MaxHp;
	Speed = 5;
	DashSpeed = 20;
	AttackDamage = 7;

	Jump = 0;
	Attack = FALSE;
	Crouch = FALSE;
	Damaged = FALSE;

	DamageTimer = 10;
	AttackCoolTime = 10;
	DashCoolTime = 50;

	Skill_1 = P_SKILL_1;
	Skill_2 = P_SKILL_2;
	Ult = P_ULT_1;

	Skill_1_MaxCoolTime = 800;
	Skill_2_MaxCoolTime = 1000;
	Ult_MaxCoolTime = 15000;

	Skill_1_CoolTime = 0;
	Skill_2_CoolTime = 0;
	Ult_CoolTime = 0;

	skillSlot[0].MakeSkill(Skill_1);
	skillSlot[1].MakeSkill(Skill_2);
	skillSlot[2].MakeSkill(Ult);

	UsingSkill = FALSE;
	UsingSkillNum = -1;

	for (int i = 0; i < 5; i++) {
		DashPrintPos[i] = { 0, 0 };
		DashPrintTimer[i] = 0;
	}
}

BOOL Player::CrashCheck2Wall(RECT WndRect, Wall* wall, int Count, int StartPrintX) {
	RECT PLrect, temp;
	BOOL isCrash = FALSE;

	for (int i = 0; i < Count; i++) {
		PLrect.left = PrintPos.x;
		PLrect.top = PrintPos.y;
		PLrect.right = PrintPos.x + PrintSizeX;
		PLrect.bottom = PrintPos.y + PrintSizeY;
		if (IntersectRect(&temp, &wall[i].rect, &PLrect)) {
			POINT tempMid = { (temp.right + temp.left) / 2,(temp.bottom + temp.top) / 2 };
			POINT PLMid = { PrintPos.x + PrintSizeX / 2 , PrintPos.y + PrintSizeY / 2 };
			int tempx, tempy;
			if (tempMid.x >= PLMid.x) { // ÁÂÃø Ãæµ¹
				tempx = tempMid.x - PLMid.x;
				if (tempMid.y >= PLMid.y) { // ³«ÇÏ Ãæµ¹
					tempy = tempMid.y - PLMid.y;
					if (tempx >= tempy) { // - ÁÂ
						PrintPos.x -= temp.right - temp.left; isCrash = TRUE;
					}
					else { // - ³«
						PrintPos.y -= temp.bottom - temp.top; isCrash = TRUE;
					}
				}
				else if (tempMid.y < PLMid.y) { // »ó½Â Ãæµ¹
					tempy = PLMid.y - tempMid.y;
					if (tempx >= tempy) { // - ÁÂ
						PrintPos.x -= temp.right - temp.left;
					}
					else { // - »ó
						PrintPos.y += temp.bottom - temp.top;
					}
				}
			}
			else if (tempMid.x <= PLMid.x) { // ¿ìÃø Ãæµ¹
				tempx = PLMid.x - tempMid.x;
				if (tempMid.y >= PLMid.y) { // ³«ÇÏ Ãæµ¹
					tempy = tempMid.y - PLMid.y;
					if (tempx >= tempy) { // - ¿ì
						PrintPos.x += temp.right - temp.left; isCrash = TRUE;
					}
					else { // - ³«
						PrintPos.y -= temp.bottom - temp.top; isCrash = TRUE;
					}
				}
				else if (tempMid.y < PLMid.y) { // »ó½Â Ãæµ¹
					tempy = PLMid.y - tempMid.y;
					if (tempx >= tempy) { // - ¿ì
						PrintPos.x += temp.right - temp.left;
					}
					else { // - »ó
						PrintPos.y += temp.bottom - temp.top;
					}
				}
			}
		}
	}
	PLrect.left = PrintPos.x;
	PLrect.top = PrintPos.y;
	PLrect.right = PrintPos.x + PrintSizeX;
	PLrect.bottom = PrintPos.y + PrintSizeY;
	OffsetRect(&WndRect, StartPrintX, 0);
	IntersectRect(&temp, &WndRect, &PLrect);
	if (temp.left != PLrect.left) { PrintPos.x = temp.left; }
	if (temp.right != PLrect.right) { PrintPos.x -= PLrect.right - temp.right; }
	if (temp.top != PLrect.top) { PrintPos.y = temp.top; }
	if (temp.bottom != PLrect.bottom) { PrintPos.y -= PLrect.bottom - temp.bottom; }
	return isCrash;
}

BOOL Player::CheckInRight() {
	if (MidPos.x > 3700) { return TRUE; }
	else { return FALSE; }
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
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 150, PrintPos.y); }
				SetPrintSizeX(150);
				SetPrintSizeY(150);
			}
			else if (skillSlot[Skill_Num].act == 1) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 200, PrintPos.y); }
				SetPrintSizeX(200);
				SetPrintSizeY(160);
				if (Direct == P_LEFT) { ChangePrintPos(-200, 0); }
				else { ChangePrintPos(200, 0); }
			}
			else if (skillSlot[Skill_Num].act == 2) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 160, PrintPos.y); }
				SetPrintSizeX(160);
				SetPrintSizeY(100);
			}
		}
		else if (Checker == P_SKILL_2) {
			if (skillSlot[Skill_Num].act == 0) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 120, PrintPos.y); }
				SetPrintSizeX(120);
				SetPrintSizeY(180);
			}
			else if (skillSlot[Skill_Num].act == 1) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 200, PrintPos.y); }
				SetPrintSizeX(200);
				SetPrintSizeY(160);
			}
			else if (skillSlot[Skill_Num].act == 2) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 240, PrintPos.y); }
				SetPrintSizeX(240);
				SetPrintSizeY(240);
				if (Direct == P_LEFT) { ChangePrintPos(-150, 0); }
				else { ChangePrintPos(150, 0); }
			}
			else if (skillSlot[Skill_Num].act == 3) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 200, PrintPos.y); }
				SetPrintSizeX(200);
				SetPrintSizeY(200);
			}
		}
		else if (Checker == P_ULT_1) {
			if (skillSlot[Skill_Num].act == 0) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 200, PrintPos.y); }
				SetPrintSizeX(200);
				SetPrintSizeY(150);
			}
			else if (skillSlot[Skill_Num].act == 1) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 400, PrintPos.y); }
				SetPrintSizeX(400);
				SetPrintSizeY(170);
			}
			else if (skillSlot[Skill_Num].act == 2) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 180, PrintPos.y); }
				SetPrintSizeX(180);
				SetPrintSizeY(200);
			}
			else if (skillSlot[Skill_Num].act == 3) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 260, PrintPos.y); }
				SetPrintSizeX(260);
				SetPrintSizeY(170);
			}
			else if (skillSlot[Skill_Num].act == 4) {
				if (Direct == P_LEFT) { SetPrintPos(PrintPos.x + PrintSizeX - 1000, PrintPos.y); }
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
		if (PrintSizeX != 80 && Direct == P_LEFT) {
			SetPrintPos(PrintPos.x + PrintSizeX - 80, PrintPos.y);
		}
		SetPrintSizeX(80);
		SetPrintSizeY(100);
		return FALSE;
	}
	return TRUE;
}

void Player::Damage2PL(int Damage) {
	if (!Damaged && act != 3 && act != 5 && DashPrintTimer[4] <= 0 && !UsingSkill) {
		NowHp -= Damage;
		Damaged = TRUE;
		DamageTimer = 10;
	}
}


//Set
void Player::SetPrintPos(int x, int y) {
	PrintPos.x = x; PrintPos.y = y;
	MidPos.x = PrintPos.x + PrintSizeX / 2;
	MidPos.y = PrintPos.y + PrintSizeY / 2;
	LBPos = { PrintPos.x,PrintPos.y + PrintSizeY };
}
void Player::Setact(int value) { act = value; }
void Player::Setcount(int value) { count = value; }
void Player::SetNumAct(int value) { NumAct = value; }
void Player::SetNumCount(int value) { NumCount[act] = value; }
void Player::SetPrintSizeX(int value) {
	PrintSizeX = value;
	MidPos.x = PrintPos.x + PrintSizeX / 2;
	MidPos.y = PrintPos.y + PrintSizeY / 2;
}
void Player::SetPrintSizeY(int value) {
	PrintSizeY = value;
	PrintPos.y = LBPos.y - PrintSizeY;
	MidPos.x = PrintPos.x + PrintSizeX / 2;
	MidPos.y = PrintPos.y + PrintSizeY / 2;
}
void Player::SetDirect(int value) { Direct = value; }

void Player::SetMaxHp(int value) { MaxHp = value; }
void Player::SetNowHp(int value) { NowHp = value; }
void Player::SetSpeed(int value) { Speed = value; }
void Player::SetDashSpeed(int value) { DashSpeed = value; }

void Player::SetJump(int value) { Jump = value; }
void Player::SetAttack(BOOL state) { Attack = state; }
void Player::SetCrouch(BOOL state) { Crouch = state; }
void Player::SetDamaged(BOOL state) { Damaged = state; }

void Player::SetDamageTimer(int i) { DamageTimer = i; }
void Player::SetAttackDamage(int i) { AttackDamage = i; }


//Change
void Player::ChangePrintPos(int cx, int cy) {
	PrintPos.x += cx; PrintPos.y += cy;
	MidPos.x = PrintPos.x + PrintSizeX / 2;
	MidPos.y = PrintPos.y + PrintSizeY / 2;
	LBPos = { PrintPos.x,PrintPos.y + PrintSizeY };
}
void Player::Changeact(int value) { act += value; }
void Player::Changecount(int value) { count += value; }
void Player::ChangeNumAct(int value) { NumAct += value; }
void Player::ChangeNumCount(int value) { NumCount[act] += value; }
void Player::ChangePrintSizeX(int value) {
	PrintSizeX += value;
	MidPos.x = PrintPos.x + PrintSizeX / 2;
	MidPos.y = PrintPos.y + PrintSizeY / 2;
}
void Player::ChangePrintSizeY(int value) {
	PrintSizeY += value;
	PrintPos.y = LBPos.y - PrintSizeY;
	MidPos.x = PrintPos.x + PrintSizeX / 2;
	MidPos.y = PrintPos.y + PrintSizeY / 2;
}
void Player::ChangeDirect(int value) { Direct += value; }

void Player::ChangeMaxHp(int value) { MaxHp += value; }
void Player::ChangeNowHp(int value) { NowHp += value; }
void Player::ChangeSpeed(int value) { Speed += value; }
void Player::ChangeDashSpeed(int value) { DashSpeed += value; }

void Player::ChangeJump(int value) { Jump += value; }
void Player::ChangeAttack() { Attack = !Attack; }
void Player::ChangeCrouch() { Crouch = !Crouch; }
void Player::ChangeDamaged() { Damaged = !Damaged; }

void Player::ChangeDamageTimer(int i) { DamageTimer += i; }
void Player::ChangeAttackDamage(int i) { AttackDamage += i; }



//Get
POINT Player::Getanimation(int x, int y) { return animation[y][x]; }
POINT Player::GetNowanimation() { return animation[act][count]; }
POINT Player::GetPrintPos() { return PrintPos; }
POINT Player::GetMidPos() { return MidPos; }
int Player::Getact() { return act; }
int Player::Getcount() { return count; }
int Player::GetNumAct() { return NumAct; }
int Player::GetNumCount() { return NumCount[act]; }
int Player::GetPrintSizeX() { return PrintSizeX; }
int Player::GetPrintSizeY() { return PrintSizeY; }
int Player::GetSpriteSizeX() { return SpriteSizeX[act]; }
int Player::GetSpriteSizeY(){ return SpriteSizeY[act]; }
int Player::GetDirect() { return Direct; }

int Player::GetMaxHp() { return MaxHp; }
int Player::GetNowHp() { return NowHp; }
int Player::GetSpeed() { return Speed; }
int Player::GetDashSpeed() { return DashSpeed; }

int Player::GetJump() { return Jump; }
BOOL Player::GetAttack() { return Attack; }
BOOL Player::GetCrouch() { return Crouch; }
BOOL Player::GetDamaged() { return Damaged; }

int Player::GetDamageTimer() { return DamageTimer; }
int Player::GetAttackCT() { return AttackCoolTime; }
int Player::GetDashCT() { return DashCoolTime; }

int Player::GetAttackDamage() { return AttackDamage; }


void Player::SetDashPT(int Snum, int x, int y, int t) {
	for (int i = Snum; i < 5; i++) {
		DashPrintPos[i] = { x, y };
		DashPrintTimer[i] = t;
	}
}
void Player::CountDownDashPt(int Snum) { DashPrintTimer[Snum]--; }
POINT Player::GetDashPp(int Snum) { return DashPrintPos[Snum]; }
int Player::GetDashPt(int Snum) { return DashPrintTimer[Snum]; }

void Player::SetNextAct(int i) { Nextact = i; }
int Player::GetNextAct() { return Nextact; }

void Player::SetS1CT(int i) { Skill_1_CoolTime = i; }
void Player::SetS2CT(int i) { Skill_2_CoolTime = i; }
void Player::SetUltCT(int i) { Ult_CoolTime = i; }
void Player::ChangeS1CT(int i) { Skill_1_CoolTime += i; }
void Player::ChangeS2CT(int i) { Skill_2_CoolTime += i; }
void Player::ChangeUltCT(int i) { Ult_CoolTime += i; }
int Player::GetS1CT() { return Skill_1_CoolTime; }
int Player::GetS2CT() { return Skill_2_CoolTime; }
int Player::GetUltCT() { return Ult_CoolTime; }
int Player::GetS1MCT() { return Skill_1_MaxCoolTime; }
int Player::GetS2MCT() { return Skill_2_MaxCoolTime; }
int Player::GetUltMCT() { return Ult_MaxCoolTime; }

HBITMAP Player::GethBitmap_move() { return hBitmap_move; }
HBITMAP Player::GethBitmap_attack() { return hBitmap_attack; }