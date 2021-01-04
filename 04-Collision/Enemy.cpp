#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//sprite->Update(dt);
	//CGameObject::Update(dt); // lưu dt, cập cập nhật dxdy cho enemy
	
}

void Enemy::Render(Camera * camera)
{
	//sprite->Update(dt);

	/*D3DXVECTOR2 pos = camera->Translate(x, y);
	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);*/
}


/* Ghost*/
Ghost::Ghost(float X, float Y, int _nx)
{
	obj_type = def_ID::GHOST;
	texture = LoadTexture::GetInstance()->GetTexture(GHOST);
	sprite = new Load_resources(texture, 100);

	x = X;
	y = Y;
	this->nx = _nx;
	this->vx = GHOST_SPEED * this->nx;
	life = 1;
}

Ghost::~Ghost()
{
	
}

void Ghost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += GHOST_GRAVITY * dt;

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == def_ID::BRICK)
			listObject_Brick.push_back(coObjects->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm 
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		
		if (ny != 0)
		{
			vy = 0;
			//vx = 0;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	sprite->Update(dt);
}

void Ghost::Render(Camera * camera)
{
	if (life < 1)
		return;
	
	D3DXVECTOR2 pos = camera->Translate(x, y);
	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
	
/*	Panther */

Panther::Panther(float X, float Y, int _nx, float autoGoX_Dx)
{
	obj_type = def_ID::PANTHER;
	life = 1;
	vx = vy = 0;
	nx = _nx;
	x = X;
	y = Y;
	x_root = x;
	autoGo_dx = autoGoX_Dx;

	texture = LoadTexture::GetInstance()->GetTexture(PANTHER);
	sprite = new Load_resources(texture, 200);

	isSitting = 1;
	isRunning = 0;
	isJumping = 0;
	isStart = 0;
	isAutoGo = 0;
}

Panther::Panther(float X, float Y, int _nx, float autoGoX_Dx, float autoGoX_Dx2)
{
	obj_type = def_ID::PANTHER;
	life = 1;
	vx = vy = 0;
	nx = _nx;
	x = X;
	y = Y;
	x_root = x;
	autoGo_dx = autoGoX_Dx;
	autogo = autoGoX_Dx2;

	texture = LoadTexture::GetInstance()->GetTexture(PANTHER);
	sprite = new Load_resources(texture, 200);

	isSitting = 1;
	isRunning = 0;
	isJumping = 0;
	isStart = 0;
	isAutoGo = 0;
}

void Panther::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void Panther::Update(DWORD dt, Simon * simon, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += SIMON_GRAVITY * dt; // Panther simple fall down

	float DistanceLimit = nx == 1 ? 100.0f : 185.0f;

	if (abs(simon->x - (x + texture->FrameWidth)) <= DistanceLimit && isStart == 0)
	{
		isSitting = false;
		Run();
		isStart = 1;
		isAutoGo = 1;
	}

	if (isSitting)
	{
		sprite->SelectIndex(PANTHER_ANI_SITTING);
	}
	else
	{
		if (isRunning)
		{
			if (PANTHER_ANI_RUNNING_BEGIN <= sprite->GetIndex() && sprite->GetIndex() < PANTHER_ANI_RUNNING_END)
			{
				sprite->Update(dt);
			}
			else
				sprite->SelectIndex(PANTHER_ANI_RUNNING_BEGIN);
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetType() == def_ID::BRICK)
			list_Brick.push_back(coObjects->at(i));
	}

	CalcPotentialCollisions(&list_Brick, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, _nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, _nx, ny);
		//x += min_tx * dx + nx * 0.4f;
		x += dx;

		if (ny == -1) // chỉ xét va chạm hướng xuống
			y += min_ty * dy + ny * 0.4f;
		else
			y += dy;

		if (ny == -1)
		{
			vy = 0;
			if (isJumping)
			{
				isJumping = false; // kết thúc nhảy
				
				if (autogo != 0)
				{
					autoGo_dx = autogo;
					autogo = 0;
					x_root = x;
					
					if (x < simon->x) // simon ở bên phải
					{
						nx = 1; // đổi hướng panther qua phải 
					}
					else
					{
						nx = -1; // đổi hướng panther qua trái
					}
					
					Run();
					isAutoGo = true;
				}
				else
				{
					if (x < simon->x) // simon ở bên phải
					{
						nx = 1; // đổi hướng panther qua phải 
					}
					else
					{
						nx = -1; // đổi hướng panther qua trái
					}
					//DebugOut(L"[PANTHER] end auto go X: %d\n", nx);
					Run();
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion


	if (isAutoGo)
	{
		if (abs(x - x_root) >= autoGo_dx)
		{
			x = x - (abs(x - x_root) - autoGo_dx);
			isAutoGo = false;
			vx = 0;

			Jump(); // Sau khi chạy xong thì nhảy
		}
	}
}

void Panther::Render(Camera * camera)
{
	if (life <= 0)
		return;

	D3DXVECTOR2 pos = camera->Translate(x, y);
	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

Panther::~Panther()
{
}

bool Panther::GetIsStart()
{
	return isStart;
}

void Panther::Jump()
{
	if (isJumping == true)
		return;

	vy -= PANTHER_VYJUMP;
	vx = PANTHER_VXJUMP * nx;
	isJumping = true;
}

void Panther::Run()
{
	vx = PANTHER_SPEED_RUNNING * nx;
	isRunning = true;
}

/* Bat */
Bat::Bat(float X, float Y, int _nx)
{
	obj_type = def_ID::BAT;
	texture = new Load_img_file("Resources\\enemy\\0.png", 4, 1, 4, 0);
	sprite = new Load_resources(texture, 100);

	x = X;
	y = Y;
	this->nx = _nx;
	this->vy = BAT_VY;
	this->vx = BAT_SPEED * this->nx;
	life = 1;
	y_root = Y;
}

Bat::~Bat()
{

}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//sprite->Update(dt);
	alpha += 1;
	if (alpha >= 360)
	{
		alpha -= 360;
	}

	x += dx;
	y += (float)sin(alpha*0.1);

	sprite->Update(dt);

	if (sprite->GetIndex() == 0)
		sprite->Update(dt);
}

void Bat::Render(Camera * camera)
{
	if (life < 1)
		return;

	/*
	đáng lý ra nên để trong update nhưng do khi ghost đi khỏi màn hình sẽ chết
	nhưng k xóa nên cho vào đây để ghost k dc update sprite
	*/
	

	D3DXVECTOR2 pos = camera->Translate(x, y);
	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

/* Fish man */
Fishmen::Fishmen(float X, float Y, int _nx)
{
	obj_type = def_ID::FISHMEN;
	texture = LoadTexture::GetInstance()->GetTexture(def_ID::FISHMEN);
	sprite = new Load_resources(texture, 500);

	this->x = X;
	this->y = Y;
	this->nx = _nx;
	//this->life = 1;
	vx = 0;
	vy = -FISHMEN_SPEED_Y_UP;
	y_root = y;
	sprite->SelectIndex(FISHMEN_ANI_JUMP);
	isRunning = 0;
	isJumping = true;
	isAttacking = false;
	shoot = false;

	x_root = x;
	distance = 0;
}

Fishmen::~Fishmen()
{
}

void Fishmen::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 5;
	top = y + 15;
	right = x + texture->FrameWidth - 5;
	bottom = y + texture->FrameHeight;
}

void Fishmen::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
}

void Fishmen::UpdateCustom(DWORD dt, vector<LPGAMEOBJECT>* listObject, Simon * simon)
{
	if (enemyBullet != NULL && enemyBullet->GetFinish() == false)
	{
		enemyBullet->Update(dt, listObject);
	}

	if (isJumping)
	{
		vy += FISHMEN_GRAVITY_JUMPING;
	}

	if (abs(x - x_root) >= FISHMEN_DX_LIMIT) // đi đủ khoảng cố định
	{
		if ((nx == -1 && !(simon->x < x)) ||
			(nx == 1 && !(x < simon->x))) // đi về hướng của simon mà đã vượt simon thì mới đổi hướng
		{
			Attack(enemyBullet);
			shoot = 0;
			distance = 0;
			x_root = x;
		}
	}

	if (distance >= 200)
	{
		distance = 0;
		Attack(enemyBullet);
		shoot = 1;
		//DebugOut(L"[Accum enough]\n");
	}

	pos_x_before = x;

	if (isRunning)
	{
		vx = nx * 0.05f;
		vy += 0.01f;// Gravity
	}
	else vx = 0;

	CGameObject::Update(dt); // update dt,dx,dy 
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();

	for (UINT i = 0; i < listObject->size(); i++)
		if (listObject->at(i)->GetType() == def_ID::BRICK)
			list_Brick.push_back(listObject->at(i));

	CalcPotentialCollisions(&list_Brick, coEvents);

	float min_tx, min_ty, _nx = 0, ny;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, _nx, ny);
	x += min_tx * dx + _nx * 0.4f;
	/*if (nx != 0)
		vx = 0;*/

	if (ny == -1)
	{
		//DebugOut(L"[Accum enough] %f\n", ny);
		vy = 0;
		//y += min_ty * dy + ny * 0.4f;
		isRunning = true;
		isJumping = false;

		if (_nx != 0)
		{
			x += dx;
		}
	}
	else
	{
		if (isJumping)
		{
			x += dx;
		}

		if (ny == 0 && !isJumping)
		{
			isRunning = 0;
			vy += FISHMEN_GRAVITY_JUMPING;
		}

		y += dy;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	if (isAttacking)
	{
		isRunning = 0;
		DWORD now = GetTickCount();
		if (now - TimeAttack >= FISHMEN_TIME_LIMIT_WAIT_AFTER_ATTACK)
		{
			isAttacking = false;
			isRunning = 1;
			if (!shoot)
				nx *= -1; //đổi hướng đi
		}
	}

	pos_x_after = x;
	distance += abs(pos_x_after - pos_x_before);

	if (isAttacking)
	{
		sprite->SelectIndex(0);
	}
	else
		if (isRunning)
		{
			int index = sprite->GetIndex();
			if (0 < index && index <= 2)
				sprite->Update(dt);
			else
				sprite->SelectIndex(1);
		}
}

void Fishmen::Render(Camera * camera)
{
	if (life <= 0)
		return;

	D3DXVECTOR2 pos = camera->Translate(x, y);
	if (nx == -1)
		sprite->Draw((int)pos.x, (int)pos.y);
	else
		sprite->DrawFlipX((int)pos.x, (int)pos.y);


	if (enemyBullet != NULL && enemyBullet->GetFinish() == false)
		enemyBullet->Render(camera); // không cần xét hướng, vì Draw của lớp Weapon đã xét khi vẽ

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void Fishmen::Attack(Weapons * _enemyBullet)
{
	if (isAttacking)
		return;

	if (enemyBullet == NULL)
	{
		enemyBullet = new EnemyBullet();
		//listWeaponOfEnemy->push_back(enemyBullet);
	}

	if (enemyBullet->GetFinish() == false)
		return;

	isAttacking = true;
	TimeAttack = GetTickCount();

	enemyBullet->Create(x + 20, y + 10, nx);
}

/* Boss */
Boss::Boss(float X, float Y, Simon * simon, Camera *camera)
{
	x = X;
	y = Y;
	hp = 2;
	obj_type = def_ID::BOSS;

	texture = LoadTexture::GetInstance()->GetTexture(def_ID::BOSS);
	sprite = new Load_resources(texture, 70);
	StatusProcessing = BOSS_PROCESS_SLEEP;

	xBefore = x;
	yBefore = y;
	this->simon = simon;
	this->camera = camera;
	isWaiting = false;
	isAttacking = false;
}

Boss::~Boss()
{
}

void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + texture->FrameWidth;
	bottom = y + texture->FrameHeight;
}

void Boss::Update(DWORD dt, Simon* simon, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetHP() <= 0)
		return;

	if (enemyBullet != NULL && enemyBullet->GetFinish() == false)
	{
		enemyBullet->Update(dt, coObjects);
	}

	if (Data::GetInstance()->bossAppear == 1)
	{
		Start();
		Data::GetInstance()->bossAppear = 0;
	}

	switch (StatusProcessing)
	{
	case BOSS_PROCESS_SLEEP:
	{
		break;
	}

	case BOSS_PROCESS_START_1: // đi xuống
	{
		// bắt đầu thì đi xuống 1 đoạn ngắn
		if (y >= yTarget)
		{
			vy = 0;
			StatusProcessing = BOSS_PROCESS_START_2; // qua trạng thái di chuyển đến cửa sổ

			xBefore = x;
			yBefore = y;

			DebugOut(L"x_boss %f  . y_boss %f\n", x, y);
			if (x <= simon->x)
				xTarget = simon->x - 200;
			else xTarget = simon->x + 200;

			yTarget = 185;

			vx = ((xTarget - xBefore) / (1500.0f)); // Vận tốc cần để đi đến target trong 1.5s
			vy = 0.12f; // tạo độ cong
		}
		break;
	}

	case BOSS_PROCESS_START_2: // đi cong xuống ngay cửa sổ
	{
		if (!isWaiting)
		{
			// tạo độ cong
			vy -= 0.0001f * dt;
			if (vy < 0)
				vy = 0;
			// tạo độ cong

			if ((xTarget - xBefore >= 0 && x >= xTarget) || (xTarget - xBefore < 0 && x <=   xTarget)) // di chuyển xong đến mục tiêu 2
			{
				vx = 0;
				vy = 0;

				isWaiting = true; // bật trạng thái chờ
				TimeWaited = 0; // reset lại time đã chờ
			}
		}
		else
		{
			TimeWaited += dt;
			if (TimeWaited >= 4000)
			{
				isWaiting = false; // ngừng chờ

				StartCurves();
			}
		}

		break;
	}
	case BOSS_PROCESS_CURVES:
	{
		if (abs(x - xBefore) >= abs(xTarget - xBefore) || x < camera->GetX_cam() || x + GetWidth()>camera->GetX_cam() + camera->GetWidth()
			) // đi xong hoặc chạm biên trái phải màn hình thì dừng
		{
			vx = 0;
			vy = 0;
			isUseBezierCurves = false;

			/*vượt quá camera thì đẩy lại vào cam*/
			if (x < camera->GetX_cam())
				x += 1.0f;

			if (x + GetWidth() > camera->GetX_cam() + camera->GetWidth())
			{
				x -= 1.0f;
			}

			/*vượt quá camera thì đẩy lại vào cam*/

			StartStaight(simon);

			break;
		}

		float perc = (x - xBefore) / (xTarget - xBefore); // sử dụng phần trăm đã đi được tương ứng t của Bézier curve

		float ya = getPt(y1, y2, perc);
		float yb = getPt(y2, y3, perc);

		float yy = getPt(ya, yb, perc);

		vy = (yy - yLastFrame/*Khoảng cách y giữa frame trước và y dự tính đi*/) / dt;

		break;
	}
	case BOSS_PROCESS_STRAIGHT_1:
	{
		if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
			abs(y - yBefore) >= abs(yTarget - yBefore) /*||
			x <camera->GetX_cam() ||
			x + GetWidth()>camera->GetX_cam() + camera->GetWidth()*/) // đi xong hoặc chạm biên trái phải màn hình thì dừng
		{
			vx = vy = 0;
		
			StartStaight(simon);
		}

		break;
	}
	case BOSS_PROCESS_STRAIGHT_2:
	{
		if (!isWaiting)
		{
			if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
				abs(y - yBefore) >= abs(yTarget - yBefore) /*||
				x <camera->GetX_cam() ||
				x + GetWidth()>camera->GetX_cam() + camera->GetWidth()*/) // đi xong hoặc chạm biên trái phải màn hình thì dừng
			{
				vx = vy = 0;
				
				isWaiting = true; // bật trạng thái chờ
				TimeWaited = 0; // reset lại time đã chờ
			}
		}
		else
		{
			TimeWaited += dt;
			if (TimeWaited >= 3000)
			{
				isWaiting = false; // ngừng chờ

				int random = rand() % 3;
				switch (random)
				{
				case 3: //25 %
					StartAttack();
					break;

				default: // 75%
					StartCurves();

					break;
				}
			}
		}

		break;
	}
	case BOSS_PROCESS_ATTACK:
	{
		if (isWaiting)
		{
			TimeWaited += dt;
			if (TimeWaited >= 3000)
			{
				isWaiting = false; // ngừng chờ
				isAttacking = false;
				StartStaight(simon); // qua trạng thái đi thẳng
			}
		}

		break;
	}
	default:
		break;
	}

	CGameObject::Update(dt);
	x += dx;
	y += dy;

	if (x < camera->GetX_cam()
		|| camera->GetX_cam() + camera->GetWidth() < x + GetWidth()
		|| y < camera->GetY_cam() + 85.0f
		|| camera->GetY_cam() + camera->GetHeight() < y + GetHeight()
		) // ra khỏi cam thì xử lí hướng tiếp theo
	{

		switch (StatusProcessing)
		{
		case BOSS_PROCESS_CURVES:
		{
			isUseBezierCurves = false;
			StartStaight(simon);
			break;
		}
		case BOSS_PROCESS_STRAIGHT_1:
		{
			StartStaight(simon);
			break;
		}
		case BOSS_PROCESS_STRAIGHT_2:
		{
			int random = rand() % 2;
			switch (random)
			{
			case 2: //33 %
				StartAttack();
				break;
			case 3: // 66%
				StartCurves();

				break;
			}

			break;
		}
		}
	}

	yLastFrame = y;// lưu lại y frame hiện tại
}

void Boss::Render(Camera * camera)
{
	if (GetHP() <= 0)
		return;

	if (StatusProcessing == BOSS_PROCESS_SLEEP)
		sprite->SelectIndex(0);
	else
	{
		sprite->Update(dt);
		if (sprite->currentFrame == 0)
			sprite->SelectIndex(1);
	}

	D3DXVECTOR2 pos = camera->Translate(x, y);
	sprite->Draw((int)pos.x, (int)pos.y);

	if (enemyBullet != NULL && enemyBullet->GetFinish() == false)
		enemyBullet->Render(camera); // không cần xét hướng, vì Draw của lớp Weapon đã xét khi vẽ

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	if (IS_DEBUG_RENDER_BBOX && isUseBezierCurves) // sử dụng BezierCurves thì mới vẽ 
	{
		for (float i = 0; i < 1; i += 0.01f)
		{
			// The Green Line
			float xa = getPt(x1, x2, i);
			float ya = getPt(y1, y2, i);
			float xb = getPt(x2, x3, i);
			float yb = getPt(y2, y3, i);

			// The Black Dot
			float xx = getPt(xa, xb, i);
			float yy = getPt(ya, yb, i);

			RECT rect;
			//float l, t, r, b;
			rect.left = 0;
			rect.top = 0;
			rect.right = 5;
			rect.bottom = 5;
			D3DXVECTOR2 pos = camera->Translate(xx, yy);
			CGame::GetInstance()->Draw(
				pos.x,
				pos.y,
				LoadTexture::GetInstance()->GetTexture(
					def_ID::RENDERBOX)->Texture,
				rect.left,
				rect.top,
				rect.right,
				rect.bottom,
				100);
		}
	}

	RECT rect;
	//float l, t, r, b;
	rect.left = 0;
	rect.top = 0;
	rect.right = 15;
	rect.bottom = 15;
	D3DXVECTOR2 pos1 = camera->Translate(xTarget, yTarget);
	CGame::GetInstance()->Draw(
		pos1.x,
		pos1.y,
		LoadTexture::GetInstance()->GetTexture(
			def_ID::RENDERBOX)->Texture,
		rect.left,
		rect.top,
		rect.right,
		rect.bottom,
		100);
}

float Boss::getPt(float n1, float n2, float perc)
{
	float diff = n2 - n1;

	return n1 + (diff * perc);
}

void Boss::Start()
{
	isStart = 1;
	StatusProcessing = BOSS_PROCESS_START_1;
	yBefore = y;
	vy = 0.03f;
	vx = 0.0f;
	yTarget = y + 40; // lúc đầu thì đi xuống 40px
}

void Boss::StartCurves()
{
	DebugOut(L"Curves!\n");

	xBefore = x;
	yBefore = y;

	x1 = x;
	y1 = y;

	x2 = simon->x;
	y2 = simon->y + simon->GetHeight();

	if (simon->x < x) // simon bên trái boss
		//xTarget = camera->GetX_cam() - 100 + rand() % ((int)(simon->y - camera->GetX_cam() + 100));
		xTarget = simon->x - rand() % (100 - 30 + 1) + 30;
	else // simon bên phải boss
		xTarget = simon->x - rand() % (100 - 30 + 1) + 30;

	yTarget = simon->y + simon->GetHeight() - 100;

	x3 = xTarget;
	y3 = yTarget;

	vx = -(x - xTarget) / (abs(xTarget - xBefore)*1000.0f / 150); // vận tốc cần để đi đến Target // quy ước: cứ 1 giây đi 150px
	vy = 0;

	isUseBezierCurves = true;
	StatusProcessing = BOSS_PROCESS_CURVES;
}

void Boss::StartStaight(Simon* simon)
{
	DebugOut(L"Staight!\n");

	switch (StatusProcessing)
	{
	case BOSS_PROCESS_STRAIGHT_1:
		StatusProcessing = BOSS_PROCESS_STRAIGHT_2;
		break;
	default:
		StatusProcessing = BOSS_PROCESS_STRAIGHT_1;
		break;
	}

	xBefore = x;
	yBefore = y;

	xTarget = simon->x + rand() % (5492 - 5178);
	yTarget = simon->y - rand() % (200 - 100 + 1) - 100;

	// fix day
	if (x > (5136.0f*2 + Window_Width) /2)
	{
		DebugOut(L"Prepared fix xTarget 1\n");
		xTarget = simon->x - rand() % (510 - 250);
		yTarget = simon->y - rand() % (400 - 300) - 50;
	}

	if (xTarget > Data::GetInstance()->boundaryRight + Window_Width - 50)
	{
		DebugOut(L"Prepared fix xTarget 2\n");
		xTarget = simon->x - rand() % (5492 - 5178);
	}

	if (xTarget < Data::GetInstance()->boundaryRight)
		xTarget += 200;

	if (xTarget < simon->x && abs(xTarget - simon->x <= 100))
		xTarget -= 100;

	DebugOut(L"This is xTarget: %f \n", xTarget);

	if (yTarget < 85)
		yTarget = simon->y + rand() % (100 - 50 + 1);

	//DebugOut(L"xBefore: %f . xTarget: %f \n", xBefore, xTarget);
	DebugOut(L"StatusProcessing = %d, Target (%f, %f) \n", StatusProcessing, xTarget, yTarget);

	vx = (xTarget - xBefore) / (1000); 
	vy = (yTarget - yBefore) / (1000);
}

void Boss::StartAttack()
{
	DebugOut(L"ATTACK!\n");

	if (isAttacking)
		return;

	isAttacking = 1;

	if (enemyBullet == NULL)
	{
		enemyBullet = new EnemyBullet();
		//listWeaponOfEnemy->push_back(enemyBullet);
	}

	if (enemyBullet->GetFinish() == false)
		return;

	int nx_Bullet;

	if (x < simon->x) nx_Bullet = 1;
	else nx_Bullet = -1;
	
	float x_Bullet = x + GetWidth() / 2;
	float y_Bullet = y + GetHeight() / 2;

	float S = sqrt((x_Bullet - simon->x) *(x_Bullet - simon->x) + (y_Bullet - simon->y)*(y - simon->y)); //s=sqrt(x^2+y^2)
																									  //																								 // thời gian bắn trúng nếu dùng vận tốc FIREBALL_SPEED
	float t = S / 0.15f;

	enemyBullet->CustomCreate(x_Bullet, y_Bullet, nx, nx_Bullet* abs(x_Bullet - simon->x) / t, abs(y_Bullet - simon->y) / t);
	
	StatusProcessing = BOSS_PROCESS_ATTACK;

	TimeWaited = 0;
	isWaiting = true;
}