#include "Simon.h"
#include "debug.h"


Simon::Simon()
{
	texture = new Load_img_file("Resources\\simon.png", 8, 3, 24, SHOWBOX_PINK);
	sprite = new Load_resources(texture, 200);
	obj_type = def_ID::SIMON;

	// states have ready
	isWalking = false; 
	isJumping = false;
	isSitting = false;
	isAttacking = false;
	hp = 16; // 16 hp
	life = 5; // 5 mạng
	HeartPoint = 5;
	point = 0;

	mainWeapon = new MorningStar();
	subWeapon = NULL;
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
		bottom = y + SIMON_BBOX_SITTING_HEIGHT - 3;
	}
	else
	{
		left = x - 12;
		top = y - 1;
		right = x + SIMON_BBOX_WIDTH - 15;
		bottom = y + SIMON_BBOX_HEIGHT - 3;
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// không cho S đi khỏi cam
	if (x < 0) // khi xuất hiện sang trái sẽ ngăn lại
			x = 0.0f;
	if (x + SIMON_BBOX_WIDTH > MapWidth)
			x = (float)(MapWidth - SIMON_BBOX_WIDTH); // phải tương tự
	//DebugOut(L"[INFO] Y: %.6f\n", y);
	/* Update về sprite */

	int index = sprite->GetIndex();

	if (isAttacking == true)
	{
		if (mainWeapon->GetFinish() == false) // nếu MorningStar đang đánh
		{
			mainWeapon->Update(dt);
			if (mainWeapon->GetFinish() == true)
				isAttacking = false;
		}
		else
		{
			if (subWeapon != NULL)
			{
				isAttacking = !(SIMON_ANI_SITTING_ATTACKING_END == index || SIMON_ANI_STANDING_ATTACKING_END == index);
			}
		}
	}

	if (subWeapon != NULL && subWeapon->GetFinish() == false)
	{
		subWeapon->Update(dt);
	}

	if (isSitting == true)
	{
		if (isAttacking == true) // tấn công
		{
			if (index < SIMON_ANI_SITTING_ATTACKING_BEGIN || index >= SIMON_ANI_SITTING_ATTACKING_END)
			{
				sprite->SelectIndex(SIMON_ANI_SITTING_ATTACKING_BEGIN);
			}
			else
			{
				//cập nhật frame mới
				sprite->Update(dt); // dt này được cập nhật khi gọi update; 
			}
		}
		else
			sprite->SelectIndex(SIMON_ANI_SITTING);
	}
	else
		if (isAttacking == true)
		{
			if (index < SIMON_ANI_STANDING_ATTACKING_BEGIN || index >= SIMON_ANI_STANDING_ATTACKING_END)
			{
				sprite->SelectIndex(SIMON_ANI_STANDING_ATTACKING_BEGIN);
			}
			else
			{
				//cập nhật frame mới
				sprite->Update(dt); // dt này được cập nhật khi gọi update; 
			}
		}
		else
		if (isWalking == true) // đang di chuyển
		{
			if (isJumping == false) // ko nhảy
			{
				if (index < SIMON_ANI_WALKING_BEGIN || index >= SIMON_ANI_WALKING_END)
					sprite->SelectIndex(SIMON_ANI_WALKING_BEGIN);

				//cập nhật frame mới
				sprite->Update(dt); // dt này được cập nhật khi gọi update; 
			}
			else
			{
				sprite->SelectIndex(SIMON_ANI_JUMPING);
			}
		}
		else
		{
			if (isJumping == true) // đang nhảy không ấn phím qua lại
			{
				sprite->SelectIndex(SIMON_ANI_JUMPING);
			}
			else
			{
				sprite->SelectIndex(SiMON_ANI_IDLE);		// k làm gì cả => đứng yên
			}
		}

	/* Update về sprite */


	/* Xử lý va chạm*/

	CGameObject::Update  (dt);  	// Calculate dx, dy 

	vy += SIMON_GRAVITY * dt; 

	if (isJumping && isWalking)
	{
		dx = vx * dt * 1.5f;
	}

	vector<LPGAMEOBJECT> coObjects_Brick; // obj brick
	coObjects_Brick.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == def_ID::BRICK)
				coObjects_Brick.push_back(coObjects->at(i)); // lấy các obj là brick va cham voi simon (trong cam)

	CollisionWithBrick(&coObjects_Brick); // check Collision and update x, y for simon

	mainWeapon->SetPosition(this->x, this->y);
	mainWeapon->SetSpeed(vx, vy); // set vận tốc để kt va chạm
	mainWeapon->UpdatePositionFitSimon();
