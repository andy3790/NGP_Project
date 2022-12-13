#include "GameObjectManager.h"


int GameObjectManager::GetEmptyIndex()
{
	for (int i = 0;i < MAX_OBJECT_COUNT;i++)
	{
		if (m_GameObjects[i] == NULL)
		{
			return i;
		}
	}
	return NO_EMPTY_GAME_OBJECT_INDEX;
}

int GameObjectManager::AddObject(GameObject* new_object, int index)
{
	if (m_GameObjects[index] == NULL)
	{
		m_GameObjects[index] = new_object;
		return index;
	}
	else
	{
		return WRONG_INDEX;
	}
	return WRONG_INDEX;
};

void GameObjectManager::InitGameObjects()
{
	for (int i = 0;i < MAX_OBJECT_COUNT;i++)
	{
		m_GameObjects[i] = NULL;
	}
}


void GameObjectManager::Update(float eTime)
{
	// 모든 오브젝트의 업데이트를 부름

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_GameObjects[i] == NULL)
			continue;
		m_GameObjects[i]->Update(eTime);
	}
}

void GameObjectManager::SetKeyBoardData(int player_num, KeyData keydata)
{
	// 해당 플레이어의 키 데이터를 업데이트
	m_GameObjects[player_num];
}

ObjectData* GameObjectManager::Encode()	// 오브젝트 데이터 배열을 반환.
{
	//ObjectData* Object_data = new ObjectData[MAX_OBJECT_COUNT];
	ObjectData Object_data[MAX_OBJECT_COUNT];

	//memset(&Object_data, 0, sizeof(ObjectData) * MAX_OBJECT_COUNT);


	for (int i = 0;i < MAX_OBJECT_COUNT;i++)
	{
		if (m_GameObjects[i] == NULL)
		{
			Object_data[i].state = STATE::NULL_data;
			continue;
		}
		Object_data[i] = m_GameObjects[i]->Encode();
		Object_data[i].index = i;
	}

	return Object_data;
} 