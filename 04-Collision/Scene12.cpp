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
	SAFE_DELETE(TileMap);
	SAFE_DELETE(board);
	SAFE_DELETE(gridGame);
	SAFE_DELETE(simon);
}

void Scene_2::KeyState(BYTE * state)
{
	if (simon->GetFreeze()) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

	if (simon->isDeadth || gameOver)
	{
		return;
	}

	if (camera->GetIsAutoGoX()) // camera đang chế độ tự đi thì ko xét phím
		return;

	if (simon->isAutoGoX == true) // đang chế độ tự đi thì ko xét phím
		return;

	if (simon->isAutoGo == true) // đang chế độ tự đi thì ko xét phím
		return;

	if (simon->isJumping)
		return;

	if (simon->isEnemyHit)
		return;

	if (simon->isAttacking) // đang attack
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
					if (simon->isCollitionAll(listObj[i])) // nếu va chạm với STAIR BOTOM
					{
						CGameObject* hidenObj = dynamic_cast<CGameObject*>(listObj[i]);

						simon->nx_stair = listObj[i]->GetDirect();
						simon->SetDirect(simon->nx_stair);
						simon->isOnStair = 1;
						simon->HeightStair = 0;
						simon->isStairUp = 1;
						//DebugOut(L"distance %f\n", abs(hidenObj->x - simon->x));
						if (simon->x < hidenObj->x)
						{
							simon->AutoGo(1, hidenObj->GetDirect(), hidenObj->x - simon->x, SIMON_WALKING_SPEED);
						}
						else
							simon->AutoGo(-1, hidenObj->GetDirect(), simon->x - hidenObj->x, SIMON_WALKING_SPEED);

						DebugOut(L"Collision stair\n");
						return;
					}
				}
			}
		}
		else
		{
			if (simon->isProcessingOnStair == 0 || simon->isProcessingOnStair == 3)
			{
				//DebugOut(L"processing in 0: = %d\n", simon->isProcessingOnStair);
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
						if (simon->isCollitionAll(listObj[i])) // nếu va chạm với STAIR TOP
						{
							CGameObject* hidenObj = dynamic_cast<CGameObject*>(listObj[i]);
							simon->nx_stair = hidenObj->GetDirect(); // lưu hướng của cầu thang đang đi vào simon
							simon->SetDirect(simon->nx_stair);// hướng của simon khi đi xuống là hướng của cầu thang
							simon->isStairUp = -1;// hướng đi xuống

							simon->isOnStair = true; // set trạng thái đang trên cầu thang
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

				if (checkCollision == 0) // ko đụng stair top, tức là ngồi bt
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
				if (simon->isProcessingOnStair == 0 || simon->isProcessingOnStair == 3) // kết thúc xử lí trước đó
				{
					simon->isWalking = true;
					simon->isProcessingOnStair = 1;
					simon->isStairUp = -1;// hướng đi xuống
					simon->HeightStair = 0;
					simon->SetDirect(-simon->nx_stair);// hướng của simon khi đi xuóng là ngược của cầu thang
					simon->SetSpeed(simon->GetDirect() * SIMON_SPEED_ONSTAIR, SIMON_SPEED_ONSTAIR);
				}
			}
		}
		else // ko nhấn phím xuống
		{
			simon->Stop();
		}
	}

	/*if (simon->isJumping)
		return;*/

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
		simon->subWeapon = new HolyWater();
	}

	if (KeyCode == DIK_F) // create hollywater
	{
		simon->SetHP(16);
		simon->setLife(9999);
		simon->SetHeartCollect(9999);
		gameTime->SetTime(0);
		simon->subWeapon = new HolyWater();
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

	if (simon == NULL)
		simon = new Simon();

	if (gameTime == NULL)
		gameTime = new CGameTime();

	TileMap = new Map();
	TileMap->LoadMap(eMap::mMap2);

	camera = SceneManager::GetInstance()->GetCamera();
	camera->SetPosition(0, 0);
	camera->SetBoundary(0, BOUNDARY_BEFORE_THROW_GATE_1); // biên camera khi chưa qua cửa
	camera->SetBoundaryBackup(0, 2561.0f); // biên camera khi chưa qua cửa

	board = new BoardGame(0, 0);

	//simon = new Simon();
	simon->SetPosition(0, 300.0f);

	simon->SetPositionBackup(SIMON_POSITION_DEFAULT);

	gridGame = new Grid();

	listItem.clear();
	listEffect.clear();
	listEnemy.clear();

	//set time = 0
	gameTime->SetTime(0);

	// bắt đầu vào -> nhạc game
	sound->Play(eSound::smusicStage1, true);

	stateGame = 1;

	CountEnemyGhost = 0;
	TimeCreateGhost = 0;
	isGenerateGhost = true; // ban đầu vào thì bắt đầu tạo ghost
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

	// nếu đang trong state freeze => k update simon
	if (simon->GetFreeze() == true)
	{
		simon->UpdateFreeze(dt);
		if (simon->GetFreeze() == true)
			return;
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

	simon->Update(dt, &listObj);

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

	if (magicDown)
	{
		magicTime += dt;
		if (magicTime >= 2000)
		{
			magicTime = 0;
			listItem.push_back(new MagicCrystal(5368, 216));
			magicDown = false;
		}
	}

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
	}

	if (!simon->isDeadth)
		CheckCollision();
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
						case 0: // ở trên
						{
							if (simon->x <= REGION_CREATE_GHOST_TOP)
							{
								listEnemy.push_back(new Ghost(camera->GetX_cam() + camera->GetWidth(), 185, -1));// bên phải chạy qua trái
								break;
							}
							else
								if (REGION_CREATE_GHOST_BOTTOM <= simon->x)
								{
									listEnemy.push_back(new Ghost(camera->GetX_cam() - 34, 185, 1));// bên trái qua phải
									break;
								}
						}
						case 1: // ở dưới
						{
							if (simon->vx>0) // đang chạy về bên phải
								listEnemy.push_back(new Ghost(camera->GetX_cam() + camera->GetWidth(), 330, -1));// bên phải chạy qua trái
							else
								if (simon->vx < 0) // đang chạy bên trái 
									listEnemy.push_back(new Ghost(camera->GetX_cam() - 34, 330, 1)); // đi từ trái qua phải
								else
								{
									if (rand() % 2 == 0)
										listEnemy.push_back(new Ghost(camera->GetX_cam() + camera->GetWidth(), 330, -1));// bên phải chạy qua trái
									else
										listEnemy.push_back(new Ghost(camera->GetX_cam() - 34, 330, 1)); // đi từ trái qua phải 
								}
							break;
						}
						}
					}
				}

				CountEnemyGhost++;
				if (countGhostBorn == 3) // ghost ra 3 con thì dừng
				{
					isGenerateGhost = false; // Đủ 3 ghost đang sống thì dừng tạo
					isExistGhost = true;
				}
				TimeCreateGhost = now; // set lại thời điểm đã tạo ghost
			}
		}
		else
		{
			if (!isExistGhost)
			{
				//DebugOut(L"[INFO] Het ghost: \n");
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
		//DebugOut(L"[INFO]Panther was created \n");
		if (isGeneratePanther)
		{
			if (CountEnemyPanther == 0) // không còn Panther nào sống thì mới dc tạo lại cả 3
			{
				//int nx_Panther_Before = abs(REGION_CREATE_PANTHER_LEFT - simon->x) < abs(REGION_CREATE_PANTHER_RIGHT - simon->x) ? -1 : 1; // hướng mặt của Panther quay về hướng simon
				//DebugOut(L"[INFO]nx_pan: %d\n", trendPanther);
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
	}
	else
	{
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
			listEnemy.push_back(new Bat(pos, simon->y + 40, bat_nx));
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
					//sound->Play(eSound::SoundGetScoreTimer, true);
				}
				else
				{
					StatusProcessClearState3 = CLEARSTATE3_PROCESS_GETSCORE_HEART;
					TimeWaited_ClearState3 = 0;
					//sound->Stop(eSound::SoundGetScoreTimer);
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
					//sound->Play(eSound::SoundGetScoreHeart, true);
				}
				else
				{
					//sound->Stop(eSound::SoundGetScoreHeart);
					StatusProcessClearState3 = CLEARSTATE3_PROCESS_DONE;
				}
			}

			break;
		}
		case CLEARSTATE3_PROCESS_DONE:
		{
			isProcessingGoThroughTheDoorBoss = 1;
			break;
		}
		default:
			break;
		}
	}
}

