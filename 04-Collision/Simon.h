#ifndef __SIMON_H__
#define __SIMON_H__

#define SIMON_POSITION_DEFAULT  50.0f, 100.0f

#define SIMON_BBOX_WIDTH 60
#define SIMON_BBOX_HEIGHT 66
#define SIMON_BBOX_SITTING_HEIGHT 48

#define SIMON_GRAVITY 0.005f
#define SIMON_VJUMP 0.34f

#define SIMON_WALKING_SPEED_SCENE_1 0.09f 
#define SIMON_WALKING_SPEED 0.15f 

#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING 1

#define SIMON_ANI_WALKING_BEGIN 1
#define SIMON_ANI_WALKING_END 3

#define SIMON_ANI_STANDING_ATTACKING_BEGIN 5
#define SIMON_ANI_STANDING_ATTACKING_END 7

#define SiMON_ANI_IDLE 0
#define SIMON_ANI_JUMPING 4
#define SIMON_ANI_SITTING 4

#define SIMON_ANI_SITTING_ATTACKING_BEGIN 15
#define SIMON_ANI_SITTING_ATTACKING_END 17

#define SIMON_ANI_STAIR_GO_UP_BEGIN 12
#define SIMON_ANI_STAIR_GO_UP_END 13

#define SIMON_ANI_STAIR_GO_DOWN_BEGIN 10
#define SIMON_ANI_STAIR_GO_DOWN_END 11

#define SIMON_ANI_STAIR_UP_ATTACKING_BEGIN 21
#define SIMON_ANI_STAIR_UP_ATTACKING_END 23

#define SIMON_ANI_STAIR_DOWN_ATTACKING_BEGIN 18
#define SIMON_ANI_STAIR_DOWN_ATTACKING_END 20

#define SIMON_ANI_ENEMY_HIT 8

#define SIMON_SPEED_ONSTAIR 0.07f
#define SIMON_VJUMP_ENEMY_HIT 0.5f

#define SIMON_ANI_STAIR_STANDING_UP 12
#define SIMON_ANI_STAIR_STANDING_DOWN 10

#define SIMON_STAIR_PROCESSING 8.0f
#define SIMON_STAIR_PROCESSING_DONE 16.0f

#define SIMON_UNTOUCHABLE_TIME 2000 

#define TIME_FREEZE_MAX 500

#define SIMON_GRAVITY_JUMPING 0.001f//0.005f
#define SIMON_BBOX_JUMPING_HEIGHT 45

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
	int HeartPoint; // số lượng heart nhặt được
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

	bool isFreeze; // Trạng thái đóng băng thay đổi màu liên tục
	DWORD TimeFreeze; // thời gian đã đóng băng

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
	void Left();  // set lại hướng của simon
	void Right(); // set lại hướng của simon
	void Go();
	void Sit();
	void ResetSit();
	void Jump();
	void Stop();
	void GoUpStair();
	void StartUntouchable();
	void SetDeadth();
	void RestoreBackupAutoGoX(); // khôi phục trạng thái 

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