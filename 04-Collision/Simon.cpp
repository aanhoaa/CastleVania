#include "Simon.h"
#include "debug.h"


Simon::Simon(Camera * _camera)
{
	obj_type = def_ID::SIMON;
	texture = LoadTexture::GetInstance()->GetTexture(SIMON);
	sprite = new Load_resources(texture, 120);

	simonDeath = new Load_resources(LoadTexture::GetInstance()->GetTexture(SIMONDEATH), 500);

	hp = 16; // 16 hp
	life = 1; // 5 mạng
	HeartPoint = 5;
	point = 0;

	this->camera = _camera;
	// states have ready
	isWalking = false; 
	isJumping = false;
	isSitting = false;
	isAttacking = false;
	isProcessingOnStair = 0;// ko phải đang xử lí
	isEnemyHit = false;
	isUntouchable = false;
	isAutoGoX = false;

	isDeadth = false;
	beforeDeath = 0;
	b = 0;

	if (Data::GetInstance()->scene >= 1)
	{
		mainWeapon = new MorningStar();
		subWeapon = NULL;
	}
	sound = Sound::GetInstance();
}

Simon::~Simon()
{
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isSitting == true) // simon sitting
	{
		left = x + 12;
		top = y - 1; // fixed y (sit() updated y)
		right = x + SIMON_BBOX_WIDTH - 15;
		bottom = y + SIMON_BBOX_SITTING_HEIGHT-3;
	}
	else
	{
		if (isDeadth)
		{
			left = x + 12;
			top = y - 1;
			right = x + SIMON_BBOX_WIDTH - 15;
			bottom = y + 52;
		}
		else
		{
			left = x + 12;
			top = y - 1;
			right = x + SIMON_BBOX_WIDTH - 15;
			bottom = y + SIMON_BBOX_HEIGHT - 3;

			if (isJumping)
				bottom = y + SIMON_BBOX_JUMPING_HEIGHT;
		}
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// không cho S đi khỏi cam
	float left = Data::GetInstance()->boundaryLeft;
	float right = Data::GetInstance()->boundaryRight;

	if (x < left) // khi xuất hiện sang trái sẽ ngăn lại
		x = left;
	
	if (x + SIMON_BBOX_WIDTH > right + Window_Width)
		x = (float)(right + Window_Width - SIMON_BBOX_WIDTH); // phải tương tự
	
	int index = sprite->GetIndex();

	if (isAttacking == true)
	{
		if (mainWeapon->GetFinish() == false) // nếu MorningStar đang đánh
		{
			mainWeapon->Update(dt, coObjects);

			if (mainWeapon->GetFinish() == true)
			{
				isAttacking = false;
			}
		}
		else
		{
			if (subWeapon != NULL)
			{
				isAttacking = !(SIMON_ANI_SITTING_ATTACKING_END == index || SIMON_ANI_STANDING_ATTACKING_END == index ||
					SIMON_ANI_STAIR_UP_ATTACKING_END == index || SIMON_ANI_STAIR_DOWN_ATTACKING_END == index);
			}
		}
	}

	if (subWeapon != NULL && subWeapon->GetFinish() == false)
	{
		subWeapon->Update(dt, coObjects);
	}

	if (isOnStair)
	{
		if (isAttacking == true) // tấn công
		{
			if (isStairUp == 1) // đang đi lên
			{
				if (index < SIMON_ANI_STAIR_UP_ATTACKING_BEGIN || index > SIMON_ANI_STAIR_UP_ATTACKING_END)
				{
					sprite->SelectIndex(SIMON_ANI_STAIR_UP_ATTACKING_BEGIN);
				}
				else
				{
					sprite->Update(dt); 
				}
			}
			else
			{
				if (index < SIMON_ANI_STAIR_DOWN_ATTACKING_BEGIN || index > SIMON_ANI_STAIR_DOWN_ATTACKING_END)
				{
					sprite->SelectIndex(SIMON_ANI_STAIR_DOWN_ATTACKING_BEGIN);
				}
				else
				{
					sprite->Update(dt);
				}
			}
		}
		else
		{
			if (isWalking == true)
			{
				if (isProcessingOnStair == 1) 
				{
					if (vy < 0) 
						sprite->SelectIndex(SIMON_ANI_STAIR_GO_UP_BEGIN);
					else
						sprite->SelectIndex(SIMON_ANI_STAIR_GO_DOWN_BEGIN);
				}

				if (isProcessingOnStair == 2) 
				{
					if (vy < 0) 
						sprite->SelectIndex(SIMON_ANI_STAIR_GO_UP_END);
					else
						sprite->SelectIndex(SIMON_ANI_STAIR_GO_DOWN_END);

				}

				HeightStair += abs(vy) * 16.0f;
				
				if (HeightStair >= SIMON_STAIR_PROCESSING && isProcessingOnStair == 1)
					isProcessingOnStair++;

				if (HeightStair >= SIMON_STAIR_PROCESSING_DONE)
				{
					ProcessingOnStair();
				}
			}
			else
			{
				if (this->isStairUp == 1) 
					sprite->SelectIndex(SIMON_ANI_STAIR_STANDING_UP);
				else
					sprite->SelectIndex(SIMON_ANI_STAIR_STANDING_DOWN);
			}
		}
	}
	else
	{
		if (isEnemyHit && !isDeadth)
		{
				sprite->SelectIndex(SIMON_ANI_ENEMY_HIT);
		}
		else
		{
			if (isDeadth)
			{
				simonDeath->Update(dt);
			}
			else
			{
				if (isSitting == true)
				{
					if (isAttacking == true)
					{
						{
							if (index < SIMON_ANI_SITTING_ATTACKING_BEGIN || index > SIMON_ANI_SITTING_ATTACKING_END)
							{
								sprite->SelectIndex(SIMON_ANI_SITTING_ATTACKING_BEGIN);
							}
							else
							{
								sprite->Update(dt); 

								if (sprite->GetIndex() == SIMON_ANI_SITTING_ATTACKING_END + 1)
									sprite->SelectIndex(SIMON_ANI_SITTING);
							}
						}
					}
					else
						sprite->SelectIndex(SIMON_ANI_SITTING);
				}
				else
				{
					if (isAttacking == true)
					{
						if (index < SIMON_ANI_STANDING_ATTACKING_BEGIN || index > SIMON_ANI_STANDING_ATTACKING_END)
						{
							sprite->SelectIndex(SIMON_ANI_STANDING_ATTACKING_BEGIN);
						}
						else
						{
							sprite->Update(dt); 
						}
					}
					else
					{
						if (isWalking == true) // đang di chuyển
						{
							if (isJumping == false) // ko nhảy
							{
								if (index < SIMON_ANI_WALKING_BEGIN || index > SIMON_ANI_WALKING_END)
									sprite->SelectIndex(SIMON_ANI_WALKING_BEGIN);

								sprite->Update(dt); 
							}
							else
							{
								sprite->SelectIndex(SIMON_ANI_JUMPING);
							}
						}
						else
						{
							if (isJumping == true) 
							{
								sprite->SelectIndex(SIMON_ANI_JUMPING);
							}
							else
							{
								sprite->SelectIndex(SiMON_ANI_IDLE);		

							}
						}
					}
				}
			}
		}
	}
				
	CGameObject::Update(dt);  

	if (isOnStair == false)
	{
		if (isJumping)
		{
			dx = vx * dt;
			dy = vy * dt;
			vy += SIMON_GRAVITY_JUMPING * dt;//dt;
		}
		else
		{
			if (isEnemyHit)
			{
				vy += 0.001f * dt;
			}
			else vy += SIMON_GRAVITY * dt;// Simple fall down
		}
	}
	else
	{
		this->dt = dt;
		dx = vx * 16;
		dy = vy * 16;
	}

	if (isProcessingOnStair == 3)
	{
		isProcessingOnStair = 0;

		vx = 0;
		vy = 0;

		isWalking = false;
	}

	if (!isOnStair)
	{
		if (!isAutoGo)
			CollisionWithBrick(coObjects); 
		else
		{
			x += dx;
		}
	}
	
	if (isOnStair)
		CollisionWithExitStair(coObjects);

	CollisionWithEnemy(coObjects);

	if (Data::GetInstance()->scene >= 1)
	{
		mainWeapon->SetPosition(this->x, this->y);
		mainWeapon->SetSpeed(vx, vy); 
		mainWeapon->UpdatePositionFitSimon();
	}

	if (isAutoGo)
	{
		if (abs(x - x_root) >= autoGo_dx)
		{
			x = x - (abs(x - x_root) - autoGo_dx);
			RestoreBackupAutoGoX();
			isAutoGo = false;
		}
	}

	if (!isDeadth && Data::GetInstance()->scene >= 2)
	{
		simonDeath->Reset();
		simonDeath->ResetTime();
		simonDeath->SelectIndex(0);
	}
}

