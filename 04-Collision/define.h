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
	HIT = 02,
	EFFECT = 03,
	FONTGAME = 04,
	BLACKBOARD = 05,
	RENDERBOX = 06,
	BRICK_TYPE_1 = 07,
	BRICK_TYPE_2 = 8,
	BRICK_TYPE_3 = 9,
	BRICK_TRANSPARENT = 10,
	HEARTPOINT = 11,
	WATER = 12,
	BRICKSPLASH = 20,
	BRICK = 21,
	BRICK_3X32 = 22,
	BRICK_4X32 = 23,
	TEX_BRICK_TRANSPARENT = 25,
	GATE = 26,
	BIGCANDLE = 41,
	HIDDENOBJECT = 42,
	SMALLCANDLE = 43,

	STAIR = 44,
	BOTTOMSTAIR = 47,
	TOPSTAIR = 48,
	
	//weapon
	MORNINGSTAR = 61,
	DAGGER = 62,
	HOLYWATER = 63,
	ENEMYBULLET = 65,
	AXE = 66,

	//item
	BIGHEART = 81,
	UPGRADEMORNINGSTAR = 82,
	iDAGGER = 83,
	MONNEYBAG = 84,
	SMALLHEART = 85,
	iHOLYWATER = 86,
	POTROAST = 87,
	iAXE = 88,
	MAGICCRYSTAL = 89,

	//enemy
	GHOST = 141,
	PANTHER = 142,
	BAT = 143,
	FISHMEN = 144,
	BOSS = 161,

	//intro
	MAINMENU = 181,
	INTRO_GO_SCENE1 = 182,
	INTRO_BAT_MENU = 183, // bat ở menu
	HELICOPTER = 184,
	INTRO_BAT = 185 // ở intro

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
	sWasEnemyHit = 8,
	sHollyWater = 9,

	smusicStage1 = 51,
	smusicLose = 52,
	sOpenDoor = 53
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
