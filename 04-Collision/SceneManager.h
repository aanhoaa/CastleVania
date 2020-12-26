#pragma once
#include "define.h" 
#include "Scenes.h"
#include "Camera.h"

class SceneManager
{
private:
	static SceneManager * _Instance;

	Scenes * scenes;
	Camera * camera;

public:
	SceneManager();
	~SceneManager();

	static SceneManager * GetInstance();

	Camera * GetCamera();
	Scenes * GetScene();
	void SetScene(Scenes * x);

	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();
};

