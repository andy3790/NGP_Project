#pragma once
#include"Global.h"

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
	char	vel_1;	//���°� ������ ��� ������Ʈ Ÿ���� �ǰ� �̿��� ��� ������ �ȴ�.
};

struct PlayerData {
	SOCKET	sock;			// Game.DataSender() ���� ���
	int		gamenum;		//-�÷��̾ �����ִ� ������ ��ȣ
	int		playerIndex;	//-�÷��̾� ĳ������ ������Ʈ �ε���

};