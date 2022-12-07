#pragma once
class KeyBoardManager {
public:
	enum {
		W,
		A,
		S,
		D,
		Shift,			// 이 위로는 false == 안 누름 ture == 누름
		Q,
		E,
		R,
		LButton,
		RButton		// Ture == 왼쪽 False == 오른쪽
	};

private:
	int num_of_key = 10;	// 수동으로 바꿔줄것
	bool key_array[10];


public:
	void reset();
	bool SetKey(int key_index, bool in);
	void SelectKey(unsigned int wParam, int& key_index);	// unsigned int -> WPARAM
};
