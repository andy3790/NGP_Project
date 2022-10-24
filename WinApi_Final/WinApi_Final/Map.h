#pragma once

class MapObject {
private:
	HBITMAP hBitmap;
	HBITMAP hMapBitmap1;
	HBITMAP hMapBitmap2;
	HBITMAP hMapBitmap3;
	HBITMAP hMapBitmap4;
	HBITMAP hWallBitmap;
	HBITMAP hBitmap_GAMEOVER;
	HBITMAP hBitmap_Interface;
	HBITMAP I_hBitmap_FACE;
	HBITMAP I_hBitmap_SKILL1;
	HBITMAP I_hBitmap_SKILL2;
	HBITMAP I_hBitmap_ULT;
	HBITMAP I_hBitmap_DASH;
	int MapSizeX;
	int MapSizeY;
	int bmW;
	int bmH;
public:
	void ResetMapObject(HDC hDC, int MapX, int MapY);
	void ChangeMapObject(HDC hDC, int MapX, int MapY);
	void Print2Map(HDC hDC, Player* PL, Enemy* E, int EnemyCount, Wall* wall, int WallCount, RECT WndRect, int* StartPrintX, int Score);
	void StartMapObject(int* map_num, Enemy E[10], int* enemy_num);
	void ClearMapObject(int* map_num, Enemy E[10], int* enemy_num);
	int GetMapX();
	int GetMapY();
	CImage brick1, brick2;
};