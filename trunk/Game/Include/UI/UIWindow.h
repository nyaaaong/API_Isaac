#pragma once

#include "../Ref.h"
#include "UIWidget.h"

class CUIWindow :
	public CRef
{
protected:
	class CScene* m_pScene;
	int		m_iZOrder;
	CUIWidget**	m_pArrWidget;
	int		m_iWidgetCount;
	int		m_iWidgetCapacity;
	bool	m_bVisibility;
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

	CUIWidget* GetWidget(int iIdx)	const
	{
		return m_pArrWidget[iIdx];
	}

	int GetWidgetCount()	const
	{
		return m_iWidgetCount;
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

public:
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

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

	int GetZOrder()	const
	{
		return m_iZOrder;
	}

public:
	static int SortWidgetZOrder(const void* pSrc, const void* pDest);

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);

protected:
	CUIWindow();
	virtual ~CUIWindow();

public:
	template <typename T>
	T* FindWidget(const std::string& strName)
	{
		for (int i = 0; i < m_iWidgetCount; ++i)
		{
			if (m_pArrWidget[i]->GetName() == strName)
				return m_pArrWidget[i];
		}

		return nullptr;
	}

	template <typename T>
	T* CreateWidget(const std::string& strName)
	{
		T* pWidget = new T;

		pWidget->SetName(strName);
		pWidget->SetScene(m_pScene);
		pWidget->SetOwner(this);

		if (!pWidget->Init())
		{
			SAFE_DELETE(pWidget);
			return nullptr;
		}

		if (m_iWidgetCount == m_iWidgetCapacity)
		{
			m_iWidgetCapacity *= 2;

			CUIWidget** pArr = new CUIWidget * [m_iWidgetCapacity];

			memcpy(pArr, m_pArrWidget, sizeof(CUIWidget*) * m_iWidgetCount);

			SAFE_DELETE_ARRAY(pArr);

			m_pArrWidget = pArr;
		}

		pWidget->AddRef();
		m_pArrWidget[m_iWidgetCount] = pWidget;
		++m_iWidgetCount;

		return static_cast<T*>(pWidget);
	}
};