void Scene_2::CheckCollision()
{
	CheckCollisionWeapon(listObj);
	CheckCollisionSimonWithItem();
	CheckCollisionSimonWithHidenObject();
	CheckCollisionSimonWithGate();
	CheckCollisionWithEnemy(); 
	CheckCollisionSimonWithEnemy();
}

void Scene_2::CheckCollisionWeapon(vector<LPGAMEOBJECT> listObj)
{
	if (listObj.size() == 0)
		return;

	if (!simon->mainWeapon->GetFinish()) // Vũ khí đang hoạt động
	{
		//DebugOut(L"Layer 1\n");
		for (UINT i = 0; i < listObj.size(); i++)
		{
			if (!simon->mainWeapon->GetSend())
				listObj[i]->SetReceive(0);
			//DebugOut(L"Layer 2\n");
			if (simon->mainWeapon->isCollision(listObj[i]))
			{
				
				CGameObject *gameObj = listObj[i];

				if (gameObj->GetReceive() && simon->mainWeapon->GetSend()) return;
				DebugOut(L"Layer ====>3 %d ,  index: %d\n", gameObj->GetType(), i);
				switch (gameObj->GetType())
				{
					case def_ID::SMALLCANDLE:
					{
						//CGameObject *candle = dynamic_cast<CGameObject*>(listObj[i]);
						gameObj->LoseLife(1);
						listItem.push_back(GetNewItem(gameObj->GetObj_id(), def_ID::SMALLCANDLE, gameObj->x, gameObj->y));
						sound->Play(eSound::sHit); // sound đánh trúng obj
						listEffect.push_back(new Hit((int)(listObj[i]->x), (int)(listObj[i]->y + 10))); // hiệu ứng lửa
						listEffect.push_back(new Effect((int)(listObj[i]->x - 5), (int)(listObj[i]->y + 8))); // hiệu ứng lửa
						break;
					}
					case def_ID::GHOST:
					{
						//CGameObject *ghost = dynamic_cast<CGameObject*>(listObj[i]);
						gameObj->LoseLife(1);
						
						if (rand() % 2 == 1) // tỉ lệ 50%
						{
							listItem.push_back(GetNewItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));
						}

						sound->Play(eSound::sHit); // sound đánh trúng obj
						listEffect.push_back(new Hit((int)(listObj[i]->x), (int)(listObj[i]->y + 10))); // hiệu ứng lửa
						listEffect.push_back(new Effect((int)(listObj[i]->x - 5), (int)(listObj[i]->y + 8))); // hiệu ứng lửa

						//RunEffectHit = true;
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
						//CGameObject *panther = dynamic_cast<CGameObject*>(listObj[i]);
						gameObj->LoseLife(1);
						simon->SetPoint(simon->GetPoint() + 200);

						if (rand() % 2 == 1) // tỉ lệ 50%
						{
							listItem.push_back(GetNewItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));
						}

						sound->Play(eSound::sHit); // sound đánh trúng obj
						listEffect.push_back(new Hit((int)(listObj[i]->x), (int)(listObj[i]->y + 10))); // hiệu ứng lửa
						listEffect.push_back(new Effect((int)(listObj[i]->x - 5), (int)(listObj[i]->y + 8))); // hiệu ứng lửa
						//RunEffectHit = true;
						CountEnemyPanther--; // giảm số lượng Ghost đang hoạt động
					
						break;
					}
					case def_ID::BAT:
					{
						//CGameObject *bat = dynamic_cast<CGameObject*>(listObj[i]);
						gameObj->LoseLife(1);
						simon->SetPoint(simon->GetPoint() + 200);
						if (rand() % 2 == 1) // tỉ lệ 50%
						{
							listItem.push_back(GetNewItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));
						}

						sound->Play(eSound::sHit); // sound đánh trúng obj
						listEffect.push_back(new Hit((int)(listObj[i]->x), (int)(listObj[i]->y + 10))); // hiệu ứng lửa
						listEffect.push_back(new Effect((int)(listObj[i]->x - 5), (int)(listObj[i]->y + 8))); // hiệu ứng lửa

						CountEnemyGhost--; // giảm số lượng Ghost đang hoạt động
						if (CountEnemyGhost == 0)
						{
							TimeWaitProcessCreateGhost = GetTickCount(); // set thời điểm hiện tại
							//isWaitProcessCreateGhost = true;
							//isAllowCheckTimeWaitProcessCreateGhost = true;
						}
						break;
					}
					case def_ID::FISHMEN:
					{
						gameObj->LoseLife(1);
						simon->SetPoint(simon->GetPoint() + 200);
						if (rand() % 2 == 1) // tỉ lệ 50% 
							listItem.push_back(GetNewItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));

						//RunEffectHit = true;
						sound->Play(eSound::sHit); // sound đánh trúng obj
						listEffect.push_back(new Hit((int)(listObj[i]->x), (int)(listObj[i]->y + 10))); // hiệu ứng lửa
						listEffect.push_back(new Effect((int)(listObj[i]->x - 5), (int)(listObj[i]->y + 8))); // hiệu ứng lửa
						CountEnemyFishmen--; // giảm số lượng Fishmen đang hoạt động

						break;
					}
					case def_ID::BOSS:
					{
						DebugOut(L"Dmg boss\n");
						gameObj->LoseHP(2);
						Data::GetInstance()->hpBoss -= 2;
						//simon->SetPoint(simon->GetPoint() + 200);
						
						if (gameObj->GetHP() == 0)
						{
							gameObj->setLife(0);
							for (int row = 0; row < 2; row++)
							{
								for (int column = 0; column < 3; column++)
								{
									listEffect.push_back(new Effect((int)(listObj[i]->x + column * 24), (int)(listObj[i]->y + row * 24 + 10), 2));
								}
							}

							magicDown = 1;
						}

						sound->Play(eSound::sHit); // sound đánh trúng obj

						break;
					}
					default:
						break;
				}
				gameObj->SetReceive(1);
				simon->mainWeapon->SetSend(1);
			}
		}
	}

	if (simon->subWeapon != NULL && simon->subWeapon->GetFinish() == false)
	{
		for (UINT i = 0; i < listObj.size(); i++)
		{
			if (simon->subWeapon->isCollision(listObj[i]))
			{
				bool runHitEffect = false;
				CGameObject *gameObj = listObj[i];
				switch (gameObj->GetType())
				{
				case def_ID::SMALLCANDLE:
				{
					//CGameObject *candle = dynamic_cast<CGameObject*>(listObj[i]);
					gameObj->LoseLife(1);
					
					listItem.push_back(GetNewItem(gameObj->GetObj_id(), def_ID::SMALLCANDLE, gameObj->x, gameObj->y));
					runHitEffect = true;
					break;
				}
				case def_ID::GHOST:
				{
					//CGameObject *ghost = dynamic_cast<CGameObject*>(listObj[i]);
					gameObj->LoseLife(1);

					if (rand() % 2 == 1) // tỉ lệ 50%
					{
						listItem.push_back(GetNewItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));
					}

					runHitEffect = true;
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
					//CGameObject *panther = dynamic_cast<CGameObject*>(listObj[i]);
					gameObj->LoseLife(1);
					simon->SetPoint(simon->GetPoint() + 200);

					if (rand() % 2 == 1) // tỉ lệ 50%
					{
						listItem.push_back(GetNewItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));
					}

					runHitEffect = true;
					CountEnemyPanther--; // giảm số lượng Ghost đang hoạt động

					break;
				}
				case def_ID::BAT:
				{
					//CGameObject *bat = dynamic_cast<CGameObject*>(listObj[i]);
					gameObj->LoseLife(1);
					simon->SetPoint(simon->GetPoint() + 200);
					if (rand() % 2 == 1) // tỉ lệ 50%
					{
						listItem.push_back(GetNewItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));
					}

					runHitEffect = true;

					break;
				}
				case def_ID::FISHMEN:
				{
					gameObj->LoseLife(1);
					simon->SetPoint(simon->GetPoint() + 200);
					if (rand() % 2 == 1) // tỉ lệ 50% 
						listItem.push_back(GetNewItem(gameObj->GetObj_id(), gameObj->GetType(), gameObj->x + 5, gameObj->y));

					//RunEffectHit = true;
					sound->Play(eSound::sHit); // sound đánh trúng obj
					listEffect.push_back(new Hit((int)(listObj[i]->x), (int)(listObj[i]->y + 10))); // hiệu ứng lửa
					listEffect.push_back(new Effect((int)(listObj[i]->x - 5), (int)(listObj[i]->y + 8))); // hiệu ứng lửa
					CountEnemyFishmen--; // giảm số lượng Fishmen đang hoạt động

					break;
				}
				case def_ID::BOSS:
				{
					gameObj->LoseHP(2);
					Data::GetInstance()->hpBoss -= 2;

					if (gameObj->GetHP() == 0)
					{
						gameObj->setLife(0);
						for (int row = 0; row < 2; row++)
						{
							for (int column = 0; column < 3; column++)
							{
								listEffect.push_back(new Effect((int)(listObj[i]->x + column * 24), (int)(listObj[i]->y + row * 24 + 10), 2));
							}
						}

						magicDown = 1;
					}

					sound->Play(eSound::sHit); // sound đánh trúng obj

					break;
				}
				default:
					break;
				}

				if (runHitEffect)
				{
					switch (simon->subWeapon->GetType())
					{
					case def_ID::iDAGGER:
					{
						sound->Play(eSound::sHit); // sound đánh trúng obj
					}
					case def_ID::iHOLYWATER:
					{
						sound->Play(eSound::sHollyWater); // sound đánh trúng obj
					}
					default:
						break;
					}

					listEffect.push_back(new Hit((int)(listObj[i]->x), (int)(listObj[i]->y + 10))); // hiệu ứng lửa
					listEffect.push_back(new Effect((int)(listObj[i]->x - 5), (int)(listObj[i]->y + 8))); // hiệu ứng lửa
				}

				switch (simon->subWeapon->GetType())
				{
				case def_ID::DAGGER:
				{
					simon->subWeapon->SetFinish(true); // hủy cây kiếm 
					break;
				}
				}
			}
		}
	}

	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == def_ID::BRICK)
		{
			CGameObject * gameObject = listObj[i];
			if (gameObject->GetLife() > 0)
			{
				switch (gameObject->GetObj_id())
				{
				case 39: // id 39 : brick 4 ô-> chỉ hiện effect
				{
					if (simon->mainWeapon->isCollision(listObj[i]) == true)
					{
						gameObject->LoseLife(1);
						if (gameObject->GetLife() < 1)
						{
							listEffect.push_back(new Hit((int)gameObject->x + 14, (int)gameObject->y + 14)); // hiệu ứng hit
							listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 1)); // hiệu ứng BrickSplash
							listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 2)); // hiệu ứng BrickSplash
							listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 3)); // hiệu ứng BrickSplash
							listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 4)); // hiệu ứng BrickSplash 
						}
						//sound->Play(eSound::soundBrickSplash);
					}
					break;
				}
				case 40: // drop pot roast
				{
					if (simon->mainWeapon->isCollision(listObj[i]) == true)
					{
						gameObject->LoseLife(1);
						listItem.push_back(GetNewItem(gameObject->GetObj_id(), gameObject->GetType(), gameObject->x, gameObject->y));
						listEffect.push_back(new Hit((int)gameObject->x + 14, (int)gameObject->y + 14)); // hiệu ứng hit
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 1)); // hiệu ứng BrickSplash
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 2)); // hiệu ứng BrickSplash
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 3)); // hiệu ứng BrickSplash
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 4)); // hiệu ứng BrickSplash 
						//sound->Play(eSound::soundBrickSplash);
					}
					break;
				}
				case 51: // id 51: brick 2 -> effect
				{
					if (simon->mainWeapon->isCollision(listObj[i]) == true)
					{
						gameObject->LoseLife(1);
						listEffect.push_back(new Hit((int)gameObject->x + 14, (int)gameObject->y + 14)); // hiệu ứng hit
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 1)); // hiệu ứng BrickSplash
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 2)); // hiệu ứng BrickSplash
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 3)); // hiệu ứng BrickSplash
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 4)); // hiệu ứng BrickSplash 
						//sound->Play(eSound::soundBrokenBrick);

					}
					break;
				}
				case 72: // id 72: brick -> a bonus
				{
					if (simon->mainWeapon->isCollision(listObj[i]) == true)
					{
						gameObject->LoseLife(1);
						sound->Play(eSound::sMonneyBag);
						listItem.push_back(GetNewItem(gameObject->GetObj_id(), gameObject->GetType(), gameObject->x, gameObject->y));
						listEffect.push_back(new Hit((int)gameObject->x + 14, (int)gameObject->y + 14)); // hiệu ứng hit
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 1)); // hiệu ứng BrickSplash
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 2)); // hiệu ứng BrickSplash
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 3)); // hiệu ứng BrickSplash
						listEffect.push_back(new BrickSplash((int)gameObject->x + 14, (int)gameObject->y + 14, 4)); // hiệu ứng BrickSplash  
						//sound->Play(eSound::soundBrickSplash);
					}
					break;
				}
				}
			}
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
				case def_ID::SMALLHEART:
				{
					simon->SetHeartCollect(simon->GetHeartCollect() + 1);
					listItem[i]->SetFinish(true);
					sound->Play(eSound::sCollectItem);
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
					simon->SetPoint(1000);
					break;
				}
				case def_ID::iHOLYWATER:
				{
					SAFE_DELETE(simon->subWeapon);
					simon->subWeapon = new HolyWater();
					listItem[i]->SetFinish(true);
					sound->Play(eSound::sCollectWeapon);
					break;
				}
				case def_ID::POTROAST:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::sCollectWeapon);
					simon->SetHP(min(simon->GetHP() + 6, 16)); // tăng 6 đơn vị máu
					break;
				}
				case def_ID::iAXE:
				{
					SAFE_DELETE(simon->subWeapon);
					simon->subWeapon = new Axe(camera);
					listItem[i]->SetFinish(true);
					sound->Play(eSound::sCollectWeapon);
					break;
				}
				case def_ID::MAGICCRYSTAL:
				{
					listItem[i]->SetFinish(true);
					isAllowProcessClearState3 = true;
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
				//LPCOLLISIONEVENT e = simon->isCollitionAllReturnE(listObj[i]);
				if (simon->isCollitionAll(hidenObject)) // có va chạm xảy ra
				{
					switch (hidenObject->GetObj_id())
					{
						case 67: 
						{
							if (isProcessingGoThroughTheDoor1)
							{
								Sound::GetInstance()->Play(eSound::sOpenDoor);
								isDoneSimonGoThroughTheDoor1 = true;
								camera->AutoGo(abs(CAMERA_AUTOGOX_AFTER_DOOR_1 - camera->GetX_cam()), 0.09f);
								simon->SetPositionBackup(simon->x, 0); // backup lại vị trí sau khi qua màn
							}

							TimeCreateBat = GetTickCount();
							TimeWaitProcessCreateBat = 3000;
							isGenerateBat = true;
							stateGame = 2;
							camera->SetPositionBackup(camera->GetX_cam(), camera->GetY_cam());
							hidenObject->LoseLife(1);
							break;
						}
						case 94: // đụng trúng box xác nhận simon đã qua GATE2
						{
							if (isProcessingGoThroughTheDoor2)
							{
								isDoneSimonGoThroughTheDoor2 = true;
								camera->AutoGo(abs(GATE2_POSITION_CAM_AFTER_GO - camera->GetX_cam()), 0.09f);
								simon->SetPositionBackup(simon->x, 0); // backup lại vị trí sau khi qua màn 
							}
							stateGame = 3;// set hiển thị đang ở state3
							camera->SetPositionBackup(camera->GetX_cam(), camera->GetY_cam());
							hidenObject->LoseLife(1);
							DebugOut(L"Xac nhan qua xong cua 2!\n");
							break;
						}
						case 41: // id 41: object ẩn -> xuống hồ nước
						{
							camera->SetPosition(camera->GetX_cam(), 384-10);
							camera->SetBoundary(CAMERA_BOUNDARY_LAKE_LEFT, CAMERA_BOUNDARY_LAKE_RIGHT);
							simon->SetPosition(3170, 430);
							isGenerateBat = false;  // không cho tạo Bat
							isAllowCreateFishmen = true;
							hidenObject->setLife(0);
							gridGame->pushToCell(GRID_INSERT_OBJECT__DIRAKHOIHONUOC_LEFT);
							break;
						}
						case 45: // id 45: object ẩn -> trở lên trước khi xuống hồ nước
						{
							camera->SetPosition(camera->GetX_cam(), 0);
							simon->SetPosition(3155, 348);
							isGenerateBat = true;  // không cho tạo Bat
							//TimeWaitProcessingCreateBat = 3000 + rand() % 1000;
							hidenObject->setLife(0);
							gridGame->pushToCell(GRID_INSERT_OBJECT__DIXUONGHONUOC_LEFT);
							break;
						}
						case 65: //id 65 : object ẩn->bonus
						{
							sound->Play(eSound::sMonneyBag);
							listItem.push_back(GetNewItem(hidenObject->GetObj_id(), hidenObject->GetType(), simon->x, simon->y));

							break;
						}
						case 66: //id 66: object ẩn -> chạm nước -> chết
						{
							simon->SetLife(0);
							sound->Play(eSound::sMonneyBag);
							
							//sound->Play(eSound::soundFallingDownWaterSurface);
							break;
						}
						case 81: // id 81: object ẩn -> ra khỏi hồ nước phía phải
						{
							camera->SetPosition(camera->GetX_cam(), 0);
							simon->SetPosition(3806, 361);
							isGenerateBat = true;
							isAllowCreateFishmen = false;
							TimeWaitProcessCreateBat = 3000 + rand() % 1000;
							hidenObject->setLife(0);
							gridGame->pushToCell(GRID_INSERT_OBJECT__DIXUONGHONUOC_RIGHT); // thêm object ẩn để có thể đi xuống sau khi đã lên lại

							break;
						}
						case 86: // id 86: object ẩn -> vào hồ nước phía phải
						{
							camera->SetPosition(camera->GetX_cam(), CAMERA_POSITION_Y_LAKE);
							simon->SetPosition(3825, 442);
							isGenerateBat = false;  // không cho tạo Bat
							isAllowCreateFishmen = true;

							hidenObject->setLife(0);

							gridGame->pushToCell(GRID_INSERT_OBJECT__DIRAKHOIHONUOC_RIGHT); // thêm object ẩn để có thể đi xuống sau khi đã lên lại

							break;
						}
						case 124:
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
					//hidenObject->LoseLife(1);
				}
			}
		}
	}
}

