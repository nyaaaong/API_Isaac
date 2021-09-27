
#include "Texture.h"
#include "../PathManager.h"
#include "../GameManager.h"

bool CTexture::LoadTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName)
{
	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(strPathName);

	TCHAR	cFullPath[MAX_PATH] = {};

	if (pInfo)
		lstrcpy(cFullPath, pInfo->cPath);

	lstrcat(cFullPath, cFileName);

	return LoadTextureFullPath(strName, cFullPath);
}

bool CTexture::LoadTextureFullPath(const std::string& strName, const TCHAR* cFullPath)
{
	SetName(strName);

	TextureInfo* pInfo = new TextureInfo;

	// 메모리 DC 생성
	pInfo->hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());
	pInfo->hBmp = static_cast<HBITMAP>(LoadImage(CGameManager::GetInst()->GetWindowInstance(), cFullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	// 위에서 생성한 메모리 DC에 생성한 Bmp를 넣기 위해 이전 Bmp를 받아온다.
	pInfo->hPrevBmp = static_cast<HBITMAP>(SelectObject(pInfo->hDC, pInfo->hBmp));

	// 비트맵 정보를 얻어와서 저장한다
	GetObject(pInfo->hBmp, sizeof(BITMAP), &pInfo->tBmpInfo);

	m_vecTextureInfo.push_back(pInfo);

	if (m_vecTextureInfo.size() == 1)
		m_eTextureType = ETexture_Type::ATLAS;

	else
		m_eTextureType = ETexture_Type::FRAME;

	return true;
}

bool CTexture::LoadTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName)
{
	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(strName);

	size_t iSize = vecFileName.size();

	TCHAR	cFullPath[MAX_PATH] = {};

	for (size_t i = 0; i < iSize; ++i)
	{
		memset(cFullPath, 0, sizeof(TCHAR) * MAX_PATH);

		if (pInfo)
			lstrcpy(cFullPath, pInfo->cPath);

		lstrcat(cFullPath, vecFileName[i].c_str());

		if (!LoadTextureFullPath(strName, cFullPath))
			return false;
	}

	if (m_vecTextureInfo.size() == 1)
		m_eTextureType = ETexture_Type::ATLAS;

	else
		m_eTextureType = ETexture_Type::FRAME;

    return true;
}

void CTexture::Render(HDC hDC, const Vector2& tWindowPos, const Vector2& tImgPos, const Vector2& tSize, int iIdx)
{
	if (m_vecTextureInfo[iIdx]->bColorKeyEnable)
		TransparentBlt(hDC, (int)tWindowPos.x, (int)tWindowPos.y, (int)tSize.x, (int)tSize.y, m_vecTextureInfo[iIdx]->hDC, (int)tImgPos.x, (int)tImgPos.y, (int)tSize.x, (int)tSize.y, m_vecTextureInfo[iIdx]->iColorKey);

	else
		BitBlt(hDC, (int)tWindowPos.x, (int)tWindowPos.y, (int)tSize.x, (int)tSize.y, m_vecTextureInfo[iIdx]->hDC, (int)tImgPos.x, (int)tImgPos.y, SRCCOPY);
}

CTexture::CTexture()	:
	m_eTextureType(ETexture_Type::ATLAS)
{
}

CTexture::~CTexture()
{
	size_t	iSize = m_vecTextureInfo.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		SAFE_DELETE(m_vecTextureInfo[i]);
	}
}
