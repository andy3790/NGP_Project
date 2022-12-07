
#include"Consol.h"
#include"utill.h"

#include"PlayerManager.h"

PlayerManager PM;

DWORD WINAPI KeyRecv(LPVOID arg)
{
	int player_data_index = (int)arg;
	PlayerData* PD = PM.GstPlayerData(player_data_index);

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

		// ���� ������ ���
		std::cout << player_data_index << "�� �÷��̾�" << key_index << " Ű�� " << flag << std::endl;
	}

	// ���� �ݱ�
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		addr, ntohs(clientaddr.sin_port));
	PM.SetPlayerDataNULL(player_data_index);
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

