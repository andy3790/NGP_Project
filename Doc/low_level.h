#pragma once
#include<atlimage.h>

#define CLIENT 0
#define SERVER 1
#define CONSOL SERVER


#define MAX_OBJECT_COUNT	1000			// 한 맵에 존재할 수 있는 최대 GameObject 개수	***임시값
#define MAX_GAME_NUM 	1					// 서버가 생성할 수 있는 최대 게임의 개수		***임시값

// 키 매핑용 Define
#define KEY_JUMP	('KEY_JUMP_1' || 'KEY_JUMP_2')	// 미정
#define KEY_RIGHT
#define KEY_LEFT
#define KEY_ATT
#define KEY_DASH
#define KEY_RUN
#define KEY_SKILL_1
#define KEY_SKILL_2
#define KEY_SKILL_3

// 통신용 Define
#define OBJECT_TYPE_PLAYER			0x0000

#define OBJECT_TYPE_BASE			0x1000
#define OBJECT_TYPE_BIRD			0x1001
#define OBJECT_TYPE_WOLF			0x1002
#define OBJECT_TYPE_PLANT			0x1003

#define OBJECT_TYPE_BRICK			0x2000
#define OBJECT_TYPE_BACKGROUND		0x2001

#define OBJECT_TYPE_PLANTPROJECTILE	0x3000

// 통신용 열거형
enum class MSG_KEY : char {
	MSG_KEY_JUMP,
	MSG_KEY_RIGHT,
	MSG_KEY_LEFT,
	MSG_KEY_ATT,
	MSG_KEY_DASH,
	MSG_KEY_RUN,
	MSG_KEY_SKILL_1,
	MSG_KEY_SKILL_2,
	MSG_KEY_SKILL_3
};


enum class STATE : short{
	create_object,
	delete_object,
	idle,
	jump,
	double_jump,
	left,
	right,
	att,
	dash,
	run,
	skill_1,
	skill_2,
	skill_3
};
//-----------------------------------------------------------------------------------

struct Pos {
	short	x;
	short	y;
};

struct KeyData {
	MSG_KEY key;
	bool is_push;
};


struct ObjectData {
	short	index;
	Pos		pos;
	STATE	state;
	char	hp;
	char	vel_1;	//상태가 생성일 경우 오브젝트 타입이 되고 이외의 경우 점수가 된다.
};
//-----------------------------------------------------------------------------------

class GameObject {
private:
	int 위치_x;
	int 위치_y;

	int 크기_x;
	int 크기_y;
public:


#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif

};
//-----------------------------------------------------------------------------------

class Player : GameObject {
private:
	int 점수;
	CImage* 이미지;
	KeyBoardManager kbm;

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	void SetKeyBoardData(KeyData keydata);
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};
//-----------------------------------------------------------------------------------

class Enemy : GameObject {
private:
	CImage 이미지;

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};

class Base : Enemy {
private:

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};
class Bird : Enemy {
private:

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};
class Wolf : Enemy {
private:

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};
class Plant : Enemy {
private:

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};

class MapObject : GameObject {
private:

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};
//-----------------------------------------------------------------------------------


class Brick : MapObject {
private:

	CImage 이미지;

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};

class BackGround : MapObject {
private:
	CImage 이미지;

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};
//-----------------------------------------------------------------------------------

class Projectile : GameObject {
private:

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};
class PlantProjectile : Projectile {
private:

public:
#if CONSOL==CLIENT
public:
	virtual void Render();
	virtual void Decode(ObjectData object_data);

#elif CONSOL==SERVER
public:
	virtual void Update(float eTime);
	virtual ObjectData Encode();
#endif
};
//-----------------------------------------------------------------------------------
class KeyBoardManager {
private:
	bool key_jump;
	bool key_right;
	bool key_left;
	bool key_att;
	bool key_dash;
	bool key_run;
	bool key_skill_1;
	bool key_skill_2;
	bool key_skill_3;

public:
	void reset();
	void SetKeyBoardData(KeyData keydata);
};
//-----------------------------------------------------------------------------------

class GameObjectManager {
private:
	GameObject* m_GameObjects[MAX_OBJECT_COUNT];

public:
	int AddObject(GameObject* new_object, int index);
	GameObject GetObject(int index);
	bool DeleteObject(int index);

#if CONSOL==CLIENT
private:
	enum class DBufPointer : int{
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
	void SetKeyBoardData(int playernum, KeyData keydata);
	ObjectData* Encode(int object_index);
#endif

};

//-----------------------------------------------------------------------------------
#if CONSOL==CLIENT
void DataReceiver();
int Connecter(char* ServerIp, int PortNum);
int RecvPlayerNum();

void Render();
bool KeySender(KeyData key_data);

void RenderScene(void);
void MouseInput(int button, int state, int x, int y);
void KeyInput(unsigned char key, int x, int y);
void KeyUpInput(unsigned char key, int x, int y);
void SpecialKeyInput(int key, int x, int y);
void SpecialUpKeyInput(int key, int x, int y);

#elif CONSOL==SERVER
class PlayerData {
	SOCKET	sock;			// Game.DataSender() 에서 사용
	int		gamenum;		//-플레이어가 속해있는 게임의 번호
	int		playerIndex;	//-플레이어 캐릭터의 오브젝트 인덱스

};

class Game {
	GameObjectManager* GOMgr;
	PlayerData* PD[2];

	void Update(float eTime);
	bool DataSender();
};

class PlayerManager {
	Game game[MAX_GAME_NUM];
	PlayerData* players[MAX_GAME_NUM * 2];

	int CheckGame();
	int MakeGame();
	int MakePlayer(int game_index);

	void SendPlayerNum(int player_index, SOCKET client_sock);

};

void DataSender();
ObjectData* Encoder(GameObjectManager* GOMgr);

#endif
