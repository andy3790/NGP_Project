#include "KeyBoardManager.h"


void KeyBoardManager::reset()
{
	for (int i = 0; i < num_of_key; i++)
	{
		key_array[i] = false;
	}
}

bool KeyBoardManager::SetKey(int key_index, bool in)
{
	key_array[key_index] = in;
	return true;
}