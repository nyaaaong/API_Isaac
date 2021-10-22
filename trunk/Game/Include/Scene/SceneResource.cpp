
#include "SceneResource.h"
#include "SceneManager.h"
#include "../Resource/ResourceManager.h"

CSceneResource::CSceneResource()
{
}

CSceneResource::~CSceneResource()
{
	{
		std::unordered_map<std::string, CSharedPtr<CAnimationSequence>>::iterator	iter = m_mapAnimationSequence.begin();
		std::unordered_map<std::string, CSharedPtr<CAnimationSequence>>::iterator	iterEnd = m_mapAnimationSequence.end();

		std::string	strName;

		for (; iter != iterEnd;)
		{
			strName = iter->first;

			iter = m_mapAnimationSequence.erase(iter);

			CResourceManager::GetInst()->ReleaseAnimationSequence(strName);
		}
	}

	{
		std::unordered_map<std::string, CSharedPtr<CTexture>>::iterator	iter = m_mapTexture.begin();
		std::unordered_map<std::string, CSharedPtr<CTexture>>::iterator	iterEnd = m_mapTexture.end();

		std::string	strName;

		for (; iter != iterEnd;)
		{
			strName = iter->first;

			iter = m_mapTexture.erase(iter);

			CResourceManager::GetInst()->ReleaseTexture(strName);
		}
	}

	{
		std::unordered_map<std::string, CSharedPtr<CSound>>::iterator	iter = m_mapSound.begin();
		std::unordered_map<std::string, CSharedPtr<CSound>>::iterator	iterEnd = m_mapSound.end();

		std::string	strName;

		for (; iter != iterEnd;)
		{
			strName = iter->first;

			iter = m_mapSound.erase(iter);

			CResourceManager::GetInst()->ReleaseSound(strName);
		}
	}
}

bool CSceneResource::LoadTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName)
{
	if (FindTexture(strName))
		return true;

	if (!CResourceManager::GetInst()->LoadTexture(strName, cFileName, strPathName))
		return false;

	CTexture* pTexture = CResourceManager::GetInst()->FindTexture(strName);

	m_mapTexture.insert(std::make_pair(strName, pTexture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& strName, const TCHAR* cFullPath)
{
	if (FindTexture(strName))
		return true;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(strName, cFullPath))
		return false;

	CTexture* pTexture = CResourceManager::GetInst()->FindTexture(strName);

	m_mapTexture.insert(std::make_pair(strName, pTexture));

	return true;
}

bool CSceneResource::LoadTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName)
{
	if (FindTexture(strName))
		return true;

	if (!CResourceManager::GetInst()->LoadTexture(strName, vecFileName, strPathName))
		return false;

	CTexture* pTexture = CResourceManager::GetInst()->FindTexture(strName);

	m_mapTexture.insert(std::make_pair(strName, pTexture));

	return true;
}

void CSceneResource::SetTextureColorKey(const std::string& strName, const unsigned char r, const unsigned char g, const unsigned char b, int iIdx)
{
	CResourceManager::GetInst()->SetTextureColorKey(strName, r, g, b, iIdx);
}

void CSceneResource::SetTextureColorKey(const std::string& strName, unsigned int iColorKey, int iIdx)
{
	CResourceManager::GetInst()->SetTextureColorKey(strName, iColorKey, iIdx);
}

CTexture* CSceneResource::FindTexture(const std::string& strName)
{
	std::unordered_map<std::string, CSharedPtr<CTexture>>::iterator	iter = m_mapTexture.find(strName);

	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second;
}

