#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "Load_img_file.h"




class Load_resources {
public:
	Load_img_file * _texture;
	
	int _start;		//chạy từ frame đầu tiên (chỉ số)
	int _end;		//chạy đến frame cuối cùng (chỉ số)
	int _index;		//frame hiện tại
	int _timeAni;	//thời gian chuyển frame
	int _timeLocal;	//biến hỗ trợ đếm thời gian

	Load_resources();
	Load_resources(const Load_resources &sprite);
	Load_resources(Load_img_file* texture, int timeAnimation);
	Load_resources(Load_img_file* texture, int start, int end, int timeAnimation);

	//sang frame tiếp theo
	void Next();

	//trở về frame đầu tiên
	void Reset();

	//chọn ID của 1 frame
	void SelectIndex(int index);

	// lấy index hiện tại
	int GetIndex();

	//update animation
	void Update(int ellapseTime);

	// Render current sprite at location (X,Y) at the target surface
	void Draw(int x, int y);

	//Render with scale (-1, 1)
	void DrawFlipX(int x, int y);
	void DrawFlipXByIndex(int index, int x, int y);

	//Render Rect of texture at (x,y)
	void DrawRect(int X, int Y, RECT SrcRect);

	void DrawIndex(int index, int X, int Y);
	~Load_resources();

	//=======================================================================================================================
	int R, G, B, A;
	void SetARGB(int r = 255, int g = 255, int b = 255, int a = 255);
};
