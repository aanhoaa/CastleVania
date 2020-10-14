#ifndef __MAP_H__
#define __MAP_H__

#include "Load_img_file.h"
#include "Load_resources.h"
#include "define.h"
#include "Camera.h"

#define TILE_FRAME_WIDTH 64
#define TILE_FRAME_HEIGHT 64

class Map
{
private:
	Load_img_file * TileTexture;
	Load_resources *TileSprite;

	int ScreenColumn;
	int ScreenRow;

	int RowMatrix; // số lượng dòng của ma trận tilemap txt
	int ColumnMatrix;// số lượng cột của ma trận tilemap txt

	int ColTile; // số lượng cột tile trong texture
	int RowTile;// số lượng dòng tile trong texture
	int CountTileFrame; // tổng số lượng tile trong texture 
	int TileMap[500][500];
	int BoardHeight;

	int row; // dòng hiện tại camera đang đứng
	int column; //cột hiện tại camera đang đứng
	int x, y;


public:
	Map();
	~Map();
	void LoadMap();
	void ReadMapTXT(char * filename);
	void DrawMap(Camera * camera);
};

#endif 