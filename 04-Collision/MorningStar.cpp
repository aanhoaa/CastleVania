#include "MorningStar.h"



MorningStar::MorningStar()
{
	texture = new Load_img_file("Resources\\weapon\\morningstar.png", 4, 3, 12, 0);
	sprite = new Load_resources(texture, 100);
	this->level = 0;
}


MorningStar::~MorningStar()
{
}

void MorningStar::Create(float simon_X, float simon_Y, int simon_nx)
{
	Weapons::Create(simon_X, simon_Y, simon_nx);

	UpdatePositionFitSimon();

	if (level == 0)
	{
		sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL0_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
	}
}

void MorningStar::Update(int dt)
{
	//if (isFinish == false)
	//{
	//	if (level == 0 && sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_END) // nếu nó chạy frame cuối rồi
	//	{
	//		isFinish = true;
	//		return;
	//	} 
	//}

	isFinish = (sprite->GetIndex() == 3) + (sprite->GetIndex() == 7) + (sprite->GetIndex() == 11); // index 1 trong 3 index 3-7-11 thì dừng đánh (sprite roi cuối)
	//DebugOut(L"[INFO] Finish: %d\n", isFinish);

	if (level == 0)
	{
		if (MORNINGSTAR_ANI_LEVEL0_START <= sprite->GetIndex() && sprite->GetIndex() < MORNINGSTAR_ANI_LEVEL0_END)
		{
			sprite->Update(dt);
		}
		else
		{
			sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL0_START); // ban đầu sẽ vào đây từ hàm set sprite
		}
	}
}

void MorningStar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (level == 0)
	{
		if (nx == 1)
		{
			left = x + 50;
			top = y + 15;
			right = x + texture->FrameWidth - 30;
			bottom = y + texture->FrameHeight - 15;
		}
		else
		{
			left = x + 30;
			top = y + 15;
			right = x + texture->FrameWidth - 50;
			bottom = y + texture->FrameHeight - 15;
		}
	}
}

void MorningStar::UpdatePositionFitSimon()
{
	if (nx == -1)
	{
		this->x = x - 65;
	}
	else
	{
		this->x = x - 30;
	}
}

