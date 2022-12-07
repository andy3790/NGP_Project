#pragma once
#include"Consol.h"
#include"GameObjectManager.h"


class Game{
public:
	enum error {
		DEFAULT_ERROR = -100,
	};
private:
	GameObjectManager* GOMgr;
	PlayerData* m_ppPlayers[2];

public:
	Game() {
		GOMgr = new GameObjectManager;
		if (GOMgr == NULL)
		{
			std::cout << "GOM생성 실패" << std::endl;
		}
		for (int i = 0;i < MAX_PLAYER_NUM;i++)
		{
			m_ppPlayers[i] = NULL;
		}
	}
	~Game() {
		;// 할당 해제
	}
	int CheckPlayer();				// player_num 확인, 반환
	void SetPlayerData(int game_index, int player_num, int player_index, SOCKET client_sock);
	int AddObject(GameObject* new_object);	// 생성된 오브젝트 인덱스 반환
	
	void ShowInformation();
	
	void Update(float eTime);
	bool DataSender(int player_num);
};

