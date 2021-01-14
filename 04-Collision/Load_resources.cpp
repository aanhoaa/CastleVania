#include "Load_resources.h" 
#include "debug.h"

Load_resources::Load_resources()
{
	_texture = NULL;
	startFrame = 0;
	lastFrame = 0;
	timeAnimation = 0;
	currentFrame = 0;
	timeLocal = 0;
	SetARGB();
}

Load_resources::Load_resources(const Load_resources &sprite)
{
	_texture = sprite._texture;
	startFrame = sprite.startFrame;
	lastFrame = sprite.lastFrame;
	timeAnimation = sprite.timeAnimation;
	currentFrame = sprite.startFrame;
	timeLocal = sprite.timeLocal;
	SetARGB();
}

Load_resources::Load_resources(Load_img_file* texture, int start, int end, int _timeAnimation)
	: _texture(texture)
{
	startFrame = start;
	lastFrame = end;
	timeAnimation = _timeAnimation;
	currentFrame = start;
	timeLocal = 0;
	SetARGB();
}

Load_resources::Load_resources(Load_img_file* texture, int _timeAnimation)
	: _texture(texture)
{
	startFrame = 0;
	lastFrame = _texture->Count - 1;
	timeAnimation = _timeAnimation;
	currentFrame = 0;
	timeLocal = 0;
	SetARGB();
}

Load_resources::~Load_resources()
{
	if (_texture != NULL)
		delete _texture;
}

void Load_resources::SetARGB(int r, int g, int b, int a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

void Load_resources::Next()
{
	currentFrame++;
	if (currentFrame > lastFrame)
		currentFrame = startFrame;
}

void Load_resources::Reset()
{
	currentFrame = startFrame;
	timeLocal = 0;
}

void Load_resources::ResetTime()
{
	timeLocal = 0;
}

void Load_resources::SelectIndex(int index)
{
	currentFrame = index;
}

void Load_resources::Update(DWORD ellapseTime)
{
	timeLocal += ellapseTime;

	if (timeLocal >= timeAnimation) // neu time dem > time ani tuc la ani do da chay du roi, can chuyen sang frame tiep
	{
		timeLocal = 0; // reset bien dem time
		this->Next(); // chuyen sang next frame
	}
}

void Load_resources::Draw(int X, int Y, int alpha)
{
	RECT srect;

	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	srect.left = (currentFrame % _texture->Cols)*(_texture->FrameWidth);
	srect.top = (currentFrame / _texture->Cols)*(_texture->FrameHeight);
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;

	D3DXVECTOR3 p((float)X, (float)Y, 0);
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		NULL,
		&p,
		D3DCOLOR_XRGB(alpha, R, G, B)
	);
}

void Load_resources::DrawS(int X, int Y, int subX, int pivot, int alpha)
{
	RECT srect;

	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	srect.left = (currentFrame % _texture->Cols)*(_texture->FrameWidth);
	srect.top = (currentFrame / _texture->Cols)*(_texture->FrameHeight);
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;

	if (pivot == 1)
	{
		srect.left += (float)subX;
	}
	else
	{
		srect.bottom -= subX;
	}

	D3DXVECTOR3 p((float)X, (float)Y, 0);
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		NULL,
		&p,
		D3DCOLOR_XRGB(alpha, R, G, B)
	);
}

void Load_resources::DrawChangeColor(int X, int Y, int alpha)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();
	RECT srect;
	srect.left = (currentFrame % _texture->Cols)*_texture->FrameWidth;
	srect.top = (currentFrame / _texture->Cols)*_texture->FrameHeight;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;

	int RR, GG, BB;

	switch (rand() % 6)
	{
	case 0:
		RR = 255;
		GG = rand() % 256;
		BB = 0;
		break;
	case 1:
		RR = rand() % 256;
		GG = 255;
		BB = 0;
		break;
	case 2:
		RR = 0;
		GG = 255;
		BB = rand() % 256;
		break;
	case 3:
		RR = 0;
		GG = rand() % 256;
		BB = 255;
		break;
	case 4:
		RR = rand() % 256;
		GG = 0;
		BB = 255;
		break;
	case 5:
		RR = 255;
		GG = 0;
		BB = rand() % 256;
		break;
	}

	D3DXVECTOR3 p((float)X, (float)Y, 0);
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		NULL,
		&p,
		D3DCOLOR_ARGB(alpha, RR, GG, BB)
	);
}

void Load_resources::DrawChangeColorFlipX(int x, int y, int alpha)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;

	D3DXVECTOR2 top_left = D3DXVECTOR2((float)x, (float)y);

	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f);

	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;
	this->DrawChangeColor(x, y, alpha);

	spriteHandler->SetTransform(&oldMt);
}

void Load_resources::DrawRect(int X, int Y, RECT SrcRect, int alpha)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXVECTOR3 position((float)X, (float)Y, 0);
	spriteHandler->Draw(
		_texture->Texture,
		&SrcRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(alpha, 255, 255, 255)
	);
}

void Load_resources::DrawFlipX(int x, int y, int alpha)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;

	D3DXVECTOR2 top_left = D3DXVECTOR2((float)x, (float)y);

	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f);

	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;
	this->Draw(x, y, alpha);

	spriteHandler->SetTransform(&oldMt);
}

void Load_resources::DrawFlipXS(int x, int y, int a, int pivot, int alpha)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;

	D3DXVECTOR2 top_left = D3DXVECTOR2((float)x, (float)y);

	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f);

	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;
	this->DrawS(x, y, a, pivot, alpha);

	spriteHandler->SetTransform(&oldMt);
}

void Load_resources::DrawFlipXByIndex(int index, int x, int y, int alpha)
{
	RECT srect;

	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	srect.left = (index % _texture->Cols)*(_texture->FrameWidth);
	srect.top = (index / _texture->Cols)*(_texture->FrameHeight);
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;
	
	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);
	D3DXMATRIX newMt;
	D3DXVECTOR2 top_left = D3DXVECTOR2((float)x, (float)y);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1.0f, 1.0f);
	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;

	D3DXVECTOR3 p((float)x, (float)y, 0);
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		NULL,
		&p,
		D3DCOLOR_XRGB(alpha, R, G, B)
	);

	spriteHandler->SetTransform(&oldMt);
}

void Load_resources::DrawIndex(int index, int X, int Y, int alpha)
{
	RECT srect;

	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	srect.left = (index % _texture->Cols)*(_texture->FrameWidth);
	srect.top = (index / _texture->Cols)*(_texture->FrameHeight);
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = (float)(X - _texture->FrameWidth / 2);
	position.y = (float)(Y - _texture->FrameHeight / 2);
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		&center,
		&position,
		//D3DCOLOR_XRGB(A, R, G, B)  //color
		D3DCOLOR_XRGB(alpha, R, G, B)
	);
}

int Load_resources::GetIndex()
{
	return currentFrame;
}
