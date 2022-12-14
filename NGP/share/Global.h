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
#define OBJECT_TYPE_PLAYER			00

#define OBJECT_TYPE_BASE			01
#define OBJECT_TYPE_BIRD			02
#define OBJECT_TYPE_WOLF			03
#define OBJECT_TYPE_PLANT			04

#define OBJECT_TYPE_BRICK			05
#define OBJECT_TYPE_BACKGROUND		06

#define OBJECT_TYPE_PLANTPROJECTILE	07

#define BUFSIZE    512


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
	skill_3,
	NULL_data
};




