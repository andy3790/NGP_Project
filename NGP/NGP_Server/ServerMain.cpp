
#include "Consol.h"
#include "utill.h"

#include "PlayerManager.h"
#include "Player.h"
#include"Game.h"

PlayerManager PM;

DWORD WINAPI GameMain(LPVOID arg)
{
	std::cout << "게임 스레드 생성" << std::endl;
	int game_id = (int)arg;
	Game* game = PM.GetGame(game_id);

	// 게임 생성시점에는 플레이어가 들어와있지 않다.
	// 따라서 플레이어 접속을 기다린다음 업데이트 루프로 들어간다.
	while (true)
	{
		if (game->IsPlayerDataNULL(0) && game->IsPlayerDataNULL(1))
		{
			Sleep(1000);
		}
		else
		{
			break;
		}
	}
	game->SetPprevTime(clock());
	while (1)
	{
		float eTime = clock() - game->GetPrevTime();
		game->SetPprevTime(clock());
		eTime = eTime / 1000.f;
		game->Update(eTime);
		//std::cout << eTime << std::endl;

		// 플레이어들에게 데이터를 보낸다.
		game->DataSender(0);
		//break;
		game->DataSender(1);
		//if (eTime < 36)
		//{
		//	Sleep(36 - eTime);
		//}
		if (game->IsPlayerDataNULL(0) && game->IsPlayerDataNULL(1))
		{
			break;
		}
	}
	if(PM.SetGameNULL(game_id))
		std::cout << "게임 변수 삭제" << std::endl;

	// 모든 플레이어의 연결이 끊어진 상태일 경우 루프를 빠져나온다.
	std::cout << "게임 스레드 종료" << std::endl;

	return 0;
}

DWORD WINAPI KeyRecv(LPVOID arg)
{
	int player_data_index = (int)arg;
	PlayerData* PD = PM.GetPlayerData(player_data_index);

	int retval;
	SOCKET client_sock = PD->sock;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	// 데이터 받기용 변수
	int key_index;
	bool flag;
	// 출력용 변수
	char* word;
	char* is_down;

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	while (1) {
		// 데이터 받기
		retval = recv(client_sock, (char*) & key_index, sizeof(int), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;
		retval = recv(client_sock, (char*)&flag, sizeof(bool), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		((Player*)PM.GetGame(PD->gamenum)->GetGOMgr()->GetGameObject(PD->playerIndex))->GetKBM()->SetKey(key_index, flag);
		
		// 받은 데이터 출력
		KeyBoardManager* K = ((Player*)PM.GetGame(PD->gamenum)->GetGOMgr()->GetGameObject(PD->playerIndex))->GetKBM();
		std::cout << player_data_index << "번 플레이어" << key_index << " 키를 " << flag << std::endl;
	}

	// 소켓 닫기
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		addr, ntohs(clientaddr.sin_port));
	// 플레이어 접속 종료 코드
	PM.SetPlayerDataNULL(player_data_index);
	PM.ShowInformation();	// 게임 스레드에서 게임을 지워버리면 오류 발생
	return 0;
}


int main() 
{
	
	int retval;
	
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread;


	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		int game_id = PM.CheckGame();
		if (game_id < 0)
		{
			break;
			// 치명적 오류 발생?
		}

		if (PM.IsGameNULL(game_id))
		{
			game_id = PM.MakeGame(game_id);
			// 스레드 생성
			hThread = CreateThread(NULL, 0, GameMain,
				(LPVOID)game_id, 0, NULL);
			if (hThread == NULL)
			{
				std::cout << "게임 스레드 생성 실패" << std::endl;
				exit(0);
			}
			else { CloseHandle(hThread); }
		}

		// 플레이어 생성 시 플레이어 keyRecv 스레드 생성해야함
		int player_data_index = PM.MakePlayer(game_id, client_sock);
		if (player_data_index < 0)
		{
			switch (player_data_index)
			{
			case PlayerManager::FAILED_MAKE_NEW_PLAYER:
				// 기타등등 오류처리
				break;
			};
			break; // or exit(0);
			// 오류 발생.?
		}
		// 스레드 생성
		hThread = CreateThread(NULL, 0, KeyRecv,
			(LPVOID)player_data_index, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }

		PM.ShowInformation();
		PM.SendPlayerNum(player_data_index, client_sock);
	}

	// 소켓 닫기
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

