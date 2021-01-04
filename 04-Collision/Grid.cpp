#include "Grid.h"
#include "debug.h"

Grid::Grid()
{
	if (Data::GetInstance()->scene == 1)
	{
		ReadFileToGrid("Resources\\map\\Obj_1.txt");
	}
	else if (Data::GetInstance()->scene == 2)
	{
		ReadFileToGrid("Resources\\map\\Obj_2.txt");
	}
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
			pushToCell(id, type, nx, x, y, w, h, update);
		}
		inp.close();
	}
}

void Grid::GetListObject(vector<CGameObject*>& ListObj, Camera * camera)
{
	ListObj.clear(); // clear list
	vector<int> listIdObject;

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
					if (find(begin(listIdObject), end(listIdObject), cells[row][col].at(i)->GetObj_id()) == end(listIdObject))
					{
						listIdObject.push_back(cells[row][col].at(i)->GetObj_id());
						ListObj.push_back(cells[row][col].at(i));
					}
				}
			}
		}
	}
}


void Grid::pushToCell(int id, int type, int nx, int x, int y, int w, int h, int update)
{
	CGameObject * dataObject = GetNewObject(type, x, y, w, h, update); // sau khi load info từ file, xác định obj ->vẽ ra màn hình
	if (dataObject == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] : Obj load fail!\n");
		return;
	}
	dataObject->SetId(id);
	dataObject->SetDirect(nx);
	//dataObject->SetIsPush(false);

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
