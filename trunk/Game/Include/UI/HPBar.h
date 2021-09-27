#pragma once

#include "UIWidget.h"
#include "../Resource/Texture.h"

class CHPBar :
	public CUIWidget
{
protected:
	std::vector<CSharedPtr<CTexture>>	m_vecTexture;
	CTexture*	m_pCurrentTexture;
	float		m_fHP;

public:
	void SetHP(float fHP)
	{
		m_fHP = fHP;

		if (m_fHP < 0)
			m_fHP = 0;

		else if (m_fHP > PLAYER_HP_MAX)
			m_fHP = PLAYER_HP_MAX;
	}

	void SetTexture(CTexture* pTexture, int iIdx)
	{
		m_vecTexture[iIdx] = pTexture;

		if (m_vecTexture[iIdx])
		{
			m_tSize.x = static_cast<float>(m_vecTexture[iIdx]->GetWidth());
			m_tSize.y = static_cast<float>(m_vecTexture[iIdx]->GetHeight());
		}
	}

public:
	void SetTexture(const std::string& strName, int iIdx);
	void SetTexture(const std::string& strName, int iIdx, const TCHAR* cFileName, const std::string& strPathName = TEXTURE_PATH);
	void SetTexture(const std::string& strName, int iIdx, const std::vector<std::wstring>& vecFileName, const std::string& strPathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& strName, int iIdx, const TCHAR* cFullPath);
	void SetTextureColorKey(unsigned char r = 255, unsigned char g = 0, unsigned char b = 255, int iIdx = 0);

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual void Render(const Vector2& tPos, HDC hDC);
	virtual CHPBar* Clone();

public:
	CHPBar();
	CHPBar(const CHPBar& widget);
	virtual ~CHPBar();
};

