#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>


#include "define.h"
#include "Load_img_file.h"
#include "Load_resources.h"
#include "Camera.h"
#include "BBox.h"
#include <algorithm>

using namespace std;


class Object;
typedef Object * LPGAMEOBJECT2;

struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT2;
struct CollisionEvent
{
	LPGAMEOBJECT2 obj;
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT2 obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT2 &a, LPCOLLISIONEVENT2 &b)
	{
		return a->t < b->t;
	}
};



class Object
{
protected:
	def_ID type; // Loại Object

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	DWORD dt;

	Load_img_file * _texture;
	Load_resources * _sprite;

public:
	Object();
	Object(def_ID _type) { this->type = _type; }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	float GetX() { return x; }
	float GetY() { return y; }

	void RenderBoundingBox(Camera * camera);
	LPCOLLISIONEVENT2 SweptAABBEx(LPGAMEOBJECT2 coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT2> *coObjects, vector<LPCOLLISIONEVENT2> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT2> &coEvents,
		vector<LPCOLLISIONEVENT2> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	int GetHeight() { return _texture->FrameHeight; }
	int GetWidth() { return _texture->FrameWidth; }

	def_ID GetType() { return type; }


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT2> *coObjects = NULL) = 0;
	virtual void Render(Camera * camera) = 0;



	~Object();
};