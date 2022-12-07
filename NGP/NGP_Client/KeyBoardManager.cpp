#include "KeyBoardManager.h"


void KeyBoardManager::reset()
{
	for (int i = 0;i < 9;i++)
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

void KeyBoardManager::SelectKey(unsigned int wParam, int& key_index)
{
	switch (wParam)
	{
	case 'w':
	case 'W':
		key_index = W;
		break;
	case 'a':
	case 'A':
		key_index = A;
		break;
	case 's':
	case 'S':
		key_index = S;
		break;
	case 'd':
	case 'D':
		key_index = D;
		break;
	case 'q':
	case 'Q':
		key_index = Q;
		break;
	case 'e':
	case 'E':
		key_index = E;
		break;
	case 'r':
	case 'R':
		key_index = R;
		break;
	case 0x10:	// VK_SHIFT
		key_index = Shift;
		break;
	}
}
