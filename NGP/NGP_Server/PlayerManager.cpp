#include "PlayerManager.h"

int PlayerManager::GetEmptyGame()
{
	return NO_EMPTY_GAME;
}

int PlayerManager::CheckGame()
{
	int game_id = GetEmptyGame();
	if (game_id == NO_EMPTY_GAME)
	{
		// 빈 게임이 없음.
		game_id = MakeGame();
	}

	return game_id;
}

int PlayerManager::MakeGame()
{
	return FAILED_MAKE_NEW_GAME;
}

int PlayerManager::MakePlayer(int game_index)
{
	return FAILED_MAKE_NEW_PLAYER;
}

void PlayerManager::SendPlayerNum(int player_index, SOCKET client_sock)
{

}
