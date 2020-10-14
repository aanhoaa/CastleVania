#pragma once


#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h> 

#include "define.h"
#include "SceneManager.h"

#define KEYBOARD_BUFFER_SIZE 1024
/*
Abstract class to define keyboard event handlers
*/
//class CKeyEventHandler
//{
//public:
//	virtual void KeyState(BYTE *state) = 0;
//	virtual void OnKeyDown(int KeyCode) = 0;
//	virtual void OnKeyUp(int KeyCode) = 0;
//};
//
//typedef CKeyEventHandler * LPKEYEVENTHANDLER;

class CGame
{
	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;		
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	//LPKEYEVENTHANDLER keyHandler;
	virtual void KeyState(BYTE *state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
public:
	void InitKeyboard();
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT r, int alpha = 255);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	//AABB
	bool CollisionAABB(RECT a, RECT b);
	bool CollisionAABB(float l1, float t1, float r1, float b1, float l2, float t2, float r2, float b2);


	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st, 
		float sr, 
		float sb,
		float &t, 
		float &nx, 
		float &ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }
	HWND GetWindowHandle(); // Quit game function

	static CGame * GetInstance();

	~CGame();
};


