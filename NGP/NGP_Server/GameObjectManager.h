#pragma once
#include"Global.h"
#include"GameObject.h"
#include"NGP_struct.h"

class GameObjectManager{
private:
	GameObject* m_GameObjects[MAX_OBJECT_COUNT];

public:
	int AddObject(GameObject* new_object, int index);
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
	void Update(float eTime);
	void SetKeyBoardData(int player_num, KeyData keydata);
	ObjectData* Encode(int object_index);
#endif

};

