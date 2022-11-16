#pragma once
#include"Consol.h"
#include"GameObject.h"
#include"NGP_struct.h"

class GameObjectManager{
public:
	enum error {
		NO_EMPTY_GAME_OBJECT_INDEX = -100,
		WRONG_INDEX
	};
private:
	GameObject* m_GameObjects[MAX_OBJECT_COUNT];

public:
	int AddObject(GameObject* new_object, int index)
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
	GameObject GetObject(int index);
	bool DeleteObject(int index);

#if CONSOL==CLIENT
private:
	enum class DBufPointer : int {
		Recv,
		Render
	};

	ObjectData RecvData[3][MAX_OBJECT_COUNT];
	ObjectData* p_Recv;
	ObjectData* p_Render;
	ObjectData* p_other;

public:
	void SetObjectData(ObjectData* input_array);
	void SwapDataBuffer(DBufPointer location);
	void Decode();

	void Render();

#elif CONSOL==SERVER
private:

public:

	int GetEmptyIndex();

	void Update(float eTime);
	void SetKeyBoardData(int player_num, KeyData keydata);
	ObjectData* Encode(int object_index);
#endif

};

