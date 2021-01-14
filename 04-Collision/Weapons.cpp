#include "Weapons.h"


Weapons::Weapons()
{
	isFinish = 1;
	isSend = 0;
}

Weapons::~Weapons()
{
}

void Weapons::Create(float X, float Y, int _nx)
{
	this->x = X;
	this->y = Y;
	this->nx = _nx;
	isFinish = 0;
	isSend = 0;
}

void Weapons::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
}

void Weapons::Render(Camera * camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
	
	//DebugOut(L"Weapons: index = %d \n", sprite->GetIndex());
	D3DXVECTOR2 pos = camera->Translate(x, y);
	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);
}

void Weapons::SetPosition(float X, float Y)
{
	this->x = X;
	this->y = Y;
}

void Weapons::UpdatePositionFitSimon()
{
}

bool Weapons::isCollision(CGameObject* obj)
{
	if (isFinish)
		return false;

	CGameObject *gameObj = dynamic_cast<CGameObject*>(obj);
	if (gameObj->GetLife() <= 0)
		return false;

	return isCollitionAll(obj);
}

void Weapons::CheckCollision(vector<LPGAMEOBJECT> *listObj)
{
	if (this != NULL && GetFinish() == false) // roi đang đánh
	{
		for (UINT i = 0; i < listObj->size(); i++)
		{
			CGameObject *gameObj = dynamic_cast<CGameObject*>(listObj->at(i));
			if (isCollision(gameObj) == true)
			{
				switch (gameObj->GetType())
				{
				case def_ID::BIGCANDLE:
				{
					gameObj->LoseLife(1);
					break;
				}
				case def_ID::SMALLCANDLE:
				{
					gameObj->LoseLife(1);
					break;
				}
				case def_ID::BRICK:
				{
					if (gameObj->GetObj_id() == 39 || gameObj->GetObj_id() == 40 
						|| gameObj->GetObj_id() == 51 || gameObj->GetObj_id() == 72)
						gameObj->LoseLife(1);
					break;
				}
				case def_ID::GHOST:
				{
					DebugOut(L"[Hit ghost]\n");
					gameObj->LoseLife(1);
					break;
				}
				case def_ID::PANTHER:
				{
					gameObj->LoseLife(1);
					break;
				}
				case def_ID::BAT:
				{
					gameObj->LoseLife(1);
					break;
				}
				case def_ID::FISHMEN:
				{
					gameObj->LoseLife(1);
					break;
				}
				case def_ID::BOSS:
				{
					gameObj->LoseHP(2);
					if (gameObj->GetHP() == 0)
						gameObj->LoseLife(1);
					Data::GetInstance()->hpBoss -= 2;
					break;
				}
				default:
					break;
				}

				isSend = true;
			}
		}
	}
}

bool Weapons::GetFinish()
{
	return isFinish;
}

void Weapons::SetFinish(bool _isFinish)
{
	isFinish = _isFinish;
}

bool Weapons::GetSend()
{
	return isSend;
}

void Weapons::SetSend(bool _isSend)
{
	isSend = _isSend;
}
