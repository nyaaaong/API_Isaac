#pragma once

#include "Texture.h"

class CAnimationSequence :
	public CRef
{
	friend class CResourceManager;

private:
	ETexture_Type	m_eTextureType;
	CSharedPtr<CTexture>	m_pTexture;
	std::vector<AnimationFrameData>	m_vecFrameData; // 프레임 당 텍스쳐의 위치와 크기를 갖고 있다.

public:
	CTexture* GetTexture()
	{
		return m_pTexture;
	}

	ETexture_Type GetTextureType()	const
	{
		return m_eTextureType;
	}

	const AnimationFrameData& GetFrameData(int iIdx)	const
	{
		return m_vecFrameData[iIdx];
	}

	int GetFrameCount()	const
	{
		return static_cast<int>(m_vecFrameData.size());
	}

public:
	bool Init(const std::string& strName, CTexture* pTexture);
	void AddFrameData(const Vector2& tStartPos, const Vector2& tSize);
	void AddFrameData(float fPosX, float fPosY, float fSizeX, float fSizeY);

private:
	CAnimationSequence();
	~CAnimationSequence();

};

