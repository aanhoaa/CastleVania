#pragma once

#include "GameObject.h"
#include "EnemyBullet.h"

class Enemy : public CGameObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
};

/* Ghost*/

class Ghost : public CGameObject
{
public:
	Ghost(float X, float Y, int _nx);
	virtual ~Ghost();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
};

/*	Panther */

class Panther : public CGameObject
{
private:
	bool isSitting;
	bool isRunning;

	bool isJumping;
	bool isStart; // trạng thái bắt đầu
	float autogo = 0;

	//float AutoGoX_Dx; // khoảng cách cần chạy
	//bool isAutoGoX;
	//float AutoGoX_Backup_X;

public:
	Panther(float X, float Y, int _nx, float autoGoX_Dx);
	Panther(float X, float Y, int _nx, float autoGoX_Dx, float autoGoX_Dx2);
	virtual ~Panther();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, Simon * simon, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera *camera);

	bool GetIsStart();

	void Jump();
	void Run();
};

/*  Bat  */
class Bat : public CGameObject
{
private:
	float y_root;
	int alpha = 0;

public:
	Bat(float X, float Y, int _nx);
	virtual ~Bat();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera *camera);
};

/* Fish men*/

class Fishmen : public CGameObject
{
private:
	float y_root; // vị trí y lúc khởi tạo
	bool isJumping;
	bool isRunning;
	bool isAttacking;
	bool shoot;

	float x_root;

	float pos_x_before;
	float pos_x_after;
	float distance;
	DWORD TimeAttack; // thời điểm attack
	
public:
	EnemyBullet * enemyBullet;
	Fishmen(float X = 0, float Y = 0, int _nx = -1);
	virtual ~Fishmen();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	void Render(Camera * camera);
	void UpdateCustom(DWORD dt, vector<LPGAMEOBJECT> *listObject, Simon* simon);
	void Attack(Weapons * _enemyBullet);
};

/* BOSS */
#include "GameObject.h"
#include "Simon.h"

class Boss : public CGameObject
{
public:
	int StatusProcessing;

private:

	float xBefore;
	float yBefore;

	float xTarget;
	float yTarget;
	Simon * simon;

	/*BezierCurves*/
	bool isUseBezierCurves = false;
	float x1;
	float y1;

	float x2;
	float y2;

	float x3;
	float y3;

	float yLastFrame; // y của frame trước đó
					  /*BezierCurves*/
	Camera *camera;

	DWORD TimeWaited; // thời gian đã chờ
	bool isWaiting;
	bool isAttacking;
	bool isStart = 0;
public:
	EnemyBullet * enemyBullet;
	Boss(float X, float Y, Simon * simon, Camera *camera);
	~Boss();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, Simon* simon, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

	void Start();
	void StartCurves();
	void StartStaight(Simon* simon);
	void StartAttack();

	float getPt(float n1, float n2, float perc);
};
