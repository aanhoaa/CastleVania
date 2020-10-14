#pragma once

#include "define.h"

class Scenes
{
public:
	Scenes();
	~Scenes();

	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;

	virtual void LoadResources() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};

