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
	int i, j;

	ifstream inp;
	inp.open(filename, ios::in);

	int id, type, nx;
	float x, y, w, h;

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
	int rowTop = floor((camera->GetViewport().y) / (float)GRID_CELL_HEIGHT);
	int rowBottom = floor((camera->GetViewport().y + camera->GetHeight()) / (float)GRID_CELL_HEIGHT);
	
	int colLeft = floor((camera->GetViewport().x) / (float)GRID_CELL_WIDTH);
	int colRight = floor((camera->GetViewport().x + camera->GetWidth()) / (float)GRID_CELL_WIDTH);

	// loop check  trong cells các obj dc đánh dấu, có thì cho vào list
	for (int row = rowTop; row <= rowBottom; row++)
	{
		for (int col = colLeft; col <= colRight; col++) // hiện tại với w và h thì nên để col < colRight (thêm <= sẽ lấy thêm obj ngoài cam)
		{
			//DebugOut(L"[INFO] Row thu: %d\n", row);
			//DebugOut(L"[INFO] So luong obj: %d\n", cells[row][col].size());

			for (int i = 0; i < cells[row][col].size(); i++) // có đánh dấu 
			{
				if (cells[row][col].at(i)->GetLife() > 0) // còn tồn tại
				{
					if (cells[row][col].at(i)->isPush == false)
					{
						ListObj.push_back(cells[row][col].at(i));
						cells[row][col].at(i)->isPush = true;
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

	int rowBottom = floor((obj->y + obj->GetHeight()) / (float)GRID_CELL_HEIGHT);
	int rowTop = floor((obj->y) / (float)GRID_CELL_HEIGHT);

	int colLeft = floor((obj->x) / (float)GRID_CELL_WIDTH);
	int colRight = floor((obj->x + obj->GetWidth()) / (float)GRID_CELL_WIDTH);

	for (int row = rowTop; row <= rowBottom; row++)
	{
		for (int col = colLeft; col <= colRight; col++)
		{
			for (int i = 0; i < cells[row][col].size(); i++)
			{
				if (cells[row][col].at(i)->GetLife() > 0) // còn tồn tại
				{
					if (cells[row][col].at(i)->isPush == false)
					{
						ListObj.push_back(cells[row][col].at(i));
						cells[row][col].at(i)->isPush = true;
					}
				}
			}
		}	
	}
}

void Grid::ResetListObj()
{
	for (int i = 0; i < listObjectGame.size(); i++)
	{
		listObjectGame[i]->isPush = false;
	}
}

void Grid::Insert(int id, int type, int nx, float x, float y, float w, float h)
{
	CGameObject * dataObject = GetNewObject(type, x, y, w, h); // sau khi load info từ file, xác định obj ->vẽ ra màn hình
	if (dataObject == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] : Obj load fail!\n");
		return;
	}
	dataObject->SetId(id);
	dataObject->SetDirect(nx);
	dataObject->isPush = false;

	listObjectGame.push_back(dataObject); // thêm vào list obj 

	int Top = floor(y / (float)GRID_CELL_HEIGHT);
	int Bottom = floor((y + h) / (float)GRID_CELL_HEIGHT);

	int Left = floor(x / (float)GRID_CELL_WIDTH);
	int Right = floor((x + w) / (float)GRID_CELL_WIDTH);

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
