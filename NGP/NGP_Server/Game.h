#pragma once
#include"Consol.h"
#include"GameObjectManager.h"


class Game{
	GameObjectManager* GOMgr;
	PlayerData* PD[2];

	void Update(float eTime);
	bool DataSender();
};

