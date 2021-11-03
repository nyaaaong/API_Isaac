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
	bool	m_bHit;		// 체력이 깎였을 경우
	float	m_fSkill1Time;
	float	m_fNoDmgTimer;		// 무적 시간을 조절하기 위해 누적시킬 시간
	float	m_fNoDmgTimerMax;	// 피격 시 일시 무적 시간
	float	m_fBlinkTimer;	// 깜빡이는 속도를 조절하기 위해 누적시킬 시간
	float	m_fBlinkSpeed;	// 피격 시 깜빡이는 속도
	class CPlayerBody* m_pPlayerBody;
	Vector2	m_tMoveDir;
	bool	m_bDie;	// 중복되서 들어오지 않도록
	float	m_fAnimDelay;
	bool	m_bIsItem;
	CObj* m_ItemAddEffect;
	bool	m_bIsItemAnim;
	bool	m_bCheatNoDamage; // NoDamage를 구별하기 위함

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
	void CheatBossRoom(float fTime);
	void CheatNoDamage(float fTime);
	void CheatDamageUp(float fTime);

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

public:
	virtual void Move(const Vector2& tDir, bool bUseField);
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual float SetDamage(float fDamage);

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

