#pragma once
class KeyBoardManager {
public:
	enum {
		W,
		A,
		S,
		D,
		Shift,			// �� ���δ� false == �� ���� ture == ����
		Q,
		E,
		R,
		LButton,
		RButton		// Ture == ���� False == ������
	};

private:
	int num_of_key = 10;	// �������� �ٲ��ٰ�
	bool key_array[10];


public:
	KeyBoardManager() {
		reset();
	}

	void reset();
	bool SetKey(int key_index, bool in);

#if CONSOL==CLIENT
	void SelectKey(unsigned int wParam, int& key_index);	// unsigned int -> WPARAM
#elif CONSOL==SERVER


#endif

};
