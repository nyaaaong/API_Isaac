#pragma once

#include "Character.h"


class CPlayer :
    public CCharacter
{
	friend class CScene;
	friend class CPlayerBody;

private:
	bool	m_bIsFire;
	bool	m_bIsMove;
	bool	m_bBombEnable;
	bool	m_bMoveUp;
	bool	m_bMoveDown;
	bool	m_bHit;		// 체력이 깎였을 경우
	float	m_fSkill1Time;
	float	m_fNoDmgTimer;		// 무적 시간을 조절하기 위해 누적시킬 시간
	float	m_fNoDmgTimerMax;	// 피격 시 일시 무적 시간
	float	m_fBlinkTimer;	// 깜빡이는 속도를 조절하기 위해 누적시킬 시간
	float	m_fBlinkSpeed;	// 피격 시 깜빡이는 속도
	class CPlayerBody* m_pPlayerBody;

public:
	void SetPlayerBody(class CPlayerBody* pPlayerBody);

private:
	void NoDamageTime(float fTime);

protected:
	virtual void SetFireStart();

private:
	void AddPlayerAnimation();
	void AddCallback();
	void BombEnable();
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
	void Bomb(float fTime);

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

