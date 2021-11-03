
#include "ResourceManager.h"

CResourceManager* CResourceManager::m_pInst = nullptr;

bool CResourceManager::LoadSound(const std::string& strGroupName, bool bLoop, const std::string& strName, const char* cFileName, const std::string& strPathName)
{
	CSound* pSound = FindSound(strName);

	if (pSound)
		return true;

	FMOD::ChannelGroup* pGroup = FindSoundChannelGroup(strGroupName);

	if (!pGroup)
		return false;

	pSound = new CSound;

	if (!pSound->LoadSound(m_pSystem, pGroup, bLoop, strName, cFileName, strPathName))
	{
		SAFE_RELEASE(pSound);
		return false;
	}

	m_mapSound.insert(std::make_pair(strName, pSound));

	return true;
}

bool CResourceManager::CreateSoundChannelGroup(const std::string& strName)
{
	FMOD::ChannelGroup* pGroup = FindSoundChannelGroup(strName);

	if (pGroup)
		return true;

	FMOD_RESULT	result = m_pSystem->createChannelGroup(strName.c_str(), &pGroup);

	if (result != FMOD_OK)
		return false;

	m_pMasterGroup->addGroup(pGroup, false);

	m_mapChannelGroup.insert(std::make_pair(strName, pGroup));

	return true;
}

bool CResourceManager::SetVolume(int iVolume)
{
	m_pMasterGroup->setVolume(iVolume / 100.f);

	return true;
}

bool CResourceManager::SetVolume(const std::string& strGroupName, int iVolume)
{
	FMOD::ChannelGroup* pGroup = FindSoundChannelGroup(strGroupName);

	if (!pGroup)
		return false;

	pGroup->setVolume(iVolume / 100.f);

	return true;
}

bool CResourceManager::SoundPlay(const std::string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Play();

	return true;
}

bool CResourceManager::SoundStop(const std::string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Stop();

	return true;
}

bool CResourceManager::SoundGroupStop(const std::string& strGroupName)
{
	std::unordered_map<std::string, FMOD::ChannelGroup*>::iterator iter = m_mapChannelGroup.find(strGroupName);

	if (iter == m_mapChannelGroup.end())
		return false;

	iter->second->stop();

	return true;
}

bool CResourceManager::SoundPause(const std::string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Pause();

	return true;
}

bool CResourceManager::SoundResume(const std::string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Resume();

	return true;
}

bool CResourceManager::IsPlaying(const std::string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	return pSound->IsPlaying();
}

void CResourceManager::ReleaseSound(const std::string& strName)
{
	std::unordered_map<std::string, CSharedPtr<CSound>>::iterator	iter = m_mapSound.find(strName);

	if (iter->second->GetRefCount() == 1)
		m_mapSound.erase(iter);
}

FMOD::ChannelGroup* CResourceManager::FindSoundChannelGroup(const std::string& strName)
{
	std::unordered_map<std::string, FMOD::ChannelGroup*>::iterator	iter = m_mapChannelGroup.find(strName);

	if (iter == m_mapChannelGroup.end())
		return nullptr;

	return iter->second;
}

CSound* CResourceManager::FindSound(const std::string& strName)
{
	std::unordered_map<std::string, CSharedPtr<CSound>>::iterator	iter = m_mapSound.find(strName);

	if (iter == m_mapSound.end())
		return nullptr;

	return iter->second;
}

bool CResourceManager::LoadTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName)
{
	CTexture* pTexture = FindTexture(strName);

	if (pTexture)
		return true;

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(strName, cFileName, strPathName))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(strName, pTexture));

	return true;
}

bool CResourceManager::LoadTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName)
{
	CTexture* pTexture = FindTexture(strName);

	if (pTexture)
		return true;

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(strName, vecFileName, strPathName))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(strName, pTexture));

    return true;
}

bool CResourceManager::LoadTextureFullPath(const std::string& strName, const TCHAR* cFullPath)
{
	CTexture* pTexture = FindTexture(strName);

	if (pTexture)
		return true;

	pTexture = new CTexture;

	if (!pTexture->LoadTextureFullPath(strName, cFullPath))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(strName, pTexture));

	return true;
}

void CResourceManager::SetTextureColorKey(const std::string& strName, const unsigned char r, const unsigned char g, const unsigned char b, int iIdx)
{
	CTexture* pTexture = FindTexture(strName);

	if (!pTexture)
		return;

	pTexture->SetColorKey(r, g, b, iIdx);
}

void CResourceManager::SetTextureColorKey(const std::string& strName, unsigned int iColorKey, int iIdx)
{
	CTexture* pTexture = FindTexture(strName);

	if (!pTexture)
		return;

	pTexture->SetColorKey(iColorKey, iIdx);
}

