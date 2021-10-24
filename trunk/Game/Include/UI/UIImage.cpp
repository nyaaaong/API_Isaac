
#include "UIImage.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "UIWindow.h"

void CUIImage::SetTexture(const std::string& strName)
{
	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CUIImage::SetTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName)
{
	m_pScene->GetSceneResource()->LoadTexture(strName, cFileName, strPathName);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CUIImage::SetTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName)
{
	m_pScene->GetSceneResource()->LoadTexture(strName, vecFileName, strPathName);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CUIImage::SetTextureFullPath(const std::string& strName, const TCHAR* cFullPath)
{
	m_pScene->GetSceneResource()->LoadTextureFullPath(strName, cFullPath);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CUIImage::SetTextureColorKey(unsigned char r, unsigned char g, unsigned char b, int iIdx)
{
	if (m_pTexture)
		m_pTexture->SetColorKey(r, g, b, iIdx);
}

bool CUIImage::Init()
{
    return true;
}

void CUIImage::Update(float fTime)
{
	if (!m_vecFrameData.empty())
	{
		m_fAnimTime += fTime;

		float	fFrameTime = m_fPlayTime / m_vecFrameData.size();

		if (m_fAnimTime >= fFrameTime)
		{
			m_fAnimTime -= fFrameTime;

			m_iFrameIndex = (m_iFrameIndex + 1) % (int)m_vecFrameData.size();
		}
	}
}

void CUIImage::Render(HDC hDC)
{
	if (m_pTexture)
	{
		Vector2	tPos = m_tPos + m_pOwner->GetPos();
		Vector2	tImagePos = {};
		Vector2	tSize = m_tSize;

		if (!m_vecFrameData.empty())
		{
			tImagePos = m_vecFrameData[m_iFrameIndex].tStartPos;
			tSize = m_vecFrameData[m_iFrameIndex].tSize;

			if (m_pTexture->GetTextureType() == ETexture_Type::FRAME)
				m_pTexture->Render(hDC, tPos + m_tOffset, tImagePos, tSize, m_iFrameIndex);

			else
				m_pTexture->Render(hDC, tPos + m_tOffset, tImagePos, tSize);
		}

		else
		{
			if (m_pTexture->GetTextureType() == ETexture_Type::FRAME)
				m_pTexture->Render(hDC, tPos + m_tOffset, tImagePos, tSize, m_iFrameIndex);

			else
				m_pTexture->Render(hDC, tPos + m_tOffset, tImagePos, tSize);
		}

		m_pTexture->Render(hDC, tPos, Vector2(0.f, 0.f), m_tSize);
	}
}

void CUIImage::Render(const Vector2& tPos, HDC hDC)
{
	if (m_pTexture)
	{
		Vector2	tImagePos = {};
		Vector2	tSize = m_tSize;

		if (!m_vecFrameData.empty())
		{
			tImagePos = m_vecFrameData[m_iFrameIndex].tStartPos;
			tSize = m_vecFrameData[m_iFrameIndex].tSize;

			if (m_pTexture->GetTextureType() == ETexture_Type::FRAME)
				m_pTexture->Render(hDC, tPos + m_tOffset, tImagePos, tSize, m_iFrameIndex);

			else
				m_pTexture->Render(hDC, tPos + m_tOffset, tImagePos, tSize);
		}

		else
		{
			if (m_pTexture->GetTextureType() == ETexture_Type::FRAME)
				m_pTexture->Render(hDC, tPos + m_tOffset, tImagePos, tSize, m_iFrameIndex);

			else
				m_pTexture->Render(hDC, tPos + m_tOffset, tImagePos, tSize);
		}
	}
}

CUIImage* CUIImage::Clone()
{
    return new CUIImage(*this);
}

CUIImage::CUIImage()	:
	m_iFrameIndex(0),
	m_fPlayTime(1.f),
	m_fAnimTime(0.f)
{
}

CUIImage::CUIImage(const CUIImage& widget)	:
	CUIWidget(widget)
{
	m_pTexture = widget.m_pTexture;
	m_iFrameIndex = widget.m_iFrameIndex;
	m_fPlayTime = widget.m_fPlayTime;
	m_fAnimTime = widget.m_fAnimTime;
	m_vecFrameData = widget.m_vecFrameData;
}

CUIImage::~CUIImage()
{
}
