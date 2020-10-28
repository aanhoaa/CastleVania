#pragma once
#include <vector>

#include "define.h"
#include "Camera.h"
#include "Load_img_file.h"
#include "Load_resources.h"
#include "debug.h"
#include "BBox.h"
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

	bool GetFinish();
	void SetFinish(bool b);

	virtual void Create(float simon_X, float simon_Y, int simon_nx);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void SetPosition(float X, float Y);
	virtual void UpdatePositionFitSimon();
	virtual bool isCollision(CGameObject* obj) = 0; // kiểm tra vũ khí này có va chạm với object kia hay không?
	virtual void RenderItem(int X, int Y) = 0; // vẽ item lên ô blackborad 
};

