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
	if (simon->isJumping && simon->isWalking)
		return;

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

	if (simon->isJumping)
		return;

	if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		if (simon->isAttacking)
		{
			float vx, vy;
			simon->GetSpeed(vx, vy);
			simon->SetSpeed(0, vy);
			return;
		}

		simon->Right();
		simon->Go();
	}
	else
		if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			if (simon->isAttacking)
			{
				float vx, vy;
				simon->GetSpeed(vx, vy);
				simon->SetSpeed(0, vy);
				return;
			}
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
	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(/*hWnd*/ CGame::GetInstance()->GetWindowHandle());

	if (KeyCode == DIK_Q)
		simon->SetPosition(SIMON_POSITION_DEFAULT);

	if (KeyCode == DIK_X)
	{
		simon->Attack(simon->mainWeapon);
	}

	if (KeyCode == DIK_Z)
	{
		if (simon->subWeapon != NULL && simon->subWeapon->GetFinish() == true && simon->GetHeartCollect() > 0)
		{
			simon->SetHeartCollect(simon->GetHeartCollect() - 1); // giảm 1 heart
			simon->Attack(simon->subWeapon);
		}
	}

	if (simon->isJumping && simon->isWalking)
	{
		return;
	}

	if (KeyCode == DIK_SPACE)
	{
		if (CGame::GetInstance()->IsKeyDown(DIK_LEFT) || CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			simon->Stop();
			float vx, vy;
			simon->GetSpeed(vx, vy);
			simon->SetSpeed(SIMON_WALKING_SPEED * simon->GetDirect(), vy - SIMON_VJUMP);
			simon->isJumping = 1;
			simon->isWalking = 1;
		}
		else
		{
			simon->Jump();
		}
	}
}

void Scene_1::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

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

	listItem.clear();

	listEffect.clear();
}

void Scene_1::Update(DWORD dt)
{
	camera->SetPosition(simon->x - Window_Width / 2 + 30, camera->GetY_cam()); // cho camera chạy theo simon
	camera->Update();

	gridGame->GetListObject(listObj, camera); // update các objec có life > 0 trong cam

	simon->Update(dt, &listObj);

	for (UINT i = 0; i < listObj.size(); i++)
	{
		listObj[i]->Update(dt, &listObj);
	}

	for (UINT i = 0; i < listItem.size(); i++) // update các Item
	{
		listItem[i]->Update(dt, &listObj); // trong các hàm update chỉ kiểm tra va chạm với đất
	}

	for (UINT i = 0; i < listEffect.size(); i++)
	{
		//DebugOut(L"[INFO] eff: %d\n", listEffect[i]->GetFinish());
		if (listEffect[i]->GetFinish() == false)
			listEffect[i]->Update(dt);
	}

	CheckCollision();
}

void Scene_1::Render()
{
	TileMap->DrawMap(camera);

	board->Render(camera, simon,simon->subWeapon, 1);

	for (UINT i = 0; i < listObj.size(); i++)
		listObj[i]->Render(camera);

	for (UINT i = 0; i < listItem.size(); i++) // Draw các item
	{
		if (listItem[i]->GetFinish() == false)
			listItem[i]->Render(camera);
	}

	for (UINT i = 0; i < listEffect.size(); i++)
	{
		if (listEffect[i]->GetFinish() == false)
			listEffect[i]->Render(camera);
	}

	simon->Render(camera);
}

void Scene_1::CheckCollision()
{
	CheckCollisionWeapon();

	CheckCollisionSimonWithItem();
}

void Scene_1::CheckCollisionWeapon()
{
	if (listObj.size() == 0)
		return;

	if (simon->mainWeapon->GetFinish() == false) // Vũ khí đang hoạt động
	{
		for (UINT i = 0; i < listObj.size(); i++)
			if (listObj[i]->GetType() == def_ID::CANDLE)
				if (simon->mainWeapon->isCollision(listObj[i]) == true)
				{
					CGameObject *candle = dynamic_cast<CGameObject*>(listObj[i]);
					candle->LoseLife(1);
					listEffect.push_back(new Hit((int)(candle->x), (int)(candle->y + 10))); // hiệu ứng lửa
					listEffect.push_back(new Effect((int)(candle->x - 5), (int)(candle->y + 8))); // hiệu ứng lửa
					listItem.push_back(GetNewItem(candle->GetObj_id(), def_ID::CANDLE, candle->x + 5, candle->y));
				}
	}

	if (simon->subWeapon != NULL && simon->subWeapon->GetFinish() == false)
	{
		for (UINT i = 0; i < listObj.size(); i++)
			if (listObj[i]->GetType() == def_ID::CANDLE)
				if (simon->subWeapon->isCollision(listObj[i]) == true)
				{
					CGameObject *candle = dynamic_cast<CGameObject*>(listObj[i]);
					candle->LoseLife(1);
					simon->subWeapon->SetFinish(true);   // cây kiếm trúng object thì tắt luôn
					listEffect.push_back(new Hit((int)(candle->x ), (int)(candle->y + 10))); // hit effect
					listEffect.push_back(new Effect((int)(candle->x - 5), (int)(candle->y + 8))); // hit effect
					listItem.push_back(GetNewItem(candle->GetObj_id(), def_ID::CANDLE, candle->x, candle->y));
				}
	}
}

void Scene_1::CheckCollisionSimonWithItem()
{
	if (listItem.size() == 0)
		return;

	for (UINT i = 0; i < listItem.size(); i++)
		// nếu item chưa biến mất (do k collect) và item đang không phải trong thời gian của hiteffect thì xét va chạm
		if (listItem[i]->GetFinish() == false && listItem[i]->isWaitingDisplay() == false) 
		{
			if (simon->isCollisionWithItem(listItem[i]) == true) // có va chạm
			{
				switch (listItem[i]->GetType())
				{
				case def_ID::BIGHEART:
				{
					simon->SetHeartCollect(simon->GetHeartCollect() + 5);
					listItem[i]->SetFinish(true);
					break;
				}
				case def_ID::UPGRADEMORNINGSTAR:
				{
					MorningStar * objMorningStar = dynamic_cast<MorningStar*>(simon->mainWeapon);
					objMorningStar->UpgradeLevel(); // Nâng cấp vũ khí roi
					listItem[i]->SetFinish(true);
					break;
				}
				case def_ID::iDAGGER:
				{
					SAFE_DELETE(simon->subWeapon);
					simon->subWeapon = new Dagger();
					listItem[i]->SetFinish(true);
					break;
				}
				default:
					DebugOut(L"[CheckCollisionSimonWithItem] Khong nhan dang duoc loai Item!\n");
					break;
				}
			}
		}
	//DebugOut(L"[INFO] listItem: %d\n", listItem.size()); chưa xóa item đã bị collect trong listItem nha.
}


Items * Scene_1::GetNewItem(int Id, def_ID Type, float X, float Y)
{
	if (Type == def_ID::CANDLE)
	{
		if (Id == 1 || Id == 4)
			return new BigHeart(X, Y);

		if (Id == 2 || Id == 3)
			return new Whip(X, Y);
		if (Id == 5)
			return new iDagger(X, Y);
	}
}