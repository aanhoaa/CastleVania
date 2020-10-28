#pragma once
#include "Game.h"
#include "dsutil.h"
#include <unordered_map>
#include "define.h"

class Sound
{
private:
	unordered_map<eSound, CSound* > _ArrSound;

public:
	static Sound * __Instance;
	static Sound * GetInstance();


	CSoundManager *dsound;

	// khởi tạo direct sound
	void Init();
	Sound();

	void Create(eSound _id, LPTSTR filename); // add sound vào bộ nhớ đệm
	void Play(eSound _id, bool isLoop = false); // phát sound
	void Stop(eSound _id); 
	void LoadResourceSound(); // load sound vào trong 1 mảng cho dễ quản lý (sử dụng nhiều lần)
};
