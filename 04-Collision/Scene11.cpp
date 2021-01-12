#include "Scene11.h"

/* Scene 1*/
Scene_1::Scene_1()
{
	Data::GetInstance()->scene = 1;
	LoadResources();
}

Scene_1::~Scene_1()
{
	SAFE_DELETE(TileMap);
	SAFE_DELETE(board);
	SAFE_DELETE(gridGame);
}

void Scene_1::KeyState(BYTE * state)
{
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
		return;

	if (simon->isAutoGo == true) // đang chế độ tự đi thì ko xét phím
		return;

	if (simon->isJumping && simon->isWalking)
		return;

	if (simon->isAttacking) // đang attack
	{
		float vx, vy;
		simon->GetSpeed(vx, vy);
		simon->SetSpeed(0, vy);

		return;
	}

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
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

	if (KeyCode == DIK_S)
	{
		DebugOut(L"x_s = %f . x_y = %f\n", simon->x, simon->y);
	}

	if (KeyCode == DIK_A)
	{
		simon->SetPosition(1275.0f, 0);
	}

	if (KeyCode == DIK_P) // simon autogo
	{
		simon->AutoGo((float)simon->GetDirect(), 1, 200.0f, SIMON_WALKING_SPEED);
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
		simon->sprite->ResetTime();
		//DebugOut(L"Simon Fight key down X\n");
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

	if (KeyCode == DIK_1)
	{
		camera->SetAllowFollowSimon(0);
		camera->SetPosition(camera->GetX_cam() + 20.0f, 0);

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
			simon->SetSpeed(SIMON_WALKING_SPEED * simon->GetDirect(), -SIMON_VJUMP);
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

void Scene_1::LoadResources()
{
	LoadTexture::GetInstance()->LoadResource();

	sound = Sound::GetInstance();

	TileMap = new Map();
	TileMap->LoadMap(eMap::mMap1);

	camera = SceneManager::GetInstance()->GetCamera();
	camera->SetBoundary(0, (float)(TileMap->GetMapWidth() - camera->GetWidth())); // set biên camera dựa vào kích thước map
	camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight()); // backup lại biên

	camera->SetPosition(0, 0);

	board = new BoardGame(0, 0);

	simon = new Simon(camera);
	simon->SetPosition(0, 300.0f);

	simon->SetPositionBackup(SIMON_POSITION_DEFAULT);

	gridGame = new Grid();

	listItem.clear();

	listEffect.clear();

	//set time = 0
	gameTime = new CGameTime();
	gameTime->SetTime(0);

	isPassScene = 0;
	// bắt đầu vào -> nhạc game
	sound->Play(eSound::smusicStage1, true);
}

void Scene_1::Update(DWORD dt)
{
	if (camera->AllowFollowSimon())
	{
		camera->SetPosition(simon->x - Window_Width / 2 + 30, camera->GetY_cam()); // cho camera chạy theo simon
	}
	camera->Update(dt);
	/*
	load vào các obj static, (1)load enemy => add vào list này => simon update lấy cả static + ene
	lúc update
	- static: cast về các obj static
	- ene: cast về enemy

	cần fix:
	(1) khi add ene vào list thì sau nó update lại từ gird, đủ 3 ghost => k push nữa => listAllobj k chứa ene để update
	*/

	/*
	giữ nguyên list cũ, add vào listall => simon update !ok => làm tiếp idea này cho roi => test => !ok
	- triển khai test hết các enemy all map + optimze code => !ok
	- Chuyển va chạm simon with all vào simon.cpp => ! đã xong ene + item, cần làm tiếp hidden + một số thứ => !ok
	- Chưa set va chạm với nước 
	*/

	// nếu đang trong state freeze => k update simon
	if (simon->GetFreeze() == true)
	{
		simon->UpdateFreeze(dt);
		if (simon->GetFreeze() == true)
			return;
	}

	if (gameTime->GetTime() >= GAME_TIME_SCENE1)
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

	if (GAME_TIME_SCENE1 - gameTime->GetTime() <= 30) // đúng còn lại 30 giây thì bật sound loop
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
		if (listEffect[i]->GetFinish() == false)
			listEffect[i]->Update(dt);
	}

	CheckCollision();
	DropItem();
}

void Scene_1::Render()
{
	TileMap->DrawMap(camera);

	board->Render(simon, Data::GetInstance()->hpBoss, GAME_TIME_SCENE1 - gameTime->GetTime(), simon->subWeapon, 1);

	for (UINT i = 0; i < listObj.size(); i++)
	{
		listObj[i]->Render(camera);
	}

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

void Scene_1::ResetResource()
{
	SAFE_DELETE(gridGame);
	gridGame = new Grid();

	listItem.clear();
	listEffect.clear();

	gameTime->SetTime(0); // đếm lại từ 0
	sound->Stop(eSound::smusicStage1); // tắt nhạc nền
	sound->Play(eSound::smusicStage1, true); // mở lại nhạc nền
}

void Scene_1::CheckCollision()
{
	simon->CollisionWithItem(&listItem);
	CheckCollisionSimonWithHidenObject();
}

void Scene_1::DropItem()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		CGameObject *gameObj = listObj[i];

		if (gameObj->GetLife() <= 0 && !gameObj->GetIsDrop())
		{
			switch (gameObj->GetType())
			{
				case def_ID::BIGCANDLE:
				{
					gameObj->SetIsDrop(1);
					listItem.push_back(GetNewItem(gameObj->GetObj_id(), def_ID::BIGCANDLE, gameObj->x, gameObj->y));
					sound->Play(eSound::sHit); // sound đánh trúng obj
					listEffect.push_back(new Hit((int)(listObj[i]->x), (int)(listObj[i]->y + 10))); // hiệu ứng lửa
					listEffect.push_back(new Effect((int)(listObj[i]->x - 5), (int)(listObj[i]->y + 8))); // hiệu ứng lửa
					break;
				}
			}
		}
		
	}
}

void Scene_1::CheckCollisionSimonWithHidenObject()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == def_ID::HIDDENOBJECT)
		{
			CGameObject * hidenObject = dynamic_cast<CGameObject*>(listObj[i]);
			if (hidenObject->GetHP() > 0)
			{
				if (simon->isCollitionAll(hidenObject))
				{
					switch (hidenObject->GetObj_id())
					{
						case eHidden::PROCESSINGSCENE1: // đụng trúng cửa
						{
							simon->AutoGo((float)simon->GetDirect(), 1, 75.0f, 0.04f);
							
							break;
						}
						case eHidden::PASSINGSCENE2:
						{
							sound->Play(eSound::sMonneyBag);
							listItem.push_back(GetNewItem(hidenObject->GetObj_id(), hidenObject->GetType(), simon->x, simon->y));
							simon->SetPoint(simon->GetPoint() + 1000);
							SceneManager::GetInstance()->SetScene(new Scene_2(simon, gameTime));
							
							return;
							break;
						}
					}

					hidenObject->LoseLife(1);
				}
			}
		}
	}
}

Items * Scene_1::GetNewItem(int Id, def_ID Type, float X, float Y)
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