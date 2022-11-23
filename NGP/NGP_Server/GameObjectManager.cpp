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