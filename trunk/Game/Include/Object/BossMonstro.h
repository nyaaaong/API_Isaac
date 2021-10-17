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
	void ChangeDirAnimation(const std::string& strAnimType);
	void DirCheck();
	void PatternMove(float fTime);
	void PatternMoveNotify();
	void PatternJump(float fTime);
	void PatternJumpNotify();
	void PatternFire(float fTime);
	void PatternDefault();

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CBossMonstro* Clone();

protected:
	CBossMonstro();
	CBossMonstro(const CBossMonstro& obj);
	virtual ~CBossMonstro();
};

