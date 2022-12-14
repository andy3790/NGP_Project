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
void GameObjectManager::Decode(ObjectData* datalist, int player_index)
{
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		
		if (m_GameObjects[datalist[i].index] != NULL) {
			m_GameObjects[datalist[i].index]->Decode(datalist[i]);
		}
		else
		{
			if (datalist[i].state == STATE::NULL_data)
				continue;
			else
			{
				//생성
				if (datalist[i].index == player_index)
				{
					// 플레이어임
					GameObject* PL = (GameObject*) new Player;

					((Player*)PL)->MakePlayer(6, P_RIGHT);

					((Player*)PL)->DashTimer = ((Player*)PL)->GetDashCT();

					m_GameObjects[datalist[i].index] = PL;
				}
				else
				{
					// 그 외
					switch (datalist[i].vel_1)
					{
					case OBJECT_TYPE_BASE:
						m_GameObjects[datalist[i].index] = (GameObject*) new Base({ 0,0 }, 0);
						break;
					case OBJECT_TYPE_BIRD:
						m_GameObjects[datalist[i].index] = (GameObject*) new Bird({ 0,0 }, 0);
						break;
					case OBJECT_TYPE_WOLF:
						m_GameObjects[datalist[i].index] = (GameObject*) new Wolf({ 0,0 }, 0);
						break;
					case OBJECT_TYPE_PLANT:
						m_GameObjects[datalist[i].index] = (GameObject*) new Plant({ 0,0 }, 0);
						break;
					case OBJECT_TYPE_BRICK:
						m_GameObjects[datalist[i].index] = (GameObject*) new Brick();
						break;
					case OBJECT_TYPE_BACKGROUND:
						m_GameObjects[datalist[i].index] = (GameObject*) new BackGround();
						break;
					case OBJECT_TYPE_PLANTPROJECTILE:
						m_GameObjects[datalist[i].index] = (GameObject*) new Projectile();
						break;
					default:
						GameObject* PL = (GameObject*) new Player;

						((Player*)PL)->MakePlayer(6, P_RIGHT);

						((Player*)PL)->DashTimer = ((Player*)PL)->GetDashCT();

						m_GameObjects[datalist[i].index] = PL;
						break;
					}
				}
				m_GameObjects[datalist[i].index]->Decode(datalist[i]);
			}
		}
	}
}

void GameObjectManager::Render(HDC hDC, HBITMAP hBitmap, RECT WndRect)
{
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (m_GameObjects[i] != NULL) {
			m_GameObjects[i]->Render(hDC, hBitmap, WndRect);
		}
	}
}