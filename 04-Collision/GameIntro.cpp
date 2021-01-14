#include "GameIntro.h"


GameIntro::GameIntro()
{
	Data::GetInstance()->scene = 0;
	LoadResources();
}


GameIntro::~GameIntro()
{
	SAFE_DELETE(simon);
	SAFE_DELETE(board);
}

void GameIntro::KeyState(BYTE * state)
{
}

void GameIntro::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_2) 
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(CGame::GetInstance()->GetWindowHandle(), &p);
		DebugOut(L"[MOUSE POSITION] %d %d \n", p.x, p.y);
	}
	else
	{
		isPressStart = true;
	}
}

void GameIntro::OnKeyUp(int KeyCode)
{
}

void GameIntro::LoadResources()
{
	LoadTexture * textureIntro = LoadTexture::GetInstance(); 

	Sprite_MainMenu = new Load_resources(textureIntro->GetTexture(def_ID::MAINMENU), 0);
	Sprite_IntroBatMenu = new Load_resources(textureIntro->GetTexture(def_ID::INTRO_BAT_MENU), 150);
	Sprite_IntroGoScene1 = new Load_resources(textureIntro->GetTexture(def_ID::INTRO_GO_SCENE1), 0);

	StatusProcess = INTRO_STATUS_PROCESS_MENU;
	TimeWaited = 0;
	isPressStart = 0;

	isDrawTextPressStart = true;

	simon = new Simon(camera);
	board = new BoardGame(0, 0);

	heliCopter = new HelicopterIntro(432, 146);
	introBat1 = new BatIntro(299.0f, 118.0f, -0.0139f, 0.0f, 2); 
	introBat2 = new BatIntro(47.0f, 224.0f, 0.0270f, -0.0182f, 1);
}

void GameIntro::Update(DWORD dt)
{
	
	switch (StatusProcess)
	{
	case INTRO_STATUS_PROCESS_MENU:
	{
		if (!isPressStart) 
			if (Sprite_IntroBatMenu->GetIndex() >= 14)
			{
				Sprite_IntroBatMenu->SelectIndex(12);
				Sprite_IntroBatMenu->Update(dt);
			}
			else Sprite_IntroBatMenu->Update(dt);

		if (isPressStart)
		{
			TimeWaited += dt;
			if (TimeWaited >= 1500)
			{
				StatusProcess = INTRO_STATUS_PROCESS_GO_SCENE1;
				camera = SceneManager::GetInstance()->GetCamera();
				camera->SetPosition(0, 0);
				listBrick.push_back(new Brick(0, 400, 600, 32, 4));
				simon->SetPosition(500, 336);
				simon->SetDirect(-1);
				simon->AutoGo((float)simon->GetDirect(), -1, 275.0f, 0.08f);
			}
			else
			{
				TimeWaitedToChangeDisplayTextPressStart += dt;
				if (TimeWaitedToChangeDisplayTextPressStart >= 150) // sau 150dt thì tắt - bật
				{
					TimeWaitedToChangeDisplayTextPressStart = 0;
					isDrawTextPressStart = !isDrawTextPressStart; // lật trạng thái
				}
			}
		}

		break;
	}
	case INTRO_STATUS_PROCESS_GO_SCENE1:
	{
		camera->Update(dt);

		if (simon->isAutoGo)
		{
			simon->Update(dt, &listBrick);
		}
		else
		{
			simon->sprite->SelectIndex(9);
		}

		heliCopter->Update(dt);

		introBat1->Update(dt);
		introBat2->Update(dt);

		if (introBat1->isCollitionAll(introBat2))
		{
			introBat1->LoseLife(1);
			introBat2->LoseLife(1);
			SceneManager::GetInstance()->SetScene(new Scene_1());
		}

		break;
	}
	}
}

void GameIntro::Render()
{
	switch (StatusProcess)
	{
	case INTRO_STATUS_PROCESS_MENU:
	{
		Sprite_MainMenu->Draw(0, -3); // vẽ nền
		Sprite_IntroBatMenu->Draw(345, 203); // vẽ nền
		if (isDrawTextPressStart)
		{
			TextPressStart.Draw(160, 270, "PUSH START KEY");
		}

		TextPressStart.Draw(160, 315, "TM AND @ 1987");
		TextPressStart.Draw(73, 331, "KONAMI INDUSTRY CO. ,LTD.");
		TextPressStart.Draw(178, 350, "LICENSED BY ");
		TextPressStart.Draw(73, 370, "NITENDO OF AMERICA INC.");

		break;
	}

	case INTRO_STATUS_PROCESS_GO_SCENE1:
	{
		Sprite_IntroGoScene1->Draw(0, 0);
		board->Render(simon, Data::GetInstance()->hpBoss, 300, simon->subWeapon, 1);
		
		heliCopter->Render(camera);

		introBat1->Render(camera);
		introBat2->Render(camera);

		simon->Render(camera);
		break;
	}
	}

}