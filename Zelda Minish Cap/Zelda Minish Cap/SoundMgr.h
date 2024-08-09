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

	// ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;

	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];

	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;
};

