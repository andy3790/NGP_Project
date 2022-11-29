#include"Consol.h"
#include"utill.h"
#include"NGP_struct.h"


#include "GameObjectManager.h"
#include "Player.h"

char* SERVERIP = (char*)"127.0.0.1";

//#ifdef _DEBUG
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

HINSTANCE g_hinst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Api Final Project";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpszCmdParam, int nCmdShow)
{
	// 서버 연결 
	int retval;
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	PlayerData player_data;

	// 데이터 받기(playerIndex)								
	retval = recv(sock, (char*)&player_data.playerIndex, sizeof(int), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		//err_asdf("recv()", 0, threadNum * 4 + 4);
	}

	// ObjectData


	// 윈도우 생성 부분
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hinst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_EX_TOPMOST | WS_POPUP, 0, 0, width, height, NULL, (HMENU)NULL, hInstance, NULL);
	//hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 100, 50, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	SetMenu(hWnd, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessageW(&Message);
	}

	// 이것들은 위치가 달라져도 될듯
	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		PAINTSTRUCT ps;
		HDC hDC;
		static RECT WndRect; // 윈도우 창 RECT

		bool Pause = false;
	
		static GameObject* PL = (GameObject*) new Player; // 플레이어 구조체
	
	
		switch (uMsg)
		{
		case WM_CREATE:
			//mciSendString(L"open bgm.mp3 type mpegvideo alias mp3", NULL, 0, NULL);
			//mciSendString(L"play bgm.mp3 repeat", NULL, 0, NULL);
			//mciSendString(L"setaudio bgm.mp3 volume to 100", NULL, 0, NULL);
	
			hDC = GetDC(hWnd);
			GetClientRect(hWnd, &WndRect);
	
			((Player*)PL)->MakePlayer(6, P_RIGHT);
	
			((Player*)PL)->DashTimer = ((Player*)PL)->GetDashCT();
			ReleaseDC(hWnd, hDC);
			break;
		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);
			break;
		case WM_LBUTTONDOWN:
			if (!Pause && !((Player*)PL)->UsingSkill) {
				if (((Player*)PL)->Getact() <= 1) { ((Player*)PL)->Setact(2); ((Player*)PL)->SetNextAct(3); ((Player*)PL)->Setcount(3); }
				else if (((Player*)PL)->Getact() == 3 && ((Player*)PL)->GetNextAct() == 0) { ((Player*)PL)->SetNextAct(4); }
			}
			break;
		case WM_RBUTTONDOWN:
			if (!Pause && !((Player*)PL)->UsingSkill) {
				if (((Player*)PL)->DashTimer == ((Player*)PL)->GetDashCT() && ((Player*)PL)->Getact() == 1) {
					if (GetAsyncKeyState('D') & 0x8000) {
						((Player*)PL)->DashTimer = 0;
					}
					else if (GetAsyncKeyState('A') & 0x8000) {
						((Player*)PL)->DashTimer = 0;
					}
				}
			}
			break;
		case WM_MOUSEMOVE:
	
			break;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE || ((Creature*)PL)->GetHp() <= 0) {
				DestroyWindow(hWnd);
			}
			else if (wParam == 'p' || wParam == 'P') { // Pause
				((Player*)PL)->SetSpeed(5);
				if (((Player*)PL)->Getact() == 1) { ((Player*)PL)->Setact(0); }
				Pause = !Pause;
			}
			if (!Pause && !((Player*)PL)->UsingSkill) {
				if (/*wParam == 'w' || wParam == 'W'*/wParam == VK_SPACE) { // Jump
					//if (((Player*)PL)->GetJump() == 0) { ((Player*)PL)->ChangePrintPos(0, -(Gravity + 1)); JumpTimer = MaxJumpTimer; SetTimer(hWnd, 5100, 10, NULL); ((Player*)PL)->ChangeJump(1); }
					//else if (((Player*)PL)->GetJump() == 1) { JumpTimer = MaxJumpTimer; SetTimer(hWnd, 5100, 10, NULL); ((Player*)PL)->ChangeJump(1); Gravity = 1; }
				}
				else if (wParam == 'a' || wParam == 'A') {
				}
				else if (wParam == 's' || wParam == 'S') {
				}
				else if (wParam == 'd' || wParam == 'D') {
				}
				else if (wParam == VK_SHIFT) {
					((Player*)PL)->SetSpeed(8);
				}
				else if ((wParam == 'q' || wParam == 'Q') && ((Player*)PL)->GetS1CT() <= 0) { // 스킬 1번
					((Player*)PL)->SetS1CT(((Player*)PL)->GetS1MCT());
					((Player*)PL)->UsingSkillNum = P_USE_SKILL_1;
					((Player*)PL)->UsingSkill = ((Player*)PL)->UseSkill(((Player*)PL)->UsingSkillNum);
				}
				else if ((wParam == 'e' || wParam == 'E') && ((Player*)PL)->GetS2CT() <= 0) { // 스킬 2번
					((Player*)PL)->SetS2CT(((Player*)PL)->GetS2MCT());
					((Player*)PL)->UsingSkillNum = P_USE_SKILL_2;
					((Player*)PL)->UsingSkill = ((Player*)PL)->UseSkill(((Player*)PL)->UsingSkillNum);
				}
				else if ((wParam == 'r' || wParam == 'R') && ((Player*)PL)->GetUltCT() <= 0) { // 궁
					((Player*)PL)->SetUltCT(((Player*)PL)->GetUltMCT());
					((Player*)PL)->UsingSkillNum = P_USE_SKILL_3;
					((Player*)PL)->UsingSkill = ((Player*)PL)->UseSkill(((Player*)PL)->UsingSkillNum);
				}
			}
			break;
		case WM_KEYUP:
			if (!Pause) {
				if (wParam == 'w' || wParam == 'W') {
				}
				else if (wParam == 'a' || wParam == 'A') {
					if (((Player*)PL)->Getact() == 1) { ((Player*)PL)->Setact(0); }
				}
				else if (wParam == 's' || wParam == 'S') {
				}
				else if (wParam == 'd' || wParam == 'D') {
					if (((Player*)PL)->Getact() == 1) { ((Player*)PL)->Setact(0); }
				}
				else if (wParam == VK_SHIFT) {
					((Player*)PL)->SetSpeed(5);
				}
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//
//	PAINTSTRUCT ps;
//	HDC hDC;
//	static RECT WndRect; // 윈도우 창 RECT
//	int mx, my;
//	static int StartPrintX; // 맵 카메라 시작점
//	static int Gravity, G_acceleration;
//	static int JumpTimer, MaxJumpTimer;
//	static BOOL Pause, StopMove, StopAct;
//
//	//static RECT wall[2] = { {0,1000,1200,1100},{600,800,800,1200} };
//	static Wall wall[3][10];
//	static int WallCount[3] = { 7,9,6 };
//
//	static MapObject Map;
//	static int Map_num = MAP1;
//
//	static Enemy E[10]; // 적 구조체
//	static int enemyNum;
//	static int e_counter;
//	static int score;
//
//	//static Player PL; // 플레이어 구조체
//	static GameObject* PL = (GameObject*) new Player; // 플레이어 구조체
//
//	//static POINT star;
//
//	switch (uMsg)
//	{
//	case WM_CREATE:
//		//PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
//		mciSendString(L"open bgm.mp3 type mpegvideo alias mp3", NULL, 0, NULL);
//		mciSendString(L"play bgm.mp3 repeat", NULL, 0, NULL);
//		mciSendString(L"setaudio bgm.mp3 volume to 100", NULL, 0, NULL);
//
//		hDC = GetDC(hWnd);
//		GetClientRect(hWnd, &WndRect);
//		Map.ResetMapObject(hDC, WndRect.right * 2, WndRect.bottom);
//		//E1.MakeEnemy(E_BIRD, { 500,440 }, 32, 32, E_LEFT, L"bat.png");
//		//E1.MakeEnemy(E_WOLF, { 500,440 }, 64, 32, E_LEFT, L"wolf.png");
//		//E1.MakeEnemy(E_BASE, { 500,440 }, 128, 128, E_LEFT, L"enemy.png");
//		//E1.MakeEnemy(E_PLANT, { 500,650 }, 128, 128, E_LEFT, L"plant.png");
//		Map.StartMapObject(&Map_num, E, &enemyNum);
//		Map.brick1.Load(L"Map/brick1.jpg");
//		Map.brick2.Load(L"Map/brick2.jpg");
//
//		//((Player*)PL)->MakePlayer(1, 1, 64, 64, 1, L"star.png");
//		((Player*)PL)->MakePlayer(6, P_RIGHT);
//
//		makeWall(wall);
//
//		Gravity = 0;
//		G_acceleration = 20;
//		MaxJumpTimer = 22;
//		StartPrintX = 0;
//		Pause = FALSE;
//		StopMove = FALSE;
//		StopAct = FALSE;
//		score = 0;
//
//		((Player*)PL)->DashTimer = ((Player*)PL)->GetDashCT();
//		SetTimer(hWnd, 1, 10, NULL); // PrintTimer
//		SetTimer(hWnd, 2, 10, NULL); // Gravity
//		SetTimer(hWnd, 3, 100, NULL); // PlayerAnimaition && Attack2Enemy
//		SetTimer(hWnd, 4, 10, NULL); // SkillCoolTimer
//		SetTimer(hWnd, 100, 50, NULL); // enemy AI
//		SetTimer(hWnd, 5002, 20, NULL); // Dash Ilution Timer
//		ReleaseDC(hWnd, hDC);
//		break;
//	case WM_PAINT:
//		hDC = BeginPaint(hWnd, &ps);
//		Map.Print2Map(hDC, &PL, E, enemyNum, wall[Map_num], WallCount[Map_num], WndRect, &StartPrintX, score);
//		EndPaint(hWnd, &ps);
//		break;
//	case WM_TIMER:
//		if (!Pause) {
//			switch (wParam)
//			{
//			case 1: // PrintTimer
//				if (((Player*)PL)->GetPrintPos().x < StartPrintX + WndRect.right / 3) { StartPrintX -= 5; }
//				else if (((Player*)PL)->GetPrintPos().x > StartPrintX + WndRect.right / 3 * 2) { StartPrintX += 5; }
//				if (!((Player*)PL)->UsingSkill) {
//					if (((Player*)PL)->Getcount() >= ((Player*)PL)->GetNumCount()) {
//						((Player*)PL)->Setcount(0);
//						if (((Player*)PL)->Getact() > 1) { ((Player*)PL)->Setact(((Player*)PL)->GetNextAct()); }
//					}
//					if (((Player*)PL)->Getcount() == 0) {
//						if (((Player*)PL)->Getact() == 2) {
//							((Player*)PL)->SetNextAct(((Player*)PL)->Getact() + 1);
//						}
//						else if (((Player*)PL)->Getact() == 3) {
//							((Player*)PL)->SetNextAct(0);
//							if (((Creature*)PL)->GetDirect() == P_LEFT) { ((Player*)PL)->SetPrintPos(((Player*)PL)->GetPrintPos().x + ((Player*)PL)->GetPrintSizeX() - 260, ((Player*)PL)->GetPrintPos().y); }
//							((Player*)PL)->SetPrintSizeX(260);
//							((Player*)PL)->SetPrintSizeY(100);
//						}
//						else if (((Player*)PL)->Getact() == 4) {
//							((Player*)PL)->SetNextAct(((Player*)PL)->Getact() + 1);
//							if (((Creature*)PL)->GetDirect() == P_LEFT) { ((Player*)PL)->SetPrintPos(((Player*)PL)->GetPrintPos().x + ((Player*)PL)->GetPrintSizeX() - 70, ((Player*)PL)->GetPrintPos().y); }
//							((Player*)PL)->SetPrintSizeX(70);
//							((Player*)PL)->SetPrintSizeY(160);
//							if (((Creature*)PL)->GetDirect() == P_RIGHT) { ((Player*)PL)->ChangePrintPos(12, 0); }
//							else { ((Player*)PL)->ChangePrintPos(-12, 0); }
//						}
//						else if (((Player*)PL)->Getact() == 5) {
//							((Player*)PL)->SetNextAct(0);
//							if (((Creature*)PL)->GetDirect() == P_LEFT) { ((Player*)PL)->SetPrintPos(((Player*)PL)->GetPrintPos().x + ((Player*)PL)->GetPrintSizeX() - 140, ((Player*)PL)->GetPrintPos().y); }
//							((Player*)PL)->SetPrintSizeX(140);
//							((Player*)PL)->SetPrintSizeY(160);
//						}
//						else {
//							if (((Player*)PL)->GetPrintSizeX() != 80 && ((Creature*)PL)->GetDirect() == P_LEFT) {
//								((Player*)PL)->SetPrintPos(((Player*)PL)->GetPrintPos().x + ((Player*)PL)->GetPrintSizeX() - 80, ((Player*)PL)->GetPrintPos().y);
//							}
//							((Player*)PL)->SetPrintSizeX(80);
//							((Player*)PL)->SetPrintSizeY(100);
//						}
//						//((Player*)PL)->CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//					}
//				}
//				InvalidateRect(hWnd, NULL, false);
//				break;
//			case 2: // Gravity
//				//if (!((Player*)PL)->UsingSkill) {
//				//	((Player*)PL)->ChangePrintPos(0, Gravity);
//				//	if (((Player*)PL)->CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX)) { ((Player*)PL)->SetJump(0); Gravity = 1; }
//				//	else if (Gravity < G_acceleration) { Gravity++; }
//				//}
//				break;
//			case 3: // PlayerAnimaition && Attack2Enemy
//				if (((Player*)PL)->Getact() == 3 || ((Player*)PL)->Getact() == 5 || ((Player*)PL)->UsingSkill) {
//					for (int i = 0; i < enemyNum; i++) {
//						RECT temp;
//						RECT plRect = { ((Player*)PL)->GetPrintPos().x,((Player*)PL)->GetPrintPos().y,((Player*)PL)->GetPrintPos().x + ((Player*)PL)->GetPrintSizeX(),((Player*)PL)->GetPrintPos().y + ((Player*)PL)->GetPrintSizeY() };
//						RECT eRect = { E[i].GetLocaition().x,E[i].GetLocaition().y ,E[i].GetLocaition().x + E[i].GetPrintSizeX() ,E[i].GetLocaition().y + E[i].GetPrintSizeY() };
//						if (IntersectRect(&temp, &plRect, &eRect)) {
//							if (((Player*)PL)->Getact() == 3) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage()); }
//							else if (((Player*)PL)->Getact() == 5) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage() * 3 / 2); }
//
//							if (((Player*)PL)->UsingSkill) {
//								if (((Player*)PL)->UsingSkillNum == P_USE_SKILL_1) {
//									if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 0) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage() / 2); }
//									else if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 1) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage() * 5); }
//									else if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 2) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage() / 2); }
//								}
//								else if (((Player*)PL)->UsingSkillNum == P_USE_SKILL_2) {
//									if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 0) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage() / 3); }
//									else if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 1) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage() / 2); }
//									else if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 2) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage()); }
//									else if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 3) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage() / 4); }
//								}
//								else if (((Player*)PL)->UsingSkillNum == P_USE_SKILL_3) {
//									if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 0) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage()); }
//									else if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 1) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage() * 3); }
//									else if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 2) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage()); }
//									else if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 3) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage() * 2); }
//									else if (((Player*)PL)->skillSlot[((Player*)PL)->UsingSkillNum].act == 4) { E[i].ChangeHp(((Player*)PL)->GetAttackDamage() * 5); }
//								}
//							}
//						}
//					}
//				}
//				((Player*)PL)->Changecount(1);
//				if (((Player*)PL)->UsingSkill) { ((Player*)PL)->UsingSkill = ((Player*)PL)->UseSkill(((Player*)PL)->UsingSkillNum); }
//				if (((Player*)PL)->GetDamageTimer() > 0) { ((Player*)PL)->ChangeDamageTimer(-1); }
//				else if (((Player*)PL)->GetDamageTimer() <= 0 && ((Player*)PL)->GetDamaged()) { ((Player*)PL)->SetDamaged(FALSE); }
//				break;
//			case 4: // SkillCoolTimer
//				if (((Player*)PL)->GetS1CT() > 0) { ((Player*)PL)->ChangeS1CT(-1); }
//				if (((Player*)PL)->GetS2CT() > 0) { ((Player*)PL)->ChangeS2CT(-1); }
//				if (((Player*)PL)->GetUltCT() > 0) { ((Player*)PL)->ChangeUltCT(-1); }
//				break;
//			case 100: // enemy AI
//				//e_counter = 0;
//				//for (int i = 0; i < enemyNum; ++i)
//				//{
//				//	Enemy_AI(hWnd, &PL, &E[i], WndRect, wall[Map_num], WallCount[Map_num], &score);
//				//	if (E[i].GetHp() > 0)
//				//	{
//				//		++e_counter;
//				//	}
//				//}
//				break;
//			case 1001: // left move
//				if (((Player*)PL)->Getact() == 0) { ((Player*)PL)->Setact(1); }
//				if (((Player*)PL)->Getact() == 1) {
//					((Creature*)PL)->SetDirect(P_LEFT);
//					((Player*)PL)->ChangePrintPos(-((Player*)PL)->GetSpeed(), 0);
//					//((Player*)PL)->CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//				}
//				break;
//			case 1002: // right move
//				if (((Player*)PL)->Getact() == 0) { ((Player*)PL)->Setact(1); }
//				if (((Player*)PL)->Getact() == 1) {
//					((Creature*)PL)->SetDirect(P_RIGHT);
//					((Player*)PL)->ChangePrintPos(((Player*)PL)->GetSpeed(), 0);
//					//((Player*)PL)->CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//				}
//				if (((Player*)PL)->CheckInRight() && e_counter == 0)
//				{
//					Map.ClearMapObject(&Map_num, E, &enemyNum);
//					((Player*)PL)->SetPrintPos(100, 500);
//					StartPrintX = 0;
//				}
//				break;
//			case 5000: // Left Dash
//				if (((Player*)PL)->DashTimer <= ((Player*)PL)->GetDashCT() / 10) {
//					((Player*)PL)->ChangePrintPos(-((Player*)PL)->GetDashSpeed(), 0);
//					//((Player*)PL)->CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//					((Player*)PL)->ChangePrintPos(0, -Gravity);
//				}
//				((Player*)PL)->DashTimer++;
//				((Player*)PL)->SetDashPT(((Player*)PL)->DashTimer - 1, ((Player*)PL)->GetPrintPos().x, ((Player*)PL)->GetPrintPos().y, 5);
//				if (((Player*)PL)->DashTimer == ((Player*)PL)->GetDashCT()) { KillTimer(hWnd, 5000); }
//				break;
//			case 5001: // Right Dash
//				if (((Player*)PL)->DashTimer <= ((Player*)PL)->GetDashCT() / 10) {
//					((Player*)PL)->ChangePrintPos(((Player*)PL)->GetDashSpeed(), 0);
//					//((Player*)PL)->CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//					((Player*)PL)->ChangePrintPos(0, -Gravity);
//				}
//				((Player*)PL)->DashTimer++;
//				((Player*)PL)->SetDashPT(((Player*)PL)->DashTimer - 1, ((Player*)PL)->GetPrintPos().x, ((Player*)PL)->GetPrintPos().y, 5);
//				if (((Player*)PL)->DashTimer == ((Player*)PL)->GetDashCT()) { KillTimer(hWnd, 5001); }
//				break;
//			case 5002: // Dash Ilution Timer
//				for (int i = 0; i < 5; i++) { if (((Player*)PL)->GetDashPt(i) > 0) { ((Player*)PL)->CountDownDashPt(i); } }
//				break;
//			case 5100: // Jump
//				((Player*)PL)->ChangePrintPos(0, -JumpTimer);
//				//((Player*)PL)->CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//				JumpTimer -= 1;
//				if (JumpTimer < 0) { KillTimer(hWnd, 5100); }
//				break;
//			}
//		}
//		break;
//	case WM_LBUTTONDOWN:
//		if (!Pause && !((Player*)PL)->UsingSkill) {
//			if (((Player*)PL)->Getact() <= 1) { ((Player*)PL)->Setact(2); ((Player*)PL)->SetNextAct(3); ((Player*)PL)->Setcount(3); }
//			else if (((Player*)PL)->Getact() == 3 && ((Player*)PL)->GetNextAct() == 0) { ((Player*)PL)->SetNextAct(4); }
//		}
//		break;
//	case WM_RBUTTONDOWN:
//		if (!Pause && !((Player*)PL)->UsingSkill) {
//			if (((Player*)PL)->DashTimer == ((Player*)PL)->GetDashCT() && ((Player*)PL)->Getact() == 1) {
//				if (GetAsyncKeyState('D') & 0x8000) {
//					((Player*)PL)->DashTimer = 0;
//					SetTimer(hWnd, 5001, 10, NULL);
//				}
//				else if (GetAsyncKeyState('A') & 0x8000) {
//					((Player*)PL)->DashTimer = 0;
//					SetTimer(hWnd, 5000, 10, NULL);
//				}
//			}
//		}
//		break;
//	case WM_MOUSEMOVE:
//
//		break;
//	case WM_KEYDOWN:
//		if (wParam == VK_ESCAPE || ((Creature*)PL)->GetHp() <= 0) {
//			DestroyWindow(hWnd);
//		}
//		else if (wParam == 'p' || wParam == 'P') {
//			KillTimer(hWnd, 1001);
//			KillTimer(hWnd, 1002);
//			((Player*)PL)->SetSpeed(5);
//			if (((Player*)PL)->Getact() == 1) { ((Player*)PL)->Setact(0); }
//			Pause = !Pause;
//		}
//		if (!Pause && !((Player*)PL)->UsingSkill) {
//			if (/*wParam == 'w' || wParam == 'W'*/wParam == VK_SPACE) { // Jump
//				if (((Player*)PL)->GetJump() == 0) { ((Player*)PL)->ChangePrintPos(0, -(Gravity + 1)); JumpTimer = MaxJumpTimer; SetTimer(hWnd, 5100, 10, NULL); ((Player*)PL)->ChangeJump(1); }
//				else if (((Player*)PL)->GetJump() == 1) { JumpTimer = MaxJumpTimer; SetTimer(hWnd, 5100, 10, NULL); ((Player*)PL)->ChangeJump(1); Gravity = 1; }
//			}
//			else if (wParam == 'a' || wParam == 'A') {
//				SetTimer(hWnd, 1001, 10, NULL);
//			}
//			else if (wParam == 's' || wParam == 'S') {
//			}
//			else if (wParam == 'd' || wParam == 'D') {
//				SetTimer(hWnd, 1002, 10, NULL);
//			}
//			else if (wParam == VK_SHIFT) {
//				((Player*)PL)->SetSpeed(8);
//			}
//			else if ((wParam == 'q' || wParam == 'Q') && ((Player*)PL)->GetS1CT() <= 0) { // 스킬 1번
//				KillTimer(hWnd, 1001);
//				KillTimer(hWnd, 1002);
//				((Player*)PL)->SetS1CT(((Player*)PL)->GetS1MCT());
//				((Player*)PL)->UsingSkillNum = P_USE_SKILL_1;
//				((Player*)PL)->UsingSkill = ((Player*)PL)->UseSkill(((Player*)PL)->UsingSkillNum);
//			}
//			else if ((wParam == 'e' || wParam == 'E') && ((Player*)PL)->GetS2CT() <= 0) { // 스킬 2번
//				KillTimer(hWnd, 1001);
//				KillTimer(hWnd, 1002);
//				((Player*)PL)->SetS2CT(((Player*)PL)->GetS2MCT());
//				((Player*)PL)->UsingSkillNum = P_USE_SKILL_2;
//				((Player*)PL)->UsingSkill = ((Player*)PL)->UseSkill(((Player*)PL)->UsingSkillNum);
//			}
//			else if ((wParam == 'r' || wParam == 'R') && ((Player*)PL)->GetUltCT() <= 0) { // 궁
//				KillTimer(hWnd, 1001);
//				KillTimer(hWnd, 1002);
//				((Player*)PL)->SetUltCT(((Player*)PL)->GetUltMCT());
//				((Player*)PL)->UsingSkillNum = P_USE_SKILL_3;
//				((Player*)PL)->UsingSkill = ((Player*)PL)->UseSkill(((Player*)PL)->UsingSkillNum);
//			}
//		}
//		break;
//	case WM_KEYUP:
//		if (!Pause) {
//			if (wParam == 'w' || wParam == 'W') {
//			}
//			else if (wParam == 'a' || wParam == 'A') {
//				KillTimer(hWnd, 1001);
//				if (((Player*)PL)->Getact() == 1) { ((Player*)PL)->Setact(0); }
//			}
//			else if (wParam == 's' || wParam == 'S') {
//			}
//			else if (wParam == 'd' || wParam == 'D') {
//				KillTimer(hWnd, 1002);
//				if (((Player*)PL)->Getact() == 1) { ((Player*)PL)->Setact(0); }
//			}
//			else if (wParam == VK_SHIFT) {
//				((Player*)PL)->SetSpeed(5);
//			}
//		}
//		break;
//	case WM_DESTROY:
//		Map.brick1.Destroy();
//		Map.brick2.Destroy();
//		PostQuitMessage(0);
//		break;
//	}
//	return DefWindowProc(hWnd, uMsg, wParam, lParam);
//}
