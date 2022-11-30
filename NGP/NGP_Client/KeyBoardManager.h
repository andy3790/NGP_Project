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
	void reset();
	void SetKey(int key_index, bool in);
};
