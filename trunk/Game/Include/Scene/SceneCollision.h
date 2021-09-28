#pragma once

#include "../GameInfo.h"

class CSceneCollision
{
	friend class CScene;

private:
	class CScene* m_pScene;
	std::vector<class CCollider*>	m_vecCollider;
	std::vector<class CUIWindow*>	m_vecUIWindow;
	class CUIWidget* m_pSelectWidget;
	class CCollider* m_pMouseCollision;

public:
	void ClearMouseCollision(class CCollider* pCollider)
	{
		if (m_pMouseCollision == pCollider)
			m_pMouseCollision = nullptr;
	}

	void SetSelectWidget(class CUIWidget* pWidget)
	{
		m_pSelectWidget = pWidget;
	}

public:
	void AddCollider(class CCollider* pCollider);
	void AddUIWindow(class CUIWindow* pWindow);
	void CollisionMouse(float fTime);
	void Collision(float fTime);

private:
	static int SortY(const void* pSrc, const void* pDest);

private:
	CSceneCollision();
	~CSceneCollision();
};

