#pragma once

#include "UIWidget.h"
#include "../Resource/Texture.h"

class CUIImage :
	public CUIWidget
{
protected:
	CSharedPtr<CTexture>	m_pTexture;
	std::vector<AnimationFrameData>	m_vecFrameData;
	int		m_iFrameIndex;
	float	m_fPlayTime;
	float	m_fAnimTime;
	Vector2	m_tOffset;

public:
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
	void AddFrameData(const Vector2& tPos, const Vector2& tSize)
	{
		AnimationFrameData	tData = {};
		tData.tStartPos = tPos;
		tData.tSize = tSize;

		m_vecFrameData.push_back(tData);
	}

public:
	void SetTexture(const std::string& strName);
	void SetTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName = TEXTURE_PATH);
	void SetTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& strName, const TCHAR* cFullPath);
	void SetTextureColorKey(unsigned char r, unsigned char g, unsigned char b, int iIdx);

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual void Render(const Vector2& tPos, HDC hDC);
	virtual CUIImage* Clone();

public:
	CUIImage();
	CUIImage(const CUIImage& widget);
	virtual ~CUIImage();
};

