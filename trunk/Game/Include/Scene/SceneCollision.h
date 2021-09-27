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

public:
	void SetSelectWidget(class CUIWidget* pWidget)
	{
		m_pSelectWidget = pWidget;
	}

public:
	void AddCollider(class CCollider* pCollider);
	void AddUIWindow(class CUIWindow* pWindow);
	void Collision(float fTime);

private:
	static int SortY(const void* pSrc, const void* pDest);

private:
	CSceneCollision();
	~CSceneCollision();
};

