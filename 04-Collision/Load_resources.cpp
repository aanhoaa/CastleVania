#include "Load_resources.h" 

Load_resources::Load_resources()
{
	_texture = NULL;
	_start = 0;
	_end = 0;
	_timeAni = 0;
	_index = 0;
	_timeLocal = 0;
	SetARGB();
}

Load_resources::Load_resources(const Load_resources &sprite)
{
	_texture = sprite._texture;
	_start = sprite._start;
	_end = sprite._end;
	_timeAni = sprite._timeAni;
	_index = sprite._start;
	_timeLocal = sprite._timeLocal;
	SetARGB();
}

Load_resources::Load_resources(Load_img_file* texture, int start, int end, int timeAnimation)
	: _texture(texture)
{
	_start = start;
	_end = end;
	_timeAni = timeAnimation;
	_index = start;
	_timeLocal = 0;
	SetARGB();
}

Load_resources::Load_resources(Load_img_file* texture, int timeAnimation)
	: _texture(texture)
{
	_start = 0;
	_end = _texture->Count - 1;
	_timeAni = timeAnimation;
	_index = 0;
	_timeLocal = 0;
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
	_index++;
	if (_index > _end)
		_index = _start;
}

void Load_resources::Reset()
{
	_index = _start;
	_timeLocal = 0;
}

void Load_resources::SelectIndex(int index)
{
	_index = index;
}

void Load_resources::Update(int ellapseTime)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni) // neu time dem > time ani tuc la ani do da chay du roi, can chuyen sang frame tiep
	{
		_timeLocal = 0; // reset bien dem time
		this->Next(); // chuyen sang next frame
	}
}

void Load_resources::Draw(int X, int Y)
{
	RECT srect;

	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	srect.left = (_index % _texture->Cols)*(_texture->FrameWidth);
	srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;

	//D3DXVECTOR3 position(0, 0, 0);
	//D3DXVECTOR3 center(0, 0, 0);
	//position.x = X - _texture->FrameWidth / 2;
	//position.y = Y - _texture->FrameHeight / 2;

	//spriteHandler->Draw(
	//	_texture->Texture,
	//	&srect,
	//	&center,
	//	&position,
	//	D3DCOLOR_XRGB(R, G, B) //color
	//	);



	D3DXVECTOR3 p(X, Y, 0);
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		NULL,
		&p,
		D3DCOLOR_XRGB(R, G, B)
	);

}

void Load_resources::DrawRect(int X, int Y, RECT SrcRect)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXVECTOR3 position((float)X, (float)Y, 0);
	spriteHandler->Draw(
		_texture->Texture,
		&SrcRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void Load_resources::DrawFlipX(int x, int y)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;

	D3DXVECTOR2 top_left = D3DXVECTOR2(x, y);

	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;
	this->Draw(x, y);

	spriteHandler->SetTransform(&oldMt);
}

void Load_resources::DrawFlipY(int x, int y)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();



	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	spriteHandler->SetTransform(&finalMt);

	this->Draw(x, y);

	spriteHandler->SetTransform(&oldMt);
}

void Load_resources::DrawIndex(int index, int X, int Y)
{
	RECT srect;

	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	srect.left = (index % _texture->Cols)*(_texture->FrameWidth);
	srect.top = (index / _texture->Cols)*(_texture->FrameHeight);
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - _texture->FrameWidth / 2;
	position.y = Y - _texture->FrameHeight / 2;
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		&center,
		&position,
		D3DCOLOR_XRGB(A, R, G, B)  //color
	);
}

void Load_resources::DrawRaw(int X, int Y)
{
	RECT srect;
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();


	srect.left = (_index % _texture->Cols)*(_texture->FrameWidth);
	srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X;
	position.y = Y;
	spriteHandler->Draw(
		_texture->Texture,
		&srect,
		&center,
		&position,
		D3DCOLOR_XRGB(R, G, B)  //color
	);
}
int Load_resources::GetIndex()
{
	return _index;
}


void Load_resources::DrawApart(int x, int y, int w)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();


	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	spriteHandler->SetTransform(&finalMt);

	x += _texture->FrameWidth;
	{
		int X = x;
		int Y = y;
		RECT srect;

		srect.left = (_index % _texture->Cols)*(_texture->FrameWidth) + _texture->FrameWidth - w;
		srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);
		srect.right = srect.left + w;
		srect.bottom = srect.top + _texture->FrameHeight;

		D3DXVECTOR3 position(0, 0, 0);
		D3DXVECTOR3 center(0, 0, 0);
		position.x = X - _texture->FrameWidth / 2;
		position.y = Y - _texture->FrameHeight / 2;
		spriteHandler->Draw(
			_texture->Texture,
			&srect,
			&center,
			&position,
			D3DCOLOR_XRGB(A, R, G, B)  //color
		);
	}

	spriteHandler->SetTransform(&oldMt);
}