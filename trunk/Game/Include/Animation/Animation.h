#pragma once

#include "AnimationInfo.h"

class CAnimation
{
	friend class CObj;

private:
	class CObj* m_pOwner;
	class CScene* m_pScene;
	std::unordered_map<std::string, AnimationInfo*>	m_mapAnimation;
	AnimationInfo* m_pCurrentAnimation;

public:
	void AddAnimation(const std::string& strSequenceName, bool bLoop = true, float fPlayTime = 1.f, float fPlayScale = 1.f, bool bReverse = false);
	void SetAnimationPlayTime(const std::string& strName, float fPlayTime);
	void SetAnimationPlayScale(const std::string& strName, float fPlayScale);
	void SetAnimationReverse(const std::string& strName, bool bReverse);
	void SetAnimationLoop(const std::string& strName, bool bLoop);
	void SetCurrentAnimation(const std::string& strName);
	void ChangeAnimation(const std::string& strName);
	bool CheckCurrentAnimation(const std::string& strName);
	const std::string GetCurrentAnimationName()	const;
	

private:
	AnimationInfo* FindInfo(const std::string& strName);

public:
	template <typename T>
	void SetEndNotify(const std::string& strSequenceName, T* pObj, void(T::*pFunc)())
	{
		AnimationInfo* pInfo = FindInfo(strSequenceName);

		if (!pInfo)
			return;

		pInfo->pEndFunc = std::bind(pFunc, pObj);
	}

	template <typename T>
	void AddNotify(const std::string& strSequenceName, int iFrame, T* pObj, void(T::* pFunc)())
	{
		AnimationInfo* pInfo = FindInfo(strSequenceName);

		if (!pInfo)
			return;

		AnimationNotify* pNotify = new AnimationNotify;
		pNotify->iFrame = iFrame;
		pNotify->pFunc = std::bind(pFunc, pObj);

		pInfo->vecNotify.push_back(pNotify);
	}

public:
	void Update(float fTime);
	CAnimation* Clone();

private:
	CAnimation();
	CAnimation(const CAnimation& anim);
	~CAnimation();
};

