#pragma once

#define MORNINGSTAR_ANI_LEVEL0_START 0
#define MORNINGSTAR_ANI_LEVEL0_END 3

#define MORNINGSTAR_ANI_LEVEL1_START 4
#define MORNINGSTAR_ANI_LEVEL1_END 7

#include "GameObject.h"
#include "Weapons.h"
#include "BigHeart.h"

class MorningStar : public Weapons
{
protected:
	int level;
	float xBackup, yBackup;
public:
	MorningStar();
	~MorningStar();
	void Create(float simon_X, float simon_Y, int simon_nx);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void UpdatePositionFitSimon();
	void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>* listObj);
	void UpgradeLevel();
};
