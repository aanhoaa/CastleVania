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
		left = x;
		top = y; // fixed y (sit() updated y)
		right = x + SIMON_BBOX_WIDTH;
		bottom = y + SIMON_BBOX_SITTING_HEIGHT;
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
	vy = 0;

	//vy += SIMON_GRAVITY * dt;// Simple fall down



	x += dx;
	y += dy;



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
	if (isSitting == false) // nếu trước đó simon chưa ngồi
		y = y + 16; // kéo simon xuống

	isSitting = 1;
}

void Simon::Stop()
{
	vx = 0;
	isWalking = 0;
	if (isSitting == true) // nếu simon đang ngồi
	{
		isSitting = 0; // hủy trạng thái ngồi
		y = y - 16; // kéo simon lên
	}

}