void CResourceManager::ReleaseTexture(const std::string& strName)
{
	std::unordered_map<std::string, CSharedPtr<CTexture>>::iterator	iter = m_mapTexture.find(strName);

	if (iter->second->GetRefCount() == 1)
		m_mapTexture.erase(iter);
}

CTexture* CResourceManager::FindTexture(const std::string& strName)
{
	std::unordered_map<std::string, CSharedPtr<CTexture>>::iterator	iter = m_mapTexture.find(strName);

	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second;
}

bool CResourceManager::CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName)
{
	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (pSequence)
		return true;

	pSequence = new CAnimationSequence;

	CTexture* pTexture = FindTexture(strTextureName);

	if (!pSequence->Init(strSequenceName, pTexture))
	{
		SAFE_RELEASE(pSequence);
		return false;
	}

	m_mapAnimationSequence.insert(std::make_pair(strSequenceName, pSequence));

    return true;
}

bool CResourceManager::CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName, const TCHAR* pFileName, const std::string& strPathName)
{
	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (pSequence)
		return true;

	if (!LoadTexture(strSequenceName, pFileName, strPathName))
	{
		SAFE_RELEASE(pSequence);
		return false;
	}

	pSequence = new CAnimationSequence;

	CTexture* pTexture = FindTexture(strTextureName);

	if (!pSequence->Init(strSequenceName, pTexture))
	{
		SAFE_RELEASE(pSequence);
		return false;
	}

	m_mapAnimationSequence.insert(std::make_pair(strSequenceName, pSequence));

	return true;
}

bool CResourceManager::CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName)
{
	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (pSequence)
		return true;

	if (!LoadTexture(strSequenceName, vecFileName, strPathName))
	{
		SAFE_RELEASE(pSequence);
		return false;
	}

	pSequence = new CAnimationSequence;

	CTexture* pTexture = FindTexture(strTextureName);

	if (!pSequence->Init(strSequenceName, pTexture))
	{
		SAFE_RELEASE(pSequence);
		return false;
	}

	m_mapAnimationSequence.insert(std::make_pair(strSequenceName, pSequence));

	return true;
}

void CResourceManager::AddAnimationFrameData(const std::string& strSequenceName, const Vector2& tStartPos, const Vector2& tSize)
{
	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (!pSequence)
		return;

	pSequence->AddFrameData(tStartPos, tSize);
}

void CResourceManager::AddAnimationFrameData(const std::string& strSequenceName, float fPosX, float fPosY, float fSizeX, float fSizeY)
{
	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (!pSequence)
		return;

	pSequence->AddFrameData(Vector2(fPosX, fPosY), Vector2(fSizeX, fSizeY));
}

void CResourceManager::ReleaseAnimationSequence(const std::string& strName)
{
	std::unordered_map<std::string, CSharedPtr<CAnimationSequence>>::iterator	iter = m_mapAnimationSequence.find(strName);

	if (iter->second->GetRefCount() == 1)
		m_mapAnimationSequence.erase(iter);
}

CAnimationSequence* CResourceManager::FindAnimationSequence(const std::string& strName)
{
	std::unordered_map<std::string, CSharedPtr<CAnimationSequence>>::iterator	iter = m_mapAnimationSequence.find(strName);

	if (iter == m_mapAnimationSequence.end())
		return nullptr;

    return iter->second;
}

bool CResourceManager::Init()
{
	FMOD_RESULT result = FMOD::System_Create(&m_pSystem);

	if (result != FMOD_OK)
		return false;

	result = m_pSystem->init(4093, FMOD_INIT_NORMAL, nullptr);

	if (result != FMOD_OK)
		return false;

	result = m_pSystem->getMasterChannelGroup(&m_pMasterGroup);

	if (result != FMOD_OK)
		return false;

	m_mapChannelGroup.insert(std::make_pair("Master", m_pMasterGroup));

	CreateSoundChannelGroup("BGM");
	CreateSoundChannelGroup("Effect");

	return true;
}

void CResourceManager::Update()
{
	m_pSystem->update();

	std::unordered_map<std::string, CSharedPtr<CSound>>::iterator	iter = m_mapSound.begin();
	std::unordered_map<std::string, CSharedPtr<CSound>>::iterator	iterEnd = m_mapSound.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->second)
			iter->second->Update();
	}
}

CResourceManager::CResourceManager()	:
	m_pSystem(nullptr),
	m_pMasterGroup(nullptr)
{
}

CResourceManager::~CResourceManager()
{
	m_mapSound.clear();
	m_mapAnimationSequence.clear();
	m_mapTexture.clear();

	std::unordered_map<std::string, FMOD::ChannelGroup*>::iterator	iter = m_mapChannelGroup.begin();
	std::unordered_map<std::string, FMOD::ChannelGroup*>::iterator	iterEnd = m_mapChannelGroup.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->release();
	}

	m_mapChannelGroup.clear();

	if (m_pSystem)
	{
		m_pSystem->close();
		m_pSystem->release();
	}
}
