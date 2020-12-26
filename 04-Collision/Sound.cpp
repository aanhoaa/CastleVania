#include "Sound.h"



Sound* Sound::__Instance = NULL;

Sound::Sound()
{
	Init();
	LoadResourceSound();
}

void Sound::LoadResourceSound()
{
	Create(eSound::sMorningStar, L"Resources/sound/usingwhip.wav");
	Create(eSound::sHit, L"Resources/sound/hit.wav");
	Create(eSound::sCollectItem, L"Resources/sound/collectitem.wav");
	Create(eSound::sCollectWeapon, L"Resources/sound/collectweapon.wav");
	Create(eSound::sStopTimer, L"Resources/sound/stoptimer.wav");
	Create(eSound::sDagger, L"Resources/sound/usingdagger.wav");
	Create(eSound::sMonneyBag, L"Resources/sound/display_monney.wav");
	Create(eSound::sWasEnemyHit, L"Resources/sound/hurting.wav");
	Create(eSound::sHollyWater, L"Resources/sound/holywater.wav");
	Create(eSound::smusicStage1, L"Resources/music/Stage_01_Vampire_Killer.wav");
	Create(eSound::smusicLose, L"Resources/music/Life_Lost.wav");
	Create(eSound::sOpenDoor, L"Resources/sound/opendoor.wav");
}

void Sound::Create(eSound _id, LPTSTR filename)
{
	CSound *wave;
	HRESULT result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		DebugOut(L"[SOUND] Load Sound that bai. eSound = %d \n", (int)_id);
		return;
	}
	_ArrSound[_id] = wave;
}

void Sound::Play(eSound _id, bool isLoop)
{
	_ArrSound[_id]->Play(0, isLoop);
	//DSBPLAY_LOOPING             0x00000001 -> int = 1

}

void Sound::Stop(eSound _id)
{
	_ArrSound[_id]->Stop();
}

void Sound::Init()
{
	dsound = new CSoundManager();
	dsound->Initialize(CGame::GetInstance()->GetWindowHandle(), DSSCL_PRIORITY);
	dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Sound * Sound::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Sound();
	return __Instance;
}