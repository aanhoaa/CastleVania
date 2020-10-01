#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "define.h"
#include "Load_img_file.h";
#include "Load_resources.h";
#include "Camera.h"

using namespace std;

#define ID_TEX_BBOX	 -100		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject *	LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
protected:
	int life;
public:
	int id; // id obj
	def_ID type_obj; // loại obj
	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	 

	int state;
	bool isPush; // xét xem obj đó đã dc cho vào list chưa (xử lý với tình huống 1 obj nằm trên 2 cells trở lên)

	DWORD dt; 

	// Render sprites:
	Load_img_file* texture;
	Load_resources* sprite;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int GetLife();
	int GetHeight();
	int GetWidth();
	void SetDirect(int nx);
	void SetId(int ID);

	int GetState() { return this->state; }

	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera) = 0;
	virtual void SetState(int state) { this->state = state; }


	~CGameObject();
};

