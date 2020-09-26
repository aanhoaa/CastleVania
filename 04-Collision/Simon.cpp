#include "Simon.h"



Simon::Simon()
{
	texture = new Load_img_file("Resources\\simon.png", 8, 3, 24, SHOWBOX_PINK);
	sprite = new Load_resources(texture, 100);
	type_obj = def_ID::SIMON;

	isWalking = 0;
	isJumping = 0;
	isSitting = 0;

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
		right = x + SIMON_BBOX_WIDTH - 17;
		bottom = y + SIMON_BBOX_SITTING_HEIGHT - 3;
	}
	else
	{
		left = x;
		top = y;
		right = x + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_HEIGHT;
	}

}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/* Update về sprite */

	int index = sprite->GetIndex();

	if (isSitting == 1)
	{
		sprite->SelectIndex(SIMON_ANI_SITTING);
	}
	else
		if (isWalking == 1) // đang di chuyển
		{
			if (index < SIMON_ANI_BEGIN_WALKING || index >= SIMON_ANI_END_WALKING)
				sprite->SelectIndex(1);

			//cập nhật frame mới
			sprite->Update(dt); // dt này được cập nhật khi gọi update; 
		}
		else
			sprite->SelectIndex(SiMON_ANI_IDLE);		// SIMON đứng yên


	/* Update về sprite */

	CGameObject::Update(dt);  	// Calculate dx, dy 

	vy += SIMON_GRAVITY * dt;

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
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		//x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		//y += min_ty * dy + ny * 0.4f;

		if (nx != 0)
			vx = 0; // nếu mà nx, ny <>0  thì nó va chạm rồi. mà chạm rồi thì dừng vận tốc cho nó đừng chạy nữa

		if (ny != 0)
			vy = 0;
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}

void Simon::Render()
{
	if (nx == -1)
		sprite->Draw(x, y);
	else
		sprite->DrawFlipX(x, y);
}

void Simon::SetState(int state)
{

	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_WALKING:
		vx = SIMON_WALKING_SPEED;
		break;


	default:
		break;
	}
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
	if (isSitting == true)
		return;
	vy -= SIMON_VJUMP;
	isJumping = true;
}

void Simon::Stop()
{
	if (vx != 0)
		vx -= dt * SIMON_GRAVITY*0.1*nx;
	if (nx == 1 && vx < 0) vx = 0;
	if (nx == -1 && vx > 0) vx = 0;

	isWalking = 0;
	if (isSitting == true) // nếu simon đang ngồi
	{
		isSitting = 0; // hủy trạng thái ngồi
		y = y - 18; // kéo simon lên
	}

}
