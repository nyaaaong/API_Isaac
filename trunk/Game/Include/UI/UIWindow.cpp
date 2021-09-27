
#include "UIWindow.h"
#include "UIWidget.h"

int CUIWindow::SortWidgetZOrder(const void* pSrc, const void* pDest)
{
	CUIWidget* pSrcObj = *(CUIWidget**)pSrc;
	CUIWidget* pDestObj = *(CUIWidget**)pDest;

	int iSrcZ = pSrcObj->GetZOrder();
	int iDestZ = pDestObj->GetZOrder();

	if (iSrcZ > iDestZ)
		return -1;

	else if (iSrcZ < iDestZ)
		return 1;

    return 0;
}

bool CUIWindow::Init()
{
	return true;
}

void CUIWindow::Update(float fTime)
{
	for (int i = 0; i < m_iWidgetCount;)
	{
		if (!m_pArrWidget[i]->IsActive())
		{
			SAFE_RELEASE(m_pArrWidget[i]);

			for (int j = i; j < m_iWidgetCount - 1; ++j)
			{
				m_pArrWidget[j] = m_pArrWidget[j + 1];
			}

			--m_iWidgetCount;
			continue;
		}

		else if (!m_pArrWidget[i]->GetVisibility())
		{
			++i;
			continue;
		}

		m_pArrWidget[i]->Update(fTime);
		++i;
	}
}

void CUIWindow::PostUpdate(float fTime)
{
	for (int i = 0; i < m_iWidgetCount;)
	{
		if (!m_pArrWidget[i]->IsActive())
		{
			SAFE_RELEASE(m_pArrWidget[i]);

			for (int j = i; j < m_iWidgetCount - 1; ++j)
			{
				m_pArrWidget[j] = m_pArrWidget[j + 1];
			}

			--m_iWidgetCount;
			continue;
		}

		else if (!m_pArrWidget[i]->GetVisibility())
		{
			++i;
			continue;
		}

		m_pArrWidget[i]->PostUpdate(fTime);
		++i;
	}
}

void CUIWindow::Collision(float fTime)
{
}

void CUIWindow::Render(HDC hDC)
{
	if (m_iWidgetCount >= 2)
		qsort(m_pArrWidget, static_cast<size_t>(m_iWidgetCount), sizeof(CUIWidget*), CUIWindow::SortWidgetZOrder);

	for (int i = 0; i < m_iWidgetCount;)
	{
		if (!m_pArrWidget[i]->IsActive())
		{
			SAFE_RELEASE(m_pArrWidget[i]);

			for (int j = i; j < m_iWidgetCount - 1; ++j)
			{
				m_pArrWidget[j] = m_pArrWidget[j + 1];
			}

			--m_iWidgetCount;
			continue;
		}

		++i;
	}

	for (int i = m_iWidgetCount - 1; i >= 0; --i)
	{
		if (!m_pArrWidget[i]->GetVisibility())
			continue;

		m_pArrWidget[i]->Render(hDC);
	}
}

CUIWindow::CUIWindow()	:
	m_pScene(nullptr),
	m_iZOrder(0),
	m_bVisibility(true),
	m_iWidgetCapacity(4),
	m_iWidgetCount(0)
{
	m_pArrWidget = new CUIWidget * [m_iWidgetCapacity];
}

CUIWindow::~CUIWindow()
{
	for (int i = 0; i < m_iWidgetCount; ++i)
	{
		SAFE_RELEASE(m_pArrWidget[i]);
	}

	SAFE_DELETE_ARRAY(m_pArrWidget);
}