void Simon::Render(Camera* camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Translate(x, y);

	// render simon
	int res = rand() % (255 - 1 + 1) + 1;
	//DebugOut(L"[INFO] res: %d\n", res);
	int alpha;
	alpha = (isUntouchable ? res : 255);
	
	if (isDeadth)
	{
		if (nx == -1)
			simonDeath->Draw((int)pos.x, (int)pos.y, 255);
		else
			simonDeath->DrawFlipX((int)pos.x, (int)pos.y, 255);
	}
	else
	{
		if (this->GetFreeze() == true)
		{
			if (nx == -1)
				sprite->DrawChangeColor((int)pos.x, (int)pos.y, alpha);
			else
				sprite->DrawChangeColorFlipX((int)pos.x, (int)pos.y, alpha);
		}
		else
		{
			if (sprite->GetIndex() != 8)
			{
				if (x + texture->FrameWidth >= 1378.0f && Data::GetInstance()->scene == 1)
				{
					if (nx == -1)
						sprite->Draw((int)pos.x, (int)pos.y, alpha);
					else
					{
						if ( x <= 1490.0f)
							sprite->DrawFlipXS((int)pos.x, (int)pos.y, (int)(abs(x + (float)(texture->FrameWidth) - 1378.0f)), 1, alpha);
						else sprite->DrawFlipX((int)pos.x, (int)pos.y, alpha);
					}
				}
				else
				{
					if (nx == -1)
						sprite->Draw((int)pos.x, (int)pos.y, alpha);
					else
						sprite->DrawFlipX((int)pos.x, (int)pos.y, alpha);
				}
			}
			else
			{
				if (nx == 1)
					sprite->Draw((int)pos.x, (int)pos.y, alpha);
				else
					sprite->DrawFlipX((int)pos.x, (int)pos.y, alpha);
			}
		}
	}
	
	if (Data::GetInstance()->scene >= 1)
	{
		if (!mainWeapon->GetFinish())
			mainWeapon->Render(camera); 

		if (subWeapon != NULL && !subWeapon->GetFinish())
			subWeapon->Render(camera); 
	}
}

