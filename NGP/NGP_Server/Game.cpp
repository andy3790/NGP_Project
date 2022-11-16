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
