#include "GameObjectManager.h"

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