void Simon::AutoGo(float _autoGo_nx, int _nx_last, float _autoGo_dx, float _autoGo_vx)
{
	CGameObject::AutoGo(_autoGo_nx, _nx_last,_autoGo_dx, _autoGo_vx);

	if (Data::GetInstance()->scene == 2)
	{
		isOnStair_Backup = isOnStair;
		isProcessingOnStair_Backup = isProcessingOnStair;
		nx_stair_Backup = nx_stair;
		isStairUp_Backup = isStairUp;

		isOnStair = 0;
		isProcessingOnStair = 0;
	}

	isWalking_Backup = isWalking;
	isJumping_Backup = isJumping;
	isSitting_Backup = isSitting;
	isAttacking_Backup = isAttacking;
	
	nx = (int)_autoGo_nx;
	vx = _autoGo_vx * _autoGo_nx;
	this->nx_AfterGo = _nx_last;

	isWalking = 1;
	isJumping = 0;
	isSitting = 0;
	isAttacking = 0;
}

void Simon::Left()
{
	if (isOnStair == true)
		return;

	nx = -1;
}

void Simon::Right()
{
	if (isOnStair == true)
		return;
	nx = 1; 
}

void Simon::Go()
{
	if (isOnStair == true)
	{
		//isWalking = 1;
		return;
	}

	if (isAttacking == true)
	{
		return;
	}

	vx = SIMON_WALKING_SPEED * nx;
	isWalking = 1;
}

void Simon::Sit()
{
	if (isOnStair == true)
		return;

	vx = 0;
	isWalking = 0;

	if (isSitting == false) 
		y = y + 16; 

	isSitting = true;
}

void Simon::ResetSit()
{
	if (isSitting == true) 
	{
		isSitting = 0; 
		y = y - 25;
	}
}


