//#include "main.h"
//#include "Wall.h"
//#include "Player.h"
//#include "Enemy.h"
//#include "Map.h"
//
//
//
////#ifdef _DEBUG
////#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
////#endif
//
//HINSTANCE g_hinst;
//LPCTSTR lpszClass = L"Window Class Name";
//LPCTSTR lpszWindowName = L"Window Api Final Project";
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpszCmdParam, int nCmdShow)
//{
//	HWND hWnd;
//	MSG Message;
//	WNDCLASSEX WndClass;
//	g_hinst = hInstance;
//
//	WndClass.cbSize = sizeof(WndClass);
//	WndClass.style = CS_HREDRAW | CS_VREDRAW;
//	WndClass.lpfnWndProc = (WNDPROC)WndProc;
//	WndClass.cbClsExtra = 0;
//	WndClass.cbWndExtra = 0;
//	WndClass.hInstance = hInstance;
//	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	WndClass.lpszMenuName = NULL;
//	WndClass.lpszClassName = lpszClass;
//	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//	RegisterClassEx(&WndClass);
//
//	int width = GetSystemMetrics(SM_CXSCREEN);
//	int height = GetSystemMetrics(SM_CYSCREEN);
//
//	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_EX_TOPMOST | WS_POPUP, 0, 0, width, height, NULL, (HMENU)NULL, hInstance, NULL);
//	//hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 100, 50, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
//	SetMenu(hWnd, NULL);
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//
//	while (GetMessage(&Message, 0, 0, 0)) {
//		TranslateMessage(&Message);
//		DispatchMessageW(&Message);
//	}
//	return Message.wParam;
//}
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
//	static Player PL; // 플레이어 구조체
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
//		//PL.MakePlayer(1, 1, 64, 64, 1, L"star.png");
//		PL.MakePlayer(6, P_RIGHT);
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
//		PL.DashTimer = PL.GetDashCT();
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
//				if (PL.GetPrintPos().x < StartPrintX + WndRect.right / 3) { StartPrintX -= 5; }
//				else if (PL.GetPrintPos().x > StartPrintX + WndRect.right / 3 * 2) { StartPrintX += 5; }
//				if (!PL.UsingSkill) {
//					if (PL.Getcount() >= PL.GetNumCount()) {
//						PL.Setcount(0);
//						if (PL.Getact() > 1) { PL.Setact(PL.GetNextAct()); }
//					}
//					if (PL.Getcount() == 0) {
//						if (PL.Getact() == 2) {
//							PL.SetNextAct(PL.Getact() + 1);
//						}
//						else if (PL.Getact() == 3) {
//							PL.SetNextAct(0);
//							if (PL.GetDirect() == P_LEFT) { PL.SetPrintPos(PL.GetPrintPos().x + PL.GetPrintSizeX() - 260, PL.GetPrintPos().y); }
//							PL.SetPrintSizeX(260);
//							PL.SetPrintSizeY(100);
//						}
//						else if (PL.Getact() == 4) {
//							PL.SetNextAct(PL.Getact() + 1);
//							if (PL.GetDirect() == P_LEFT) { PL.SetPrintPos(PL.GetPrintPos().x + PL.GetPrintSizeX() - 70, PL.GetPrintPos().y); }
//							PL.SetPrintSizeX(70);
//							PL.SetPrintSizeY(160);
//							if (PL.GetDirect() == P_RIGHT) { PL.ChangePrintPos(12, 0); }
//							else { PL.ChangePrintPos(-12, 0); }
//						}
//						else if (PL.Getact() == 5) {
//							PL.SetNextAct(0);
//							if (PL.GetDirect() == P_LEFT) { PL.SetPrintPos(PL.GetPrintPos().x + PL.GetPrintSizeX() - 140, PL.GetPrintPos().y); }
//							PL.SetPrintSizeX(140);
//							PL.SetPrintSizeY(160);
//						}
//						else {
//							if (PL.GetPrintSizeX() != 80 && PL.GetDirect() == P_LEFT) {
//								PL.SetPrintPos(PL.GetPrintPos().x + PL.GetPrintSizeX() - 80, PL.GetPrintPos().y);
//							}
//							PL.SetPrintSizeX(80);
//							PL.SetPrintSizeY(100);
//						}
//						PL.CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//					}
//				}
//				InvalidateRect(hWnd, NULL, false);
//				break;
//			case 2: // Gravity
//				if (!PL.UsingSkill) {
//					PL.ChangePrintPos(0, Gravity);
//					if (PL.CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX)) { PL.SetJump(0); Gravity = 1; }
//					else if (Gravity < G_acceleration) { Gravity++; }
//				}
//				break;
//			case 3: // PlayerAnimaition && Attack2Enemy
//				if (PL.Getact() == 3 || PL.Getact() == 5 || PL.UsingSkill) {
//					for (int i = 0; i < enemyNum; i++) {
//						RECT temp;
//						RECT plRect = { PL.GetPrintPos().x,PL.GetPrintPos().y,PL.GetPrintPos().x + PL.GetPrintSizeX(),PL.GetPrintPos().y + PL.GetPrintSizeY() };
//						RECT eRect = { E[i].GetLocaition().x,E[i].GetLocaition().y ,E[i].GetLocaition().x + E[i].GetPrintSizeX() ,E[i].GetLocaition().y + E[i].GetPrintSizeY() };
//						if (IntersectRect(&temp, &plRect, &eRect)) {
//							if (PL.Getact() == 3) { E[i].ChangeHp(PL.GetAttackDamage()); }
//							else if (PL.Getact() == 5) { E[i].ChangeHp(PL.GetAttackDamage() * 3 / 2); }
//
//							if (PL.UsingSkill) {
//								if (PL.UsingSkillNum == P_USE_SKILL_1) {
//									if (PL.skillSlot[PL.UsingSkillNum].act == 0) { E[i].ChangeHp(PL.GetAttackDamage() / 2); }
//									else if (PL.skillSlot[PL.UsingSkillNum].act == 1) { E[i].ChangeHp(PL.GetAttackDamage() * 5); }
//									else if (PL.skillSlot[PL.UsingSkillNum].act == 2) { E[i].ChangeHp(PL.GetAttackDamage() / 2); }
//								}
//								else if (PL.UsingSkillNum == P_USE_SKILL_2) {
//									if (PL.skillSlot[PL.UsingSkillNum].act == 0) { E[i].ChangeHp(PL.GetAttackDamage() / 3); }
//									else if (PL.skillSlot[PL.UsingSkillNum].act == 1) { E[i].ChangeHp(PL.GetAttackDamage() / 2); }
//									else if (PL.skillSlot[PL.UsingSkillNum].act == 2) { E[i].ChangeHp(PL.GetAttackDamage()); }
//									else if (PL.skillSlot[PL.UsingSkillNum].act == 3) { E[i].ChangeHp(PL.GetAttackDamage() / 4); }
//								}
//								else if (PL.UsingSkillNum == P_USE_SKILL_3) {
//									if (PL.skillSlot[PL.UsingSkillNum].act == 0) { E[i].ChangeHp(PL.GetAttackDamage()); }
//									else if (PL.skillSlot[PL.UsingSkillNum].act == 1) { E[i].ChangeHp(PL.GetAttackDamage() * 3); }
//									else if (PL.skillSlot[PL.UsingSkillNum].act == 2) { E[i].ChangeHp(PL.GetAttackDamage()); }
//									else if (PL.skillSlot[PL.UsingSkillNum].act == 3) { E[i].ChangeHp(PL.GetAttackDamage() * 2); }
//									else if (PL.skillSlot[PL.UsingSkillNum].act == 4) { E[i].ChangeHp(PL.GetAttackDamage() * 5); }
//								}
//							}
//						}
//					}
//				}
//				PL.Changecount(1);
//				if (PL.UsingSkill) { PL.UsingSkill = PL.UseSkill(PL.UsingSkillNum); }
//				if (PL.GetDamageTimer() > 0) { PL.ChangeDamageTimer(-1); }
//				else if (PL.GetDamageTimer() <= 0 && PL.GetDamaged()) { PL.SetDamaged(FALSE); }
//				break;
//			case 4: // SkillCoolTimer
//				if (PL.GetS1CT() > 0) { PL.ChangeS1CT(-1); }
//				if (PL.GetS2CT() > 0) { PL.ChangeS2CT(-1); }
//				if (PL.GetUltCT() > 0) { PL.ChangeUltCT(-1); }
//				break;
//			case 100: // enemy AI
//				e_counter = 0;
//				for (int i = 0; i < enemyNum; ++i)
//				{
//					Enemy_AI(hWnd, &PL, &E[i], WndRect, wall[Map_num], WallCount[Map_num], &score);
//					if (E[i].GetHp() > 0)
//					{
//						++e_counter;
//					}
//				}
//				break;
//			case 1001: // left move
//				if (PL.Getact() == 0) { PL.Setact(1); }
//				if (PL.Getact() == 1) {
//					PL.SetDirect(P_LEFT);
//					PL.ChangePrintPos(-PL.GetSpeed(), 0);
//					PL.CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//				}
//				break;
//			case 1002: // right move
//				if (PL.Getact() == 0) { PL.Setact(1); }
//				if (PL.Getact() == 1) {
//					PL.SetDirect(P_RIGHT);
//					PL.ChangePrintPos(PL.GetSpeed(), 0);
//					PL.CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//				}
//				if (PL.CheckInRight() && e_counter == 0)
//				{
//					Map.ClearMapObject(&Map_num, E, &enemyNum);
//					PL.SetPrintPos(100, 500);
//					StartPrintX = 0;
//				}
//				break;
//			case 5000: // Left Dash
//				if (PL.DashTimer <= PL.GetDashCT() / 10) {
//					PL.ChangePrintPos(-PL.GetDashSpeed(), 0);
//					PL.CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//					PL.ChangePrintPos(0, -Gravity);
//				}
//				PL.DashTimer++;
//				PL.SetDashPT(PL.DashTimer - 1, PL.GetPrintPos().x, PL.GetPrintPos().y, 5);
//				if (PL.DashTimer == PL.GetDashCT()) { KillTimer(hWnd, 5000); }
//				break;
//			case 5001: // Right Dash
//				if (PL.DashTimer <= PL.GetDashCT() / 10) {
//					PL.ChangePrintPos(PL.GetDashSpeed(), 0);
//					PL.CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//					PL.ChangePrintPos(0, -Gravity);
//				}
//				PL.DashTimer++;
//				PL.SetDashPT(PL.DashTimer - 1, PL.GetPrintPos().x, PL.GetPrintPos().y, 5);
//				if (PL.DashTimer == PL.GetDashCT()) { KillTimer(hWnd, 5001); }
//				break;
//			case 5002: // Dash Ilution Timer
//				for (int i = 0; i < 5; i++) { if (PL.GetDashPt(i) > 0) { PL.CountDownDashPt(i); } }
//				break;
//			case 5100: // Jump
//				PL.ChangePrintPos(0, -JumpTimer);
//				PL.CrashCheck2Wall(WndRect, wall[Map_num], WallCount[Map_num], StartPrintX);
//				JumpTimer -= 1;
//				if (JumpTimer < 0) { KillTimer(hWnd, 5100); }
//				break;
//			}
//		}
//		break;
//	case WM_LBUTTONDOWN:
//		if (!Pause && !PL.UsingSkill) {
//			if (PL.Getact() <= 1) { PL.Setact(2); PL.SetNextAct(3); PL.Setcount(3); }
//			else if (PL.Getact() == 3 && PL.GetNextAct() == 0) { PL.SetNextAct(4); }
//		}
//		break;
//	case WM_RBUTTONDOWN:
//		if (!Pause && !PL.UsingSkill) {
//			if (PL.DashTimer == PL.GetDashCT() && PL.Getact() == 1) {
//				if (GetAsyncKeyState('D') & 0x8000) {
//					PL.DashTimer = 0;
//					SetTimer(hWnd, 5001, 10, NULL);
//				}
//				else if (GetAsyncKeyState('A') & 0x8000) {
//					PL.DashTimer = 0;
//					SetTimer(hWnd, 5000, 10, NULL);
//				}
//			}
//		}
//		break;
//	case WM_MOUSEMOVE:
//
//		break;
//	case WM_KEYDOWN:
//		if (wParam == VK_ESCAPE || PL.GetNowHp() <= 0) {
//			DestroyWindow(hWnd);
//		}
//		else if (wParam == 'p' || wParam == 'P') {
//			KillTimer(hWnd, 1001);
//			KillTimer(hWnd, 1002);
//			PL.SetSpeed(5);
//			if (PL.Getact() == 1) { PL.Setact(0); }
//			Pause = !Pause;
//		}
//		if (!Pause && !PL.UsingSkill) {
//			if (/*wParam == 'w' || wParam == 'W'*/wParam == VK_SPACE) { // Jump
//				if (PL.GetJump() == 0) { PL.ChangePrintPos(0, -(Gravity + 1)); JumpTimer = MaxJumpTimer; SetTimer(hWnd, 5100, 10, NULL); PL.ChangeJump(1); }
//				else if (PL.GetJump() == 1) { JumpTimer = MaxJumpTimer; SetTimer(hWnd, 5100, 10, NULL); PL.ChangeJump(1); Gravity = 1; }
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
//				PL.SetSpeed(8);
//			}
//			else if ((wParam == 'q' || wParam == 'Q') && PL.GetS1CT() <= 0) { // 스킬 1번
//				KillTimer(hWnd, 1001);
//				KillTimer(hWnd, 1002);
//				PL.SetS1CT(PL.GetS1MCT());
//				PL.UsingSkillNum = P_USE_SKILL_1;
//				PL.UsingSkill = PL.UseSkill(PL.UsingSkillNum);
//			}
//			else if ((wParam == 'e' || wParam == 'E') && PL.GetS2CT() <= 0) { // 스킬 2번
//				KillTimer(hWnd, 1001);
//				KillTimer(hWnd, 1002);
//				PL.SetS2CT(PL.GetS2MCT());
//				PL.UsingSkillNum = P_USE_SKILL_2;
//				PL.UsingSkill = PL.UseSkill(PL.UsingSkillNum);
//			}
//			else if ((wParam == 'r' || wParam == 'R') && PL.GetUltCT() <= 0) { // 궁
//				KillTimer(hWnd, 1001);
//				KillTimer(hWnd, 1002);
//				PL.SetUltCT(PL.GetUltMCT());
//				PL.UsingSkillNum = P_USE_SKILL_3;
//				PL.UsingSkill = PL.UseSkill(PL.UsingSkillNum);
//			}
//		}
//		break;
//	case WM_KEYUP:
//		if (!Pause) {
//			if (wParam == 'w' || wParam == 'W') {
//			}
//			else if (wParam == 'a' || wParam == 'A') {
//				KillTimer(hWnd, 1001);
//				if (PL.Getact() == 1) { PL.Setact(0); }
//			}
//			else if (wParam == 's' || wParam == 'S') {
//			}
//			else if (wParam == 'd' || wParam == 'D') {
//				KillTimer(hWnd, 1002);
//				if (PL.Getact() == 1) { PL.Setact(0); }
//			}
//			else if (wParam == VK_SHIFT) {
//				PL.SetSpeed(5);
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