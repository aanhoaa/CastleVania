#pragma once
#include "GameObject.h"
#include "Data.h"
#include "Sound.h"
#include "define.h"

class HidenObject : public CGameObject
{
private:
	int width;
	int height;

public:
	HidenObject(int X, int Y, int Wight, int Height);
	~HidenObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
};

class Gate : public CGameObject
{
private:
	int isOpen;
public:
	Gate(int X, int Y);
	virtual ~Gate();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void Open();
	int GetStart();
};