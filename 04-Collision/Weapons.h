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

class Weapons
{
protected:
	def_ID wea_type;

	float vx;	// Vận tốc theo trục X
	float vy;	// Vận tốc theo trục Y

	int nx;		// hướng trái = -1, phải = 1;

	bool isFinish;

	float x;	// Vị trí theo trục X
	float y;	// Vị trí theo trục Y 

	Load_img_file * texture;
	Load_resources * sprite;

public:
	Weapons();
	~Weapons();

	int GetDirect();
	void SetDirect(int nx);
	int GetFinish();
	void SetFinish(bool b);
	void RenderBoundingBox(Camera * camera);

	virtual void Create(float simon_X, float simon_Y, int simon_nx);
	virtual void Update(int dt);
	virtual void Draw(Camera *camera);
	virtual void SetPosition(float X, float Y);
	virtual void UpdatePositionFitSimon();
	
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>* listObj) = 0;

	def_ID GetType();
};

