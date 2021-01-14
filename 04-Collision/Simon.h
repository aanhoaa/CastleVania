#ifndef __SIMON_H__
#define __SIMON_H__

#include "GameObject.h"
#include "Weapons.h"
#include "MorningStar.h"
#include "Sound.h"
#include "Camera.h"
#include "Data.h"
#include "Dagger.h"
#include "HolyWater.h"
#include "Axe.h"
#include "Sound.h"

class Simon : public CGameObject
{
	Load_resources * simonDeath;
	Sound * sound;
public:
	int HeartPoint;
	int point;
	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isAttacking;
	bool isOnStair;
	bool isEnemyHit; // render sprite was hit
	int isProcessingOnStair;  // có 2 giai đoạn 
	float HeightStair = 0;//
	int isStairUp = 1; // -1: down, 1: up
	int nx_stair = 1; // -1: left, 1: right

	bool isAutoGoX = 0; // đang ở chế độ auto go?

	bool isFreeze;
	DWORD TimeFreeze;

	bool isUntouchable; // 1: đang tàng hình, 0: bình thường
	DWORD startUntouchable;

	D3DXVECTOR2 PositionBackup;

	bool isWalking_Backup;
	bool isJumping_Backup;
	bool isSitting_Backup;
	bool isAttacking_Backup;
	bool isOnStair_Backup;
	int isProcessingOnStair_Backup;
	int nx_stair_Backup;
	int isStairUp_Backup;
	int nx_AfterGo;

	bool isDeadth;
	DWORD TimeWaitedAfterDeath;

	bool beforeDeath;

	Camera * camera;
public:
	Simon(Camera * _camera);
	~Simon();

	MorningStar * mainWeapon;
	Weapons * subWeapon;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	virtual void AutoGo(float _autoGo_nx, int _nx_last, float _autoGo_dx, float _autoGo_vx);

	DWORD a;
	bool b;
	void Left();  
	void Right();
	void Go();
	void Sit();
	void ResetSit();
	void Jump();
	void Stop();
	void GoUpStair();
	void StartUntouchable();
	void SetDeadth();
	void RestoreBackupAutoGoX();
	void ProcessingOnStair();

	void SetEnemyHit(LPCOLLISIONEVENT e);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithEnemy(vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithItem(vector<Items*> *listItem = NULL);
	void CollisionWithExitStair(vector<LPGAMEOBJECT> *coObjects = NULL);
	void Attack(Weapons *weapon);

	bool isCollisionWithItem(Items * item);

	void SetHeartCollect(int h);
	int GetHeartCollect();

	void SetLife(int l);
	int GetPoint();
	void SetPoint(int s);

	bool GetFreeze();
	void SetFreeze(bool _isFreeze);
	void UpdateFreeze(DWORD dt);

	bool LoseLife();
	void SetPositionBackup(float X, float Y);  // lưu vị trí cần backup để simon die thì bắt đầu lại từ đây

	//void checkCollisionW
};






#endif