#include "Scene12.h"

/* Scene 1*/
Scene_2::Scene_2(Simon * _simon, CGameTime* _gameTime)
{
	simon = _simon;
	gameTime = _gameTime;
	Data::GetInstance()->scene = 2;
	LoadResources();
}

Scene_2::~Scene_2()
{

}

void Scene_2::KeyState(BYTE * state)
{
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

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

void Scene_2::OnKeyDown(int KeyCode)
{
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(/*hWnd*/ CGame::GetInstance()->GetWindowHandle());

	if (KeyCode == DIK_Q)
		simon->SetPosition(SIMON_POSITION_DEFAULT);

	if (KeyCode == DIK_X)
	{
		if (simon->isAttacking == false)
			sound->Play(eSound::sMorningStar);
		simon->Attack(simon->mainWeapon);
	}

	if (KeyCode == DIK_Z)
	{
		if (simon->subWeapon != NULL && simon->subWeapon->GetFinish() == true && simon->GetHeartCollect() > 0)
		{
			simon->SetHeartCollect(simon->GetHeartCollect() - 1); // giảm 1 heart
			simon->Attack(simon->subWeapon);
			sound->Play(eSound::sDagger);
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

void Scene_2::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

	switch (KeyCode)
	{
	case DIK_SPACE:
		//simon->Sit();
		break;
	}
}

void Scene_2::LoadResources()
{
	sound = Sound::GetInstance();

	if (simon == NULL)
		simon = new Simon();

	if (gameTime == NULL)
		gameTime = new CGameTime();

	TileMap = new Map();
	TileMap->LoadMap(eMap::mMap2);

	camera = new Camera(Window_Width, Window_Height);
	camera->SetPosition(0, 0);

	board = new BoardGame(0, 0);

	//simon = new Simon();
	simon->SetPosition(SIMON_POSITION_DEFAULT);

	simon->SetPositionBackup(SIMON_POSITION_DEFAULT);

	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources\\map\\Obj_2.txt"); // đọc các object từ file vào Grid

	listItem.clear();

	listEffect.clear();

	//set time = 0
	gameTime->SetTime(0);

	// bắt đầu vào -> nhạc game
	sound->Play(eSound::smusicStage1, true);
}

void Scene_2::Update(DWORD dt)
{
	camera->SetPosition(simon->x - Window_Width / 2 + 30, camera->GetY_cam()); // cho camera chạy theo simon
	camera->Update();

	// nếu đang trong state freeze => k update simon
	if (simon->GetFreeze() == true)
	{
		simon->UpdateFreeze(dt);
		if (simon->GetFreeze() == true)
			return;
	}

	if (gameTime->GetTime() >= GAME_TIME_SCENE2)
	{
		sound->Play(eSound::smusicLose);
		if (simon->GetLife() == 0)
			return;
		bool result = simon->LoseLife();
		if (result == true) // còn mạng để chơi tiếp, giảm mạng reset máu xong
		{
			ResetResource(); // reset lại game
		}
		return;
	}
	else
		gameTime->Update();

	if (GAME_TIME_SCENE2 - gameTime->GetTime() <= 30) // đúng còn lại 30 giây thì bật sound loop
	{
		if (gameTime->checkIstandardTime() == true) // check khi nào đủ 1s sẽ phát sound
		{
			sound->Play(eSound::sStopTimer);
		}
	}

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

void Scene_2::Render()
{
	TileMap->DrawMap(camera);

	board->Render(camera, simon, GAME_TIME_SCENE2 - gameTime->GetTime(), simon->subWeapon, 1);

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

void Scene_2::ResetResource()
{
	SAFE_DELETE(gridGame);
	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources/map/Obj_2.txt"); // đọc lại các object từ list

	listItem.clear();
	listEffect.clear();

	gameTime->SetTime(0); // đếm lại từ 0
	sound->Stop(eSound::smusicStage1); // tắt nhạc nền
	sound->Play(eSound::smusicStage1, true); // mở lại nhạc nền
}

void Scene_2::CheckCollision()
{
	CheckCollisionWeapon();
	CheckCollisionSimonWithItem();
	CheckCollisionSimonWithHidenObject();
}

void Scene_2::CheckCollisionWeapon()
{
	if (listObj.size() == 0)
		return;

	if (simon->mainWeapon->GetFinish() == false) // Vũ khí đang hoạt động
	{
		for (UINT i = 0; i < listObj.size(); i++)
			if (listObj[i]->GetType() == def_ID::BIGCANDLE)
				if (simon->mainWeapon->isCollision(listObj[i]) == true)
				{
					CGameObject *candle = dynamic_cast<CGameObject*>(listObj[i]);
					candle->LoseLife(1);
					listEffect.push_back(new Hit((int)(candle->x), (int)(candle->y + 10))); // hiệu ứng lửa
					listEffect.push_back(new Effect((int)(candle->x - 5), (int)(candle->y + 8))); // hiệu ứng lửa
					listItem.push_back(GetNewItem(candle->GetObj_id(), def_ID::BIGCANDLE, candle->x + 5, candle->y));
					sound->Play(eSound::sHit); // sound đánh trúng obj
				}
	}

	if (simon->subWeapon != NULL && simon->subWeapon->GetFinish() == false)
	{
		for (UINT i = 0; i < listObj.size(); i++)
			if (listObj[i]->GetType() == def_ID::BIGCANDLE)
				if (simon->subWeapon->isCollision(listObj[i]) == true)
				{
					CGameObject *candle = dynamic_cast<CGameObject*>(listObj[i]);
					candle->LoseLife(1);
					simon->subWeapon->SetFinish(true);   // cây kiếm trúng object thì tắt luôn
					listEffect.push_back(new Hit((int)(candle->x), (int)(candle->y + 10))); // hit effect
					listEffect.push_back(new Effect((int)(candle->x - 5), (int)(candle->y + 8))); // hit effect
					listItem.push_back(GetNewItem(candle->GetObj_id(), def_ID::BIGCANDLE, candle->x, candle->y));
					sound->Play(eSound::sHit); // sound đánh trúng obj
				}
	}
}

void Scene_2::CheckCollisionSimonWithItem()
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
					sound->Play(eSound::sCollectItem); // sound collect item
					break;
				}
				case def_ID::UPGRADEMORNINGSTAR:
				{
					MorningStar * objMorningStar = dynamic_cast<MorningStar*>(simon->mainWeapon);
					objMorningStar->UpgradeLevel(); // Nâng cấp vũ khí roi
					listItem[i]->SetFinish(true);
					simon->SetFreeze(true); // bật trạng thái đóng băng
					sound->Play(eSound::sCollectWeapon);
					break;
				}
				case def_ID::iDAGGER:
				{
					SAFE_DELETE(simon->subWeapon);
					simon->subWeapon = new Dagger();
					listItem[i]->SetFinish(true);
					sound->Play(eSound::sCollectWeapon);
					break;
				}
				case def_ID::MONNEYBAG:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::sCollectItem);
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

void Scene_2::CheckCollisionSimonWithHidenObject()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == def_ID::HIDDENOBJECT)
		{
			CGameObject * hidenObject = dynamic_cast<CGameObject*>(listObj[i]);
			if (hidenObject->GetHP() > 0)
			{
				LPCOLLISIONEVENT e = simon->SweptAABBEx(listObj[i]);
				if (0 < e->t && e->t <= 1) // có va chạm xảy ra
				{
					switch (hidenObject->GetObj_id())
					{
					case 8:
					{
						sound->Play(eSound::sMonneyBag);
						listItem.push_back(GetNewItem(hidenObject->GetObj_id(), def_ID::HIDDENOBJECT, simon->x, simon->y));
						// chưa hiện effect 1000d
						simon->SetPoint(simon->GetPoint() + 1000);

						break;
					}
					}

					hidenObject->LoseLife(1);
				}
			}
		}
	}
}

Items * Scene_2::GetNewItem(int Id, def_ID Type, float X, float Y)
{
	if (Type == def_ID::BIGCANDLE)
	{
		if (Id == 1 || Id == 4)
			return new BigHeart(X, Y);

		if (Id == 2 || Id == 3)
			return new Whip(X, Y);
		if (Id == 5)
			return new iDagger(X, Y);
	}

	if (Type == def_ID::HIDDENOBJECT)
	{
		if (Id == 8)
			return new MoneyBag(1240, 305);
	}
	return new BigHeart(X, Y);
}