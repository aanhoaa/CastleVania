#pragma once
#include "define.h" 
#include "Scenes.h"

class SceneManager
{
private:
	static SceneManager * _Instance;

	Scenes * scenes;

public:
	SceneManager();
	~SceneManager();

	static SceneManager * GetInstance();

	void SetScene(Scenes * x);

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();
};

