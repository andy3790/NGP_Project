#pragma once
#define MAP1 0
#define MAP2 1
#define MAP3 2

#define WALL 0
#define SHELF 1

class Wall {
private:
public:
	RECT rect;
	int type;
};
void makeWall(Wall wall[3][10]);