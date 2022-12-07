#include "Game.h"

int Game::CheckPlayer()
{
    for (int i = 0;i < MAX_PLAYER_NUM;i++)
    {
        if (m_ppPlayers[i] == NULL)
            return i;
        else
            continue;
    }

    return DEFAULT_ERROR;
}

void Game::SetPlayerData(int game_index, int player_num, int player_index, SOCKET client_sock)
{
    m_ppPlayers[player_num] = new PlayerData;

    m_ppPlayers[player_num]->gamenum = game_index;
    m_ppPlayers[player_num]->player_num = player_num;
    m_ppPlayers[player_num]->playerIndex = player_index;
    m_ppPlayers[player_num]->sock = client_sock;
}

int Game::AddObject(GameObject* new_object)
{
    int index = GOMgr->GetEmptyIndex();
    if (index < 0)
    {
        exit(0);
    }
    GOMgr->AddObject(new_object, index);
    return index;
}

void Game::ShowInformation()
{
    for (int i = 0;i < MAX_PLAYER_NUM;i++)
    {
        if (m_ppPlayers[i] == NULL)
        {
            std::cout << i << " 번 플레이어----------------" << std::endl;
            std::cout << "NULL" << std::endl;
        }
        else
        {
            std::cout << i << " 번 플레이어----------------" << std::endl;
            std::cout << "NOT ? NULL" << std::endl;
        }
    }
    std::cout << "-----------------------------" << std::endl;
}

bool Game::DataSender(int player_num)
{
    //bool flag;
    ObjectData* object_data = GOMgr->Encode();

    SOCKET sock = m_ppPlayers[player_num]->sock;
    //배열의 데이터를 보낸다.
    // 성공 실패 여부에 따라 리턴값 변경?

    return false;
}