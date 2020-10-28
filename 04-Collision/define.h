#ifndef _DEFINE_H__
#define _DEFINE_H__

#define _USE_MATH_DEFINES

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include "debug.h"
#include <vector>
#include <Windows.h> 
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 448
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480

#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)  
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) 


#define SHOWBOX_PINK 0

#define IS_DEBUG_RENDER_BBOX 1


extern int Window_Width;
extern int Window_Height;

extern int MapWidth;
extern int MapHeight;

extern int ScreenColumn;
extern int ScreenRow;

// ID của Sprite, object
enum def_ID
{
	SIMON = 01,
	BRICK = 21,
	BIGCANDLE = 41,
	HIDDENOBJECT = 42,
	SMALLCANDLE = 43,
	MORNINGSTAR = 61,
	DAGGER = 62,

	BIGHEART = 81,
	UPGRADEMORNINGSTAR = 82,
	iDAGGER = 83,
	MONNEYBAG = 84
};

enum eDirection
{
	NONE = 0,
	TOP = (1 << 0),
	LEFT = (1 << 1),
	RIGHT = (1 << 2),
	BOTTOM = (1 << 3)
};

enum eSound
{
	sMorningStar = 1,
	sHit = 2,
	sCollectItem = 3,
	sCollectWeapon = 4,
	sStopTimer = 5,
	sDagger = 6,
	sMonneyBag = 7,

	smusicStage1 = 51,
	smusicLose = 52
};

enum eMap
{
	mMap1 = 104,
	mMap2 = 106
};

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)


#ifndef SAFE_DELETE

#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif // !SAFE_DELETE

#endif // !_DEFINE_H__
