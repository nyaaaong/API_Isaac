
#pragma once
#pragma warning(disable: 26812)		//'enum'(Enum.3) ��� 'enum class'�� ����ϼ���. ��� ����
#pragma warning(disable: 6031)		//��ȯ ���� ���õǾ����ϴ�. 'rand'. ��� ����
#pragma warning(disable: 6011)		//NULL ������ 'm_pArrWidget[i]'��(��) �������ϰ� �ֽ��ϴ�. ��� ����
#pragma warning(disable: 26451)		//��� �����÷�: 4 ����Ʈ ���� '-' �����ڸ� ����� ���� ����� 8 ����Ʈ ���� ĳ��Ʈ�մϴ�. �����÷θ� �����Ϸ��� '-' �����ڸ� ȣ���ϱ� ���� �� �������� ���Ŀ� ���� ĳ��Ʈ�մϴ�(io.2). ��� ����
#pragma warning(disable: 6029)		//'fread'�� ���� ȣ�⿡�� ���� �������� �߻��� �� �ֽ��ϴ�.�˻���� ���� �� '~'��(��) ����߽��ϴ�. ��� ����


#include <Windows.h>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <crtdbg.h>
#include <functional>
#include <assert.h>

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
#define MAP_PATH		"MapPath"

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
	float	fTearSpeed;
	float	fShotSpeed;
	float	fTearDistance;
	float	fMoveSpeed;
};

struct CollisionProfile
{
	std::string						strName;
	ECollision_Channel				eChannel;
	bool							bCollisionEnable;
	std::vector<ECollision_State>	vecState;	// Channel�� ����ŭ �����ϸ� ���� ���������� �ٸ� �������ϰ� �浹ó���� �� �� �ش� ���������� ����ϴ� ä�ΰ� Ignore���� Collision���� �Ǵ��� �� ����Ѵ�.

	CollisionProfile() :
		eChannel(Channel_Max),
		bCollisionEnable(true)
	{
	}
};