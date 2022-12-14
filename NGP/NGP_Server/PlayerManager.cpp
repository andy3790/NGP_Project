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
	RECT WndRect = { 0, 0, 1920, 1080 };
	{
		int ti = 0;
		//// BackGround
		MapObject* newMapObject = (MapObject*) new BackGround(WndRect.right * 2, WndRect.bottom);
		m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newMapObject, ti++);

		//// Brick
		newMapObject = (MapObject*) new Brick(RECT{ 0,900,3900,1080 }, Brick::Ground);
		m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newMapObject, ti++);
		//newMapObject = (MapObject*) new Brick(RECT{ 1760,600,2360,900 }, Brick::Wall);
		//m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newMapObject, ti++);
		//newMapObject = (MapObject*) new Brick(RECT{ 2360,700,2600,900 }, Brick::Wall);
		//m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newMapObject, ti++);
		//newMapObject = (MapObject*) new Brick(RECT{ 2600,800,3300,900 }, Brick::Wall);
		//m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newMapObject, ti++);
		//newMapObject = (MapObject*) new Brick(RECT{ 400,750,860,900 }, Brick::Wall);
		//m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newMapObject, ti++);
		//newMapObject = (MapObject*) new Brick(RECT{ 1020,680,1540,700 }, Brick::Shelf);
		//m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newMapObject, ti++);
		//newMapObject = (MapObject*) new Brick(RECT{ 660,470,1540,490 }, Brick::Shelf);
		//m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newMapObject, ti++);

		// Player

		// Enemy
		Enemy* newEnemyObject = (Enemy*) new Base(POINT{ 300, 400 }, Enemy::direction::E_LEFT);
		m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newEnemyObject, ti++);
		newEnemyObject = (Enemy*) new Bird(POINT{ 300, 500 }, Enemy::direction::E_LEFT);
		m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newEnemyObject, ti++);
		newEnemyObject = (Enemy*) new Wolf(POINT{ 300, 600 }, Enemy::direction::E_LEFT);
		m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newEnemyObject, ti++);
		newEnemyObject = (Enemy*) new Plant(POINT{ 300, 700 }, Enemy::direction::E_LEFT);
		m_ppGame[game_id]->GetGOMgr()->AddObject((GameObject*)newEnemyObject, ti++);

	}


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

	m_ppPlayers[player_data_index]->is_ready = true;
	m_ppGame[game_index]->SetPlayerData(player_num, true);
	// �����͸� �����ִ� �Լ�. ���� ���� ����.
	//m_ppGame[game_index]->DataSender(player_num);
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
	m_ppPlayers[player_data_index]->is_ready = false;


	return player_data_index;
}

void PlayerManager::ShowInformation()
{
	for (int i = 0;i < MAX_GAME_NUM;i++)
	{
		if (m_ppGame[i] != NULL)
		{
			std::cout << i << " �� ����====================" << std::endl;
			if (m_ppGame[i] != NULL) m_ppGame[i]->ShowInformation();
			std::cout << "=============================" << std::endl;
		}
	}
}

void PlayerManager::SetPlayerDataNULL(int player_data_index) {
	m_ppGame[m_ppPlayers[player_data_index]->gamenum]->SetPlayerDataNULL(m_ppPlayers[player_data_index]->player_num);

	if (m_ppPlayers[player_data_index] != NULL)
	{
		delete m_ppPlayers[player_data_index];
		m_ppPlayers[player_data_index] = NULL;
	}
	else
	{
		std::cout << "PM�� �÷��̾� ������ ���� �� ���� �߻�" << std::endl;
		exit(0);
	}
};

bool PlayerManager::IsGameNULL(int game_id)
{
	return m_ppGame[game_id] == NULL;
}

bool PlayerManager::SetGameNULL(int game_id)
{
	if (IsGameNULL(game_id))
		return false;
	delete m_ppGame[game_id];
	m_ppGame[game_id] = NULL;
	return true;
}