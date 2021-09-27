
#include "BossHPBar.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

void CBossHPBar::SetTexture(const std::string& strName)
{
	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CBossHPBar::SetTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName)
{
	m_pScene->GetSceneResource()->LoadTexture(strName, cFileName, strPathName);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CBossHPBar::SetTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName)
{
	m_pScene->GetSceneResource()->LoadTexture(strName, vecFileName, strPathName);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CBossHPBar::SetTextureFullPath(const std::string& strName, const TCHAR* cFullPath)
{
	m_pScene->GetSceneResource()->LoadTextureFullPath(strName, cFullPath);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CBossHPBar::SetTextureColorKey(unsigned char r, unsigned char g, unsigned char b, int iIdx)
{
	if (m_pTexture)
		m_pTexture->SetColorKey(r, g, b, iIdx);
}

bool CBossHPBar::Init()
{
	if (!CUIWidget::Init())
		return false;

	return true;
}

void CBossHPBar::Update(float fTime)
{
	CUIWidget::Update(fTime);

	if (!m_bBackGroundBar)
		m_fPercent = m_fHP / m_fHPMax;
}

void CBossHPBar::PostUpdate(float fTime)
{
	CUIWidget::PostUpdate(fTime);
}

void CBossHPBar::Collision(float fTime)
{
	CUIWidget::Collision(fTime);
}

void CBossHPBar::Render(HDC hDC)
{
	CUIWidget::Render(hDC);

	if (m_pTexture)
	{
		Vector2	tPos = m_tPos + m_pOwner->GetPos();

		if (!m_bBackGroundBar)
			m_pTexture->Render(hDC, tPos, Vector2(0.f, 0.f), m_tSize * Vector2(m_fPercent, 1.f));

		else
			m_pTexture->Render(hDC, tPos, Vector2(0.f, 0.f), m_tSize);
	}
}

void CBossHPBar::Render(const Vector2& tPos, HDC hDC)
{
	CUIWidget::Render(tPos, hDC);

	if (m_pTexture)
	{
		if (!m_bBackGroundBar)
			m_pTexture->Render(hDC, tPos, Vector2(0.f, 0.f), m_tSize * Vector2(m_fPercent, 1.f));

		else
			m_pTexture->Render(hDC, tPos, Vector2(0.f, 0.f), m_tSize);
	}
}

CBossHPBar* CBossHPBar::Clone()
{
	return new CBossHPBar(*this);
}

CBossHPBar::CBossHPBar()	:
	m_fHP(100.f),
	m_fHPMax(100.f),
	m_fPercent(1.f),
	m_bBackGroundBar(false)
{
}

CBossHPBar::CBossHPBar(const CBossHPBar& widget)	:
	CUIWidget(widget)
{
	m_fHP = widget.m_fHP;
	m_fHPMax = widget.m_fHPMax;
	m_fPercent = widget.m_fPercent;
	m_bBackGroundBar = widget.m_bBackGroundBar;
}

CBossHPBar::~CBossHPBar()
{
}