bool CSceneResource::CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName)
{
	if (FindAnimationSequence(strSequenceName))
		return true;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(strSequenceName, strTextureName))
		return false;

	CAnimationSequence* pSequence = CResourceManager::GetInst()->FindAnimationSequence(strSequenceName);

	m_mapAnimationSequence.insert(std::make_pair(strSequenceName, pSequence));

	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName, const TCHAR* pFileName, const std::string& strPathName)
{
	if (FindAnimationSequence(strSequenceName))
		return true;

	LoadTexture(strTextureName, pFileName, strPathName);

	if (!CResourceManager::GetInst()->CreateAnimationSequence(strSequenceName, strTextureName))
		return false;

	CAnimationSequence* pSequence = CResourceManager::GetInst()->FindAnimationSequence(strSequenceName);

	m_mapAnimationSequence.insert(std::make_pair(strSequenceName, pSequence));

	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName)
{
	if (FindAnimationSequence(strSequenceName))
		return true;

	LoadTexture(strTextureName, vecFileName, strPathName);

	if (!CResourceManager::GetInst()->CreateAnimationSequence(strSequenceName, strTextureName))
		return false;

	CAnimationSequence* pSequence = CResourceManager::GetInst()->FindAnimationSequence(strSequenceName);

	m_mapAnimationSequence.insert(std::make_pair(strSequenceName, pSequence));

	return true;
}

void CSceneResource::AddAnimationFrameData(const std::string& strSequenceName, const Vector2& tStartPos, const Vector2& tSize)
{
	if (CSceneManager::GetInst()->IsInputAnimFrameData()) // 吝汗 积己 规瘤
		return;

	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (!pSequence)
		return;

	pSequence->AddFrameData(tStartPos, tSize);
}

void CSceneResource::AddAnimationFrameData(const std::string& strSequenceName, float fPosX, float fPosY, float fSizeX, float fSizeY)
{
	if (CSceneManager::GetInst()->IsInputAnimFrameData()) // 吝汗 积己 规瘤
		return;

	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (!pSequence)
		return;

	pSequence->AddFrameData(Vector2(fPosX, fPosY), Vector2(fSizeX, fSizeY));
}

CAnimationSequence* CSceneResource::FindAnimationSequence(const std::string& strName)
{
	std::unordered_map<std::string, CSharedPtr<CAnimationSequence>>::iterator	iter = m_mapAnimationSequence.find(strName);

	if (iter == m_mapAnimationSequence.end())
		return nullptr;

	return iter->second;
}

bool CSceneResource::LoadSound(const std::string& strGroupName, bool bLoop, const std::string& strName, const char* cFileName, const std::string& strPathName)
{
	if (FindSound(strName))
		return true;

	if (!CResourceManager::GetInst()->LoadSound(strGroupName, bLoop, strName, cFileName, strPathName))
		return false;

	CSound* pSound = CResourceManager::GetInst()->FindSound(strName);

	m_mapSound.insert(std::make_pair(strName, pSound));

	return true;
}

bool CSceneResource::SetVolume(int iVolume)
{
	return CResourceManager::GetInst()->SetVolume(iVolume);
}

bool CSceneResource::SetVolume(const std::string& strGroupName, int iVolume)
{
	return CResourceManager::GetInst()->SetVolume(strGroupName, iVolume);
}

bool CSceneResource::SoundPlay(const std::string& strName)
{
	return CResourceManager::GetInst()->SoundPlay(strName);
}

bool CSceneResource::SoundStop(const std::string& strName)
{
	return CResourceManager::GetInst()->SoundStop(strName);
}

bool CSceneResource::SoundPause(const std::string& strName)
{
	return CResourceManager::GetInst()->SoundPause(strName);
}

bool CSceneResource::SoundResume(const std::string& strName)
{
	return CResourceManager::GetInst()->SoundResume(strName);
}

bool CSceneResource::IsPlaying(const std::string& strName)
{
	return CResourceManager::GetInst()->IsPlaying(strName);
}

CSound* CSceneResource::FindSound(const std::string& strName)
{
	std::unordered_map<std::string, CSharedPtr<CSound>>::iterator	iter = m_mapSound.find(strName);

	if (iter == m_mapSound.end())
		return nullptr;

	return iter->second;
}
