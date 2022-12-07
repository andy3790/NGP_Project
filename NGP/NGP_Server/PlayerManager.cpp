#include "PlayerManager.h"
#include "Player.h"
#include "ServerThread.h"

int PlayerManager::GetEmptyGame()
{
	int player_num;
	// ���� �迭�� ���鼭 �÷��̾� �ڸ� Ȯ��
	// �̹� �����Ǿ� �ִ� ���� �� �� �ڸ��� ���� ã��, ������ ���� �����Ѵ�.
	for (int i = 0;i < MAX_GAME_NUM;i++)
	{
		if (m_ppGame[i] == NULL)
		{
			return i;
			break;
		}

		player_num = m_ppGame[i]->CheckPlayer();
		if (player_num < 0)
			// ���ӿ� �� �ڸ� ����
			continue;
		else
			// ���ӿ� �� �ڸ��� ����
			return i;
	}

	return NO_EMPTY_GAME;
}

int PlayerManager::GetEmptyPlayerData()
{
	//int player_data_index;
	// ���� �迭�� ���鼭 �÷��̾� �ڸ� Ȯ��
	for (int i = 0;i < MAX_GAME_NUM * 2;i++)
	{
		if (m_ppPlayers[i] == NULL)
		{
			return i;
			break;
		}
	}

	return NO_EMPTY_PLAYER_DATA;
}

int PlayerManager::CheckGame()
{
	int game_id = GetEmptyGame();
	if (game_id == NO_EMPTY_GAME)
	{
		// �� ������ ����.
		std::cout << "�� ������ ����" << std::endl;
		exit(1);
	}
	if (m_ppGame[game_id] == NULL)
	{
		game_id = MakeGame(game_id);
	}

	return game_id;
}

int PlayerManager::MakeGame(int game_id)
{
	// ���� ���� �ڵ� �����ؾ���.
	// ���� ������ ���� ������ �����ؾ���.
	m_ppGame[game_id] = new Game; // �������� �˻��ؾ���.

	//HANDLE hThread1 = CreateThread(NULL, 0, GameThread, m_ppGame[game_id], 0, NULL);
	////if (hThread1 == NULL) return 1;
	//CloseHandle(hThread1);

	if (m_ppGame[game_id] == NULL)
		return FAILED_MAKE_NEW_GAME;
	else
		return game_id;
}

int PlayerManager::MakePlayer(int game_index, SOCKET client_sock)
{
	int player_num = m_ppGame[game_index]->CheckPlayer();
	if (player_num < 0)
		return FAILED_MAKE_NEW_PLAYER;
	else
	{
		// �Ʒ� �ڵ带 �÷��̾� �����ϴ� �ڵ�� �����.
		Player* player = new Player;
		player->MakePlayer(6, P_RIGHT); // ������ �ʿ䰡 �ִ�.
		GameObject* GOplayer = (GameObject*)player;


		int player_index = m_ppGame[game_index]->AddObject(GOplayer);
		int player_data_index = SetPlayerData(game_index, player_num, player_index, client_sock);
		return player_data_index;
	}

}

void PlayerManager::SendPlayerNum(int player_data_index, SOCKET client_sock)
{
	int retval;

	// ������ ������ �����Ϳ� �÷��̾� ������Ʈ �ε����� ������ �Ѵ�.
	int game_index = m_ppPlayers[player_data_index]->gamenum;
	int player_num = m_ppPlayers[player_data_index]->player_num;
	int playerIndex = m_ppPlayers[player_data_index]->playerIndex;
	SOCKET sock = m_ppPlayers[player_data_index]->sock;

	// �÷��̾� ������Ʈ�� �ε��� ��ȣ�� ���������.
	retval = send(sock, (char*)&playerIndex, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		//err_display("send() playerIndex");
		std::cout << "send() playerIndex" << std::endl;
		exit(0);
	}

	// �����͸� �����ִ� �Լ�. ���� ���� ����.
	m_ppGame[game_index]->DataSender(player_num);
}

int PlayerManager::SetPlayerData(int game_index, int player_num, int player_index, SOCKET client_sock)
{
	// ���ӿ����� ����.
	m_ppGame[game_index]->SetPlayerData(game_index, player_num, player_index, client_sock);

	// �ڱ�͵� ����.

	int player_data_index = GetEmptyPlayerData();
	m_ppPlayers[player_data_index] = new PlayerData;

	m_ppPlayers[player_data_index]->gamenum = game_index;
	m_ppPlayers[player_data_index]->player_num = player_num;
	m_ppPlayers[player_data_index]->playerIndex = player_index;
	m_ppPlayers[player_data_index]->sock = client_sock;


	return player_data_index;
}

void PlayerManager::ShowInformation()
{
	for (int i = 0;i < MAX_GAME_NUM;i++)
	{
		if (m_ppGame[i] != NULL)
		{
			std::cout << i << " �� ����====================" << std::endl;
			m_ppGame[i]->ShowInformation();
			std::cout << "=============================" << std::endl;
		}
	}
}

void PlayerManager::SetPlayerDataNULL(int player_data_index) {
	m_ppGame[m_ppPlayers[player_data_index]->gamenum]->SetPlayerDataNULL(m_ppPlayers[player_data_index]->player_num);

	if (m_ppPlayers[player_data_index] != NULL)
		m_ppPlayers[player_data_index] = NULL;
	else
	{
		std::cout << "PM�� �÷��̾� ������ ���� �� ���� �߻�" << std::endl;
		exit(0);
	}
};