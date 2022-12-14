#pragma once
#include"Creature.h"
#include "KeyBoardManager.h"

#define P_LEFT 1
#define P_RIGHT 2
#define P_SKILL_1 1
#define P_SKILL_2 2
#define P_ULT_1 100
#define P_USE_SKILL_1 0 // Skill 1
#define P_USE_SKILL_2 1 // Skill 2
#define P_USE_SKILL_3 2 // Ult


class SKILL {
public:
	HBITMAP hBitmap;
	POINT** animation;
	int act;
	int count;
	int NumAct;
	int* NumCount;
	int* SpriteSizeX; // �� ������ X ũ��
	int* SpriteSizeY; // �� ������ Y ũ��

	void MakeSkill(int Select);
};

class Player : Creature {
private:
	HBITMAP hBitmap_move;
	HBITMAP hBitmap_attack;
	HBITMAP hBitmap_Interface;
	HBITMAP I_hBitmap_FACE;
	HBITMAP I_hBitmap_SKILL1;
	HBITMAP I_hBitmap_SKILL2;
	HBITMAP I_hBitmap_ULT;
	HBITMAP I_hBitmap_DASH;
	POINT** animation; // �÷��̾� ��������Ʈ �ִϸ��̼� ����Ʈ �迭
	POINT PrintPos; // ����� ��ġ
	POINT LBPos; // ��� ���ϴ� ��ǥ (��� ������ ����� ���)
	POINT MidPos; // �÷��̾� �߰� ��
	int act; // ���� �ϴ� �ൿ
	int Nextact; // ������ �� �ൿ
	int count; // �ϴ� �ൿ�� ������
	int NumAct; // �ൿ ������ ����
	int* NumCount; // �ൿ ������ ����
	int* SpriteSizeX; // �� ������ X ũ��
	int* SpriteSizeY; // �� ������ Y ũ��
	int PrintSizeX; // ����� X ũ��
	int PrintSizeY; // ����� Y ũ��
	//int Direct; // �����ִ� ����

	//int MaxHp; // �ִ�ü��
	//int NowHp; // ����ü��
	int Speed; // �̵��ӵ�
	int DashSpeed; // �뽬 �̵��ӵ�
	int AttackDamage; // ���ݷ�

	int Skill_1; // ��ų 1�� ID
	int Skill_2; // ��ų 2�� ID
	int Ult; // �ñر� ID

	int Skill_1_MaxCoolTime;
	int Skill_1_CoolTime;
	int Skill_2_MaxCoolTime;
	int Skill_2_CoolTime;
	int Ult_MaxCoolTime;
	int Ult_CoolTime;


	int Jump; // ���� ���ΰ�   0=�� 1=���� 2=��������
	BOOL Attack; // �������ΰ�
	BOOL Crouch; // ��ũ�ȴ°�
	BOOL Damaged; // �������� �Ծ��°�.

	int DamageTimer; // ������ ���� �ð�
	int AttackCoolTime; // ���� ������ð�
	int DashCoolTime; // �뽬 ������ð�

	POINT DashPrintPos[5];
	int DashPrintTimer[5];

public:
	int StartPrintX = 0;
	int Score = 0;

#if CONSOL==CLIENT
public:
	void Render(HDC hDC, HBITMAP hBitmap, RECT WndRect);
	void Decode(ObjectData object_data);

#elif CONSOL==SERVER
private:
	KeyBoardManager *KBM;

public:
	void Update(float eTime, RECT WndRect);
	ObjectData Encode();

	KeyBoardManager* GetKBM() { return KBM; };

#endif

	int DashTimer;
	SKILL skillSlot[3];
	BOOL UsingSkill; // ��ų ������ΰ�
	int UsingSkillNum; // ������� ��ų�� ��ȣ

	void MakePlayer(int actNum, int dir);
	BOOL CheckInRight();
	BOOL UseSkill(int Skill_Num);
	void Damage2PL(int Damage);

	STATE ChnageAct2State(int act)
	{
		switch (act)
		{
		case 0: // ���
			break;
		case 1: // �̵�
			break;
		case 2: // ���� 1-1
			break;
		case 3: // ���� 1-2
			break;
		case 4: // ���� 2-1
			break;
		case 5: // ���� 2-2
			break;
		}

		if (GetDirect() == P_LEFT)
			return STATE::left;
		else if (GetDirect() == P_RIGHT)
			return STATE::right;

		return STATE::idle;
	}

	//Set
	void SetPrintPos(int x, int y) {
		PrintPos.x = x; PrintPos.y = y;
		MidPos.x = PrintPos.x + PrintSizeX / 2;
		MidPos.y = PrintPos.y + PrintSizeY / 2;
		LBPos = { PrintPos.x,PrintPos.y + PrintSizeY };
	}
	void Setact(int i) { act = i; }
	void Setcount(int i) { count = i; }
	void SetNumAct(int i) { NumAct = i; }
	void SetNumCount(int i) { NumCount[act] = i; }
	void SetPrintSizeX(int i) {
		PrintSizeX = i;
		MidPos.x = PrintPos.x + PrintSizeX / 2;
		MidPos.y = PrintPos.y + PrintSizeY / 2;
	}
	void SetPrintSizeY(int i) {
		PrintSizeY = i;
		PrintPos.y = LBPos.y - PrintSizeY;
		MidPos.x = PrintPos.x + PrintSizeX / 2;
		MidPos.y = PrintPos.y + PrintSizeY / 2;
	}

