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
	char	vel_1;	//���°� ������ ��� ������Ʈ Ÿ���� �ǰ� �̿��� ��� ������ �ȴ�.
};

struct PlayerData {
	SOCKET	sock;			// Game.DataSender() ���� ���
	int		gamenum;		//-�÷��̾ �����ִ� ������ ��ȣ
	int		player_num;		// m_ppPlayers�� �ε���
	int		playerIndex;	//-�÷��̾� ĳ������ ������Ʈ �ε���

};