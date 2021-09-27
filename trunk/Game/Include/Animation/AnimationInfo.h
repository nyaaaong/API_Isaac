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

// ��� �������� �����Ѵ�
struct AnimationInfo
{
	CSharedPtr<CAnimationSequence> pSequence;
	int		iFrame;	// ���� �� ����������
	float	fTime;	// ���� �ð�
	float	fFrameTime;	// 1�������� �� �� �ȿ� �귯�� �ϴ���
	float	fPlayTime;	// ����� �ѹ� �� �� �ʿ��� �ð�
	float	fPlayScale;	// ��� ����
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