void Simon::Jump()
{
	if (isJumping == true)
		return;

	if (isOnStair == true)
		return;

	if (isSitting == true)
		return;

	if (isAttacking == true)
		return;

	if (isEnemyHit)
		return;

	vy =- SIMON_VJUMP;
	isJumping = true;
}

void Simon::Stop()
{
	if (isAttacking == true)
		return;

	if (isOnStair == true)
		return;

	if (isEnemyHit)
		return;

	vx = 0;
	
	isWalking = 0;
	if (isSitting == true) 
	{
		isSitting = 0; 
		y = y - 25; 
	}
}

void Simon::SetEnemyHit(LPCOLLISIONEVENT e)
{
	if (isEnemyHit == true)
		return;

	if (e->nx == 0 && e->ny == 0) // ko có va chạm
		return;

	// dừng mọi action
	isWalking = 0;
	isAttacking = 0;
	isJumping = 0;

	if (isSitting == true) // nếu simon đang ngồi
	{
		isSitting = 0; // hủy trạng thái ngồi
		y = y - 18; // kéo simon lên
	}

	if (!isOnStair && !isAutoGo)
	{
		if (e->nx != 0)
		{
			vx = 0.11f * e->nx;
			vy = -0.2f;
			isEnemyHit = true;
		}

		if (e->ny != 0)
		{
			//vx = 0.09f * e->nx * 2;
			vy = -0.2f;
			isEnemyHit = true;
		}
	}
	else
	{
		isWalking = 1;
	}

	StartUntouchable(); 

	mainWeapon->SetFinish(true);
	LoseHP(2); 
	Sound::GetInstance()->Play(eSound::sWasEnemyHit);
}

