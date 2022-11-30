#include "KeyBoardManager.h"


void KeyBoardManager::reset()
{
	for (int i = 0;i < 9;i++)
	{
		key_array[i] = false;
	}
}

void KeyBoardManager::SetKey(int key_index, bool in)
{
	key_array[key_index] = in;
}
