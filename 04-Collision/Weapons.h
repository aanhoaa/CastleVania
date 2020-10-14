#pragma once
#include <vector>

#include "define.h"
#include "Camera.h"
#include "Load_img_file.h"
#include "Load_resources.h"
#include "debug.h"
#include "BBox.h"
#include "Game.h"
#include "GameObject.h"
#include "Items.h"
#include "BigHeart.h"

class Weapons : public CGameObject
{
protected:
	//int nx;		// hướng trái = -1, phải = 1;
	bool isFinish;
public:
	Weapons();
	~Weapons();

	//int GetDirect();
	//void SetDirect(int nx);
	bool GetFinish();
	void SetFinish(bool b);
	static Items * GetItem(int Id, def_ID Type, float X, float Y);

	virtual void Create(float simon_X, float simon_Y, int simon_nx);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void SetPosition(float X, float Y);
	virtual void UpdatePositionFitSimon();
	
	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>* listObj) = 0;
};

