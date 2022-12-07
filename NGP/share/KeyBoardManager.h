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
	#define num_of_key 10	// 수동으로 바꿔줄것
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


#endif

};
