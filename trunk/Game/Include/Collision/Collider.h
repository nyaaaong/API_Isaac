#pragma once

#include "../Ref.h"

class CCollider :
    public CRef
{
protected:
	class CScene* m_pScene;
	class CObj* m_pOwner;
	ECollider_Type	m_eType;
	Vector2	m_tOffset;
	CollisionProfile* m_pProfile;
	std::function<void(CCollider*, CCollider*, float)>	m_pBeginFunc;
	std::function<void(CCollider*, CCollider*, float)>	m_pEndFunc;
	std::list<CSharedPtr<CCollider>>	m_CollisionList;

public:
	void SetOffset(const Vector2& tOffset)
	{
		m_tOffset = tOffset;
	}

	void SetOffset(float x, float y)
	{
		m_tOffset.x = x;
		m_tOffset.y = y;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetOwner(class CObj* pOwner)
	{
		m_pOwner = pOwner;
	}

public:
	const Vector2& GetOffset()	const
	{
		return m_tOffset;
	}

	virtual float GetBottom()	const
	{
		return 0.f;
	}

	CollisionProfile* GetProfile()	const
	{
		return m_pProfile;
	}

	class CObj* GetOwner()	const
	{
		return m_pOwner;
	}

	class CScene* GetScene()	const
	{
		return m_pScene;
	}

	ECollider_Type GetColliderType()	const
	{
		return m_eType;
	}

public:
	void SetCollisionProfile(const std::string& strName);
	void AddCollisionList(CCollider* pCollider);
	bool CheckCollisionList(CCollider* pCollider);
	void DeleteCollisionList(CCollider* pCollider);
	void ClearCollisionList();
	void CallCollisionBegin(CCollider* pDest, float fTime);
	void CallCollisionEnd(CCollider* pDest, float fTime);

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(HDC hDC);
	virtual CCollider* Clone();
	virtual bool Collision(CCollider* pDest) = 0;

protected:
	CCollider();
	CCollider(const CCollider& collider);
	virtual ~CCollider() = 0;

public:
	template <typename T>
	void SetCollisionBeginFunc(T* pObj, void(T::* pFunc)(CCollider*, CCollider*, float))
	{
		m_pBeginFunc = std::bind(pFunc, pObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}

	template <typename T>
	void SetCollisionEndFunc(T* pObj, void(T::* pFunc)(CCollider*, CCollider*, float))
	{
		m_pEndFunc = std::bind(pFunc, pObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}
};

