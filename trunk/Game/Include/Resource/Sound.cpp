
#include "Sound.h"
#include "../PathManager.h"

bool CSound::LoadSound(FMOD::System* pSystem, FMOD::ChannelGroup* pGroup, bool bLoop, const std::string& strName, const char* cFileName, const std::string& strPathName)
{
	m_strName = strName;
	m_pSystem = pSystem;
	m_pGroup = pGroup;
	m_bLoop = bLoop;

	char	cFullPath[MAX_PATH] = {};

	const PathInfo* pPathInfo = CPathManager::GetInst()->FindPath(strPathName);

	if (pPathInfo)
		strcpy_s(cFullPath, pPathInfo->cPathMultibyte);

	strcat_s(cFullPath, cFileName);

	FMOD_MODE	iMode = FMOD_DEFAULT;

	if (m_bLoop)
		iMode = FMOD_LOOP_NORMAL;

	FMOD_RESULT	result = m_pSystem->createSound(cFullPath, iMode, nullptr, &m_pSound);

	if (result != FMOD_OK)
		return false;

	return true;
}

void CSound::Play()
{
	m_pSystem->playSound(m_pSound, m_pGroup, false, &m_pChannel);
	m_bPlay = true;
}

void CSound::Stop()
{
	if (m_pChannel)
	{
		bool	bPlaying = false;

		m_pChannel->isPlaying(&bPlaying);

		if (bPlaying)
		{
			m_pChannel->stop();
			m_pChannel = nullptr;

			m_bPlay = false;
		}
	}
}

void CSound::Pause()
{
	if (!m_pChannel)
		return;

	bool	bPlaying = false;

	m_pChannel->isPlaying(&bPlaying);

	if (bPlaying)
		m_pChannel->setPaused(true);

	m_bPlay = false;
}

void CSound::Resume()
{
	if (!m_pChannel)
		return;

	bool	bPlaying = false;

	m_pChannel->isPlaying(&bPlaying);

	if (bPlaying)
		m_pChannel->setPaused(false);

	m_bPlay = true;
}

void CSound::Update()
{
	if (m_pChannel)
		m_pChannel->isPlaying(&m_bPlay);
}

CSound::CSound()	:
	m_pSystem(nullptr),
	m_pSound(nullptr),
	m_pGroup(nullptr),
	m_pChannel(nullptr),
	m_bPlay(false),
	m_bLoop(false)
{
}

CSound::~CSound()
{
	if (m_pSound)
		m_pSound->release();
}
