
#include "Consol.h"
#include "utill.h"

#include "PlayerManager.h"
#include "Player.h"
#include"Game.h"

PlayerManager PM;

DWORD WINAPI GameMain(LPVOID arg)
{
	std::cout << "���� ������ ����" << std::endl;
	int game_id = (int)arg;
	Game* game = PM.GetGame(game_id);

	// ���� ������������ �÷��̾ �������� �ʴ�.
	// ���� �÷��̾� ������ ��ٸ����� ������Ʈ ������ ����.
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

		// �÷��̾�鿡�� �����͸� ������.
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
		std::cout << "���� ���� ����" << std::endl;

	// ��� �÷��̾��� ������ ������ ������ ��� ������ �������´�.
	std::cout << "���� ������ ����" << std::endl;

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
	// ������ �ޱ�� ����
	int key_index;
	bool flag;
	// ��¿� ����
	char* word;
	char* is_down;

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr*)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));

	while (1) {
		// ������ �ޱ�
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
		
		// ���� ������ ���
		KeyBoardManager* K = ((Player*)PM.GetGame(PD->gamenum)->GetGOMgr()->GetGameObject(PD->playerIndex))->GetKBM();
		std::cout << player_data_index << "�� �÷��̾�" << key_index << " Ű�� " << flag << std::endl;
	}

	// ���� �ݱ�
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		addr, ntohs(clientaddr.sin_port));
	// �÷��̾� ���� ���� �ڵ�
	PM.SetPlayerDataNULL(player_data_index);
	PM.ShowInformation();	// ���� �����忡�� ������ ���������� ���� �߻�
	return 0;
}


int main() 
{
	
	int retval;
	
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
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

	// ������ ��ſ� ����� ����
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
			// ġ���� ���� �߻�?
		}

		if (PM.IsGameNULL(game_id))
		{
			game_id = PM.MakeGame(game_id);
			// ������ ����
			hThread = CreateThread(NULL, 0, GameMain,
				(LPVOID)game_id, 0, NULL);
			if (hThread == NULL)
			{
				std::cout << "���� ������ ���� ����" << std::endl;
				exit(0);
			}
			else { CloseHandle(hThread); }
		}

		// �÷��̾� ���� �� �÷��̾� keyRecv ������ �����ؾ���
		int player_data_index = PM.MakePlayer(game_id, client_sock);
		if (player_data_index < 0)
		{
			switch (player_data_index)
			{
			case PlayerManager::FAILED_MAKE_NEW_PLAYER:
				// ��Ÿ��� ����ó��
				break;
			};
			break; // or exit(0);
			// ���� �߻�.?
		}
		// ������ ����
		hThread = CreateThread(NULL, 0, KeyRecv,
			(LPVOID)player_data_index, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }

		PM.ShowInformation();
		PM.SendPlayerNum(player_data_index, client_sock);
	}

	// ���� �ݱ�
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}

