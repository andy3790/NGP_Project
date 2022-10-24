#include "main.h"
#include "Wall.h"

void makeWall(Wall wall[3][10])
{
	//(wall)[MAP1][0].rect = { 0,500,3900,1080 }; // 창화면 테스트 용
	(wall)[MAP1][0].rect = { 0,900,3900,1080 };
	(wall)[MAP1][0].type = WALL;
	(wall)[MAP1][6].rect = { 400,750,860,900 };
	(wall)[MAP1][6].type = WALL;
	(wall)[MAP1][1].rect = { 1760,600,2360,900 };
	(wall)[MAP1][1].type = WALL;
	(wall)[MAP1][2].rect = { 2360,700,2600,900 };
	(wall)[MAP1][2].type = WALL;
	(wall)[MAP1][3].rect = { 2600,800,3300,900 };
	(wall)[MAP1][3].type = WALL;
	(wall)[MAP1][4].rect = { 1020,680,1540,700 };
	(wall)[MAP1][4].type = SHELF;
	(wall)[MAP1][5].rect = { 660,470,1540,490 };
	(wall)[MAP1][5].type = SHELF;

	(wall)[MAP2][0].rect = { 0,900,3900,1080 };
	(wall)[MAP2][0].type = WALL;
	(wall)[MAP2][1].rect = { 1280,800,2560,900 };
	(wall)[MAP2][1].type = WALL;
	(wall)[MAP2][2].rect = { 980,400,2860,500 };
	(wall)[MAP2][2].type = WALL;
	(wall)[MAP2][3].rect = { 300,600,700,700 };
	(wall)[MAP2][3].type = WALL;
	(wall)[MAP2][4].rect = { 3140,600,3540,700 };
	(wall)[MAP2][4].type = WALL;
	(wall)[MAP2][5].rect = { 850,700,1150,720 };
	(wall)[MAP2][5].type = SHELF;
	(wall)[MAP2][6].rect = { 2690,700,2990,720 };
	(wall)[MAP2][6].type = SHELF;
	(wall)[MAP2][7].rect = { 800,480,980,500 };
	(wall)[MAP2][7].type = SHELF;
	(wall)[MAP2][8].rect = { 2860,480,3040,500 };
	(wall)[MAP2][8].type = SHELF;

	(wall)[MAP3][0].rect = { 0,900,3900,1080 };
	(wall)[MAP3][0].type = WALL;
	(wall)[MAP3][1].rect = { 360,750,800,900 };
	(wall)[MAP3][1].type = WALL;
	(wall)[MAP3][2].rect = { 1020,600,1400,700 };
	(wall)[MAP3][2].type = WALL;
	(wall)[MAP3][3].rect = { 2440,600,2820,700 };
	(wall)[MAP3][3].type = WALL;
	(wall)[MAP3][4].rect = { 3040,750,3480,770 };
	(wall)[MAP3][4].type = SHELF;
	(wall)[MAP3][5].rect = { 1600,650,2240,670 };
	(wall)[MAP3][5].type = SHELF;

}