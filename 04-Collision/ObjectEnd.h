#pragma once
#include "GameObject.h"

class CastleTop : public CGameObject
{
	bool isActive;
	DWORD time;
	bool isDown;
	bool endGame;
public:
	CastleTop(float X = 0, float Y = 0);
	~CastleTop();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	void Render(Camera * camera);
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	bool GetActive();
	void SetActive(bool _isActive);
	bool GetEndGame();
};

