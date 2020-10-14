#include "Scene11.h"

/* Scene 1*/
Scene_1::Scene_1()
{
}


Scene_1::~Scene_1()
{
}

void Scene_1::KeyState(BYTE * state)
{

	if (CGame::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		simon->Sit();

		if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
			simon->Right();

		if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
			simon->Left();

		return;
	}
	else
		simon->Stop();


	if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		simon->Right();
		simon->Go();
	}
	else
		if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			simon->Left();
			simon->Go();
		}
		else
		{
			simon->Stop();
		}
}

void Scene_1::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(/*hWnd*/ CGame::GetInstance()->GetWindowHandle());

		if (KeyCode == DIK_Q)
			simon->SetPosition(SIMON_POSITION_DEFAULT);

	if (KeyCode == DIK_SPACE)
	{
		simon->Jump();
	}

	if (KeyCode == DIK_1)
	{
		DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->x + 10, simon->y);
	}

	if (KeyCode == DIK_X)
	{
		//DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->x + 10, simon->y);
		simon->Attack(simon->ListWeapon[0]);
	}
}

void Scene_1::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	switch (KeyCode)
	{
	case DIK_SPACE:
		//simon->Sit();
		break;
	}
}

void Scene_1::LoadResources()
{
	TileMap = new Map();

	camera = new Camera(Window_Width, Window_Height/*, Window_Width/2, MapWidth - Window_Width / 2*/);
	camera->SetPosition(0, 0);

	board = new BoardGame(0, 0);

	simon = new Simon();
	simon->SetPosition(0, 0);

	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources\\map\\Obj_1.txt"); // đọc các object từ file vào Grid

	_data = Data::GetInstance();
	_data->ListItem.clear();

}

void Scene_1::Update(DWORD dt)
{
	camera->SetPosition(simon->x - Window_Width / 2 + 30, camera->GetY_cam()); // cho camera chạy theo simon
	camera->Update();

	gridGame->GetListObject(ListObj, camera); // lấy hết các object trong vùng camera;

	simon->Update(dt, &ListObj);

	for (UINT i = 0; i < ListObj.size(); i++)
	{
		ListObj[i]->Update(dt, &ListObj);
	}

	for (UINT i = 0; i < _data->ListItem.size(); i++) // update các Item
	{
		_data->ListItem[i]->Update(dt, &ListObj);
	}
}

void Scene_1::Render()
{
	TileMap->DrawMap(camera);

	board->Render(camera);

	for (UINT i = 0; i < ListObj.size(); i++)
		ListObj[i]->Render(camera);

	for (UINT i = 0; i < _data->ListItem.size(); i++) // Draw các item
		_data->ListItem[i]->Render(camera);

	simon->Render(camera);
}