#include "PlayerManager.h"

int PlayerManager::GetEmptyGame()
{
	return -1;
}

int PlayerManager::CheckGame()
{
	int game_id = GetEmptyGame();
	if (game_id == -1)
	{
		// 오류발생
	}
	return 0;
}

int PlayerManager::MakeGame()
{
	return 0;
}

int PlayerManager::MakePlayer(int game_index)
{
	return 0;
}

void PlayerManager::SendPlayerNum(int player_index, SOCKET client_sock)
{
}
