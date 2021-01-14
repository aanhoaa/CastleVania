#pragma once
#include "define.h"
#include "Camera.h"
#include "Load_img_file.h"
#include "Load_resources.h"
#include "debug.h"
#include "BBox.h"
#include "GameObject.h"
#include "LoadTexture.h"

class Items : public CGameObject
{
protected:
	DWORD  TimeDisplayMax; 
	DWORD  TimeDisplayed; 

	DWORD TimeWaited; 
	DWORD TimeWaitMax; 

	bool isFinish;
	float x_before;
public:
	Items(def_ID item, float X, float Y);
	~Items();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	virtual void Render(Camera * camera);
	virtual bool isWaiting();

	bool GetFinish();
	void SetFinish(bool _isFinish);
};
