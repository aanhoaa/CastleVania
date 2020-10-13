#include "Scenes.h"

Scenes * Scenes::__Instance = NULL;


Scenes::Scenes()
{
	listScenes.clear();
}


Scenes::~Scenes()
{
}

Scenes * Scenes::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Scenes();
	return __Instance;
}

void Scenes::LoadResources()
{
	listScenes.back()->LoadResources();
}

void Scenes::Update(DWORD dt)
{
	listScenes.back()->Update(dt);
}

void Scenes::Render()
{
	listScenes.back()->Render();
}

void Scenes::ChangeScene(Scenes * Scene)
{
	Scenes * Scenes_current = listScenes.back();
	listScenes.pop_back();
	SAFE_DELETE(Scenes_current);


	listScenes.push_back(Scene);
}