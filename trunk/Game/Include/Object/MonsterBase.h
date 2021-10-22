#pragma once

#include "Character.h"

class CMonsterBase :
	public CCharacter
{
	friend class CScene;

protected:
	Vector2	m_tDir;
	Vector2	m_tM2PDir;
	float	m_fFireTime;
	float	m_fFireTimeMax;
	int		m_iCount;
	float	m_fM4PDist;		// 몬스터와 플레이어 사이 거리
	float	m_fMaxDist;		// 몬스터의 플레이어 감지 거리
	Vector2	m_arrDir[4];	// 랜덤으로 뽑기 위한 방향 배열
	bool	m_bUseKnockBack;
	bool	m_bBlockCollision;	// 블럭에 충돌됐을 때 방향을 바꾸기 위함
	std::string	m_strCurAnim;
	bool	m_bSmokeEnd;	// 연기가 끝났을때만 움직이도록

public:
	void BlockCollision()
	{
		m_bBlockCollision = true;
	}

protected:
	void GetM2PDir();	// Monster To Player : 몬스터 기준 플레이어의 방향을 구해준다
	void RandomDir();

public:
	virtual bool Init();
	virtual CMonsterBase* Clone();

public:
	virtual void Move(const Vector2& tDir, bool bUseField);
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);

protected:
	CMonsterBase();
	CMonsterBase(const CMonsterBase& obj);
	virtual ~CMonsterBase();
};

