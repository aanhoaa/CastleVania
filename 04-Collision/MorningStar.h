#pragma once

#define MORNINGSTAR_ANI_LEVEL0_START 0
#define MORNINGSTAR_ANI_LEVEL0_END 3

#define MORNINGSTAR_ANI_LEVEL1_START 4
#define MORNINGSTAR_ANI_LEVEL1_END 7

#define MORNINGSTAR_ANI_LEVEL2_START 8
#define MORNINGSTAR_ANI_LEVEL2_END 11

#include "GameObject.h"
#include "Weapons.h"
#include "HitEffect.h"


class MorningStar : public Weapons
{
protected:
	int level;
	vector <HitEffect*> listEffect;
	vector <CGameObject*> listEnemy;
public:
	MorningStar();
	~MorningStar();
	void Create(float simon_X, float simon_Y, int simon_nx);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void UpdatePositionFitSimon();
	bool isCollision(CGameObject* obj);
	void UpgradeLevel();
	void RenderItem(int X, int Y);
	int GetLevel();
};
