#include "Load_img_file.h"
#include "debug.h"


Load_img_file::Load_img_file(char* _fileName, int cols, int rows, int count, int Showbox)
{
	Cols = cols;
	Rows = rows;
	Count = count;
	fileName = _fileName;
	this->Load(Showbox);
}

Load_img_file::Load_img_file(char* _fileName, int cols, int rows, int count, int R, int G, int B)
{
	Cols = cols;
	Rows = rows;
	Count = count;
	fileName = _fileName;
	this->Load(R, G, B);
}


Load_img_file::~Load_img_file()
{
	if (this->Texture != NULL)
		this->Texture->Release();
}

void Load_img_file::Draw(int x, int y)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXVECTOR3 p((float)x, (float)y, 0);
	spriteHandler->Draw(Texture, &Size, NULL, &p, 0xFFFFFFFF);
}

void Load_img_file::Load(int ShowBox)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFileA(fileName, &info);

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();

	RECT s = { 0, 0, info.Width, info.Height };
	this->Size = s;

	FrameWidth = info.Width / Cols;
	FrameHeight = info.Height / Rows;

	if (result != D3D_OK)
	{
		//	GLMessage("Can not load texture");
		//	GLTrace("[texture.h] Failed to get information from image file [%s]", FileName);
		OutputDebugStringA(fileName);
		return;
	}

	result = D3DXCreateTextureFromFileExA(
		d3ddv,
		fileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, ShowBox, 255), //color
		&info,
		0,
		&Texture
	);

	if (result != D3D_OK)
	{
		//GLMessage("Can not load texture");
		//	GLTrace("[texture.h] Failed to create texture from file '%s'", FileName);
		return;
	}
}

void Load_img_file::Load(int R, int G, int B)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();



	result = D3DXGetImageInfoFromFileA(fileName, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	this->Size = s;

	FrameWidth = info.Width / Cols;
	FrameHeight = info.Height / Rows;

	if (result != D3D_OK)
	{
		//GLMessage("Can not load texture");
		//GLTrace("[texture.h] Failed to get information from image file [%s]", FileName);
		OutputDebugStringA(fileName);
		return;
	}

	result = D3DXCreateTextureFromFileExA(
		d3ddv,
		fileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(R, G, B), //color
		&info,
		0,
		&Texture
	);

	if (result != D3D_OK)
	{
		//GLMessage("Can not load texture");
		//GLTrace("[texture.h] Failed to create texture from file '%s'", FileName);
		return;
	}
}