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
    if (IsPlayerDataNULL(player_num))
        return false;
    std::cout << player_num << "번p 전송" << std::endl;

    //bool flag;
    ObjectData* object_data = GOMgr->Encode();

    SOCKET sock;
    // 임계영역 필요할지도?
    if (!IsPlayerDataNULL(player_num))
        sock = m_ppPlayers[player_num]->sock;
    //배열의 데이터를 보낸다.

    int retval = 0;
    int sendSize = BUFSIZE;
    int progress = 0;
    int max_size = sizeof(ObjectData) * (MAX_OBJECT_COUNT);

    while (progress != max_size)
    {
        if (IsPlayerDataNULL(player_num))
            return false;

        if (progress > max_size -BUFSIZE)
            sendSize = max_size -progress;
        retval = send(sock, (char*)&object_data + progress, sendSize, 0);
        if (retval == SOCKET_ERROR) {
            std::cout << player_num << "에러" << std::endl;
            //err_display("recv()");
            break;
        }
        progress += retval;
    }
    
     
    // 성공 실패 여부에 따라 리턴값 변경?

    return false;
}

bool Game::SetPlayerDataNULL(int player_num)
{
    if (m_ppPlayers[player_num] != NULL)
    {
        delete m_ppPlayers[player_num];
        m_ppPlayers[player_num] = NULL;
    }
    else
    {
        std::cout << "Game의 플레이어 데이터 리셋 중 오류 발생" << std::endl;
        exit(0);
    }
    return 0;
}

void Game::Update(float eTime)
{
    GOMgr->Update(eTime);
}