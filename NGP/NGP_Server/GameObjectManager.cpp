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

ObjectData* GameObjectManager::Encode()	// 오브젝트 데이터 배열을 반환.
{
	ObjectData Object_data[MAX_OBJECT_COUNT];
	for (int i = 0;i < MAX_OBJECT_COUNT;i++)
	{
		if (m_GameObjects[i] == NULL)
			continue;
		Object_data[i] = m_GameObjects[i]->Encode();
	}

	return Object_data;
} 

