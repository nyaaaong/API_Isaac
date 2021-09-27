#pragma once

#include "../Resource/AnimationSequence.h"

struct AnimationNotify
{
	int		iFrame;
	bool	bCall;
	std::function<void()>	pFunc;

	AnimationNotify()	:
		iFrame(0),
		bCall(false)
	{}
};

// 모션 정보들을 저장한다
struct AnimationInfo
{
	CSharedPtr<CAnimationSequence> pSequence;
	int		iFrame;	// 현재 몇 프레임인지
	float	fTime;	// 현재 시간
	float	fFrameTime;	// 1프레임이 몇 초 안에 흘러야 하는지
	float	fPlayTime;	// 모션이 한번 돌 때 필요한 시간
	float	fPlayScale;	// 재생 배율
	bool	bLoop;
	bool	bReverse;
	std::function<void()>	pEndFunc;
	std::vector<AnimationNotify*>	vecNotify;

	AnimationInfo() :
		pSequence(nullptr),
		iFrame(0),
		fTime(0.f),
		fFrameTime(0.f),
		fPlayTime(0.f),
		fPlayScale(1.f),
		bLoop(false),
		bReverse(false)
	{}

	~AnimationInfo()
	{
		size_t	iSize = vecNotify.size();

		for (size_t i = 0; i < iSize; ++i)
		{
			SAFE_DELETE(vecNotify[i]);
		}
	}
};