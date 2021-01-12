#include "LoadTexture.h"



LoadTexture* LoadTexture::__Instance = NULL;

LoadTexture * LoadTexture::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new LoadTexture();
	return __Instance;
}

void LoadTexture::AddTexture(def_ID type, Load_img_file *texture)
{
	Textures[type] = texture;
}

Load_img_file * LoadTexture::GetTexture(def_ID type)
{
	return Textures[type];
}

void LoadTexture::LoadResource()
{
	//if (Data::GetInstance()->scene == 2) // intro game
	{
		DebugOut(L"[0] Load resource scene: %d\n", Data::GetInstance()->scene);
		AddTexture(def_ID::MAINMENU, new Load_img_file("Resources/mainmenu.png"));
		AddTexture(def_ID::INTRO_BAT, new Load_img_file("Resources/intro_bat.png", 2, 1, 2));
		AddTexture(def_ID::INTRO_BAT_MENU, new Load_img_file("Resources/IntroBatMenu.png", 5, 3, 15));
		AddTexture(def_ID::INTRO_GO_SCENE1, new Load_img_file("Resources/intro_go_scene_1.png"));
		AddTexture(def_ID::HELICOPTER, new Load_img_file("Resources/helicopter.png"));
		AddTexture(def_ID::SIMON, new Load_img_file("Resources/simon.png", 8, 3, 24));
		
		AddTexture(def_ID::BRICK_TRANSPARENT, new Load_img_file("Resources/ground/brick_transparent.png")); // loại trong suốt

		AddTexture(def_ID::RENDERBOX, new Load_img_file("Resources/bbox.png")); // dùng để vẽ BBOX
		AddTexture(def_ID::FONTGAME, new Load_img_file("Resources/font/1.png", 13, 3, 37));
		AddTexture(def_ID::BLACKBOARD, new Load_img_file("Resources/blackboard.png", 1, 1, 1));
		AddTexture(def_ID::HEARTPOINT, new Load_img_file("Resources\\heal.png", 3, 1, 3));

		//resource simon die
		AddTexture(def_ID::SIMONDEATH, new Load_img_file("Resources/test.png", 3, 1, 3));
	}

	//if (Data::GetInstance()->scene == 1) // stage 1-1
	{
		DebugOut(L"[1] Load resource scene: %d\n", Data::GetInstance()->scene);
		AddTexture(def_ID::BRICK_TYPE_1, new Load_img_file("Resources/ground/2.png")); // loại dành cho state 1
		AddTexture(def_ID::BIGCANDLE, new Load_img_file("Resources/ground/0.png", 2, 1, 2));
		AddTexture(def_ID::BIGHEART, new Load_img_file("Resources/item/1.png"));
		AddTexture(def_ID::UPGRADEMORNINGSTAR, new Load_img_file("Resources/item/3.png"));
		AddTexture(def_ID::iDAGGER, new Load_img_file("Resources/item/4.png"));
		AddTexture(def_ID::MONNEYBAG, new Load_img_file("Resources/item/2.png", 3, 1, 3));

		//resoure effect
		AddTexture(def_ID::EFFECT, new Load_img_file("Resources/other/1.png", 4, 1, 4));
		AddTexture(def_ID::HIT, new Load_img_file("Resources/other/0.png", 2, 1, 2));

		//resoure weapon
		AddTexture(def_ID::MORNINGSTAR, new Load_img_file("Resources/weapon/morningstar.png", 4, 3, 12));
		AddTexture(def_ID::DAGGER, new Load_img_file("Resources/weapon/1.png"));
	}

	//if (Data::GetInstance()->scene == 1) // stage 1-2
	{
		//resoure object static
		AddTexture(def_ID::BRICK_TYPE_2, new Load_img_file("Resources/ground/2-2.png")); // dành cho state 2
		AddTexture(def_ID::BRICK_TYPE_3, new Load_img_file("Resources/ground/8.png")); // loại nhỏ
		AddTexture(def_ID::BRICK_3X32, new Load_img_file("Resources/ground/8-2.png"));
		AddTexture(def_ID::BRICK_4X32, new Load_img_file("Resources/ground/8-1.png"));
		AddTexture(def_ID::GATE, new Load_img_file("Resources/ground/Gate1.png", 4, 1, 4));
		AddTexture(def_ID::SMALLCANDLE, new Load_img_file("Resources/ground/1.png", 2, 1, 2));

		//resoure enemy
		AddTexture(def_ID::GHOST, new Load_img_file("Resources/enemy/1.png", 2, 1, 2));
		AddTexture(def_ID::PANTHER, new Load_img_file("Resources/enemy/2.png", 4, 1, 4));
		AddTexture(def_ID::BAT, new Load_img_file("Resources/enemy/0.png", 4, 1, 4));
		AddTexture(def_ID::FISHMEN, new Load_img_file("Resources/enemy/3.png", 3, 1, 3));
		AddTexture(def_ID::BOSS, new Load_img_file("Resources/boss/0.png", 3, 1, 3));

		//resoure effect
		AddTexture(def_ID::BRICKSPLASH, new Load_img_file("Resources/other/BrokenBrick64.png", 4, 4, 16));
		AddTexture(def_ID::WATER, new Load_img_file("Resources/other/2.png"));

		//resoure enemy bullet
		AddTexture(def_ID::ENEMYBULLET, new Load_img_file("Resources/weapon/fireball.png"));

		

		//resource item
		AddTexture(def_ID::SMALLHEART, new Load_img_file("Resources/item/0.png"));
		AddTexture(def_ID::iHOLYWATER, new Load_img_file("Resources/item/9.png"));
		AddTexture(def_ID::POTROAST, new Load_img_file("Resources/item/10.png"));
		AddTexture(def_ID::iAXE, new Load_img_file("Resources/item/7.png"));
		AddTexture(def_ID::MAGICCRYSTAL, new Load_img_file("Resources/item/13.png", 2, 1, 2));

		//resource weapon
		AddTexture(def_ID::HOLYWATER, new Load_img_file("Resources/weapon/2.png", 4, 1, 4));
		AddTexture(def_ID::AXE, new Load_img_file("Resources/weapon/3.png", 4, 1, 4));
	}

	if (Data::GetInstance()->scene == 3) // endgame
	{
		AddTexture(def_ID::CASTLE, new Load_img_file("Resources/castle.png"));
		AddTexture(def_ID::TOPCASTLE, new Load_img_file("Resources/e.png", 3, 1, 3));
	}

}

LoadTexture::LoadTexture()
{
	LoadResource();
}


LoadTexture::~LoadTexture()
{
	SAFE_DELETE(__Instance);
}