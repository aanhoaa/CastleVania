#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

#include "Brick.h"

#include "Simon.h"
#include "define.h"
#include "Map.h"
#include "Camera.h"
#include "Grid.h"
#include "Items.h"

class Scenes
{
public:
	static Scenes * __Instance;
	vector <Scenes*> listScenes;

	Scenes();
	~Scenes();

	static Scenes* GetInstance();

	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void ChangeScene(Scenes * scene);

};

