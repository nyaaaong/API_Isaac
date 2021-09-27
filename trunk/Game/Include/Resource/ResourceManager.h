#pragma once

#include "Texture.h"
#include "AnimationSequence.h"
#include "Sound.h"

/*
SceneResource 클래스에서 텍스쳐를 이용하기 위한 클래스이다. 
*/

class CResourceManager
{
private:
	std::unordered_map<std::string, CSharedPtr<CTexture>>	m_mapTexture;
	std::unordered_map<std::string, CSharedPtr<CAnimationSequence>>	m_mapAnimationSequence;

private:
	FMOD::System* m_pSystem;
	FMOD::ChannelGroup* m_pMasterGroup;
	std::unordered_map<std::string, FMOD::ChannelGroup*>	m_mapChannelGroup;
	std::unordered_map<std::string, CSharedPtr<CSound>>	m_mapSound;

public:
	bool LoadSound(const std::string& strGroupName, bool bLoop, const std::string& strName, const char* cFileName, const std::string& strPathName = SOUND_PATH);
	bool CreateSoundChannelGroup(const std::string& strName);
	bool SetVolume(int iVolume);
	bool SetVolume(const std::string& strGroupName, int iVolume);
	bool SoundPlay(const std::string& strName);
	bool SoundStop(const std::string& strName);
	bool SoundPause(const std::string& strName);
	bool SoundResume(const std::string& strName);
	void ReleaseSound(const std::string& strName);
	FMOD::ChannelGroup* FindSoundChannelGroup(const std::string& strName);
	CSound* FindSound(const std::string& strName);

public:
	bool LoadTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName = TEXTURE_PATH);
	bool LoadTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& strName, const TCHAR* cFullPath);
	void SetTextureColorKey(const std::string& strName, const unsigned char r, const unsigned char g, const unsigned char b, int iIdx = 0);
	void ReleaseTexture(const std::string& strName);
	CTexture* FindTexture(const std::string& strName);

public:
	bool CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName);
	bool CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName, const TCHAR* pFileName, const std::string& strPathName = TEXTURE_PATH);
	bool CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName = TEXTURE_PATH);
	void AddAnimationFrameData(const std::string& strSequenceName, const Vector2& tStartPos, const Vector2& tSize);
	void AddAnimationFrameData(const std::string& strSequenceName, float fPosX, float fPosY, float fSizeX, float fSizeY);

	void ReleaseAnimationSequence(const std::string& strName);

	CAnimationSequence* FindAnimationSequence(const std::string& strName);

public:
	bool Init();
	void Update();

private:
	static CResourceManager* m_pInst;

public:
	static CResourceManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CResourceManager;

		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	CResourceManager();
	~CResourceManager();
};

