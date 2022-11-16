#include "PlayerManager.h"

int PlayerManager::GetEmptyGame()
{
	int playerIndex;
	// ���� �迭�� ���鼭 �÷��̾� �ڸ� Ȯ��
	for (int i = 0;i < MAX_GAME_NUM;i++)
	{
		if (m_ppGame[i] == NULL)
			//return NO_EMPTY_GAME;
			break;

			playerIndex = m_ppGame[i]->CheckPlayer();
		if (playerIndex == -1)
			continue;
		else
			return i;
	}

	return NO_EMPTY_GAME;
}

int PlayerManager::CheckGame()
{
	int game_id = GetEmptyGame();
	if (game_id == NO_EMPTY_GAME)
	{
		// �� ������ ����.
		game_id = MakeGame(game_id);
	}

	return game_id;
}

int PlayerManager::MakeGame(int game_id)
{
	m_ppGame[game_id] = new Game; // �������� �˻��ؾ���.
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
		GameObject* player = NULL;
		int player_index = m_ppGame[game_index]->AddObject(player);
		m_ppGame[game_index]->SetPlayerData(game_index, player_num, player_index, client_sock);
		return player_index;
	}

}

void PlayerManager::SendPlayerNum(int player_index, SOCKET client_sock)
{

}
