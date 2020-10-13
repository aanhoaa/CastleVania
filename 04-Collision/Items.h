#pragma once
#include "define.h"
#include "Camera.h"
#include "Load_img_file.h"
#include "Load_resources.h"
#include "debug.h"
#include "BBox.h"
#include "Game.h"
#include "GameObject.h"

class Items : public CGameObject
{
protected:
	int TimeDisplayMax; // thời gian tối đa cho phép hiển thị.
	int TimeDisplayed; // Thời gian đã hiển thị.

	bool isFinish; // đã kết thúc chưa?
public:
	Items();
	~Items();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<CGameObject*> *listObject = NULL);
	virtual void Render(Camera * camera);
	virtual void SetReward() = 0; // Cập nhật điểm game

	bool GetFinish();
	void SetFinish(bool _isFinish);
};

