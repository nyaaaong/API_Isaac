#pragma once

#include "../Ref.h"

struct TextureInfo
{
	HDC	hDC;	// �޸� DC
	HBITMAP	hBmp;	// ������� Bmp
	HBITMAP hPrevBmp;	// �����ִ� Bmp
	BITMAP	tBmpInfo;
	bool	bColorKeyEnable;
	unsigned int iColorKey;
	TCHAR	cFileName[MAX_PATH];

	TextureInfo() :
		hDC(0),
		hBmp(0),
		hPrevBmp(0),
		tBmpInfo{},
		bColorKeyEnable(false),
		iColorKey(RGB(255, 0, 255)),
		cFileName{}
	{}

	~TextureInfo()
	{
		SelectObject(hDC, hPrevBmp);	// ���� Bmp�� �����ְ�,
		DeleteObject(hBmp);	// Bmp ����
		DeleteDC(hDC);	// �޸� DC�� Release�� �ƴ� Delete�� �ؾ��Ѵ�.
	}
};

class CTexture :
	public CRef
{
private:
	std::vector<TextureInfo*>	m_vecTextureInfo;
	ETexture_Type	m_eTextureType;

public:
	ETexture_Type GetTextureType()	const
	{
		return m_eTextureType;
	}

	unsigned int GetWidth(int iIdx = 0)	const
	{
		return static_cast<unsigned int>(m_vecTextureInfo[iIdx]->tBmpInfo.bmWidth);
	}

	unsigned int GetHeight(int iIdx = 0)	const
	{
		return static_cast<unsigned int>(m_vecTextureInfo[iIdx]->tBmpInfo.bmHeight);
	}

	void SetColorKey(const unsigned char r, const unsigned char g, const unsigned char b, int iIdx = 0)
	{
		m_vecTextureInfo[iIdx]->bColorKeyEnable = true;
		m_vecTextureInfo[iIdx]->iColorKey = RGB(r, g, b);
	}

	void SetColorKey(unsigned int iColorKey = RGB(255, 0, 255), int iIdx = 0)
	{
		m_vecTextureInfo[iIdx]->bColorKeyEnable = true;
		m_vecTextureInfo[iIdx]->iColorKey = iColorKey;
	}

public:
	bool LoadTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName = TEXTURE_PATH);
	bool LoadTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& strName, const TCHAR* cFullPath);
	void Render(HDC hDC, const Vector2& tWindowPos, const Vector2& tImgPos, const Vector2& tSize, int iIdx = 0);

public:
	void Save(FILE* pFile);
	void Load(FILE* pFile);
	
public:
	static CTexture* LoadStatic(FILE* pFile, class CScene* pScene);

public:
	CTexture();
	~CTexture();
};

