#pragma once

#include "../Ref.h"

class CSound :
	public CRef
{
	friend class CResourceManager;

private:
	std::string			m_strName;
	FMOD::System*		m_pSystem;
	FMOD::Sound*		m_pSound;
	FMOD::ChannelGroup* m_pGroup;
	FMOD::Channel*		m_pChannel;
	bool				m_bPlay;
	bool				m_bLoop;

public:
	bool IsPlaying()	const
	{
		return m_bPlay;
	}

	bool IsLoop()	const
	{
		return m_bLoop;
	}

public:
	void Update();
	bool LoadSound(FMOD::System* pSystem, FMOD::ChannelGroup* pGroup, bool bLoop, const std::string& strName, const char* cFileName, const std::string& strPathName = SOUND_PATH);
	void Play();
	void Stop();
	void Pause();
	void Resume();

private:
	CSound();
	~CSound();
};

