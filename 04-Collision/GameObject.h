#pragma once

#include "Object.h"
#include "define.h"
#include "Load_img_file.h"
#include "Load_resources.h"
#include "Camera.h"
#include "BBOX.h"

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
	int hp;
	int life;
	def_ID obj_type; // loại obj
	bool isPush; // xét xem obj đó đã dc cho vào list chưa (xử lý với tình huống 1 obj nằm trên 2 cells trở lên)
public:
	int id; // id obj
	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	 

	int state;

	DWORD dt; 

	// Render sprites:
	Load_img_file* texture;
	Load_resources* sprite;

public: 
	CGameObject(def_ID type);
	void GetPosition(float &x, float &y);
	void SetPosition(float x, float y);
	void GetSpeed(float &vx, float &vy);
	void SetSpeed(float vx, float vy);

	int GetObj_id();

	int GetHP();
	int GetLife();

	bool GetIsPush();
	void SetIsPush(int _isPush);

	int GetHeight();
	int GetWidth();
	def_ID GetType();
	int GetDirect();
	void SetDirect(int nx);
	void SetId(int ID);

	void LoseLife(int health);

	int GetState() { return this->state; }
	void RenderBoundingBox(Camera * camera);

	bool isCollitionAll(CGameObject *obj); 	// AABB và Sweept AABB check all

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


//class CGameObject : public Object
//{
//protected:
//	int Health;
//
//public:
//	int id; // ID của object
//
//	int trend;	// hướng -1 : trái, 1: phải
//
//	bool isTake;
//
//public:
//
//
//	CGameObject();
//
//	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
//	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
//	virtual void Render(Camera * camera) = 0;
//
//	int GetHealth();
//	void SubHealth(int th);
//	void SetTrend(int Trend);
//	void SetId(int ID);
//
//	~CGameObject();
//};