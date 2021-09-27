#pragma once

#include "../Resource/Texture.h"
#include "../Animation/AnimationInfo.h"
#include "../Resource/AnimationSequence.h"
#include "../Resource/Sound.h"

/*
������ ���ҽ��� ������ �ְ� �ؾ��ϰ�, �ٸ� �������� ������ �ϱ����� ���������.
������Ʈ �κп��� �ʱ�ȭ�� �� �ؽ��ĸ� �ҷ����� ���� Ŭ�����̴�.
������Ʈ�� ���� ������ GetSceneResource �Լ��� ���� �ҷ��� �� �ؽ��ĸ� ó���Ѵ�.
*/

class CSceneResource
{
	friend class CScene;

private:
	std::unordered_map<std::string, CSharedPtr<CTexture>>	m_mapTexture;
	std::unordered_map<std::string, CSharedPtr<CAnimationSequence>>	m_mapAnimationSequence;
	std::unordered_map<std::string, CSharedPtr<CSound>>	m_mapSound;

public:
	bool LoadSound(const std::string& strGroupName, bool bLoop, const std::string& strName, const char* cFileName, const std::string& strPathName = SOUND_PATH);
	bool SetVolume(int iVolume);
	bool SetVolume(const std::string& strGroupName, int iVolume);
	bool SoundPlay(const std::string& strName);
	bool SoundStop(const std::string& strName);
	bool SoundPause(const std::string& strName);
	bool SoundResume(const std::string& strName);
	CSound* FindSound(const std::string& strName);

public:
	bool LoadTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName = TEXTURE_PATH);
	bool LoadTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& strName, const TCHAR* cFullPath);
	void SetTextureColorKey(const std::string& strName, const unsigned char r = 255, const unsigned char g = 0, const unsigned char b = 255, int iIdx = 0);
	CTexture* FindTexture(const std::string& strName);

public:
	bool CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName);
	bool CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName, const TCHAR* pFileName, const std::string& strPathName = TEXTURE_PATH);
	bool CreateAnimationSequence(const std::string& strSequenceName, const std::string& strTextureName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName = TEXTURE_PATH);
	void AddAnimationFrameData(const std::string& strSequenceName, const Vector2& tStartPos, const Vector2& tSize);
	void AddAnimationFrameData(const std::string& strSequenceName, float fPosX, float fPosY, float fSizeX, float fSizeY);

	CAnimationSequence* FindAnimationSequence(const std::string& strName);

private:
	CSceneResource();
	~CSceneResource();
};