	void SetSpeed(int i) { Speed = i; }
	void SetDashSpeed(int i) { DashSpeed = i; }

	void SetJump(int i) { Jump = i; }
	void SetAttack(BOOL i) { Attack = i; }
	void SetCrouch(BOOL i) { Crouch = i; }
	void SetDamaged(BOOL i) { Damaged = i; }

	void SetDamageTimer(int i) { DamageTimer = i; }
	void SetAttackDamage(int i) { AttackDamage = i; }

	//Change
	void ChangePrintPos(int cx, int cy) {
		PrintPos.x += cx; PrintPos.y += cy;
		MidPos.x = PrintPos.x + PrintSizeX / 2;
		MidPos.y = PrintPos.y + PrintSizeY / 2;
		LBPos = { PrintPos.x,PrintPos.y + PrintSizeY };
	}
	void Changeact(int i) { act += i; }
	void Changecount(int i) { count += i; }
	void ChangeNumAct(int i) { NumAct += i; }
	void ChangeNumCount(int i) { NumCount[act] += i; }
	void ChangePrintSizeX(int i) {
		PrintSizeX += i;
		MidPos.x = PrintPos.x + PrintSizeX / 2;
		MidPos.y = PrintPos.y + PrintSizeY / 2;
	}
	void ChangePrintSizeY(int i) {
		PrintSizeY += i;
		PrintPos.y = LBPos.y - PrintSizeY;
		MidPos.x = PrintPos.x + PrintSizeX / 2;
		MidPos.y = PrintPos.y + PrintSizeY / 2;
	}

	void ChangeSpeed(int i) { Speed += i; }
	void ChangeDashSpeed(int i) { DashSpeed += i; }

	void ChangeJump(int i) { Jump += i; }
	void ChangeAttack() { Attack = !Attack; }
	void ChangeCrouch() { Crouch = !Crouch; }
	void ChangeDamaged() { Damaged = !Damaged; }

	void ChangeDamageTimer(int i) { DamageTimer += i; }
	void ChangeAttackDamage(int i) { AttackDamage += i; }


	//Get
	POINT Getanimation(int x, int y) { return animation[y][x]; }
	POINT GetNowanimation() { return animation[act][count]; }
	POINT GetPrintPos() { return PrintPos; }
	POINT GetMidPos() { return MidPos; }
	int Getact() { return act; }
	int Getcount() { return count; }
	int GetNumAct() { return NumAct; }
	int GetNumCount() { return NumCount[act]; }
	int GetPrintSizeX() { return PrintSizeX; }
	int GetPrintSizeY() { return PrintSizeY; }
	int GetSpriteSizeX() { return SpriteSizeX[act]; }
	int GetSpriteSizeY() { return SpriteSizeY[act]; }

	int GetSpeed() { return Speed; }
	int GetDashSpeed() { return DashSpeed; }

	int GetJump() { return Jump; }
	BOOL GetAttack() { return Attack; }
	BOOL GetCrouch() { return Crouch; }
	BOOL GetDamaged() { return Damaged; }

	int GetDamageTimer() { return DamageTimer; }
	int GetAttackCT() { return AttackCoolTime; }
	int GetDashCT() { return DashCoolTime; }

	int GetAttackDamage() { return AttackDamage; }


	void SetDashPT(int Snum, int x, int y, int t) {
		for (int i = Snum; i < 5; i++) {
			DashPrintPos[i] = { x, y };
			DashPrintTimer[i] = t;
		}
	}
	void CountDownDashPt(int Snum) { DashPrintTimer[Snum]--; }
	POINT GetDashPp(int Snum) { return DashPrintPos[Snum]; }
	int GetDashPt(int Snum) { return DashPrintTimer[Snum]; }

	void SetNextAct(int i) { Nextact = i; }
	int GetNextAct() { return Nextact; }

	void SetS1CT(int i) { Skill_1_CoolTime = i; }
	void SetS2CT(int i) { Skill_2_CoolTime = i; }
	void SetUltCT(int i) { Ult_CoolTime = i; }
	void ChangeS1CT(int i) { Skill_1_CoolTime += i; }
	void ChangeS2CT(int i) { Skill_2_CoolTime += i; }
	void ChangeUltCT(int i) { Ult_CoolTime += i; }
	int GetS1CT() { return Skill_1_CoolTime; }
	int GetS2CT() { return Skill_2_CoolTime; }
	int GetUltCT() { return Ult_CoolTime; }
	int GetS1MCT() { return Skill_1_MaxCoolTime; }
	int GetS2MCT() { return Skill_2_MaxCoolTime; }
	int GetUltMCT() { return Ult_MaxCoolTime; }

	HBITMAP GethBitmap_move() { return hBitmap_move; }
	HBITMAP GethBitmap_attack() { return hBitmap_attack; }

};