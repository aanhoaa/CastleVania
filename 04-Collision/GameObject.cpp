#include <d3dx9.h>
#include <algorithm>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	life = 1; // đang sống
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions( // danh sach cac doi tuong duoc cho la co va cham
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i)); // lay cac doi tuong co kha nang chuyen dong

		if (e->t > 0 && e->t <= 1.0f) // ktra co va cham hay khong
			coEvents.push_back(e); // co va cham thi nhet vao day
		else
			delete e; 
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare); // sort lai ma?ng ket qua theo thoi gian "t"
}

void CGameObject::FilterCollision( // 
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]); 
	if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}


void CGameObject::RenderBoundingBox(Camera * camera)
{
	RECT rect;

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	D3DXVECTOR2 pos = camera->Translate(l, t);

	LPDIRECT3DTEXTURE9  _Texture = BBox::GetInstance()->GetTexture();

	CGame::GetInstance()->Draw(pos.x, pos.y, _Texture, rect.left, rect.top, rect.right, rect.bottom, 100);
}

int CGameObject::GetLife()
{
	return life;
}

int CGameObject::GetHeight()
{
	return texture->FrameHeight;
}

int CGameObject::GetWidth()
{
	return texture->FrameWidth;
}

def_ID CGameObject::GetType() {
	return obj_type;
}

int CGameObject::GetDirect()
{
	return nx;
}

void CGameObject::SetDirect(int nx)
{
	this->nx = nx;
}

void CGameObject::SetId(int ID)
{
	this->id = ID;
}

void CGameObject::LoseLife(int health)
{
	life -= health;
	if (life < 0)
		life = 0;
}

CGameObject::~CGameObject()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(sprite);
}