#include "Scene12.h"

Scene_2::Scene_2(Simon * _simon, CGameTime* _gameTime)
{
	simon = _simon;
	gameTime = _gameTime;
	Data::GetInstance()->scene = 2;
	FirstTimeGenGhost = GetTickCount();
	LoadResources();
}

Scene_2::~Scene_2()
{
	SAFE_DELETE(TileMap);
	SAFE_DELETE(board);
	SAFE_DELETE(gridGame);
	SAFE_DELETE(simon);
}

void Scene_2::KeyState(BYTE * state)
{
	if (simon->GetFreeze() || simon->isDeadth 
		|| gameOver || simon->isAutoGo
		|| simon->isJumping || simon->isEnemyHit || camera->GetIsAutoGoX())
		return;

	if (simon->isAttacking)
	{
		float vx, vy;
		simon->GetSpeed(vx, vy);
		simon->SetSpeed(0, vy);

		return;
	}

	if (CGame::GetInstance()->IsKeyDown(DIK_UP) && simon->isAttacking == false)
	{
		if (!simon->isOnStair) // chưa lên cầu thang
		{
			for (UINT i = 0; i < listObj.size(); i++)
			{
				if (listObj[i]->GetType() == def_ID::BOTTOMSTAIR)
				{
					if (simon->isCollitionAll(listObj[i])) 
					{
						CGameObject* hidenObj = dynamic_cast<CGameObject*>(listObj[i]);

						simon->nx_stair = listObj[i]->GetDirect();
						simon->SetDirect(simon->nx_stair);
						simon->isOnStair = 1;
						simon->HeightStair = 0;
						simon->isStairUp = 1;
						
						if (simon->x < hidenObj->x)
						{
							simon->AutoGo(1, hidenObj->GetDirect(), hidenObj->x - simon->x, SIMON_WALKING_SPEED);
						}
						else
							simon->AutoGo(-1, hidenObj->GetDirect(), simon->x - hidenObj->x, SIMON_WALKING_SPEED);

						return;
					}
				}
			}
		}
		else
		{
			if (simon->isProcessingOnStair == 0 || simon->isProcessingOnStair == 3)
			{
				simon->SetDirect(simon->nx_stair);
				simon->isWalking = true;
				simon->isStairUp = 1;
				simon->isProcessingOnStair = 1;
				simon->SetSpeed(simon->GetDirect() * SIMON_SPEED_ONSTAIR, -1 * SIMON_SPEED_ONSTAIR);
			}
		}
	}
	else
	{
		if (CGame::GetInstance()->IsKeyDown(DIK_DOWN))
		{
			if (!simon->isOnStair) // chưa lên cầu thang
			{
				int checkCollision = 0;
				for (UINT i = 0; i < listObj.size(); i++)
				{
					if (listObj[i]->GetType() == def_ID::TOPSTAIR)
					{
						if (simon->isCollitionAll(listObj[i])) 
						{
							CGameObject* hidenObj = dynamic_cast<CGameObject*>(listObj[i]);
							simon->nx_stair = hidenObj->GetDirect(); 
							simon->SetDirect(simon->nx_stair);
							simon->isStairUp = -1;

							simon->isOnStair = true; 
							simon->HeightStair = 0;

							if (simon->x < hidenObj->x)
							{
								simon->AutoGo(1, -hidenObj->GetDirect(), hidenObj->x - simon->x + 3, SIMON_WALKING_SPEED);
							}
							else
								simon->AutoGo(-1, -hidenObj->GetDirect(), simon->x - hidenObj->x + 3, SIMON_WALKING_SPEED);
							checkCollision++;

							return;
						}
					}
				}

				if (checkCollision == 0) 
				{
					simon->Sit();
					if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
						simon->Right();

					if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
						simon->Left();
					return;
				}
			}
			else
			{
				if (simon->isProcessingOnStair == 0 || simon->isProcessingOnStair == 3) 
				{
					simon->isWalking = true;
					simon->isProcessingOnStair = 1;
					simon->isStairUp = -1;
					simon->HeightStair = 0;
					simon->SetDirect(-simon->nx_stair);
					simon->SetSpeed(simon->GetDirect() * SIMON_SPEED_ONSTAIR, SIMON_SPEED_ONSTAIR);
				}
			}
		}
		else 
		{
			simon->Stop();
		}
	}

	if (simon->isOnStair) 
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

	if (camera->GetIsAutoGoX()) // camera đang chế độ tự đi thì ko xét phím
		return;

	if (simon->isEnemyHit)
		return;

	if (simon->isAttacking)
		return;

	if (simon->isAutoGo)
		return;

	if (gameOver)
	{
		switch (KeyCode)
		{
		case DIK_UP:
		{
			optionSelect = OPTION_SELECT_CONTINUE;
			break;
		}
		case DIK_DOWN:
		{
			optionSelect = OPTION_SELECT_END;
			break;
		}
		case DIK_RETURN:
		{
			if (optionSelect == OPTION_SELECT_CONTINUE)
			{
				SceneManager::GetInstance()->SetScene(new Scene_1());
			}
			else
				if (optionSelect == OPTION_SELECT_END)
				{
					DestroyWindow(CGame::GetInstance()->GetWindowHandle()); // thoát
				}
			break;
		}
		}
		return;
	}

	if (KeyCode == DIK_S)
	{
		DebugOut(L"x_s = %f . x_y = %f\n", simon->x, simon->y);
	}

	if (KeyCode == DIK_H) // create hollywater
	{
		simon->subWeapon = new HolyWater(camera);
	}

	if (KeyCode == DIK_F) // create hollywater
	{
		simon->SetHP(16);
		simon->setLife(9999);
		simon->SetHeartCollect(9999);
		gameTime->SetTime(0);
		simon->subWeapon = new Axe(camera);
	}

	if (KeyCode == DIK_P) // simon autogo
	{
		simon->AutoGo((float)simon->GetDirect(), -1, 200.0f, SIMON_WALKING_SPEED);
	}

	if (KeyCode == DIK_P) // simon autogo
	{
		simon->AutoGo((float)simon->GetDirect(), -1, 200.0f, SIMON_WALKING_SPEED);
	}

	if (KeyCode == DIK_T)
	{
		listEnemy.push_back(new Bat(simon->x + 100, 326, 1));// 34 framewidth của ghost
	}

	if (KeyCode == DIK_D)
	{
		simon->SetHP(16);
		simon->setLife(1);
		simon->SetHeartCollect(2);
		gameTime->SetTime(0);
		simon->subWeapon = new Dagger();
	}

	if (KeyCode == DIK_A)
	{
		simon->SetPosition(2866.0f, 0);
	}

	if (KeyCode == DIK_1)
	{
		DebugOut(L"x_cam %f . y_cam%f\n", camera->GetBoundaryLeft(), camera->GetY_cam());
	}

	if (KeyCode == DIK_2)
	{
		simon->SetPosition(5000.0f, 100.0f);
	}

	if (KeyCode == DIK_3)
	{
		DebugOut(L"x_cam %f\n", camera->GetX_cam());
	}

	if (KeyCode == DIK_7)
	{
		testa = 1;
		sound->Stop(eSound::smusicStage1);
		SceneManager::GetInstance()->SetScene(new GameEnd());
	}

	if (KeyCode == DIK_8) // đứng ngay cầu thang gần xuoosg hồ nước
	{
		DebugOut(L"[SET POSITION SIMON] x = .... \n");
		simon->SetPosition(5000.0f, 310.0f);


		camera->SetBoundary(camera->GetBoundaryLeft(), CAMERA_BOUNDARY_BOSS_RIGHT);// mở biên phải rộng ra thêm để chạy AutoGo
																	 //camera->SetAutoGoX(abs(ViTriCameraDiChuyenTruocKhiQuaCua - camera->GetXCam()), SIMON_WALKING_SPEED);
		simon->Stop(); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()
		isProcessingGoThroughTheDoor2 = true; // bật trạng thái xử lí qua cửa
		isDoneSimonGoThroughTheDoor2 = false;


		isDoneSimonGoThroughTheDoor2 = true;
		//	camera->SetAutoGoX(abs(ViTriCameraDiChuyenSauKhiQuaCua - camera->GetXCam()), SIMON_WALKING_SPEED);
		isDoneCameraGoThroughTheDoor1 = false;
		simon->SetPositionBackup(simon->x, 0); // backup lại vị trí sau khi qua màn 
		isGenerateBat = 0;
		stateGame = 3;// set hiển thị đang ở state2
		camera->SetPositionBackup(camera->GetX_cam(), camera->GetY_cam());
	}

	if (KeyCode == DIK_9) // đứng ngay cầu thang gần xuoosg hồ nước
	{
		DebugOut(L"[SET POSITION SIMON] x = .... \n");
		simon->SetPosition(3084.0f, 310.0f);


		camera->SetBoundary(3073, camera->GetBoundaryRight() + 1023);// mở biên phải rộng ra thêm để chạy AutoGo
																	 //camera->SetAutoGoX(abs(ViTriCameraDiChuyenTruocKhiQuaCua - camera->GetXCam()), SIMON_WALKING_SPEED);
		simon->Stop(); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()
		isProcessingGoThroughTheDoor1 = true; // bật trạng thái xử lí qua cửa
		isDoneSimonGoThroughTheDoor1 = false;
		isDoneSimonGoThroughTheDoor1 = true;
		//	camera->SetAutoGoX(abs(ViTriCameraDiChuyenSauKhiQuaCua - camera->GetXCam()), SIMON_WALKING_SPEED);
		isDoneCameraGoThroughTheDoor1 = false;
		simon->SetPositionBackup(simon->x, 0); // backup lại vị trí sau khi qua màn 
		TimeCreateBat = GetTickCount();
		TimeWaitProcessCreateBat = 2000;
		isGenerateBat = true;
		stateGame = 2;// set hiển thị đang ở state2
		camera->SetPositionBackup(camera->GetX_cam(), camera->GetY_cam());
	}

	if (KeyCode == DIK_B)
	{
		simon->SetPosition(1300.0f, 0);
	}

	if (KeyCode == DIK_C) // test AUTO GO CAM
	{
		camera->AutoGo(200.0f, SIMON_WALKING_SPEED);
	}

	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(/*hWnd*/ CGame::GetInstance()->GetWindowHandle());

	if (KeyCode == DIK_Q)
		simon->SetPosition(SIMON_POSITION_DEFAULT);

	if (KeyCode == DIK_X && simon->isProcessingOnStair == 0)
	{
		if (simon->isAttacking == false)
			sound->Play(eSound::sMorningStar);
		simon->Attack(simon->mainWeapon);
		simon->sprite->ResetTime();
	}

	if (KeyCode == DIK_Z)
	{
		if (simon->subWeapon != NULL && simon->subWeapon->GetFinish() == true && simon->GetHeartCollect() > 0)
		{
			simon->SetHeartCollect(simon->GetHeartCollect() - 1); // giảm 1 heart
			simon->Attack(simon->subWeapon);
			
			//DebugOut(L"type sub: = %d\n", simon->subWeapon->GetType());
		}
	}

	if (!testa)
		if (simon->isJumping && simon->isWalking)
		{
			return;
		}

	if (KeyCode == DIK_SPACE && simon->isOnStair == false)
	{
		if (CGame::GetInstance()->IsKeyDown(DIK_LEFT) || CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			simon->Stop();
			//float vx, vy;
			//simon->GetSpeed(vx, vy);
			simon->SetSpeed(SIMON_WALKING_SPEED * simon->GetDirect(), - SIMON_VJUMP);
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

	if (simon->isDeadth)
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
	LoadTexture::GetInstance()->LoadResource();
	sound = Sound::GetInstance();

	camera = SceneManager::GetInstance()->GetCamera();
	camera->SetPosition(0, 0);
	camera->SetBoundary(0, BOUNDARY_BEFORE_THROW_GATE_1); // biên camera khi chưa qua cửa
	camera->SetBoundaryBackup(0, 2561.0f); // biên camera khi chưa qua cửa

	if (simon == NULL)
		simon = new Simon(camera);

	if (gameTime == NULL)
		gameTime = new CGameTime();

	TileMap = new Map();
	TileMap->LoadMap(eMap::mMap2);

	board = new BoardGame(0, 0);

	simon->SetPosition(0, 300.0f);

	simon->SetPositionBackup(SIMON_POSITION_DEFAULT);

	addHitEffect = new HitEffect();
	gridGame = new Grid();

	listItem.clear();
	listEffect.clear();
	listEnemy.clear();

	//set time = 0
	gameTime->SetTime(0);

	// bắt đầu vào -> nhạc game
	sound->Play(eSound::smusicStage1, true);

	stateGame = 1;

	isFirstGhost = 0;
	CountEnemyGhost = 0;
	TimeCreateGhost = 0;
	isGenerateGhost = 0; // ban đầu vào thì bắt đầu tạo ghost
	//isExistGhost = 1;

	isProcessingGoThroughTheDoor1 = false; // ban đầu chưa cần xử lí qua cửa
	isDoneSimonGoThroughTheDoor1 = false;

	isProcessingGoThroughTheDoor2 = false; // ban đầu chưa cần xử lí qua cửa
	isDoneSimonGoThroughTheDoor2 = false;

	isGeneratePanther = true;
	CountEnemyPanther = 0;

	TimeCreateBat = 0;
	TimeWaitProcessCreateBat = 0;
	isGenerateBat = false;

	isAllowCreateFishmen = false;
	TimeCreateFishmen = 0;
	TimeWaitCreateFishmen = 0;
	CountEnemyFishmen = 0;
	listWeaponOfEnemy.clear();

	CountBoss = 0;
	isAllowProcessClearState3 = false;
	testa = 0;
	magicDown = 0;
	isProcessingGoThroughTheDoorBoss = 0;
	gameOver = 0;
	isDone = 0;

	optionHeart = new Load_resources(LoadTexture::GetInstance()->GetTexture(def_ID::BIGHEART), 100);
	optionSelect = OPTION_SELECT_CONTINUE;
}

void Scene_2::Update(DWORD dt)
{
	if (testa || gameOver) 
	{
		return;
	}
	//DebugOut(L"[INFO] cam_X: %f\n", camera->GetX_cam());
	if (camera->AllowFollowSimon())
	{
		camera->SetPosition(simon->x - Window_Width / 2 + 30, camera->GetY_cam()); // cho camera chạy theo simon
	}
	camera->Update(dt);

	if (simon->GetFreeze() == true)
	{
		simon->UpdateFreeze(dt);
		if (simon->GetFreeze() == true)
			return;
	}

	if (!isFirstGhost)
	{
		DWORD nowFisrtGhost = GetTickCount();
		
		if (nowFisrtGhost - FirstTimeGenGhost> 3000)
		{
			isFirstGhost = 1;
			isGenerateGhost = 1;
		}
	}

	ProcessingDoneStateBoss(dt);

	if (!isAllowProcessClearState3)
	{
		if (gameTime->GetTime() >= GAME_TIME_SCENE2 || simon->GetHP() <= 0)
		{
			if (simon->isDeadth)
			{
				
				simon->TimeWaitedAfterDeath += dt;
				if (simon->TimeWaitedAfterDeath >= 1500)
				{
					if (simon->GetLife() == 0)
					{
						DebugOut(L"VOer\n");
						gameOver = 1;
						return;
					}

					bool result = simon->LoseLife(); // đã khôi phục x,y
					simon->isDeadth = false;
					camera->RestorePosition(); // khôi phục vị trí camera;
					camera->RestoreBoundary(); // khôi phục biên camera

					if (result == true) // còn mạng để chơi tiếp, giảm mạng reset máu xong
					{
						ResetResource(); // reset lại game
					}

					/* Set Chờ hiển thị màn đen */
					//TimeWaitedResetGame = 0;
					//isWaitResetGame = true;

					return;
				}
			}
			else
			{
				sound->Play(eSound::smusicLose);
				simon->SetDeadth();
				simon->Update(dt, &listObj);
			}
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
	}

	ProcessingPassDoorState();

	gridGame->GetListObject(listObj, camera); // update các objec có life > 0 trong cam

	/* Create Ghost */
	GenerateGhost();
	
	/* Create Panther*/
	GeneratePanther();

	/* Create Bat*/
	GenerateBat();

	/* Create Fishmen*/
	GenerateFishmen();
	
	/* Create Boss*/
	GenerateBoss();

	listAllObj.clear();

	for (UINT i = 0; i < listObj.size(); i++)
	{
		listAllObj.push_back(listObj[i]);
	}

	for (UINT i = 0; i < listEnemy.size(); i++)
	{
		listAllObj.push_back(listEnemy[i]);
	}

	simon->Update(dt, &listAllObj);
	listEnemy.clear();

	for (UINT i = 0; i < listAllObj.size(); i++)
	{
		if (dynamic_cast<Ghost*>(listAllObj[i]) || dynamic_cast<Panther*>(listAllObj[i]) 
			|| dynamic_cast<Bat*>(listAllObj[i]) || dynamic_cast<Fishmen*>(listAllObj[i]) 
			|| dynamic_cast<Boss*>(listAllObj[i]))
		{
			listEnemy.push_back(listAllObj[i]);
		}
	}

	if (magicDown)
	{
		magicTime += dt;
		if (magicTime >= 2000)
		{
			magicTime = 0;
			listItem.push_back(new Items(def_ID::MAGICCRYSTAL, 5368.0f, 216.0f));
			magicDown = false;
		}
	}

	for (UINT i = 0; i < listObj.size(); i++)
	{
		listObj[i]->Update(dt, &listObj);
	}

	for (UINT i = 0; i < listItem.size(); i++) // update các Item
	{
		if (listItem[i]->GetFinish() == false)
			listItem[i]->Update(dt, &listObj);
		else listItem.erase(listItem.begin() + i);
	}

	for (UINT i = 0; i < listEffect.size(); i++)
	{
		if (listEffect[i]->GetFinish() == false)
			listEffect[i]->Update(dt);
		else listEffect.erase(listEffect.begin() + i);
	}

	for (UINT i = 0; i < listEnemy.size(); i++)
	{
		CGameObject * enemy = listEnemy[i];
		if (listEnemy[i]->GetLife() > 0) // còn máu
		{
			switch (enemy->GetType())
			{
			case def_ID::GHOST:
			{
				if (!camera->isObjectInCamera(
					enemy->x,
					enemy->y,
					(float)enemy->GetWidth(),
					(float)enemy->GetHeight()))  // vượt khỏi cam
				{
					enemy->setLife(0); // ra khỏi cam thì coi như chết
					if (dynamic_cast<Ghost*>(enemy) != NULL) // object này là ghost
					{
						CountEnemyGhost--; // giảm số lượng ghost hiện tại
						if (CountEnemyGhost == 0)
						{
							if (countGhostBorn >= 3)
							{
								TimeWaitProcessCreateGhost = GetTickCount(); // set thời điểm hiện tại
								isGenerateGhost = false;
								isExistGhost = false;
							}
						}
					}
				}
				else
					enemy->Update(dt, &listObj);
				break;
			}
			case def_ID::PANTHER:
			{
				Panther * objPanther = dynamic_cast<Panther *>(enemy);
				if (camera->isObjectInCamera(
					objPanther->x,
					objPanther->y,
					(float)objPanther->GetWidth(),
					(float)objPanther->GetHeight())) // nếu Panther nằm trong camera thì update
											  // vì do Grid load object nền (Brick) dựa vào vùng camera, nên có nguy cơ khiến 1 số object Panther không xét được va chạm đất.
				{
					objPanther->Update(dt, simon, &listObj);
				}
				else // nằm ngoài camera
				{
					if (objPanther->GetIsStart())// ngoài cam và đã được kích hoạt r
					{
						objPanther->setLife(0); // cho Panther chết
						CountEnemyPanther--;
					}
				}
				break;
			}
			case def_ID::BAT:
			{
				if (camera->isObjectInCamera(
					enemy->x,
					enemy->y,
					(float)enemy->GetWidth(),
					(float)enemy->GetHeight())) // nếu bat nằm trong camera thì update
				{
					enemy->Update(dt);
				}
				else
				{
					enemy->setLife(0); // ra khỏi cam coi như chết
				}
				break;
			}
			case def_ID::FISHMEN:
			{
				if (camera->isObjectInCamera(
					enemy->x,
					enemy->y,
					(float)enemy->GetWidth(),
					(float)enemy->GetHeight())) // nếu nằm trong camera thì update
				{
					Fishmen *fishmen = dynamic_cast<Fishmen*>(enemy);
					fishmen->UpdateCustom(dt, &listObj, simon);
				}
				else
				{
					enemy->setLife(0); // ra khỏi cam coi như chết
					CountEnemyFishmen--;
				}

				break;
			}
			case def_ID::BOSS:
			{
				Boss * objPanther = dynamic_cast<Boss *>(enemy);
				if (camera->isObjectInCamera(
					objPanther->x,
					objPanther->y,
					(float)objPanther->GetWidth(),
					(float)objPanther->GetHeight())) // nếu Panther nằm trong camera thì update
													 // vì do Grid load object nền (Brick) dựa vào vùng camera, nên có nguy cơ khiến 1 số object Panther không xét được va chạm đất.
				{
					objPanther->Update(dt, simon, &listObj);
				}
				else // nằm ngoài cameraF
				{
						objPanther->setLife(0); // cho Panther chết
						CountEnemyPanther--;
				}
				break;
			}
			default:
				break;
			}
		}
		else
		{
			listEnemy.erase(listEnemy.begin() + i);
		}
	}
	
	if (!simon->isDeadth)
	{
		CheckCollision();
		DropItem();
	}

	isAllowProcessClearState3 = Data::GetInstance()->passBoss;
	
}

void Scene_2::Render()
{
	if (gameOver)
	{
		option.Draw(200, 200, "GAME OVER");
		option.Draw(215, 250, "CONTINUE");
		option.Draw(215, 280, "END");
		switch (optionSelect)
		{
		case OPTION_SELECT_CONTINUE:
		{
			optionHeart->Draw(175, 245);
			break;
		}
		case OPTION_SELECT_END:
		{
			optionHeart->Draw(175, 275);
			break;
		}
		}
	}

	else
	{
		TileMap->DrawMap(camera);

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

		for (UINT i = 0; i < listEnemy.size(); i++)
		{
			listEnemy[i]->Render(camera);
		}

		/*for (UINT i = 0; i < listWeaponOfEnemy.size(); i++)
		listWeaponOfEnemy[i]->Render(camera);*/

		simon->Render(camera);
	}
	board->Render(simon, Data::GetInstance()->hpBoss, GAME_TIME_SCENE2 - gameTime->GetTime(), simon->subWeapon, stateGame);
}

void Scene_2::ResetResource()
{
	SAFE_DELETE(gridGame);
	gridGame = new Grid();

	listItem.clear();
	listEffect.clear();
	listEnemy.clear();

	CountEnemyGhost = 0;
	TimeCreateGhost = 0;
	isGenerateGhost = true; // lúc đầu thì không cần chờ

	gameTime->SetTime(0); // đếm lại từ 0
	sound->Stop(eSound::smusicStage1); // tắt nhạc nền
	sound->Play(eSound::smusicStage1, true); // mở lại nhạc nền

	isGeneratePanther = true;
	CountEnemyPanther = 0;

	isProcessingGoThroughTheDoor1 = false; // ban đầu chưa cần xử lí qua cửa
	isDoneSimonGoThroughTheDoor1 = false;

	isProcessingGoThroughTheDoor2 = false; // ban đầu chưa cần xử lí qua cửa
	isDoneSimonGoThroughTheDoor2 = false;

	TimeCreateBat = 0;
	TimeWaitProcessCreateBat = 0;
	isGenerateBat = false;

	isAllowCreateFishmen = false;
	TimeCreateFishmen = 0;
	TimeWaitCreateFishmen = 0;
	CountEnemyFishmen = 0;

	CountBoss = 0;
	simon->isDeadth = 0;
	

	camera->SetAllowFollowSimon(true);
}

void Scene_2::GenerateGhost()
{
	DWORD now = GetTickCount();

	if ((simon->x >= REGION_CREATE_GHOST_LEFT_1 && simon->x <= REGION_CREATE_GHOST_RIGHT_1) ||
		(simon->x >= REGION_CREATE_GHOST_LEFT_2 && simon->x <= REGION_CREATE_GHOST_RIGHT_2) ||
		(simon->x >= REGION_CREATE_GHOST_LEFT_3 && simon->x <= REGION_CREATE_GHOST_RIGHT_3))
	{
		if (isGenerateGhost)
		{
			if (now - TimeCreateGhost >= TIME_BETWEEN_GHOSTS_CREATE)
			{
				if (CountEnemyGhost < 3)
				{
					countGhostBorn++;
					if (stateGame != 3)
					{
						if (simon->vx > 0) // vx>0 đang chạy về bên phải
						{
							// cho ghost chạy từ bên phải qua
							listEnemy.push_back(new Ghost(camera->GetX_cam() + camera->GetWidth(), 310, -1));// 34 framewidth của ghost
						}
						else
							if (simon->vx < 0) // vx<0 đang chạy về bên trái
							{
								listEnemy.push_back(new Ghost(camera->GetX_cam() - 34, 310, 1));
							}
							else // đứng yên thì random
							{
								int random = rand() % 2;
								if (random == 0) // đi từ bên trái
								{
									listEnemy.push_back(new Ghost(camera->GetX_cam() - 34, 310, 1));
								}
								else // đi từ bên phải
								{
									listEnemy.push_back(new Ghost(camera->GetX_cam() + camera->GetWidth(), 310, -1));
								}
							}
					}
					else
					{
						int random = rand() % 2; // tỉ lệ 50%
						switch (random)
						{
						case 0:
						{
							if (simon->x <= REGION_CREATE_GHOST_TOP)
							{
								listEnemy.push_back(new Ghost(camera->GetX_cam() + camera->GetWidth(), 185, -1));
								break;
							}
							else
								if (REGION_CREATE_GHOST_BOTTOM <= simon->x)
								{
									listEnemy.push_back(new Ghost(camera->GetX_cam() - 34, 185, 1));
									break;
								}
						}
						case 1: 
						{
							if (simon->vx>0) 
								listEnemy.push_back(new Ghost(camera->GetX_cam() + camera->GetWidth(), 330, -1));
							else
								if (simon->vx < 0) 
									listEnemy.push_back(new Ghost(camera->GetX_cam() - 34, 330, 1)); 
								else
								{
									if (rand() % 2 == 0)
										listEnemy.push_back(new Ghost(camera->GetX_cam() + camera->GetWidth(), 330, -1));
									else
										listEnemy.push_back(new Ghost(camera->GetX_cam() - 34, 330, 1)); 
								}
							break;
						}
						}
					}
				}

				CountEnemyGhost++;
				if (countGhostBorn == 3) 
				{
					isGenerateGhost = false;
					isExistGhost = true;
				}
				TimeCreateGhost = now; 
			}
		}
		else
		{
			if (!isExistGhost && isFirstGhost)
			{
				if (now - TimeWaitProcessCreateGhost >= TIME_GHOST_REBORN) // đã chờ đủ
				{
					isGenerateGhost = true; // bắt đầu tạo lại ghost
					isExistGhost = true;
					countGhostBorn = 0; // reset count
				}
			}
		}
	}
}

void Scene_2::GeneratePanther()
{
	if (REGION_CREATE_PANTHER_LEFT < simon->x && simon->x < REGION_CREATE_PANTHER_RIGHT)
	{
		if (isGeneratePanther)
		{
			if (CountEnemyPanther == 0) // không còn Panther nào sống thì mới dc tạo lại cả 3
			{
				int nx_Panther_Before = simon->nx == 1 ? -1 : 1;
				for (UINT i = 0; i < 3; i++)
				{
					switch (i)
					{
					case 0:
						listEnemy.push_back(new Panther(1398.0f, 225.0f, nx_Panther_Before, nx_Panther_Before == -1 ? 20.0f : 9.0f));
						break;
					case 1:
						listEnemy.push_back(new Panther(1750.0f, 160.0f, nx_Panther_Before, nx_Panther_Before == -1 ? 278.0f : 10.0f, nx_Panther_Before == -1 ? 0 : 60.0f));
						break;
					case 2:
						listEnemy.push_back(new Panther(1923.0f, 225.0f, nx_Panther_Before, nx_Panther_Before == -1 ? 68.0f : 66.0f));
						break;
					}
					CountEnemyPanther++;
				}
			}

			isGeneratePanther = false;
		}
		//DebugOut(L"Panther in range= %d\n", CountEnemyPanther);
	}
	else
	{
		//DebugOut(L"Panther out range= %d\n", CountEnemyPanther);
		isGeneratePanther = true;
	}
}

void Scene_2::GenerateBat()
{
	if (isGenerateBat)
	{
		DWORD now = GetTickCount();

		if (now - TimeCreateBat >= TimeWaitProcessCreateBat) // đủ thời gian chờ
		{
			TimeCreateBat = now; // đặt lại thời gian đã tạo bat
			int bat_nx = -simon->nx;
			float pos = bat_nx == 1 ? camera->GetX_cam() : camera->GetX_cam() + camera->GetWidth() - 10;
			listEnemy.push_back(new Bat(pos, simon->y, bat_nx));
			TimeWaitProcessCreateBat = 6000 + (rand() % 4000);
		}
	}
}

void Scene_2::GenerateFishmen()
{
	if (isAllowCreateFishmen && CountEnemyFishmen < 2)
	{
		DWORD now = GetTickCount();
		if (now - TimeCreateFishmen >= TimeWaitCreateFishmen) // đủ thời gian chờ
		{
			TimeCreateFishmen = now; // đặt lại thời gian đã tạo

			float vtx = 0;

			if (FISHMEN_ZONE_1_LEFT < simon->x && simon->x <= FISHMEN_ZONE_1_RIGHT)
			{
				//vtx = (rand() % 2) ? (FISHMEN_POS_2) : ((rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4));
				vtx = (rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4);
			}

			if (FISHMEN_ZONE_2_LEFT < simon->x && simon->x <= FISHMEN_ZONE_2_RIGHT)
			{
				vtx = (rand() % 2) ? (FISHMEN_POS_1) : ((rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4)); // random fishmen generate 3 pos
			}

			if (FISHMEN_ZONE_3_LEFT < simon->x && simon->x <= FISHMEN_ZONE_3_RIGHT)
			{
				vtx = (rand() % 2) ? (FISHMEN_POS_4) : (FISHMEN_POS_5);
			}

			if (FISHMEN_ZONE_4_LEFT < simon->x && simon->x <= FISHMEN_ZONE_4_RIGHT)
			{
				vtx = (rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_5);
			}

			if (FISHMEN_ZONE_5_LEFT < simon->x && simon->x <= FISHMEN_ZONE_5_RIGHT)
			{
				vtx = (rand() % 2) ? (FISHMEN_POS_4) : (FISHMEN_POS_6);
			}

			if (FISHMEN_ZONE_6_LEFT < simon->x && simon->x <= FISHMEN_ZONE_6_RIGHT)
			{
				vtx = (rand() % 2) ? (FISHMEN_POS_5) : ((rand() % 2) ? (FISHMEN_POS_7) : (FISHMEN_POS_8));

			}

			if (FISHMEN_ZONE_7_LEFT < simon->x && simon->x <= FISHMEN_ZONE_7_RIGHT)
			{
				vtx = (rand() % 2) ? (FISHMEN_POS_6) : (FISHMEN_POS_8);

			}
			if (FISHMEN_ZONE_8_LEFT < simon->x && simon->x <= FISHMEN_ZONE_8_RIGHT)
			{
				vtx = (rand() % 2) ? (FISHMEN_POS_6) : (FISHMEN_POS_7);

			}
			int directionFishmen = vtx < simon->x ? 1 : -1;

			float vty = 805;
			listEnemy.push_back(new Fishmen(vtx, vty, directionFishmen));

			CountEnemyFishmen++;

			listEffect.push_back(new Water(vtx, vty, 1));
			listEffect.push_back(new Water(vtx, vty, 2));
			listEffect.push_back(new Water(vtx, vty, 3));
			//sound->Play(eSound::soundSplashwater);

			TimeWaitCreateFishmen = 2000 + (rand() % 2000);
		}
	}
}

void Scene_2::GenerateBoss()
{
	if (simon->x >= 5100)
	{
		if (CountBoss < 1)
		{
			listEnemy.push_back(new Boss(5295, 90, simon, camera));
			CountBoss++;
		}
	}
}

void Scene_2::ProcessingPassDoorState()
{
	if (isProcessingGoThroughTheDoor1)
	{
		if (isDoneSimonGoThroughTheDoor1 == false) // simon chưa hoàn thành việc qua cửa
		{
			if (camera->GetX_cam() >= CAMERA_AUTOGOX_BEFORE_DOOR_1) // camera đã AutoGo xong đến vị trí 2825.0f
			{
				{
					if (Data::GetInstance()->passGate)
					{
						simon->AutoGo(1, 1, abs(3143.0f - simon->x), SIMON_WALKING_SPEED);
						Data::GetInstance()->passGate = 0;
					}
				}
			}
			//DebugOut(L"[INFO] 3: \n");
		}
		else
		{
			if (camera->GetX_cam() >= CAMERA_AUTOGOX_AFTER_DOOR_1)
			{
				DebugOut(L"[INFO] 2: \n");
				camera->SetBoundary(CAMERA_AUTOGOX_AFTER_DOOR_1, camera->GetBoundaryRight());
				camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight());
				camera->SetAllowFollowSimon(true);
				isProcessingGoThroughTheDoor1 = false; // xong việc xử lí qua cửa 1
				camera->StopAutoGoX(); // cam autogo done
			}
		}
	}

	if (isProcessingGoThroughTheDoor2) // simon chạm cửa thì bắt đầu xử lí
	{
		if (isDoneSimonGoThroughTheDoor2 == false) // simon chưa hoàn thành việc qua cửa
		{
			if (camera->GetX_cam() >= GATE2_POSITION_CAM_BEFORE_GO)
			{

				if (Data::GetInstance()->passGate)
				{
					simon->AutoGo(1, 1, abs(GATE2_POSITION_CAM_AFTER_GO + DISTANCE_AUTO_WALK_AFTER_GATE - simon->x), SIMON_WALKING_SPEED); // bắt đầu cho simon di chuyển tự động đến vị trí tiếp theo
					Data::GetInstance()->passGate = 0;
				}
			}
		}
		else
		{
			if (camera->GetX_cam() >= GATE2_POSITION_CAM_AFTER_GO)
			{
				camera->SetBoundary(GATE2_POSITION_CAM_AFTER_GO, camera->GetBoundaryRight());
				camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight());
				camera->SetAllowFollowSimon(true);
				isProcessingGoThroughTheDoor2 = false; // xong việc xử lí qua cửa 2
				camera->StopAutoGoX(); // dừng việc tự di chuyển
			}
		}
	}

}

void Scene_2::ProcessingDoneStateBoss(DWORD dt)
{
	if (isAllowProcessClearState3)
	{
		if (!isProcessingGoThroughTheDoorBoss)
			simon->Stop();
		switch (StatusProcessClearState3)
		{
		case CLEARSTATE3_PROCESS_HEALTH:
		{
			TimeWaited_ClearState3 += dt;
			if (TimeWaited_ClearState3 >= CLEARSTATE3_LIMITTIMEWAIT_PROCESS_HEALTH)
			{
				TimeWaited_ClearState3 = 0;

				if (simon->GetHP() < 16)
				{
					simon->SetHP(simon->GetHP() + 1);
				}
				else
				{
					StatusProcessClearState3 = CLEARSTATE3_PROCESS_GETSCORE_TIME;
				}
			}
			break;
		}
		case CLEARSTATE3_PROCESS_GETSCORE_TIME:
		{
			TimeWaited_ClearState3 += dt;
			if (TimeWaited_ClearState3 >= CLEARSTATE3_LIMITTIMEWAIT_PROCESS_GETSCORE_TIME)
			{
				TimeWaited_ClearState3 = 0;

				if (GAME_TIME_SCENE2 - gameTime->GetTime() > 0) // thời gian còn lại lớn hơn 0
				{
					simon->SetPoint(simon->GetPoint() + 10); // mỗi giây +10 điểm
					gameTime->SetTime(gameTime->GetTime() + 1);// giảm giây còn lại
				}
				else
				{
					StatusProcessClearState3 = CLEARSTATE3_PROCESS_GETSCORE_HEART;
					TimeWaited_ClearState3 = 0;
				}
			}
			break;
		}
		case CLEARSTATE3_PROCESS_GETSCORE_HEART:
		{
			TimeWaited_ClearState3 += dt;
			if (TimeWaited_ClearState3 >= CLEARSTATE3_LIMITTIMEWAIT_PROCESS_GETSCORE_HEART)
			{
				TimeWaited_ClearState3 = 0;

				if (simon->GetHeartCollect() > 0) // hear > 0
				{
					simon->SetPoint(simon->GetPoint() + 100); // mỗi heart +100 điểm
					simon->SetHeartCollect(simon->GetHeartCollect() - 1); // giảm 1 heart
				}
				else
				{
					StatusProcessClearState3 = CLEARSTATE3_PROCESS_DONE;
				}
			}

			break;
		}
		case CLEARSTATE3_PROCESS_DONE:
		{
			isProcessingGoThroughTheDoorBoss = 1;
			isDone = 1;
			break;
		}
		default:
			break;
		}
	}
}

void Scene_2::CheckCollision()
{
	simon->CollisionWithItem(&listItem);
	CheckCollisionSimonWithHidenObject();
	CheckCollisionSimonWithGate();
}

void Scene_2::DropItem()
{
	if (isDone)
		return;

	if (!simon->mainWeapon->GetFinish() || (simon->subWeapon != NULL && !simon->subWeapon->GetFinish()))
	{
		for (UINT i = 0; i < listAllObj.size(); i++)
		{
			CGameObject *gameObj = listAllObj[i];

			if (gameObj->GetLife() <= 0 && !gameObj->GetIsDrop())
			{
				switch (gameObj->GetType())
				{
				case def_ID::SMALLCANDLE:
				{
					gameObj->SetIsDrop(1);
					listItem.push_back(GetRandomItem(gameObj->GetObj_id(), def_ID::SMALLCANDLE, gameObj->x, gameObj->y));
					sound->Play(eSound::sHit); 
					addHitEffect->AddHitEffect(&listEffect, gameObj->x, gameObj->y + 10, gameObj->x - 5, gameObj->y + 8);
					break;
				}
				case def_ID::BRICK:
				{
					switch (gameObj->GetObj_id())
						{
						case 39:
						{
							gameObj->LoseLife(1);
							break;
						}
						case 40: 
						{
							gameObj->LoseLife(1);
							listItem.push_back(GetRandomItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x, gameObj->y));
							break;
						}
						case 51:
						{
							gameObj->LoseLife(1);
							break;
						}
						case 72:
						{
							gameObj->LoseLife(1);
							sound->Play(eSound::sMonneyBag);
							listItem.push_back(GetRandomItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x, gameObj->y));
						
							break;
						}
						default:
							break;
					}
					addHitEffect->AddBrickSplash(&listEffect, (float)gameObj->x + 14, (float)gameObj->y + 14);
				}
				case def_ID::GHOST:
				{
					gameObj->SetIsDrop(1);

					if (rand() % 2 == 1) // tỉ lệ 50%
					{
						listItem.push_back(GetRandomItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));
					}

					sound->Play(eSound::sHit); // sound đánh trúng obj

					CountEnemyGhost--; // giảm số lượng Ghost đang hoạt động
					if (CountEnemyGhost == 0)
					{
						if (countGhostBorn >= 3)
						{
							TimeWaitProcessCreateGhost = GetTickCount(); // set thời điểm hiện tại
							isGenerateGhost = false;
							isExistGhost = false;
						}
					}
					break;
				}
				case def_ID::PANTHER:
				{
					gameObj->SetIsDrop(1);
					simon->SetPoint(simon->GetPoint() + 200);

					if (rand() % 2 == 1) // tỉ lệ 50%
					{
						listItem.push_back(GetRandomItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));
					}

					sound->Play(eSound::sHit); // sound đánh trúng obj
					CountEnemyPanther--; // giảm số lượng Ghost đang hoạt động

					break;
				}
				case def_ID::BAT:
				{
					gameObj->SetIsDrop(1);
					simon->SetPoint(simon->GetPoint() + 200);
					if (rand() % 2 == 1) // tỉ lệ 50%
					{
						listItem.push_back(GetRandomItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));
					}

					sound->Play(eSound::sHit); // sound đánh trúng obj

					CountEnemyGhost--; // giảm số lượng Ghost đang hoạt động
					if (CountEnemyGhost == 0)
					{
						TimeWaitProcessCreateGhost = GetTickCount(); // set thời điểm hiện tại											
					}
					break;
				}
				case def_ID::FISHMEN:
				{
					gameObj->SetIsDrop(1);
					simon->SetPoint(simon->GetPoint() + 200);
					if (rand() % 2 == 1) // tỉ lệ 50% 
						listItem.push_back(GetRandomItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));

					//RunEffectHit = true;
					sound->Play(eSound::sHit); // sound đánh trúng obj
					listEffect.push_back(new Hit((int)(listAllObj[i]->x), (int)(listAllObj[i]->y + 10))); // hiệu ứng lửa
					listEffect.push_back(new Effect((int)(listAllObj[i]->x - 5), (int)(listAllObj[i]->y + 8))); // hiệu ứng lửa
					CountEnemyFishmen--; // giảm số lượng Fishmen đang hoạt động

					break;
				}
				case def_ID::BOSS:
				{
					gameObj->SetIsDrop(1);
					//simon->SetPoint(simon->GetPoint() + 200);

					for (int row = 0; row < 2; row++)
					{
						for (int column = 0; column < 3; column++)
						{
							listEffect.push_back(new Effect((int)(listAllObj[i]->x + column * 24), (int)(listAllObj[i]->y + row * 24 + 10), 2));
						}
					}

					magicDown = 1;
					sound->Play(eSound::sHit); // sound đánh trúng obj

					break;
				}
				default:
					break;
				}

				if(gameObj->GetType() != def_ID::BRICK || gameObj->GetType() != def_ID::BOSS)
					addHitEffect->AddHitEffect(&listEffect, gameObj->x, gameObj->y + 10, gameObj->x - 5, gameObj->y + 8);

				if (simon->subWeapon != NULL && !simon->subWeapon->GetFinish())
				{
					if (simon->subWeapon->GetType() != def_ID::HOLYWATER && simon->subWeapon->GetType() != def_ID::AXE)
						simon->subWeapon->SetFinish(true);
				}
			}
		}
	}
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
				if (simon->isCollitionAll(hidenObject))
				{
					switch (hidenObject->GetObj_id())
					{
						case eHidden::PASSINGDOOR1:
						{
							if (isProcessingGoThroughTheDoor1)
							{
								Sound::GetInstance()->Play(eSound::sOpenDoor);
								isDoneSimonGoThroughTheDoor1 = true;
								camera->AutoGo(abs(CAMERA_AUTOGOX_AFTER_DOOR_1 - camera->GetX_cam()), 0.09f);
								simon->SetPositionBackup(simon->x, 0); 
							}

							TimeCreateBat = GetTickCount();
							TimeWaitProcessCreateBat = 3000;
							isGenerateBat = true;
							stateGame = 2;
							camera->SetPositionBackup(camera->GetX_cam(), camera->GetY_cam());
							hidenObject->LoseLife(1);
							break;
						}
						case eHidden::PASSINGDOOR2: 
						{
							if (isProcessingGoThroughTheDoor2)
							{
								isDoneSimonGoThroughTheDoor2 = true;
								camera->AutoGo(abs(GATE2_POSITION_CAM_AFTER_GO - camera->GetX_cam()), 0.09f);
								simon->SetPositionBackup(simon->x, 0); 
							}
							stateGame = 3;
							camera->SetPositionBackup(camera->GetX_cam(), camera->GetY_cam());
							hidenObject->LoseLife(1);
							break;
						}
						case eHidden::WATERDOWNLEFT: // id 41: object ẩn -> xuống hồ nước
						{
							camera->SetPosition(camera->GetX_cam(), 384-10);
							camera->SetBoundary(CAMERA_BOUNDARY_LAKE_LEFT, CAMERA_BOUNDARY_LAKE_RIGHT);
							simon->SetPosition(3170, 430);
							isGenerateBat = false; 
							isAllowCreateFishmen = true;
							hidenObject->setLife(0);
							gridGame->pushToCell(GRID_INSERT_OBJECT__DIRAKHOIHONUOC_LEFT);
							break;
						}
						case eHidden::WATERUPLEFT:
						{
							camera->SetPosition(camera->GetX_cam(), 0);
							simon->SetPosition(3155, 348);
							isGenerateBat = true;  
							//TimeWaitProcessingCreateBat = 3000 + rand() % 1000;
							hidenObject->setLife(0);
							gridGame->pushToCell(GRID_INSERT_OBJECT__DIXUONGHONUOC_LEFT);
							break;
						}
						case eHidden::BONUS: 
						{
							sound->Play(eSound::sMonneyBag);
							listItem.push_back(GetRandomItem(hidenObject->GetObj_id(), hidenObject->GetType(), simon->x, simon->y));

							break;
						}
						case eHidden::WATERFISHMEN: 
						{
							simon->SetHP(0);
							sound->Play(eSound::sMonneyBag);
							break;
						}
						case eHidden::WATERDOWNRIGHT: 
						{
							camera->SetPosition(camera->GetX_cam(), 0);
							simon->SetPosition(3806, 361);
							isGenerateBat = true;
							isAllowCreateFishmen = false;
							TimeWaitProcessCreateBat = 3000 + rand() % 1000;
							hidenObject->setLife(0);
							gridGame->pushToCell(GRID_INSERT_OBJECT__DIXUONGHONUOC_RIGHT);

							break;
						}
						case eHidden::WATERUPRIGHT: 
						{
							camera->SetPosition(camera->GetX_cam(), CAMERA_POSITION_Y_LAKE);
							simon->SetPosition(3825, 442);
							isGenerateBat = false;  
							isAllowCreateFishmen = true;
							hidenObject->setLife(0);

							gridGame->pushToCell(GRID_INSERT_OBJECT__DIRAKHOIHONUOC_RIGHT); 

							break;
						}
						case eHidden::BOSSAPPEAR:
						{
							for (UINT i = 0; i < listEnemy.size(); i++)
							{
								CGameObject * enemy = listEnemy[i];
								if (enemy->GetType() != def_ID::BOSS)
								{
									enemy->setLife(0);
								}
							}

							Data::GetInstance()->bossAppear = 1;
							camera->SetBoundary(camera->GetBoundaryRight(), camera->GetBoundaryRight());
							camera->SetAllowFollowSimon(false);
							hidenObject->setLife(0);

							break;
						}
					}
				}
			}
		}
	}
}

