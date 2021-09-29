#pragma once

#include "../GameInfo.h"

class CMap
{
	friend class CScene;

protected:
	CMap();
	virtual ~CMap();

protected:
	class CScene* m_pScene;
	std::string	m_strName;
	Vector2	m_tPos;
	Vector2	m_tSize;
	int		m_iZOrder;
	bool	m_bEnable;
	bool	m_bActive;
	int		m_iRoomNum;
	EObject	m_eObject;

public:
	int GetRoomNumber()	const
	{
		return m_iRoomNum;
	}

	EObject GetEObject()	const
	{
		return m_eObject;
	}

	bool IsActive()	const
	{
		return m_bActive;
	}

	bool IsEnable()	const
	{
		return m_bEnable;
	}

	int GetZOrder()	const
	{
		return m_iZOrder;
	}

	const std::string& GetName()	const
	{
		return m_strName;
	}

	const Vector2& GetPos()	const
	{
		return m_tPos;
	}

	const Vector2& GetSize()	const
	{
		return m_tSize;
	}

public:
	void SetRoomNumber(int iNum)
	{
		m_iRoomNum = iNum;
	}

	void SetEObject(EObject eObj)
	{
		m_eObject = eObj;
	}

	void SetEObject(int iObj)
	{
		m_eObject = static_cast<EObject>(iObj);
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetName(const std::string& strName)
	{
		m_strName = strName;
	}

	void SetPos(const Vector2& tPos)
	{
		m_tPos = tPos;
	}

	void SetPos(float x, float y)
	{
		m_tPos = Vector2(x, y);
	}

	void SetSize(const Vector2& tSize)
	{
		m_tSize = tSize;
	}

	void SetSize(float x, float y)
	{
		m_tSize = Vector2(x, y);
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void PrevRender();
	virtual void Render(HDC hDC);
};

