#pragma once

#include "Obj.h"

class CItem :
    public CObj
{
	friend class CScene;

protected:
	class CPlayer* m_pPlayer;
	float	m_fValue;
	

public:
	void SetPlayer(class CPlayer* pPlayer)
	{
		m_pPlayer = pPlayer;
	}

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CItem* Clone();

protected:
	CItem();
	CItem(const CItem& obj);
	virtual ~CItem() = 0;
};

