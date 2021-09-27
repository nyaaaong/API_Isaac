#pragma once

#include "../Ref.h"

class CUIWidget :
    public CRef
{
protected:
	class CScene* m_pScene;
	int		m_iZOrder;
	bool	m_bVisibility;
	class CUIWindow* m_pOwner;
	Vector2	m_tPos;
	Vector2	m_tSize;

public:
	const Vector2& GetPos()	const
	{
		return m_tPos;
	}

	const Vector2& GetSize()	const
	{
		return m_tSize;
	}

public:
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

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetOwner(class CUIWindow* pOwner)
	{
		m_pOwner = pOwner;
	}

public:
	void SetVisibility(bool bVisibility)
	{
		m_bVisibility = bVisibility;
	}

	bool GetVisibility()	const
	{
		return m_bVisibility;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	void SetZOrder(EZOrder eZOrder)
	{
		m_iZOrder = static_cast<int>(eZOrder);
	}

	int GetZOrder()	const
	{
		return m_iZOrder;
	}

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual void Render(const Vector2& tPos, HDC hDC);
	virtual CUIWidget* Clone();

public:
	CUIWidget();
	CUIWidget(const CUIWidget& widget);
	virtual ~CUIWidget();
};

