﻿#include "MorningStar.h"


MorningStar::MorningStar()
{
	texture = new Load_img_file("Resources\\weapon\\morningstar.png", 4, 3, 12, 0);
	sprite = new Load_resources(texture, 100);
	this->level = 0;
	obj_type = def_ID::MORNINGSTAR;
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

	if (level == 1)
	{
		sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL1_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
	}
}

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
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

	if (level == 1)
	{
		if (MORNINGSTAR_ANI_LEVEL1_START <= sprite->GetIndex() && sprite->GetIndex() < MORNINGSTAR_ANI_LEVEL1_END)
		{
			sprite->Update(dt);
		}
		else
		{
			sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL1_START);
		}
	}
}

void MorningStar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	//if (level == 0)
	{
		if (sprite->GetIndex() == 2 || sprite->GetIndex() == 5) { // sprite simon đánh thì mới set boundingbox
			if (nx == 1)
			{
				left = x + (sprite->GetIndex() >= 2) * 80; // đánh roi thì left = x + 50
				top = y + 15;
				// Là 2 frame đầu thì right = x - 110
				right = x + texture->FrameWidth
					- 30 - (sprite->GetIndex() == 0 || sprite->GetIndex() == 1) * 80;
				bottom = y + texture->FrameHeight - 15;
			}
			else {
				left = x + 30 + (sprite->GetIndex() == 0 || sprite->GetIndex() == 1) * 80;
				top = y + 15;
				right = x + texture->FrameWidth - (sprite->GetIndex() >= 2) * 80;
				bottom = y + texture->FrameHeight - 15;
			}
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

void MorningStar::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>* listObj)
{
	RECT object, other;
	float l_obj, t_obj, r_obj, b_obj;
	float l_oth, t_oth, r_oth, b_oth;

	GetBoundingBox(l_obj, t_obj, r_obj, b_obj);
	object.left = (int)l_obj;
	object.top = (int)t_obj;
	object.right = (int)r_obj;
	object.bottom = (int)b_obj;

	for (int i = 0; i < listObj->size(); i++)
		if (listObj->at(i)->GetType() == def_ID::CANDLE)
		{
			CGameObject *obj = dynamic_cast<CGameObject*>(listObj->at(i));
			if (obj->GetLife() > 0 )
			{
				listObj->at(i)->GetBoundingBox(l_oth, t_oth, r_oth, b_oth);
				other.left = (int)l_oth;
				other.top = (int)t_oth;
				other.right = (int)r_oth;
				other.bottom = (int)b_oth;

				if (CGame::GetInstance()->CollisionAABB(object, other))
				{
					listObj->at(i)->LoseLife(1);
					Data::GetInstance()->ListItem.push_back(Weapons::GetItem(obj->id, obj->GetType(), listObj->at(i)->x, listObj->at(i)->y));
				}
			}
		}
}

void MorningStar::UpgradeLevel()
{
	if (level >= 2)
		return;
	level++;
}