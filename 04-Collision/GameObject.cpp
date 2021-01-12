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
	
	isDrop = 0;
	isAutoGo = 0;
	isReceive = 0;

	if (GetObj_id() == 39) life = 2;
	else life = 1; // đang sống
}

CGameObject::CGameObject(def_ID type)
{
	this->obj_type = type;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

void CGameObject::AutoGo(float _autoGo_nx, int _nx_last, float _autoGo_dx, float _autoGo_vx)
{
	if (isAutoGo)
		return;

	isAutoGo = true;// chưa vào chế độ autoGo thì set

	this->x_root = this->x;
	autoGo_nx = _autoGo_nx;
	autoGo_dx = _autoGo_dx;
	autoGo_vx = _autoGo_vx;
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

bool CGameObject::AABB(LPGAMEOBJECT obj)
{
	float l, t, r, b;
	float l1, t1, r1, b1;
	this->GetBoundingBox(l, t, r, b);
	obj->GetBoundingBox(l1, t1, r1, b1);

	if (CGame::GetInstance()->CollisionAABB(l, t, r, b, l1, t1, r1, b1))
		return true;

	return false;
}

bool CGameObject::isCollitionAll(LPGAMEOBJECT obj)
{
	if (AABB(obj))
		return true;

	// va chạm sweaptAABBx
	LPCOLLISIONEVENT e = SweptAABBEx(obj);
	bool result = e->t > 0 && e->t <= 1.0f; // ĐK va chạm
	SAFE_DELETE(e);

	return result;
}

LPCOLLISIONEVENT CGameObject::isCollitionAllReturnE(LPGAMEOBJECT obj)
{
	if (AABB(obj))
	{
		LPCOLLISIONEVENT e = new CCollisionEvent(1.0f, GetDirect(), 0, NULL);
		return e;
	}

	// va chạm sweaptAABBx
	LPCOLLISIONEVENT e = SweptAABBEx(obj);
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

		if (c->t <= min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t <= min_ty  && c->ny != 0) {
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

void CGameObject::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CGameObject::GetPosition(float &x, float &y)
{
	x = this->x;
	y = this->y;
}

void CGameObject::SetSpeed(float vx, float vy)
{
	this->vx = vx;
	this->vy = vy;
}

void CGameObject::GetSpeed(float &vx, float &vy)
{
	vx = this->vx;
	vy = this->vy;
}

int CGameObject::GetObj_id()
{
	return this->id;
}

int CGameObject::GetLife()
{
	return life;
}

void CGameObject::setLife(int _life)
{
	life = _life;
}

int CGameObject::GetHP()
{
	return hp;
}

void CGameObject::SetHP(int _hp)
{
	hp = _hp;
}

bool CGameObject::GetIsPush()
{
	return isPush;
}

void CGameObject::SetIsPush(int _isPush)
{
	isPush = _isPush;
}

bool CGameObject::GetIsDrop()
{
	return isDrop;
}

void CGameObject::SetIsDrop(int _isDrop)
{
	isDrop = _isDrop;
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

void CGameObject::SetEnabled(bool _isEnabled)
{
	this->isEnabled = _isEnabled;
}

void CGameObject::LoseLife(int health)
{
	life -= health;
	if (life < 0)
		life = 0;
}

void CGameObject::LoseHP(int _hp)
{
	hp -= _hp;
	if (hp < 0)
		hp = 0;
}

bool CGameObject::GetReceive()
{
	return isReceive;
}

void CGameObject::SetReceive(bool _isReceive)
{
	isReceive = _isReceive;
}

CGameObject::~CGameObject()
{
	DebugOut(L"[INFO] Delete nay: \n");
	//SAFE_DELETE(texture);
	SAFE_DELETE(sprite);
}

