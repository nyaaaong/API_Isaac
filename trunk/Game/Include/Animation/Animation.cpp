
#include "Animation.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CAnimation::CAnimation()	:
	m_pOwner(nullptr),
	m_pScene(nullptr),
	m_pCurrentAnimation(nullptr)
{
}

CAnimation::CAnimation(const CAnimation& anim) :
	m_pOwner(nullptr),
	m_pScene(nullptr),
	m_pCurrentAnimation(nullptr)
{
	// const 객체인 anim에서 iterator을 사용하려면 const_iterator을 사용해야 한다.
	std::unordered_map<std::string, AnimationInfo*>::const_iterator	iter = anim.m_mapAnimation.begin();
	std::unordered_map<std::string, AnimationInfo*>::const_iterator	iterEnd = anim.m_mapAnimation.end();

	for (; iter != iterEnd; ++iter)
	{
		AnimationInfo* pInfo = new AnimationInfo;

		pInfo->pSequence = iter->second->pSequence;
		pInfo->fFrameTime = iter->second->fFrameTime;
		pInfo->fPlayTime = iter->second->fPlayTime;
		pInfo->fPlayScale = iter->second->fPlayScale;
		pInfo->bLoop = iter->second->bLoop;
		pInfo->bReverse = iter->second->bReverse;

		if (anim.m_pCurrentAnimation->pSequence->GetName() == pInfo->pSequence->GetName())
			m_pCurrentAnimation = pInfo;

		m_mapAnimation.insert(std::make_pair(iter->first, pInfo));
	}
}

CAnimation::~CAnimation()
{
	std::unordered_map<std::string, AnimationInfo*>::iterator	iter = m_mapAnimation.begin();
	std::unordered_map<std::string, AnimationInfo*>::iterator	iterEnd = m_mapAnimation.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

void CAnimation::AddAnimation(const std::string& strSequenceName, bool bLoop, float fPlayTime, float fPlayScale, bool bReverse)
{
	CAnimationSequence* pSequence = m_pScene->GetSceneResource()->FindAnimationSequence(strSequenceName);

	if (!pSequence)
		return;

	AnimationInfo* pInfo = new AnimationInfo;

	pInfo->pSequence = pSequence;
	pInfo->bLoop = bLoop;
	pInfo->fPlayTime = fPlayTime;
	pInfo->fPlayScale = fPlayScale;
	pInfo->bReverse = bReverse;
	pInfo->fFrameTime = fPlayTime / pSequence->GetFrameCount();

	// 맨 처음 등록하는 애니메이션은 현재 애니메이션으로 지정한다
	if (m_mapAnimation.empty())
		m_pCurrentAnimation = pInfo;

	m_mapAnimation.insert(std::make_pair(strSequenceName, pInfo));
}

void CAnimation::SetAnimationPlayTime(const std::string& strName, float fPlayTime)
{
	AnimationInfo* pInfo = FindInfo(strName);

	if (!pInfo)
		return;

	pInfo->fPlayTime = fPlayTime;
}

void CAnimation::SetAnimationPlayScale(const std::string& strName, float fPlayScale)
{
	AnimationInfo* pInfo = FindInfo(strName);

	if (!pInfo)
		return;

	pInfo->fPlayScale = fPlayScale;
}

void CAnimation::SetAnimationReverse(const std::string& strName, bool bReverse)
{
	AnimationInfo* pInfo = FindInfo(strName);

	if (!pInfo)
		return;

	pInfo->bReverse = bReverse;
}

void CAnimation::SetAnimationLoop(const std::string& strName, bool bLoop)
{
	AnimationInfo* pInfo = FindInfo(strName);

	if (!pInfo)
		return;

	pInfo->bLoop = bLoop;
}

void CAnimation::SetCurrentAnimation(const std::string& strName)
{
	m_pCurrentAnimation = FindInfo(strName);

	if (!m_pCurrentAnimation)
		return;

	m_pCurrentAnimation->iFrame = 0;
	m_pCurrentAnimation->fTime = 0.f;

	size_t iSize = m_pCurrentAnimation->vecNotify.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		m_pCurrentAnimation->vecNotify[i]->bCall = false;
	}
}

