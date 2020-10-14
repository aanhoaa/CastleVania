#include "SceneManager.h"

SceneManager * SceneManager::_Instance = NULL;


SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

SceneManager * SceneManager::GetInstance()
{
	if (_Instance == NULL)
		_Instance = new SceneManager();
	return _Instance;
}

void SceneManager::SetScene(Scenes * x)
{
	Scenes * scene_temp = scenes;

	scenes = x;
	SAFE_DELETE(scene_temp);
}


void SceneManager::KeyState(BYTE * state)
{
	scenes->KeyState(state);
}

void SceneManager::OnKeyDown(int KeyCode)
{
	scenes->OnKeyDown(KeyCode);
}

void SceneManager::OnKeyUp(int KeyCode)
{
	scenes->OnKeyUp(KeyCode);

}

void SceneManager::LoadResources()
{
	scenes->LoadResources();
}

void SceneManager::Update(DWORD dt)
{
	scenes->Update(dt);
}

void SceneManager::Render()
{
	scenes->Render();
}