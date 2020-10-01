#ifndef __GRID_H__
#define	__GRID_H__

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Game.h" 
#include "Load_img_file.h" 
#include "Map.h"
#include "Candle.h"
#include "Brick.h"
#include "define.h"


using namespace std;

#define GRID_CELL_WIDTH 256
#define GRID_CELL_HEIGHT 224

class Grid
{

private:
	vector<CGameObject*> listObjectGame;
	vector<CGameObject*> cells[500][500];

	void ResetListObj();

public:
	void ReadFileToGrid(char * filename); // Đọc các object từ file
	void GetListObject(vector<CGameObject*>& ListObj, Camera * camera);
	void GetListObject(vector<CGameObject*> &ListObj, CGameObject * obj);

	void Insert(int id, int type, int nx, float x, float y, float w, float h); //Thêm object vào grid

	CGameObject * GetNewObject(int type, int x, int y, int w, int h);

	Grid();
	~Grid();
};

#endif