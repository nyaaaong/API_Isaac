
#pragma once
#pragma warning(disable: 26812)	//'enum'(Enum.3) 대신 'enum class'를 사용하세요. 경고 무시
#pragma warning(disable: 6031)	//반환 값이 무시되었습니다. 'rand'. 경고 무시
#pragma warning(disable: 6011)		//NULL 포인터 'm_pArrWidget[i]'을(를) 역참조하고 있습니다. 경고 무시


#include <Windows.h>
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <crtdbg.h>
#include <functional>
#include <assert.h>

#include "resource.h"
#include "Math.h"
#include "Flag.h"
#include "SharedPtr.h"
#include "fmod.hpp"

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "fmod64_vc.lib")

#ifdef	_DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define GRAVITY	9.8f

#define KEY_COUNT_MAX	256


#define ROOT_PATH		"RootPath"
#define TEXTURE_PATH	"TexturePath"
#define SOUND_PATH		"SoundPath"

#define SAFE_DELETE(p)			if (p)	{ delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p)	if (p)	{ delete[] p; p = nullptr; }
#define SAFE_RELEASE(p)			if (p)	{ p->Release(); p = nullptr; }

#define PLAYER_HP_MAX	6.f
#define	PLAYER_BODY_OFFSET_Y	45.f

struct Resolution
{
	int iW;
	int iH;

	Resolution() :
		iW(1280),
		iH(720)
	{}
};

struct RectInfo
{
	float fL;
	float fT;
	float fR;
	float fB;

	RectInfo()	:
		fL(0.f),
		fT(0.f),
		fR(0.f),
		fB(0.f)
	{}
};

struct SphereInfo
{
	Vector2	tCenter;
	float	fRadius;

	SphereInfo() :
		fRadius(0.f)
	{}
};

struct AnimationFrameData
{
	Vector2 tStartPos;
	Vector2	tSize;
};

struct CharacterInfo
{
	float	fAttack;
	float	fHP;
	float	fHPMax;
	int		iBomb;
	int		iBombMax;
	float	fTearTimer;
	float	fShotSpeed;
	float	fTearDistance;
	float	fMoveSpeed;
};

struct CollisionProfile
{
	std::string						strName;
	ECollision_Channel				eChannel;
	bool							bCollisionEnable;
	std::vector<ECollision_State>	vecState;	// Channel의 수만큼 저장하며 현재 프로파일이 다른 프로파일과 충돌처리를 할 때 해당 프로파일이 사용하는 채널과 Ignore인지 Collision인지 판단할 떄 사용한다.

	CollisionProfile() :
		eChannel(Channel_Max),
		bCollisionEnable(true)
	{
	}
};