#include "MorningStar.h"


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

	switch (level)
	{
	case 0:
			sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL0_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
			break;
	case 1:
		sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL1_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
		break;
	case 2:
		sprite->SelectIndex(MORNINGSTAR_ANI_LEVEL2_START - 1); // đặt sai index cho hàm update cập nhật ngay frame đầu
		break;
	}
}

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	this->dx = vx * dt;
	this->dy = vy * dt;

	// index 1 trong 3 index 3-7-11 thì dừng đánh (sprite roi cuối)
	//DebugOut(L"[INFO] Level: %d\n", level);
	isFinish = (sprite->GetIndex() == 3 && level == 0) + (sprite->GetIndex() == 7 && level == 1) + (sprite->GetIndex() == 11 && level == 2);
	
	int StartFrame = MORNINGSTAR_ANI_LEVEL0_START + 4 * level; // ánh xạ chỉ số frame bằng level thay vì ifelse 
	int EndFrame = MORNINGSTAR_ANI_LEVEL0_END + 4 * level;

	if (StartFrame <= sprite->GetIndex() && sprite->GetIndex() < EndFrame)
		sprite->Update(dt);
	else
		sprite->SelectIndex(StartFrame);
}

void MorningStar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
		switch (level)
		{
		case 0:
		case 1:
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
			break;
		case 2:
			//if (sprite->GetIndex() == 2 || sprite->GetIndex() == 5) { // sprite simon đánh thì mới set boundingbox
			if (nx == 1)
			{
				left = x + (sprite->GetIndex() >= 2) * 20; // đánh roi thì left = x + 50
				top = y + 15;
				// Là 2 frame đầu thì right = x - 110
				right = x + texture->FrameWidth
					+ (sprite->GetIndex() == 0 || sprite->GetIndex() == 1) * 100;
				bottom = y + texture->FrameHeight - 15;
			}
			else {
				left = x + 30 + (sprite->GetIndex() == 0 || sprite->GetIndex() == 1) * 80;
				top = y + 15;
				right = x + texture->FrameWidth - (sprite->GetIndex() >= 2) * 80;
				bottom = y + texture->FrameHeight - 15;
			}
			//}
			break;
			//case 2:
		default:
			break;
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

void MorningStar::UpgradeLevel()
{
	if (level >= 2)
		return;
	level++;
}

bool MorningStar::isCollision(CGameObject * obj)
{
	if (level == 0 && sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_START || sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL0_START + 1)
		return false; // frame đầu và frame chuẩn bị đánh thì ko xét va chạm

	if (level == 1 && sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL1_START || sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL1_START + 1)
		return false; // frame đầu và frame chuẩn bị đánh thì ko xét va chạm

	if (level == 2 && sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL2_START || sprite->GetIndex() == MORNINGSTAR_ANI_LEVEL2_START + 1)
		return false; // frame đầu và frame chuẩn bị đánh thì ko xét va chạm

	CGameObject *Obj = dynamic_cast<CGameObject*>(obj);
	if (Obj->GetLife() <= 0) // vật này die rồi thì ko va chạm
		return false;
	
	return isCollitionAll(Obj);
}

void MorningStar::RenderItem(int X, int Y)
{
}