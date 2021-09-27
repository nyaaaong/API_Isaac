#pragma once

#include "UIWidget.h"
#include "../Resource/Texture.h"

class CBossHPBar :
	public CUIWidget
{
protected:
	CSharedPtr<CTexture>	m_pTexture;
	float		m_fHP;
	float		m_fHPMax;
	float		m_fPercent;
	bool		m_bBackGroundBar;	// 백그라운드바 인 경우

public:
	void SetBackGroundBar(bool bBackGroundBar)
	{
		m_bBackGroundBar = bBackGroundBar;
	}

	void SetHP(float fHP)
	{
		m_fHP = fHP;

		if (m_fHP < 0)
			m_fHP = 0;

		else if (m_fHP > m_fHPMax)
			m_fHP = m_fHPMax;
	}

	void SetTexture(CTexture* pTexture)
	{
		m_pTexture = pTexture;

		if (m_pTexture)
		{
			m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
			m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
		}
	}

public:
	void SetTexture(const std::string& strName);
	void SetTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName = TEXTURE_PATH);
	void SetTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& strName, const TCHAR* cFullPath);
	void SetTextureColorKey(unsigned char r = 255, unsigned char g = 0, unsigned char b = 255, int iIdx = 0);

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual void Render(const Vector2& tPos, HDC hDC);
	virtual CBossHPBar* Clone();

public:
	CBossHPBar();
	CBossHPBar(const CBossHPBar& widget);
	virtual ~CBossHPBar();
};

