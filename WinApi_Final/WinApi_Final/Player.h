#pragma once
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

class Player {
private:
	HBITMAP hBitmap_move;
	HBITMAP hBitmap_attack;
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
	int Direct; // �����ִ� ����

	int MaxHp; // �ִ�ü��
	int NowHp; // ����ü��
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
	int DashTimer;
	SKILL skillSlot[3];
	BOOL UsingSkill; // ��ų ������ΰ�
	int UsingSkillNum; // ������� ��ų�� ��ȣ

	void MakePlayer(int actNum, int dir);
	BOOL CrashCheck2Wall(RECT WndRect, Wall* wall, int Count, int StartPrintX);
	BOOL CheckInRight();
	BOOL UseSkill(int Skill_Num);
	void Damage2PL(int Damage);
	//Set
	void SetPrintPos(int x, int y);
	void Setact(int i);
	void Setcount(int i);
	void SetNumAct(int i);
	void SetNumCount(int i);
	void SetPrintSizeX(int i);
	void SetPrintSizeY(int i);
	void SetDirect(int i);

	void SetMaxHp(int i);
	void SetNowHp(int i);
	void SetSpeed(int i);
	void SetDashSpeed(int i);

	void SetJump(int i);
	void SetAttack(BOOL i);
	void SetCrouch(BOOL i);
	void SetDamaged(BOOL i);

	void SetDamageTimer(int i);
	void SetAttackDamage(int i);

	//Change
	void ChangePrintPos(int cx, int cy);
	void Changeact(int i);
	void Changecount(int i);
	void ChangeNumAct(int i);
	void ChangeNumCount(int i);
	void ChangePrintSizeX(int i);
	void ChangePrintSizeY(int i);
	void ChangeDirect(int i);

	void ChangeMaxHp(int i);
	void ChangeNowHp(int i);
	void ChangeSpeed(int i);
	void ChangeDashSpeed(int i);

	void ChangeJump(int i);
	void ChangeAttack();
	void ChangeCrouch();
	void ChangeDamaged();

	void ChangeDamageTimer(int i);
	void ChangeAttackDamage(int i);


	//Get
	POINT Getanimation(int x, int y);
	POINT GetNowanimation();
	POINT GetPrintPos();
	POINT GetMidPos();
	int Getact();
	int Getcount();
	int GetNumAct();
	int GetNumCount();
	int GetPrintSizeX();
	int GetPrintSizeY();
	int GetSpriteSizeX();
	int GetSpriteSizeY();
	int GetDirect();

	int GetMaxHp();
	int GetNowHp();
	int GetSpeed();
	int GetDashSpeed();

	int GetJump();
	BOOL GetAttack();
	BOOL GetCrouch();
	BOOL GetDamaged();

	int GetDamageTimer();
	int GetAttackCT();
	int GetDashCT();

	int GetAttackDamage();

	void SetDashPT(int Snum, int x, int y, int t);
	void CountDownDashPt(int Snum);
	POINT GetDashPp(int Snum);
	int GetDashPt(int Snum);

	void SetNextAct(int i);
	int GetNextAct();

	void SetS1CT(int i);
	void SetS2CT(int i);
	void SetUltCT(int i);
	void ChangeS1CT(int i);
	void ChangeS2CT(int i);
	void ChangeUltCT(int i);
	int GetS1CT();
	int GetS2CT();
	int GetUltCT();
	int GetS1MCT();
	int GetS2MCT();
	int GetUltMCT();

	HBITMAP GethBitmap_move();
	HBITMAP GethBitmap_attack();
};