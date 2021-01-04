#pragma once
#include <vector>
#include "define.h"
#include "Camera.h"
#include "Load_img_file.h"
#include "Load_resources.h"
#include "GameObject.h"
#include "Items.h"
#include "Heart.h"
#include "LoadTexture.h"
#include "Sound.h"

class Weapons : public CGameObject
{
protected:         
	bool isFinish;
	bool isSend;
public:
	Weapons();
	~Weapons();
	                                                                    
	bool GetFinish();
	void SetFinish(bool _isFinish);
	bool GetSend();
	void SetSend(bool _isSend);

	virtual void Create(float X, float Y, int _nx);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void SetPosition(float X, float Y);
	virtual void UpdatePositionFitSimon();
	virtual bool isCollision(CGameObject* obj) = 0; // kiểm tra vũ khí này có va chạm với object kia hay không?
	virtual void RenderItem(int X, int Y) = 0; // vẽ item lên ô blackborad 
};                                            

