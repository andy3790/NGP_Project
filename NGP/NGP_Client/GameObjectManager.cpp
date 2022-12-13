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

bool GameObjectManager::DeleteObject(int index)
{
	if (m_GameObjects[index] != NULL)
	{
		delete m_GameObjects[index];
		return true;
	}
	return false;
}
void GameObjectManager::InitGameObjects()
{

}

void GameObjectManager::SetObjectData(ObjectData* input_array)
{

}
void GameObjectManager::SwapDataBuffer(DBufPointer location)
{

}
void GameObjectManager::Decode()
{

}

void GameObjectManager::Render(HDC hDC, HBITMAP hBitmap, RECT WndRect)
{
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (m_GameObjects[i] != NULL) {
			m_GameObjects[i]->Render(hDC, hBitmap, WndRect);
		}
	}
}