void Simon::CollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == def_ID::BRICK)
			list_Brick.push_back(coObjects->at(i));

	CalcPotentialCollisions(&list_Brick, coEvents); // Lấy danh sách các va chạm

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny; // cái này của brick
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (ny == -1)
			y += min_ty * dy + ny * 0.4f;
		else
			y += dy;

		if (ny == -1)
		{
			vy = 0.1f;
			dy = vy * dt;

			if (isJumping)
			{
				isJumping = false;
				y = y - 25;
			}
		}

		if (nx != 0 || ny <= 0)
		{
			isEnemyHit = 0;
			beforeDeath = 1;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Simon::CollisionWithEnemy(vector<LPGAMEOBJECT>* listEnemy)
{
	if (isUntouchable)
	{
		if (GetTickCount() - startUntouchable > SIMON_UNTOUCHABLE_TIME)
		{
			startUntouchable = 0;
			isUntouchable = false;
		}
	}

	if (!isUntouchable) // mode va chạm
	{
		for (UINT i = 0; i < listEnemy->size(); i++)
		{
			CGameObject * enemy = dynamic_cast<CGameObject *> (listEnemy->at(i));
			
			if (enemy->GetType() == def_ID::GHOST || enemy->GetType() == def_ID::PANTHER || enemy->GetType() == def_ID::BAT ||
				enemy->GetType() == def_ID::FISHMEN || enemy->GetType() == def_ID::BOSS)
			{
				if (enemy->GetLife() > 0) // còn sống
				{
					if (isCollitionAll(enemy))
					{
						LPCOLLISIONEVENT e = isCollitionAllReturnE(enemy);
						SetEnemyHit(e);
						return;
					}
				}
			}
		}
	}
}

void Simon::CollisionWithItem(vector<Items*> * listItem)
{
	if (listItem->size() == 0)
		return;

	for (UINT i = 0; i < listItem->size(); i++)
		if (listItem->at(i)->GetFinish() == false && !listItem->at(i)->isWaiting())
		{
			if (isCollisionWithItem(listItem->at(i))) 
			{
				listItem->at(i)->SetFinish(true);
				switch (listItem->at(i)->GetType())
				{
				case def_ID::BIGHEART:
				{
					SetHeartCollect(GetHeartCollect() + 5);
					sound->Play(eSound::sCollectItem); // sound collect item
					break;
				}
				case def_ID::SMALLHEART:
				{
					SetHeartCollect(GetHeartCollect() + 1);
					sound->Play(eSound::sCollectItem);
					break;
				}
				case def_ID::UPGRADEMORNINGSTAR:
				{
					MorningStar * objMorningStar = dynamic_cast<MorningStar*>(mainWeapon);
					objMorningStar->UpgradeLevel(); 
					SetFreeze(true);
					sound->Play(eSound::sCollectWeapon);
					break;
				}
				case def_ID::iDAGGER:
				{
					SAFE_DELETE(subWeapon);
					this->subWeapon = new Dagger();
					sound->Play(eSound::sCollectWeapon);
					break;
				}
				case def_ID::MONNEYBAG:
				{
					sound->Play(eSound::sCollectItem);
					SetPoint(1000);
					break;
				}
				case def_ID::iHOLYWATER:
				{
					SAFE_DELETE(subWeapon);
					subWeapon = new HolyWater(camera);
					sound->Play(eSound::sCollectWeapon);
					break;
				}
				case def_ID::POTROAST:
				{
					sound->Play(eSound::sCollectWeapon);
					SetHP(min(GetHP() + 6, 16)); // tăng 6 đơn vị máu
					break;
				}
				case def_ID::iAXE:
				{
					SAFE_DELETE(subWeapon);
					subWeapon = new Axe(camera);
					sound->Play(eSound::sCollectWeapon);
					break;
				}
				case def_ID::MAGICCRYSTAL:
				{
					Data::GetInstance()->passBoss = 1;
					break;
				}
				default:
					break;
				}
			}
		}
}

void Simon::CollisionWithExitStair(vector<LPGAMEOBJECT> *coObjects)
{
	if (isStairUp == -1)
	{
		int checkCollision = 0;

		for (UINT i = 0; i < (*coObjects).size(); i++)
			if ((*coObjects)[i]->GetType() == def_ID::BOTTOMSTAIR) // nếu là object ở dưới
			{
				if (this->isCollitionAll((*coObjects)[i]))
				{
					checkCollision++;
					break;
				}
			}

		if (checkCollision > 0) // có va chạm với bottom
		{
			DebugOut(L"VA cham bottom ne\n");
			//for (UINT j = 0; j < coObjects->size(); j++)
			//{
			//	if (coObjects->at(j)->GetType() == def_ID::BRICK)
			//	{
			//		if (isCollitionAll(coObjects->at(j)))
			//		{
			//				DebugOut(L"VA cham brick ne\n");
			//				vx = 0;
			//				vy = 0;
			//				isOnStair = false; // đã chạm đất
			//				isWalking = false;
			//				isProcessingOnStair = 0;
			//				return;
			//		}
			//	}
			//}
			vx = 0;
			vy = 0;
			isOnStair = false; // đã chạm đất
			isWalking = false;
			isProcessingOnStair = 0;
			return;
		}
	}

	if (isStairUp == 1) // đang đi lên
	{
		int checkCollision = 0;

		for (UINT i = 0; i < (*coObjects).size(); i++)
			if ((*coObjects)[i]->GetType() == def_ID::TOPSTAIR) // nếu là object ở trên
			{
				if (this->isCollitionAll((*coObjects)[i])) // có va chạm với top stair
				{
					checkCollision++;
					break;
				}
			}

		if (checkCollision > 0) // có va chạm với top, và nó đang đi lên
		{
			float backupVy = vy;

			y = y - 50; // kéo simon lên cao, để tạo va chạm giả xuống mặt đất. tính thời gian tiếp đất
			vy = 15; // vận tốc kéo xuống lớn
			dy = vy * dt; // cập nhật lại dy
			//y = y - 50; // push lên (tránh lỗi)
			//vy = 999; // kéo về ngay lập 
			//dy = vy * dt;
			//
			//vx = 0;
			//isOnStair = false; // kết thúc việc đang trên cầu thang
			//isWalking = false;
			//isProcessingOnStair = 0;
			//////vy = backupVy;
			////dy = vy * dt; // cập nhật lại dy
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;
			coEvents.clear();
			vector<LPGAMEOBJECT> list_Brick;
			list_Brick.clear();

			for (UINT i = 0; i < coObjects->size(); i++)
				if (coObjects->at(i)->GetType() == def_ID::BRICK)
					list_Brick.push_back(coObjects->at(i));

			CalcPotentialCollisions(&list_Brick, coEvents);

			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else
			{
				//DebugOut(L"dx2 %f\n", x);
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
				//DebugOut(L"dy %f\n", dy);
				if (nx != 0 || ny != 0)
				{
					vx = 0;
					vy = 0;
					isOnStair = false; // kết thúc việc đang trên cầu thang
					isWalking = false;
					isProcessingOnStair = 0;
				}
			}

			for (UINT i = 0; i < coEvents.size(); i++)
				delete coEvents[i];

			vy = backupVy;
			dy = vy * dt; // cập nhật lại dy

			return; // ko cần xét tiếp
		}
	}

	x += dx;
	y += dy;
}

void Simon::Attack(Weapons * weapon)
{
	if (isAttacking == true && dynamic_cast<MorningStar*>(weapon) != NULL) // đang tấn công mà là roi thì bỏ qua
		return;

	isAttacking = true; 
	
	 weapon->Create(this->x, this->y, this->nx);
}

void Simon::SetHeartCollect(int HeartP)
{
	HeartPoint = HeartP;
}

int Simon::GetHeartCollect()
{
	return HeartPoint;
}

void Simon::SetLife(int _life)
{
	life = _life;
}

int Simon::GetPoint()
{
	return point;
}

void Simon::SetPoint(int _point)
{
	point = _point;
}

bool Simon::isCollisionWithItem(Items * item)
{
	if (item->GetFinish() == true)
		return false;

	return isCollitionAll(item);
}

bool Simon::GetFreeze()
{
	return isFreeze;
}

void Simon::SetFreeze(bool _isFreeze)
{
	isFreeze = _isFreeze;
	TimeFreeze = 0; // thời gian đã đóng băng
}

void Simon::UpdateFreeze(DWORD dt)
{
	if (TimeFreeze + dt >= TIME_FREEZE_MAX)
	{
		SetFreeze(false); // kết thúc đóng băng
	}
	else
		TimeFreeze += dt;
}

bool Simon::LoseLife()
{
	if (life - 1 < 0)
		return false;
	hp = 2;
	life = life - 1;
	HeartPoint = 5;
	
	//SAFE_DELETE(mainWeapon);
	SAFE_DELETE(subWeapon);
	mainWeapon = new MorningStar();
	subWeapon = NULL;

	isAttacking = 0;
	isJumping = 0;
	isFreeze = 0;
	isSitting = 0;
	isWalking = 0;
	isEnemyHit = 0;

	nx = 1;

	x = PositionBackup.x;
	y = PositionBackup.y;

	return true;
}

void Simon::SetPositionBackup(float X, float Y)
{
	PositionBackup = D3DXVECTOR2(X, Y);
}

void Simon::GoUpStair()
{
	isOnStair = true;
	vx = nx * 0.5f;
	vy = -1 * 0.5f;
}

void Simon::StartUntouchable()
{
	isUntouchable = true; // bật mode k va chạm
	startUntouchable = GetTickCount();
}

void Simon::SetDeadth()
{
	isDeadth = true;
	TimeWaitedAfterDeath = 0;

	ResetSit();
	vx = 0;
	isWalking = 0;
	isOnStair = 0;
	Stop();
}

void Simon::RestoreBackupAutoGoX()
{
	isWalking = isWalking_Backup;
	isJumping = isJumping_Backup;
	isSitting = isSitting_Backup;
	isAttacking = isAttacking_Backup;

	if (Data::GetInstance()->scene == 2)
	{
		isOnStair = isOnStair_Backup;
		isProcessingOnStair = isProcessingOnStair_Backup;
		nx_stair = nx_stair_Backup;
		isStairUp = isStairUp_Backup;
	}

	nx = nx_AfterGo; // set hướng sau khi đi

	isWalking = 0; // tắt trạng thái đang đi
	isAutoGoX = 0; // tắt trạng thái auto

	vx = 0;
	vy = 0;
	// đi xong thì cho simon đứng yên
}

void Simon::ProcessingOnStair()
{
	isProcessingOnStair++;
	if (nx == 1 && isStairUp == 1)
	{
		x -= (HeightStair - 16.0f);
		y += (HeightStair - 16.0f);
	}
	if (nx == -1 && isStairUp == 1)
	{
		x += (HeightStair - 16.0f);
		y += (HeightStair - 16.0f);
	}

	if (nx == 1 && isStairUp == -1)
	{
		x -= (HeightStair - 16.0f);
		y -= (HeightStair - 16.0f);
	}
	if (nx == -1 && isStairUp == -1)
	{
		x += (HeightStair - 16.0f);
		y -= (HeightStair - 16.0f);
	}

	HeightStair = 0;
}
