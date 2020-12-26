#pragma once
#include "Weapons.h" 

#define EnemyBullet_SPEED 0.15f

class EnemyBullet :
	public Weapons
{
public:
	EnemyBullet();
	virtual ~EnemyBullet();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float X, float Y, int _nx);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderItem(int X, int Y);
	bool isCollision(CGameObject* obj);
	void CustomCreate(float X, float Y, int _nx, float _vx, float _vy);

	void Render(Camera *camera);

};