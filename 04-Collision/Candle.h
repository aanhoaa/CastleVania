#pragma once

#include "GameObject.h";

class Candle : public CGameObject
{
public:
	Candle(int X, int Y);
	~Candle();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
};