void CAnimation::ChangeAnimation(const std::string& strName)
{
	if (!m_pCurrentAnimation)
		return;

	if (m_pCurrentAnimation->pSequence->GetName() == strName)
		return;

	m_pCurrentAnimation->iFrame = 0;
	m_pCurrentAnimation->fTime = 0.f;

	size_t iSize = m_pCurrentAnimation->vecNotify.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		m_pCurrentAnimation->vecNotify[i]->bCall = false;
	}

	SetCurrentAnimation(strName);
}

bool CAnimation::CheckCurrentAnimation(const std::string& strName)
{
	if (!m_pCurrentAnimation)
		return false;

    return m_pCurrentAnimation->pSequence->GetName() == strName;
}

const std::string CAnimation::GetCurrentAnimationName() const
{
	if (!m_pCurrentAnimation)
		return "";

	return m_pCurrentAnimation->pSequence->GetName();
}

AnimationInfo* CAnimation::FindInfo(const std::string& strName)
{
	std::unordered_map<std::string, AnimationInfo*>::iterator	iter = m_mapAnimation.find(strName);

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;
}

void CAnimation::Update(float fTime)
{
	m_pCurrentAnimation->fTime += fTime * m_pCurrentAnimation->fPlayScale;

	bool bAnimEnd = false;

	if (m_pCurrentAnimation->fTime >= m_pCurrentAnimation->fFrameTime)
	{
		m_pCurrentAnimation->fTime -= m_pCurrentAnimation->fFrameTime;

		if (m_pCurrentAnimation->bReverse)
		{
			--m_pCurrentAnimation->iFrame;

			if (m_pCurrentAnimation->iFrame < 0)
				bAnimEnd = true;
		}

		else
		{
			++m_pCurrentAnimation->iFrame;

			if (m_pCurrentAnimation->iFrame == m_pCurrentAnimation->pSequence->GetFrameCount())
				bAnimEnd = true;
		}
	}

	size_t iSize = m_pCurrentAnimation->vecNotify.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		if (!m_pCurrentAnimation->vecNotify[i]->bCall && m_pCurrentAnimation->vecNotify[i]->iFrame == m_pCurrentAnimation->iFrame) // 만약 Notify가 호출되지 않았으면서, Notify가 세팅된 프레임에 다다른 경우
		{
			m_pCurrentAnimation->vecNotify[i]->bCall = true;
			m_pCurrentAnimation->vecNotify[i]->pFunc();
		}
	}

	if (bAnimEnd)
	{
		if (m_pCurrentAnimation->bLoop)
		{
			if (m_pCurrentAnimation->bReverse)
				m_pCurrentAnimation->iFrame = m_pCurrentAnimation->pSequence->GetFrameCount() - 1;

			else
				m_pCurrentAnimation->iFrame = 0;
		}

		else
		{
			if (m_pCurrentAnimation->bReverse)
				m_pCurrentAnimation->iFrame = 0;

			else
				m_pCurrentAnimation->iFrame = m_pCurrentAnimation->pSequence->GetFrameCount() - 1;
		}

		if (m_pCurrentAnimation->pEndFunc) // 모션이 끝난 경우 EndFunction이 있는 경우 호출
			m_pCurrentAnimation->pEndFunc();

		if (m_pCurrentAnimation->bLoop)
		{
			size_t iSize = m_pCurrentAnimation->vecNotify.size();

			for (size_t i = 0; i < iSize; ++i)
			{
				m_pCurrentAnimation->vecNotify[i]->bCall = false;
			}
		}
	}
}

CAnimation* CAnimation::Clone()
{
	return new CAnimation(*this);
}