/*
	if (isAttacking == true) //  update postion roi sau vì kiểm tra va chạm bên trên có thể khiến x,y của simon thay đổi, gây lệch vị trí roi với simon
	{
		if (mainWeapon->GetFinish() == false) // nếu MorningStar chưa hoặc đang đánh
		{
			mainWeapon->SetPosition(this->x, this->y);
			mainWeapon->UpdatePositionFitSimon();
			mainWeapon->Update(dt);

			if (mainWeapon->GetFinish() == true)  // đánh xong
				isAttacking = false;
		}	
		else
		{
			if (subWeapon != NULL)
			{
				isAttacking = !(SIMON_ANI_SITTING_ATTACKING_END + 1 == sprite->GetIndex() || SIMON_ANI_STANDING_ATTACKING_END + 1 == sprite->GetIndex());
			}
		}
	}
	*/
}

void Simon::Render(Camera* camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	D3DXVECTOR2 pos = camera->Translate(x, y);
	//DebugOut(L"[INFO] y_s: %.6f\n", y);
	
	// render simon
	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);

	// render weapons
	if (mainWeapon->GetFinish() == false)
		mainWeapon->Render(camera); // không cần xét hướng, vì Draw của lớp Weapon đã xét khi vẽ

	if (subWeapon != NULL && subWeapon->GetFinish() == false)
		subWeapon->Render(camera); // không cần xét hướng, vì Draw của lớp Weapon đã xét khi vẽ
}

void Simon::Left()
{
	nx = -1;
}

void Simon::Right()
{
	nx = 1; // quay qua phải
}

void Simon::Go()
{
	if (isAttacking == true)
	{
		return;
	}
	vx = SIMON_WALKING_SPEED * nx;
	isWalking = 1;
}

void Simon::Sit()
{
	vx = 0;
	isWalking = 0;

	if (isSitting == false) // nếu trước đó simon chưa ngồi
		y = y + 16; // kéo simon xuống

	isSitting = 1;
}

void Simon::Jump()
{
	if (isJumping == true)
		return;

	if (isSitting == true)
		return;

	if (isAttacking == true)
		return;

	vy -= SIMON_VJUMP;
	isJumping = true;
}

void Simon::Stop()
{
	if (isAttacking == true)
		return;

	vx = 0;

	/*if (vx != 0)
		vx -= dt * SIMON_GRAVITY*0.1*nx;

	nx != 0 ? (vx != 0 ? vx = 0 : vx = vx) : nx;*/

	isWalking = 0;
	if (isSitting == true) // nếu simon đang ngồi
	{
		isSitting = 0; // hủy trạng thái ngồi
		y = y - 25; // kéo simon lên
	}
}

void Simon::CollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents); // Lấy danh sách các va chạm

												  // No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny; // cái này của brick

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f; // ny = -1 thì hướng từ trên xuống....

		if (nx != 0)
			vx = 0; // nếu mà nx, ny <>0  thì nó va chạm rồi. mà chạm rồi thì dừng vận tốc cho nó đừng chạy nữa

		if (ny != 0)
		{
			vy = 0;
			isJumping = false; // kết thúc nhảy
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Simon::Attack(Weapons * weapon)
{
	if (isAttacking == true && dynamic_cast<MorningStar*>(weapon) != NULL) // đang tấn công mà là roi thì bỏ qua
		return;

	isAttacking = true; // set trang thái tấn công
	weapon->Create(this->x, this->y, this->nx); // set vị trí weapon theo simon
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

	//float l, t, r, b;
	//float l1, t1, r1, b1;
	//this->GetBoundingBox(l, t, r, b);  // lấy BBOX của simon

	//item->GetBoundingBox(l1, t1, r1, b1);
	//if (CGame::GetInstance()->CollisionAABB(l, t, r, b, l1, t1, r1, b1) == true)
	//{
	//	return true; // check with AABB
	//}

	return isCollitionAll(item);
}