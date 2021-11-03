#pragma once

#include "MonsterBase.h"

class CIsaac :
    public CMonsterBase
{
public:
	CIsaac();
	CIsaac(const CIsaac& obj);
	virtual ~CIsaac();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CIsaac* Clone();

private:
	float	m_fTearTimer;
	float	m_fPatternTimer;
	float	m_fPatternTimerMax;
	float	m_fPatternDelay;
	float	m_fMonsterSpawnTimer;
	float	m_fMonsterSpawnTimerMax;
	float	m_fFire1Delay;
	float	m_fFire2Delay;
	float	m_fFire1DelayMax;
	float	m_fFire2DelayMax;
	float	m_fM2PAngle2;
	int		m_iFire1BulletCount;
	int		m_iFire1BulletCountMax;
	int		m_iFire2BulletCount;
	int		m_iFire2BulletCountMax;
	bool	m_bProgress;
	bool	m_bNeedTransform;
	Vector2	m_tM2PDir2;
	EDie_State	m_eDieState;
	EFire_State	m_eFire1State;
	EFire_State	m_eFire2State;
	CCharacter* m_pPlayer;
	EIsaac_Status	m_eStatus;

private:
	void TransformAnim();
	void TransformAnimEnd();
	void CheckPhase();
	void BossPattern(float fTime);
	void DetectPlayer(float fTime);
	void Attack1(float fTime);
	void Attack2(float fTime);
	void JumpPattern1();
	void JumpPattern2();
	void JumpEnd();

private:
	void FireLoop();
	void FireCross(ESpecial_Tear eSpecialPattern = ESpecial_Tear::None);
	void FireReverseCross(ESpecial_Tear eSpecialPattern = ESpecial_Tear::None);
	void Fire8Dir();
	void FirePattern1();
	void FirePattern1Progress(float fTime);
	void FirePattern2();
	void FirePattern2Progress(float fTime);

private:
	void BossDieEvent();
	void BossDieEventProgress();
	void BossDieEventEnd();
	void BossMoveToPlayer();

private:
	void GetM2PDir2();

private:
	void MonsterSpawn(float fTime);

public:
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
};

