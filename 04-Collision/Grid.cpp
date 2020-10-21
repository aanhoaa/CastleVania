#include "Grid.h"
#include "debug.h"

Grid::Grid()
{

}

Grid::~Grid()
{

}

void Grid::ReadFileToGrid(char * filename)
{
	listObjectGame.clear();

	ifstream inp;
	inp.open(filename, ios::in);

	int id, type, nx, x, y, w, h;

	if (inp)
	{
		while (inp >> id >> type >> nx >> x >> y >> w >> h)
		{
			Insert(id, type, nx, x, y, w, h);
		}
		inp.close();
	}
}

void Grid::GetListObject(vector<CGameObject*>& ListObj, Camera * camera)
{
	ListObj.clear(); // clear list
	ResetListObj();

	// lấy tọa độ của cam hiện tại để thiết lập các cells 
	int rowTop = (int)floor((camera->GetY_cam() + 1) / (float)GRID_CELL_HEIGHT);
	int rowBottom = (int)floor((camera->GetY_cam() + camera->GetHeight() - 1) / (float)GRID_CELL_HEIGHT);
	
	int colLeft = (int)floor((camera->GetX_cam() + 1) / (float)GRID_CELL_WIDTH);
	int colRight = (int)floor((camera->GetX_cam() + camera->GetWidth() - 1) / (float)GRID_CELL_WIDTH);

	// loop check  trong cells các obj dc đánh dấu, có thì cho vào list
	for (int row = rowTop; row <= rowBottom; row++)
	{
		for (int col = colLeft; col <= colRight; col++) // hiện tại với w và h thì nên để col < colRight (thêm <= sẽ lấy thêm obj ngoài cam)
		{
			//DebugOut(L"[INFO] Row thu: %d\n", row);
			//DebugOut(L"[INFO] So luong obj: %d\n", cells[row][col].size());

			for (UINT i = 0; i < cells[row][col].size(); i++) // có đánh dấu 
			{
				if (cells[row][col].at(i)->GetLife() > 0) // còn tồn tại
				{
					if (cells[row][col].at(i)->GetIsPush() == false)
					{
						ListObj.push_back(cells[row][col].at(i));
						cells[row][col].at(i)->SetIsPush(true);
					}
				}
			}
		}
	}
}

void Grid::GetListObject(vector<CGameObject*> &ListObj, CGameObject * obj)
{
	ListObj.clear(); // clear list
	ResetListObj();

	int rowBottom = (int)floor((obj->y + obj->GetHeight()) / (float)GRID_CELL_HEIGHT);
	int rowTop = (int)floor((obj->y) / (float)GRID_CELL_HEIGHT);

	int colLeft = (int)floor((obj->x) / (float)GRID_CELL_WIDTH);
	int colRight = (int)floor((obj->x + obj->GetWidth()) / (float)GRID_CELL_WIDTH);

	for (int row = rowTop; row <= rowBottom; row++)
	{
		for (int col = colLeft; col <= colRight; col++)
		{
			for (UINT i = 0; i < cells[row][col].size(); i++)
			{
				if (cells[row][col].at(i)->GetLife() > 0) // còn tồn tại
				{
					if (cells[row][col].at(i)->GetIsPush() == false)
					{
						ListObj.push_back(cells[row][col].at(i));
						cells[row][col].at(i)->SetIsPush(true);
					}
				}
			}
		}	
	}
}

void Grid::ResetListObj()
{
	for (UINT i = 0; i < listObjectGame.size(); i++)
	{
		listObjectGame[i]->SetIsPush(false);
	}
}

void Grid::Insert(int id, int type, int nx, int x, int y, int w, int h)
{
	CGameObject * dataObject = GetNewObject(type, x, y, w, h); // sau khi load info từ file, xác định obj ->vẽ ra màn hình
	if (dataObject == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] : Obj load fail!\n");
		return;
	}
	dataObject->SetId(id);
	dataObject->SetDirect(nx);
	dataObject->SetIsPush(false);

	listObjectGame.push_back(dataObject); // thêm vào list obj 

	int Top = (int)floor(y / (float)GRID_CELL_HEIGHT);
	int Bottom = (int)floor((y + h) / (float)GRID_CELL_HEIGHT);

	int Left = (int)floor(x / (float)GRID_CELL_WIDTH);
	int Right = (int)floor((x + w) / (float)GRID_CELL_WIDTH);

	for (int row = Top; row <= Bottom; row++)
	{
		for (int col = Left; col <= Right; col++)
		{
			cells[row][col].push_back(dataObject); // thêm vào grid
		}
	}
}

// check type_obj để vẽ ra màn hình
CGameObject * Grid::GetNewObject(int type, int x, int y, int w, int h)
{
	if (type == def_ID::BRICK) return new Brick(x, y, w, h); 
	if (type == def_ID::CANDLE) return new Candle(x, y);
	return NULL;
}
