#pragma once

#include "Obj.h"

class CMenu :
    public CObj
{
	friend class CScene;

public:
	void GameStart(float fTime);
	void GameExit(float fTime);

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
	virtual CMenu* Clone();

protected:
	CMenu();
	CMenu(const CMenu& obj);
	virtual ~CMenu();

};

