#pragma once

#include "Character.h"

class CPlayer :
    public CCharacter
{
	friend class CScene;
	friend class CPlayerBody;
	friend class CObjManager;

private:
	bool	m_bIsFire;
	bool	m_bIsMove;
	bool	m_bUseBomb;
	bool	m_bMoveUp;
	bool	m_bMoveDown;
	bool	m_bHit;		// ü���� ���� ���
	float	m_fSkill1Time;
	float	m_fNoDmgTimer;		// ���� �ð��� �����ϱ� ���� ������ų �ð�
	float	m_fNoDmgTimerMax;	// �ǰ� �� �Ͻ� ���� �ð�
	float	m_fBlinkTimer;	// �����̴� �ӵ��� �����ϱ� ���� ������ų �ð�
	float	m_fBlinkSpeed;	// �ǰ� �� �����̴� �ӵ�
	class CPlayerBody* m_pPlayerBody;
	Vector2	m_tMoveDir;
	bool	m_bDie;	// �ߺ��Ǽ� ������ �ʵ���
	class CMother* m_pMother;
	float	m_fAnimDelay;
	bool	m_bIsItem;
	CObj* m_ItemAddEffect;
	bool	m_bIsItemAnim;

public:
	bool IsItem()	const
	{
		return m_bIsItem;
	}

	bool IsMove()	const
	{
		return m_bIsMove;
	}

	const Vector2& GetMoveDir()	const
	{
		return m_tMoveDir;
	}

public:
	void SetBoss(class CMother* pMother)
	{
		m_pMother = pMother;
	}

	void UseBomb(bool bUse)
	{
		m_bUseBomb = bUse;
	}

private:
	void NoDamageTime(float fTime);

protected:
	virtual void SetFireStart();
	virtual void SetItemFireStart();

public:
	void AddItem();

private:
	void AddPlayerAnimation();
	void AddNotify();
	void AddCallback();
	void ChangeDirAnimation(const std::string& strAnimType);
	void DefaultAnimation();
	bool CheckMoveUpDown();
	void UpdateMoveUpDown();

private:
	void MoveUp(float fTime);
	void MoveDown(float fTime);
	void MoveLeft(float fTime);
	void MoveRight(float fTime);
	void FireUp(float fTime);
	void FireDown(float fTime);
	void FireLeft(float fTime);
	void FireRight(float fTime);
	void FireEnd();
	void ItemFireEnd();
	void Bomb(float fTime);
	void IsaacDeath(float fTime);
	void IsaacDeathEnd();
	void IsaacAddItemUpdater(float fTime);

private:
	void CheatDie(float fTime);
	void CheatBossRoom(float fTime);
	void CheatBossHurt(float fTime);

public:
	virtual void Move(const Vector2& tDir, bool bUseField);
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual float SetDamage(float fDamage);
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CPlayer* Clone();

protected:
	CPlayer();
	CPlayer(const CPlayer& obj);
	virtual ~CPlayer();
};

