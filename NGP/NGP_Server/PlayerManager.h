#pragma once
#include"Consol.h"
#include"Game.h"
#include"NGP_struct.h"


class PlayerManager {
public:
	enum error {
		NO_EMPTY_GAME = -100,
		FAILED_MAKE_NEW_GAME,
		FAILED_MAKE_NEW_PLAYER
	};
private:
	Game* m_ppGame[MAX_GAME_NUM];
	//PlayerData* m_ppPlayers[MAX_GAME_NUM * 2];

public:
	PlayerManager() {
		for (int i = 0;i < MAX_GAME_NUM;i++)
		{
			m_ppGame[i] = NULL;
		}
		//for (int i = 0;i < MAX_GAME_NUM * 2;i++)
		//{
		//	m_ppPlayers[i] = NULL;
		//}
	}
	~PlayerManager() {
		// 얘는 동적할당이 아니야 아직?
	}
	int GetEmptyGame();
	int CheckGame();
	int MakeGame(int game_id);
	int MakePlayer(int game_index, SOCKET client_sock);

	void SendPlayerNum(int player_index, SOCKET client_sock);
};

