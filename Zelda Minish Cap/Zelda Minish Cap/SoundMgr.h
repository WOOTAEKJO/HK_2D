#pragma once
#include "framework.h"

class CSoundMgr
{
private:
	CSoundMgr();
	~CSoundMgr();
public:

	static CSoundMgr* Get_Instance() {
		if (!m_Instance) {
			m_Instance = new CSoundMgr;
		}
		return m_Instance;
	}

	static void Delete_Instance() {
		if (m_Instance) {
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
public:
	void Initialize();
	void Release();
public:
	void PlaySound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void PlayBGM(const TCHAR* pSoundKey, float fVolume);
	void StopSound(CHANNELID eID);
	void StopAll();
	void SetChannelVolume(CHANNELID eID, float fVolume);
private:
	void LoadSoundFile();

private:
	static CSoundMgr* m_Instance;

	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;

	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];

	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem;
};

