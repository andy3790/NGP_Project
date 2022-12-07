#pragma once
#define _WINSOCK_DEPERCATED_NO_WARNINGS

#include<winsock2.h>
#include<ws2tcpip.h>

#include<iostream>
#include<Windows.h>
#include<tchar.h>
#include<atlimage.h>
#include<string.h>

#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"msimg32.lib")
#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ


#define CLIENT 0
#define SERVER 1

#define SERVERPORT 9000
#define BUFSIZE    512

#define MAX_OBJECT_COUNT	1000			// �� �ʿ� ������ �� �ִ� �ִ� GameObject ����	***�ӽð�
#define MAX_GAME_NUM 	2					// ������ ������ �� �ִ� �ִ� ������ ����		***�ӽð�
#define MAX_PLAYER_NUM 	2					// ���� �ȿ� ������ �� �ִ� �ִ� �÷��̾��� ����***�ӽð�

// Ű ���ο� Define
#define KEY_JUMP	('KEY_JUMP_1' || 'KEY_JUMP_2')	// ����
#define KEY_RIGHT
#define KEY_LEFT
#define KEY_ATT
#define KEY_DASH
#define KEY_RUN
#define KEY_SKILL_1
#define KEY_SKILL_2
#define KEY_SKILL_3

// ��ſ� Define
#define OBJECT_TYPE_PLAYER			0x0000

#define OBJECT_TYPE_BASE			0x1000
#define OBJECT_TYPE_BIRD			0x1001
#define OBJECT_TYPE_WOLF			0x1002
#define OBJECT_TYPE_PLANT			0x1003

#define OBJECT_TYPE_BRICK			0x2000
#define OBJECT_TYPE_BACKGROUND		0x2001

#define OBJECT_TYPE_PLANTPROJECTILE	0x3000

// ��ſ� ������
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


enum class STATE : short {
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

