#pragma once
#include "MonsterBase.h"
class CBossMonstro :
    public CMonsterBase
{
	friend class CScene;

private:
	bool	m_bMove;

private:
	void AddBossAnimation();
	void AddBossNotify();
	void AddBossPattern();
	void AddCallback();
	void ChangeDirAnimation(const std::string& strAnimType);
	void DirCheck();
	void PatternMove(float fTime);
	void PatternMoveNotify();
	void PatternJump(float fTime);
	void PatternJumpNotify();
	void PatternFire(float fTime);
	void PatternDefault();

public:
	virtual void Move(const Vector2& tDir, bool bUseActivity);
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseActivity);
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CBossMonstro* Clone();

protected:
	CBossMonstro();
	CBossMonstro(const CBossMonstro& obj);
	virtual ~CBossMonstro();
};

