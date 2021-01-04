#ifndef __GRID_H__
#define	__GRID_H__

#include "Game.h" 
#include "Load_resources.h" 
#include "Map.h"
#include "Candle.h"
#include "Brick.h"
#include "HidenObject.h"
#include "Stairs.h"
#include "define.h"


using namespace std;

#define GRID_CELL_WIDTH 256
#define GRID_CELL_HEIGHT 224

#define GRID_INSERT_OBJECT__DIXUONGHONUOC_LEFT 41, def_ID::HIDDENOBJECT, -1, 3210, 410, 40, 10, 0 
#define GRID_INSERT_OBJECT__DIRAKHOIHONUOC_LEFT 45, def_ID::HIDDENOBJECT, -1, 3142, 435, 20, 20, 0 

#define GRID_INSERT_OBJECT__DIXUONGHONUOC_RIGHT 86, def_ID::HIDDENOBJECT, -1, 3835, 423, 25, 10, 0 
#define GRID_INSERT_OBJECT__DIRAKHOIHONUOC_RIGHT 81, def_ID::HIDDENOBJECT, -1, 3807, 460, 30, 20, 0 
class Grid
{

private:
	vector<CGameObject*> listObjectGame;
	vector<CGameObject*> cells[22][4];

public:
	void ReadFileToGrid(char * filename); // Đọc các object từ file
	void GetListObject(vector<CGameObject*>& ListObj, Camera * camera);

	void pushToCell(int id, int type, int nx, int x, int y, int w, int h, int update); //Thêm object vào grid

	CGameObject * GetNewObject(int type, int x, int y, int w, int h, int update);

	Grid();
	~Grid();
};

#endif