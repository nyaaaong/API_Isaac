#include "AnimationSequence.h"

bool CAnimationSequence::Init(const std::string& strName, CTexture* pTexture)
{
	m_strName = strName;
	m_pTexture = pTexture;
	m_eTextureType = m_pTexture->GetTextureType();

	return true;
}

void CAnimationSequence::AddFrameData(const Vector2& tStartPos, const Vector2& tSize)
{
	AnimationFrameData	tData;
	tData.tStartPos = tStartPos;
	tData.tSize = tSize;

	m_vecFrameData.push_back(tData);
}

void CAnimationSequence::AddFrameData(float fPosX, float fPosY, float fSizeX, float fSizeY)
{
	AnimationFrameData	tData;
	tData.tStartPos = Vector2(fPosX, fPosY);
	tData.tSize = Vector2(fSizeX, fSizeY);

	m_vecFrameData.push_back(tData);
}

CAnimationSequence::CAnimationSequence()	:
	m_eTextureType(ETexture_Type::ATLAS)
{
}

CAnimationSequence::~CAnimationSequence()
{
}
