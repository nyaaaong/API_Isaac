#pragma once

#include "Obj.h"

class CDoor :
    public CObj
{
	friend class CScene;
	friend class CRoomBase;

protected:
	EDoorType	m_eDoorType;
	EDoorDir	m_eDoorDir;
	bool		m_bOpenStart;

public:
	void SetDoorType(EDoorType eDoorType)
	{
		m_eDoorType = eDoorType;
	}

	void SetDoorDir(EDoorDir eDoorDir)
	{
		m_eDoorDir = eDoorDir;
	}

private:
	void SetDoor(bool bIsOpen);

public:
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CDoor* Clone();

protected:
	CDoor();
	CDoor(const CDoor& obj);
	virtual ~CDoor();
};

