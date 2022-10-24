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
	int* SpriteSizeX; // 한 프레임 X 크기
	int* SpriteSizeY; // 한 프레임 Y 크기

	void MakeSkill(int Select);
};

class Player {
private:
	HBITMAP hBitmap_move;
	HBITMAP hBitmap_attack;
	POINT** animation; // 플레이어 스프라이트 애니메이션 포인트 배열
	POINT PrintPos; // 출력할 위치
	POINT LBPos; // 출력 좌하단 좌표 (출력 사이즈 변경시 사용)
	POINT MidPos; // 플레이어 중간 점
	int act; // 현재 하는 행동
	int Nextact; // 다음에 할 행동
	int count; // 하는 행동의 프레임
	int NumAct; // 행동 종류의 개수
	int* NumCount; // 행동 프레임 개수
	int* SpriteSizeX; // 한 프레임 X 크기
	int* SpriteSizeY; // 한 프레임 Y 크기
	int PrintSizeX; // 출력할 X 크기
	int PrintSizeY; // 출력할 Y 크기
	int Direct; // 보고있는 방향

	int MaxHp; // 최대체력
	int NowHp; // 현재체력
	int Speed; // 이동속도
	int DashSpeed; // 대쉬 이동속도
	int AttackDamage; // 공격력

	int Skill_1; // 스킬 1번 ID
	int Skill_2; // 스킬 2번 ID
	int Ult; // 궁극기 ID

	int Skill_1_MaxCoolTime;
	int Skill_1_CoolTime;
	int Skill_2_MaxCoolTime;
	int Skill_2_CoolTime;
	int Ult_MaxCoolTime;
	int Ult_CoolTime;


	int Jump; // 점프 중인가   0=땅 1=점프 2=더블점프
	BOOL Attack; // 공격중인가
	BOOL Crouch; // 웅크렸는가
	BOOL Damaged; // 데미지를 입었는가.

	int DamageTimer; // 데미지 무적 시간
	int AttackCoolTime; // 공격 재사용대기시간
	int DashCoolTime; // 대쉬 재사용대기시간

	POINT DashPrintPos[5];
	int DashPrintTimer[5];
public:
	int DashTimer;
	SKILL skillSlot[3];
	BOOL UsingSkill; // 스킬 사용중인가
	int UsingSkillNum; // 사용중인 스킬의 번호

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