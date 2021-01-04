#include "GameEnd.h"



GameEnd::GameEnd(/*Simon * _simon*/)
{
	//simon = _simon;
	Data::GetInstance()->scene = 3;
	LoadResources();
}


GameEnd::~GameEnd()
{

}

void GameEnd::KeyState(BYTE * state)
{
}

void GameEnd::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_2) // lấy tọa độ world của chuột 
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(CGame::GetInstance()->GetWindowHandle(), &p);
		DebugOut(L"[MOUSE POSITION] %d %d \n", p.x, p.y);
	}

	if (KeyCode == DIK_3) // lấy tọa độ world của chuột 
	{
		castle->SetActive(1);
	}

	if (KeyCode == DIK_4) // lấy tọa độ world của chuột 
	{
		DebugOut(L"c_x %f  . c_y %f \n", camera->GetX_cam(), camera->GetY_cam());
	}
}

void GameEnd::OnKeyUp(int KeyCode)
{
}


void GameEnd::LoadResources()
{
	LoadTexture::GetInstance()->LoadResource();
	LoadTexture * _textureManager = LoadTexture::GetInstance(); // Đã gọi load resource

	Sprite_Castle = new Load_resources(_textureManager->GetTexture(def_ID::CASTLE), 0);
	//Sprite_Top = new Load_resources(_textureManager->GetTexture(def_ID::TOPCASTLE), 0);
	camera = SceneManager::GetInstance()->GetCamera();
	camera->SetPosition(0, 0);

	castle = new CastleTop(336, 75);
}

void GameEnd::Update(DWORD dt)
{
	camera->Update(dt);
	castle->Update(dt);
}

void GameEnd::Render()
{
	Sprite_Castle->Draw(0, 0);
	//Sprite_Top->Draw(0, 0);
	castle->Render(camera);
	
	if (castle->GetEndGame())
		TextInfor.Draw(160, 200, "END GAME");
}