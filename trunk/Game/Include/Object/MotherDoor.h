#pragma once

#include "Obj.h"

class CMotherDoor :
	public CObj
{
	friend class CScene;
	friend class CMonsterSpawner;

protected:
	CMotherDoor();
	CMotherDoor(const CMotherDoor& obj);
	virtual ~CMotherDoor();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual CMotherDoor* Clone();

private:
	class CMother* m_pMother;
	EDoorDir	m_eDoorDir;
	EMotherDoor_Type	m_eDoorType;
	float		m_fM4PDist;
	float		m_fM4PMaxDist;
	bool		m_bAttackEnd;
	float		m_fAttackEndDelay;
	Vector2		m_tM2PDir;
	Vector2		m_tBulletStartPos;
	float		m_fStartFuncDelay;

public:
	void SetDoorDir(EDoorDir eDoorDir)
	{
		m_eDoorDir = eDoorDir;
	}

	void SetMother(class CMother* pMother)
	{
		m_pMother = pMother;
	}

public:
	void SetDoorType(EMotherDoor_Type eDoorType);

private:
	void AddDoorAnimation();
	void DetectPlayer(float fTime);
	void DoorTypeUpdater();
	void StartFunc(float fTime);
	void ResizeColliderBox();
	void GetM2PDir();

public:
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual float SetDamage(float fDamage);
	virtual void EnableTask();
	virtual void DisableTask();
};

