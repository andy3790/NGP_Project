#include "Player.h"

void SKILL::MakeSkill(int Select) {
	if (Select == P_SKILL_1) {
		hBitmap = (HBITMAP)LoadImage(NULL, TEXT("./Resorce/Image/Player/SK1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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
		hBitmap = (HBITMAP)LoadImage(NULL, TEXT("./Resorce/Image/Player/SK2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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
		hBitmap = (HBITMAP)LoadImage(NULL, TEXT("./Resorce/Image/Player/Ult.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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
	// actNum = 플레이어가 할 수 있는 행동의 갯수
	// dir = 플레이어가 생성될 때 바라보고 있는 방향

	hBitmap_move = (HBITMAP)LoadImage(NULL, TEXT("./Resorce/Image/Player/Player_move.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap_attack = (HBITMAP)LoadImage(NULL, TEXT("./Resorce/Image/Player/Player_attack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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
	NumCount[0] = 3; // 대기
	NumCount[1] = 4; // 이동
	NumCount[2] = 4; // 공격 1-1
	NumCount[3] = 3; // 공격 1-2
	NumCount[4] = 2; // 공격 2-1
	NumCount[5] = 3; // 공격 2-2

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

	SetDirect(dir);

	SetMaxHp(100);
	SetHp(GetMaxHp());
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

void Player::Damage2PL(int Damage) {
	if (!Damaged && act != 3 && act != 5 && DashPrintTimer[4] <= 0 && !UsingSkill) {
		SetHp(GetHp() - Damage);
		//ChangeHp(Damage * -1);
		//NowHp -= Damage;
		Damaged = TRUE;
		DamageTimer = 10;
	}
}


void Player::Update(float eTime)
{

}

ObjectData Player::Encode()
{
	//short	index;
	//Pos		pos;
	//STATE	state;
	//char	hp;
	//char	vel_1;	//상태가 생성일 경우 오브젝트 타입이 되고 이외의 경우 점수가 된다.

	ObjectData obd;

	obd.index = 0;
	obd.pos = Pos(0, 0);
	obd.state = ChnageAct2State(Player::Getact());
	obd.hp = Creature::GetHp();
	obd.vel_1 = 0;

	return 
}