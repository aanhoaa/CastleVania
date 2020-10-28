#ifndef __SIMON_H__
#define __SIMON_H__

#define SIMON_POSITION_DEFAULT  50.0f, 0

#define SIMON_BBOX_WIDTH 60
#define SIMON_BBOX_HEIGHT 66
#define SIMON_BBOX_SITTING_HEIGHT 48

#define SIMON_GRAVITY 0.005f
#define SIMON_VJUMP 0.9f

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

#define TIME_FREEZE_MAX 500

#include "GameObject.h"
#include "Weapons.h"
#include "MorningStar.h"

class Simon : public CGameObject
{
public:
	int HeartPoint; // số lượng heart nhặt được
	int point;
	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isAttacking;

	bool isFreeze; // Trạng thái đóng băng thay đổi màu liên tục
	DWORD TimeFreeze; // thời gian đã đóng băng

	D3DXVECTOR2 PositionBackup;

public:
	Simon();
	~Simon();

	Weapons* mainWeapon;
	Weapons* subWeapon;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

	void Left();  // set lại hướng của simon
	void Right(); // set lại hướng của simon
	void Go();
	void Sit();
	void Jump();
	void Stop();

	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
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
};






#endif