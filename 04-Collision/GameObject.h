#pragma once

#include "define.h"
#include "Load_img_file.h"
#include "Load_resources.h"
#include "Camera.h"
#include "BBOX.h"
#include "LoadTexture.h"

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
	def_ID obj_type; 
	bool isDrop;
	bool isEnabled;
public:
	int scene;
	int id;
	float x; 
	float y;

	float dx;	
	float dy;	

	float vx;
	float vy;

	int nx;	 

	bool isReceive;

	// auto go object
	bool isAutoGo;
	float x_root;
	float autoGo_dx;
	float autoGo_vx;
	float autoGo_nx;

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
	void SetHP(int _hp);
	int GetLife();
	void setLife(int _life);

	bool GetIsDrop();
	void SetIsDrop(int _isDrop);

	int GetHeight();
	int GetWidth();
	def_ID GetType();
	int GetDirect();
	void SetDirect(int nx);
	void SetId(int ID);

	void SetEnabled(bool _isEnabled);

	void LoseLife(int health);
	void LoseHP(int _hp);

	bool GetReceive();
	void SetReceive(bool _isReceive);

	void RenderBoundingBox(Camera * camera);

	bool AABB(LPGAMEOBJECT obj);
	bool isCollitionAll(LPGAMEOBJECT obj); 	// AABB và Sweept AABB check all
	LPCOLLISIONEVENT isCollitionAllReturnE(LPGAMEOBJECT obj);
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
	virtual void AutoGo(float _autoGo_nx, int _nx_last, float _autoGo_dx, float _autoGo_vx);

	 ~CGameObject();
};
