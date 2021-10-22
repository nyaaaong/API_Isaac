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
	float	m_fM4PDist;		// ���Ϳ� �÷��̾� ���� �Ÿ�
	float	m_fMaxDist;		// ������ �÷��̾� ���� �Ÿ�
	Vector2	m_arrDir[4];	// �������� �̱� ���� ���� �迭
	bool	m_bUseKnockBack;
	bool	m_bBlockCollision;	// ���� �浹���� �� ������ �ٲٱ� ����
	std::string	m_strCurAnim;
	bool	m_bSmokeEnd;	// ���Ⱑ ���������� �����̵���

public:
	void BlockCollision()
	{
		m_bBlockCollision = true;
	}

protected:
	void GetM2PDir();	// Monster To Player : ���� ���� �÷��̾��� ������ �����ش�
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

