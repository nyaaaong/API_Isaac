
#include "UIWidget.h"

bool CUIWidget::Init()
{
    return true;
}

void CUIWidget::Update(float fTime)
{
}

void CUIWidget::PostUpdate(float fTime)
{
}

void CUIWidget::Collision(float fTime)
{
}

void CUIWidget::Render(HDC hDC)
{
}

void CUIWidget::Render(const Vector2& tPos, HDC hDC)
{
}

CUIWidget* CUIWidget::Clone()
{
    return nullptr;
}

CUIWidget::CUIWidget()	:
	m_iZOrder(0),
	m_bVisibility(true),
	m_pOwner(nullptr),
	m_pScene(nullptr)
{
}

CUIWidget::CUIWidget(const CUIWidget& widget)
{
	*this = widget;
}

CUIWidget::~CUIWidget()
{
}
