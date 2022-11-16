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
