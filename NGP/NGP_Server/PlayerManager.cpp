#include "PlayerManager.h"
#include "Player.h"

int PlayerManager::GetEmptyGame()
{
	int playerIndex;
	// 게임 배열을 돌면서 플레이어 자리 확인
	for (int i = 0;i < MAX_GAME_NUM;i++)
	{
		if (m_ppGame[i] == NULL)
			return i;
			break;

		playerIndex = m_ppGame[i]->CheckPlayer();
		if (playerIndex < 0)
			// 게임에 빈 자리 없음
			continue;
		else
			// 게임에 빈 자리가 있음
			return i;
	}

	return NO_EMPTY_GAME;
}

int PlayerManager::CheckGame()
{
	int game_id = GetEmptyGame();
	if (game_id == NO_EMPTY_GAME)
	{
		// 빈 게임이 없음.
		std::cout << "빈 게임이 없음" << std::endl;
		exit(1);
	}
	game_id = MakeGame(game_id);

	return game_id;
}

int PlayerManager::MakeGame(int game_id)
{
	// 게임 생성 코드 구현해야함.
	m_ppGame[game_id] = new Game; // 성공여부 검사해야함.


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
		// 아래 코드를 플레이어 생성하는 코드로 만든다.
		Player* player = new Player;
		player->MakePlayer(6, P_RIGHT); // 개선할 필요가 있다.
		GameObject* GOplayer = (GameObject*)player;


		int player_index = m_ppGame[game_index]->AddObject(GOplayer);
		m_ppGame[game_index]->SetPlayerData(game_index, player_num, player_index, client_sock);
		return player_index;
	}

}

void PlayerManager::SendPlayerNum(int player_index, SOCKET client_sock)
{

}
