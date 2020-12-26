#pragma once
#include "GameObject.h"

#define HELICOPTER_SPEED_X 0.01f
#define HELICOPTER_SPEED_Y 0.004f

/* Bat intro */
class BatIntro :public CGameObject
{
	int typeBat;
public:
	BatIntro(float X = 0, float Y = 0, float VX = 0, float VY = 0, int _typeBat = 1);
	~BatIntro();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	void Render(Camera * camera);
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
};

/* Helicoper intro*/
class HelicopterIntro :public CGameObject
{
public:
	HelicopterIntro(float X = 0, float Y = 0);
	virtual ~HelicopterIntro();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	void Render(Camera * camera);
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
};
