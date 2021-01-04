#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "Load_img_file.h"


class Load_resources {
public:
	Load_img_file * _texture;
	
	int startFrame;		
	int lastFrame;		
	int currentFrame;		
	int timeAnimation;	//time của 1 frame
	int timeLocal;	// time đang có

	Load_resources();
	Load_resources(const Load_resources &sprite);
	Load_resources(Load_img_file* texture, int timeAnimation);
	Load_resources(Load_img_file* texture, int start, int end, int timeAnimation);

	//sang frame tiếp theo
	void Next();

	//trở về frame đầu tiên
	void Reset();

	void ResetTime();
	//chọn ID của 1 frame
	void SelectIndex(int index);

	// lấy index hiện tại
	int GetIndex();

	//update animation
	void Update(DWORD ellapseTime);

	// Render current sprite at location (X,Y) at the target surface
	void Draw(int x, int y, int alpha = 255);
	void DrawS(int x, int y, int a, int pivot, int alpha = 255);

	// Render with change coler
	void DrawChangeColor(int X, int Y, int alpha = 255);
	void DrawChangeColorFlipX(int x, int y, int alpha = 255);

	//Render with scale (-1, 1)
	void DrawFlipX(int x, int y, int alpha = 255);
	void DrawFlipXByIndex(int index, int x, int y, int alpha = 255);

	void DrawFlipXS(int x, int y, int subX, int pivot, int alpha = 255);

	//Render Rect of texture at (x,y)
	void DrawRect(int X, int Y, RECT SrcRect, int alpha = 255);

	void DrawIndex(int index, int X, int Y, int alpha = 255);
	~Load_resources();

	//=======================================================================================================================
	int R, G, B, A;
	void SetARGB(int r = 255, int g = 255, int b = 255, int a = 255);
};
