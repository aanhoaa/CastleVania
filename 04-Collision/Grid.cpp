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

	int id, type, nx, x, y, w, h, update;

	if (inp)
	{
		int n;
		inp >> n;

		for (int i = 0; i < n; i++)
		{
			inp >> id >> type >> nx >> x >> y >> w >> h >> update;
			Insert(id, type, nx, x, y, w, h, update);
		}
		inp.close();
	}
}

void Grid::GetListObject(vector<CGameObject*>& ListObj, Camera * camera)
{
	ListObj.clear(); // clear list
	unordered_map<int, CGameObject*> ListObject;

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
				
				if ((cells[row][col].at(i)->GetLife() > 0)) // còn tồn tại
				{
					if (ListObject.find(cells[row][col].at(i)->GetObj_id()) == ListObject.end()) // check không trùng id
					{
						ListObject[cells[row][col].at(i)->GetObj_id()] = cells[row][col].at(i);
						ListObj.push_back(cells[row][col].at(i));
					}
				}
			}
		}
	}
}

void Grid::GetListObject(vector<CGameObject*> &ListObj, CGameObject * obj)
{
	ListObj.clear(); // clear list
	//ResetListObj();

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


void Grid::Insert(int id, int type, int nx, int x, int y, int w, int h, int update)
{
	CGameObject * dataObject = GetNewObject(type, x, y, w, h, update); // sau khi load info từ file, xác định obj ->vẽ ra màn hình
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
CGameObject * Grid::GetNewObject(int type, int x, int y, int w, int h, int update)
{
	if (type == def_ID::BRICK) return new Brick(x, y, w, h, update);
	if (type == def_ID::BIGCANDLE) return new Candle(x, y);
	if (type == def_ID::HIDDENOBJECT) return new HidenObject(x, y, w, h);
	if (type == def_ID::SMALLCANDLE) return new Candle(x, y);
	if (type == def_ID::BOTTOMSTAIR) return new Stairs(x, y, update);
	if (type == def_ID::TOPSTAIR) return new Stairs(x, y, update);
	if (type == def_ID::GATE) return new Gate(x, y);
	
	return NULL;
}
