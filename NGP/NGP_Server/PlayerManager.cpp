#include "PlayerManager.h"
#include "Player.h"
#include "ServerThread.h"

int PlayerManager::GetEmptyGame()
{
	int player_num;
	// 게임 배열을 돌면서 플레이어 자리 확인
	// 이미 생성되어 있는 게임 중 빈 자리를 먼저 찾고, 없으면 새로 생성한다.
	for (int i = 0;i < MAX_GAME_NUM;i++)
	{
		if (m_ppGame[i] == NULL)
		{
			return i;
			break;
		}

		player_num = m_ppGame[i]->CheckPlayer();
		if (player_num < 0)
			// 게임에 빈 자리 없음
			continue;
		else
			// 게임에 빈 자리가 있음
			return i;
	}

	return NO_EMPTY_GAME;
}

int PlayerManager::GetEmptyPlayerData()
{
	//int player_data_index;
	// 게임 배열을 돌면서 플레이어 자리 확인
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
		// 빈 게임이 없음.
		std::cout << "빈 게임이 없음" << std::endl;
		exit(1);
	}

	return game_id;
}

int PlayerManager::MakeGame(int game_id)
{
	// 게임 생성 코드 구현해야함.
	// 게임 생성시 게임 스레드 생성해야함.
	m_ppGame[game_id] = new Game; // 성공여부 검사해야함.

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
		// 아래 코드를 플레이어 생성하는 코드로 만든다.
		Player* player = new Player;
		player->MakePlayer(6, P_RIGHT); // 개선할 필요가 있다.
		GameObject* GOplayer = (GameObject*)player;


		int player_index = m_ppGame[game_index]->AddObject(GOplayer);
		int player_data_index = SetPlayerData(game_index, player_num, player_index, client_sock);
		return player_data_index;
	}

}

void PlayerManager::SendPlayerNum(int player_data_index, SOCKET client_sock)
{
	int retval;

	// 게임을 생성할 데이터와 플레이어 오브젝트 인덱스를 보내야 한다.
	int game_index = m_ppPlayers[player_data_index]->gamenum;
	int player_num = m_ppPlayers[player_data_index]->player_num;
	int playerIndex = m_ppPlayers[player_data_index]->playerIndex;
	SOCKET sock = m_ppPlayers[player_data_index]->sock;

	// 플레이어 오브젝트의 인덱스 번호도 보내줘야함.
	retval = send(sock, (char*)&playerIndex, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		//err_display("send() playerIndex");
		std::cout << "send() playerIndex" << std::endl;
		exit(0);
	}

	m_ppPlayers[player_data_index]->is_ready = true;
	m_ppGame[game_index]->SetPlayerData(player_num, true);
	// 데이터를 보내주는 함수. 아직 정의 없음.
	//m_ppGame[game_index]->DataSender(player_num);
}

int PlayerManager::SetPlayerData(int game_index, int player_num, int player_index, SOCKET client_sock)
{
	// 게임에서도 설정.
	m_ppGame[game_index]->SetPlayerData(game_index, player_num, player_index, client_sock);

	// 자기것도 설정.

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
			std::cout << i << " 번 게임====================" << std::endl;
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
		std::cout << "PM의 플레이어 데이터 리셋 중 오류 발생" << std::endl;
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