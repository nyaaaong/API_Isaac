
#include "HPBar.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

void CHPBar::SetTexture(const std::string& strName, int iIdx)
{
	m_vecTexture[iIdx] = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_vecTexture[iIdx])
	{
		m_tSize.x = static_cast<float>(m_vecTexture[iIdx]->GetWidth());
		m_tSize.y = static_cast<float>(m_vecTexture[iIdx]->GetHeight());
	}
}

void CHPBar::SetTexture(const std::string& strName, int iIdx, const TCHAR* cFileName, const std::string& strPathName)
{
	m_pScene->GetSceneResource()->LoadTexture(strName, cFileName, strPathName);

	m_vecTexture[iIdx] = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_vecTexture[iIdx])
	{
		m_tSize.x = static_cast<float>(m_vecTexture[iIdx]->GetWidth());
		m_tSize.y = static_cast<float>(m_vecTexture[iIdx]->GetHeight());
	}
}

void CHPBar::SetTexture(const std::string& strName, int iIdx, const std::vector<std::wstring>& vecFileName, const std::string& strPathName)
{
	m_pScene->GetSceneResource()->LoadTexture(strName, vecFileName, strPathName);

	m_vecTexture[iIdx] = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_vecTexture[iIdx])
	{
		m_tSize.x = static_cast<float>(m_vecTexture[iIdx]->GetWidth());
		m_tSize.y = static_cast<float>(m_vecTexture[iIdx]->GetHeight());
	}
}

void CHPBar::SetTextureFullPath(const std::string& strName, int iIdx, const TCHAR* cFullPath)
{
	m_pScene->GetSceneResource()->LoadTextureFullPath(strName, cFullPath);

	m_vecTexture[iIdx] = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_vecTexture[iIdx])
	{
		m_tSize.x = static_cast<float>(m_vecTexture[iIdx]->GetWidth());
		m_tSize.y = static_cast<float>(m_vecTexture[iIdx]->GetHeight());
	}
}

void CHPBar::SetTextureColorKey(unsigned char r, unsigned char g, unsigned char b, int iIdx)
{
	for (int i = 0; i <= static_cast<int>(PLAYER_HP_MAX); ++i)
	{
		if (m_vecTexture[i])
			m_vecTexture[i]->SetColorKey(r, g, b, iIdx);
	}
}

bool CHPBar::Init()
{
	if (!CUIWidget::Init())
		return false;

	SetZOrder(EZOrder::UI);

	return true;
}

void CHPBar::Update(float fTime)
{
	CUIWidget::Update(fTime);

	m_pCurrentTexture = m_vecTexture[static_cast<int>(m_fHP)];
}

void CHPBar::PostUpdate(float fTime)
{
	CUIWidget::PostUpdate(fTime);
}

void CHPBar::Collision(float fTime)
{
	CUIWidget::Collision(fTime);
}

void CHPBar::Render(HDC hDC)
{
	CUIWidget::Render(hDC);

	if (m_pCurrentTexture)
	{
		Vector2	tPos = m_tPos + m_pOwner->GetPos();

		m_pCurrentTexture->Render(hDC, tPos, Vector2(0.f, 0.f), m_tSize);
	}
}

void CHPBar::Render(const Vector2& tPos, HDC hDC)
{
	CUIWidget::Render(tPos, hDC);

	if (m_pCurrentTexture)
		m_pCurrentTexture->Render(hDC, tPos, Vector2(0.f, 0.f), m_tSize);
}

CHPBar* CHPBar::Clone()
{
	return new CHPBar(*this);
}

CHPBar::CHPBar()	:
	m_fHP(PLAYER_HP_MAX),
	m_pCurrentTexture(nullptr)
{
	m_vecTexture.resize(static_cast<int>(PLAYER_HP_MAX) + 1);
}

CHPBar::CHPBar(const CHPBar& widget) :
	CUIWidget(widget)
{
	m_fHP = widget.m_fHP;
	m_pCurrentTexture = widget.m_pCurrentTexture;
	m_vecTexture = widget.m_vecTexture;
}

CHPBar::~CHPBar()
{
	m_vecTexture.clear();
}
