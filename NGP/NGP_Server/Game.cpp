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
            std::cout << i << " �� �÷��̾�----------------" << std::endl;
            std::cout << "NULL" << std::endl;
        }
        else
        {
            std::cout << i << " �� �÷��̾�----------------" << std::endl;
            std::cout << "NOT ? NULL" << std::endl;
        }
    }
    std::cout << "-----------------------------" << std::endl;
}

bool Game::DataSender(int player_num)
{
    if (IsPlayerDataNULL(player_num))
        return false;
    std::cout << player_num << "��p ����" << std::endl;

    //bool flag;
    ObjectData* object_data = GOMgr->Encode();

    SOCKET sock;
    // �Ӱ迵�� �ʿ�������?
    if (!IsPlayerDataNULL(player_num))
        sock = m_ppPlayers[player_num]->sock;
    //�迭�� �����͸� ������.

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
            std::cout << player_num << "����" << std::endl;
            //err_display("recv()");
            break;
        }
        progress += retval;
    }
    
     
    // ���� ���� ���ο� ���� ���ϰ� ����?

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
        std::cout << "Game�� �÷��̾� ������ ���� �� ���� �߻�" << std::endl;
        exit(0);
    }
    return 0;
}

void Game::Update(float eTime)
{
    GOMgr->Update(eTime);
}