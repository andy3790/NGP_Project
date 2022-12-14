#pragma once
class KeyBoardManager {
public:
	enum {
		W,
		A,
		S,
		D,
		SpaceBar,
		Shift,			// �� ���δ� false == �� ���� ture == ����
		Q,
		E,
		R,
		LButton,
		RButton		// Ture == ���� False == ������
	};

private:
	#define num_of_key 11	// �������� �ٲ��ٰ�
	bool key_array[num_of_key];


public:
	KeyBoardManager() {
		reset();
	}

	void reset();
	bool SetKey(int key_index, bool in);

#if CONSOL==CLIENT
	void SelectKey(unsigned int wParam, int& key_index);	// unsigned int -> WPARAM
#elif CONSOL==SERVER
	bool GetKeyState(int key_index) { return key_array[key_index]; }

#endif

};