void Scene_2::CheckCollisionSimonWithGate()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == def_ID::GATE)
		{
			if (simon->isCollitionAll(listObj[i]))
			{
				Gate* objGate = dynamic_cast<Gate*>(listObj[i]);
				switch (objGate->GetObj_id())
				{
				case 64:
				{
					if (objGate->GetStart() == 0)
					{
						//di chuyển camera đến ViTriCameraDiChuyenTruocKhiQuaCua = 2825.0f
						camera->SetBoundary(camera->GetBoundaryLeft(), camera->GetBoundaryRight() + 1164);// mở biên phải rộng ra thêm để chạy AutoGo
						camera->AutoGo(abs(CAMERA_AUTOGOX_BEFORE_DOOR_1 - camera->GetX_cam()), SIMON_WALKING_SPEED);
						simon->Stop(); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()

						objGate->Open();

						isProcessingGoThroughTheDoor1 = true; // bật trạng thái xử lí qua cửa
						isDoneSimonGoThroughTheDoor1 = false;
						break;
					}
					break;
				}
				case 93: // gate 2
				{
					for (UINT i = 0; i < listEnemy.size(); i++)
					{
						CGameObject * enemy = listEnemy[i];
						enemy->setLife(0);
					}

					if (objGate->GetStart() == 0)
					{
						camera->SetBoundary(camera->GetBoundaryLeft(), CAMERA_BOUNDARY_BOSS_RIGHT);// mở biên phải rộng ra thêm để chạy AutoGo
						camera->AutoGo(abs(GATE2_POSITION_CAM_BEFORE_GO - camera->GetX_cam()), SIMON_WALKING_SPEED);
						simon->SetSpeed(0, simon->vy); // cho simon dừng, tránh trường hợp không vào được trạng thái stop trong KeyState()
						simon->Stop();
						if (simon->isSitting == true) // nếu simon đang ngồi
						{
							simon->isSitting = 0; // hủy trạng thái ngồi
							//simon->set(simon->GetY() - PULL_UP_SIMON_AFTER_SITTING); // kéo simon lên
						}
						objGate->Open();
						isProcessingGoThroughTheDoor2 = true; // bật trạng thái xử lí qua cửa
						isDoneSimonGoThroughTheDoor2 = false;
						isGenerateBat = 0;

						break;
					}
					break;
				}
				case 105:
				{
					if (isProcessingGoThroughTheDoorBoss)
					{
						testa = 1;
						sound->Stop(eSound::smusicStage1);
						SceneManager::GetInstance()->SetScene(new GameEnd());
					}

					break;
				}
				}
			}
		}
	}
}

