#pragma once
#include"Consol.h"

struct Pos {
	short	x;
	short	y;

	Pos() : x(0), y(0) {};
	Pos(short x, short y) : x(x), y(y) {};
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

struct PlayerData {
	SOCKET	sock;			// Game.DataSender() 에서 사용
	int		gamenum;		//-플레이어가 속해있는 게임의 번호
	int		player_num;		// m_ppPlayers의 인덱스
	int		playerIndex;	//-플레이어 캐릭터의 오브젝트 인덱스

};