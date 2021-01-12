#pragma once
#include "Weapons.h" 
#include "Simon.h"

#define EnemyBullet_SPEED 0.15f

class EnemyBullet :
	public Weapons
{
public:
	EnemyBullet();
	virtual ~EnemyBullet();

	void Update(DWORD dt, Simon *simon);
	void Create(float X, float Y, int _nx);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderItem(int X, int Y);
	bool isCollision(CGameObject* obj);
	void CustomCreate(float X, float Y, int _nx, float _vx, float _vy);
	void CheckCollision(Simon * simon);
	void Render(Camera *camera);

};