Items * Scene_2::GetRandomItem(int _id, def_ID Type, float X, float Y)
{
	if (Type == def_ID::SMALLCANDLE)
	{
		switch (_id)
		{
		case 71:
			if (simon->subWeapon != NULL && simon->subWeapon->GetType() != def_ID::HOLYWATER || simon->subWeapon == NULL)
				return new Items(def_ID::iHOLYWATER, X, Y);
			break;
		case 113:
			return new Items(def_ID::iAXE, X, Y);
			break;
		default:
			return new Items(def_ID::SMALLHEART, X, Y);
			break;
		}
	}

	if (Type == def_ID::GHOST || Type == def_ID::PANTHER || Type == def_ID::BAT)
	{
		int random = rand() % 10;
		switch (random)
		{
		case 0:
			return new Items(def_ID::BIGHEART, X, Y);
			break;
		case 1:
			return new Items(def_ID::SMALLHEART, X, Y);
			break;
		case 2:
			if (simon->subWeapon != NULL && simon->subWeapon->GetType() != def_ID::DAGGER || simon->subWeapon == NULL)
				return new Items(def_ID::iDAGGER, X, Y);
			break;
		case 3:
			return new Items(def_ID::MONNEYBAG, X, Y);
			break;
		case 4:
			if (simon->mainWeapon->GetLevel() < 2)
				return new Items(def_ID::MORNINGSTAR, X, Y);
			break;
		case 5:
			if (simon->subWeapon != NULL && simon->subWeapon->GetType() != def_ID::HOLYWATER || simon->subWeapon == NULL)
				return new Items(def_ID::iHOLYWATER, X, Y);
			break;
		default:
			return new Items(def_ID::SMALLHEART, X, Y);
			break;
		}
	}

	if (Type == def_ID::BRICK)
	{
		switch (_id)
		{
		case 40:
			return new Items(def_ID::POTROAST, X, Y);
			break;
		case 72:
			return new Items(def_ID::MONNEYBAG, X, Y);
			break;
		default:
			break;
		}
	}

	if (Type == def_ID::HIDDENOBJECT)
	{
		if (_id == 65)
			return new Items(def_ID::MONNEYBAG, 3763.0f, 587.0f);
	}

	return new Items(def_ID::BIGHEART, X, Y);
}