void Scene_2::CheckCollisionWithEnemy()
{
	CheckCollisionWeapon(listEnemy);
}

void Scene_2::CheckCollisionSimonWithEnemy()
{
	if (testa)
		return;

	if (simon->isUntouchable)
	{
		if (GetTickCount() - simon->startUntouchable > SIMON_UNTOUCHABLE_TIME)
		{
			simon->startUntouchable = 0;
			simon->isUntouchable = false;
		}
	}

	if (!simon->isUntouchable) // mode va chạm
	{
		for (UINT i = 0; i < listEnemy.size(); i++)
		{
			CGameObject * enemy = dynamic_cast<CGameObject *> (listEnemy[i]);
			if (enemy->GetLife() > 0) // còn sống
			{
				if (simon->isCollitionAll(enemy))
				{
					LPCOLLISIONEVENT e = simon->isCollitionAllReturnE(enemy);
					simon->SetEnemyHit(e);
					return;
				}

				if (enemy->GetType() == def_ID::FISHMEN)
				{
					Fishmen * fishmen = dynamic_cast<Fishmen *> (listEnemy[i]);
					if (fishmen->enemyBullet != NULL && !fishmen->enemyBullet->GetFinish())
					{
						if (simon->isCollitionAll(fishmen->enemyBullet))
						{
							LPCOLLISIONEVENT e = simon->isCollitionAllReturnE(fishmen->enemyBullet);
							simon->SetEnemyHit(e);
							fishmen->enemyBullet->SetFinish(true);
							return;
						}
					}
				}

				if (enemy->GetType() == def_ID::BOSS)
				{
					Boss * boss = dynamic_cast<Boss *> (listEnemy[i]);
					if (boss->enemyBullet != NULL && !boss->enemyBullet->GetFinish())
					{
						if (simon->isCollitionAll(boss->enemyBullet))
						{
							LPCOLLISIONEVENT e = simon->isCollitionAllReturnE(boss->enemyBullet);
							simon->SetEnemyHit(e);
							boss->enemyBullet->SetFinish(true);
							return;
						}
					}
				}
			}
		}
	}

	//if (!simon->isUntouchable) // mode va chạm
	//{

	//}
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
				//if (objGate->GetObj_id() == 64) // id object
				//{
				//	
				//}
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
						DebugOut(L"Simon dung trung cua 2!\n");

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

Items * Scene_2::GetNewItem(int Id, def_ID Type, float X, float Y)
{
	if (Type == def_ID::SMALLCANDLE)
	{
		//return new SmallHeart(X, Y);
		switch (Id)
		{
		case 40:
		case 71:
			if (simon->subWeapon != NULL && simon->subWeapon->GetType() != def_ID::HOLYWATER || simon->subWeapon == NULL)
				return new iHolyWater(X, Y);
			break;
		case 113:
			return new iAxe(X, Y);
			break;
		default:
			return new SmallHeart(X, Y);
			break;
		}
	}

	if (Type == def_ID::GHOST || Type == def_ID::PANTHER || Type == def_ID::BAT)
	{
		int random = rand() % 10;
		switch (random)
		{
		case 0:
			return new BigHeart(X, Y);
			break;
		case 1:
			return new SmallHeart(X, Y);
			break;
		case 2:
			if (simon->subWeapon != NULL && simon->subWeapon->GetType() != def_ID::DAGGER || simon->subWeapon == NULL)
				return new iDagger(X, Y);
			break;
		case 3:
			return new MoneyBag(X, Y);
			break;
		case 4:
			if (simon->mainWeapon->GetLevel() < 2)
				return new Whip(X, Y);
			break;
		case 5:
			if (simon->subWeapon != NULL && simon->subWeapon->GetType() != def_ID::HOLYWATER || simon->subWeapon == NULL)
				return new iHolyWater(X, Y);
			break;
		default: // 50%
			return new SmallHeart(X, Y);
			break;
		}
	}

	if (Type == def_ID::BRICK)
	{
		switch (Id)
		{
		case 40:
			return new PotRoast(X, Y);
			break;
		case 72:
			return new MoneyBag(X, Y);
			break;
		default:
			return new SmallHeart(X, Y);
			break;
		}
	}

	if (Type == def_ID::HIDDENOBJECT)
	{
		if (Id == 65)
			return new MoneyBag(3763.0f, 587.0f);
	}

	return new BigHeart(X, Y);
}