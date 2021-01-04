#pragma once

#include "Game.h"
#include "define.h"


class Load_img_file
{
public:
	char* fileName; //đường dẫn tới file ảnh
	RECT Size;		//độ phân giải ảnh
	LPDIRECT3DTEXTURE9 Texture; // lưu sprite
	int Cols;		//số cột frame
	int Rows;		//số hàng frame
	int Count;		//tổng số frame
	int FrameWidth;		//width of 1 frame
	int FrameHeight;	//height of 1 frame

	Load_img_file(char* _fileName, int cols = 1, int rows = 1, int count = 1, int Showbox = 0);
	Load_img_file(char* _fileName, int cols, int rows, int count, int R, int G, int B);
	~Load_img_file();
	//vẽ texture tại vị trí (x, y) trên màn hình
	void Draw(int x, int y);

protected:
	void Load(int ShowBox);
	void Load(int R, int G, int B);
};

