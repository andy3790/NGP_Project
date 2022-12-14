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
	GameObjectManager() {
		InitGameObjects();

	}

	int AddObject(GameObject* new_object, int index);
	bool DeleteObject(int index);
	void InitGameObjects();

	GameObject* GetGameObject(int index) { return m_GameObjects[index]; }

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
	void Decode(ObjectData* datalist);

	void Render(HDC hDC, HBITMAP hBitmap, RECT WndRect);

#elif CONSOL==SERVER
private:

public:
	

	int GetEmptyIndex();

	void Update(float eTime, RECT WndRect);
	void SetKeyBoardData(int player_num, KeyData keydata);
	ObjectData* Encode(); // 오브젝트 데이터 배열을 반환.
#endif

};

