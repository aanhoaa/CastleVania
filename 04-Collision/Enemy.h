#pragma once
#include "GameObject.h"
#include "Simon.h"
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

#define GHOST_SPEED 0.08f

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

#define PANTHER_ANI_SITTING 0
#define PANTHER_ANI_RUNNING_BEGIN 1
#define PANTHER_ANI_RUNNING_END 3

#define PANTHER_SPEED_RUNNING 0.20f
#define PANTHER_VYJUMP 0.5f
#define PANTHER_VXJUMP 0.5f

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
#define BAT_SPEED 0.08f
#define BAT_VY 0.08f
#define GHOST_GRAVITY 0.005f

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
#define FISHMEN_SPEED_Y_UP 0.6f
#define FISHMEN_SPEED_Y_DOWN 0.3f

#define FISHMEN_DY_JUMP 350 // nhảy lên khoảng 330px thì rớt xuống

#define FISHMEN_ANI_JUMP 2 // nhảy lên khoảng 330px thì rớt xuống
#define FISHMEN_GRAVITY_JUMPING 0.0083f

#define FISHMEN_DX_LIMIT 140 // đi được khoảng 140px thì đổi hướng
#define FISHMEN_DX_ATTACK_LIMIT 130 // đi được khoảng 140px thì đổi hướng

#define FISHMEN_TIME_LIMIT_WAIT_AFTER_ATTACK 700 // thời gian fishmen phải đứng lại chờ trước khi đi tiếp, sau khi attack

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


#define BOSS_PROCESS_SLEEP 0

#define BOSS_PROCESS_START_1 1 // lúc bắt đầu, Bat di chuyển xuống
#define BOSS_PROCESS_START_2 2 // lúc bắt đầu, Bat di chuyển đến cửa sổ (nửa vòng cung)

#define BOSS_PROCESS_CURVES 3 // lúc di chuyển theo vòng cung

#define BOSS_PROCESS_STRAIGHT_1 4 // xử lí di chuyển thẳng lần 1
#define BOSS_PROCESS_STRAIGHT_2 5 // xử lí di chuyển thẳng lần 2

#define BOSS_PROCESS_ATTACK 6 // xử lí tấn công


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

	//vector <Weapons*> * listWeaponOfEnemy;

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
