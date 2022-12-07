#include "KeyBoardManager.h"


void KeyBoardManager::reset()
{
	for (int i = 0; i < 9; i++)
	{
		key_array[i] = false;
	}
}

bool KeyBoardManager::SetKey(int key_index, bool in)
{
	if (key_array[key_index] == in)
		return false;
	else
	{
		key_array[key_index] = in;
		return true;
	}
}