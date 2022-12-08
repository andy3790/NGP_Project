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

	float m_fprevTime;

public:
	Game() {
		GOMgr = new GameObjectManager;
		if (GOMgr == NULL)
		{
			std::cout << "GOM���� ����" << std::endl;
		}
		for (int i = 0;i < MAX_PLAYER_NUM;i++)
		{
			m_ppPlayers[i] = NULL;
		}
	}
	~Game() {
		;// �Ҵ� ����
	}
	int CheckPlayer();				// player_num Ȯ��, ��ȯ
	void SetPlayerData(int game_index, int player_num, int player_index, SOCKET client_sock);
	int AddObject(GameObject* new_object);	// ������ ������Ʈ �ε��� ��ȯ
	
	void ShowInformation();
	
	void Update(float eTime);
	bool DataSender(int player_num);

	void SetPprevTime(float in) { m_fprevTime = in; };
	float GetPrevTime() { return m_fprevTime; };
	bool SetPlayerDataNULL(int player_num);
	bool IsPlayerDataNULL(int in) { return m_ppPlayers[in] == NULL; }

	GameObjectManager* GetGOMgr() { return GOMgr; }
};

