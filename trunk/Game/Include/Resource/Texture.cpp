
#include "Texture.h"
#include "../PathManager.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

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

	TCHAR	cFileName[MAX_PATH] = {};

	char	cFullPathMultiByte[MAX_PATH] = {};

#ifdef UNICODE
	int iConvertLength = WideCharToMultiByte(CP_ACP, 0, cFullPath, -1, nullptr, 0, 0, 0);

	WideCharToMultiByte(CP_ACP, 0, cFullPath, -1, cFullPathMultiByte, iConvertLength, 0, 0);
#else
	strcpy_s(cFullPathMultiByte, cFullPath);
#endif // UNICODE

	// 모두 대문자로 변환
	_strupr_s(cFullPathMultiByte);

	int iPathLength = static_cast<int>(strlen(cFullPathMultiByte));

	for (int i = iPathLength - 1; i >= 0; --i)
	{
		if (cFullPathMultiByte[i] == '\\')
		{
			char	cFolderName[9] = {};
			strcpy_s(cFolderName, "ERUTXET\\");

			bool	bFind = true;

			for (int j = 1; j <= 8; ++j)
			{
				// 찾아온 폴더 이름이 맞는지 비교
				if (cFullPathMultiByte[i - j] != cFolderName[j - 1])
				{
					bFind = false;
					break;
				}
			}

			if (bFind)
				lstrcpy(cFileName, &cFullPath[i + 1]);
		}
	}

	TextureInfo* pInfo = new TextureInfo;

	lstrcpy(pInfo->cFileName, cFileName);

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

void CTexture::Save(FILE* pFile)
{
	int iLength = static_cast<int>(m_strName.length());

	fwrite(&iLength, sizeof(int), 1, pFile);
	fwrite(m_strName.c_str(), sizeof(char), iLength, pFile);

	fwrite(&m_eTextureType, sizeof(ETexture_Type), 1, pFile);

	int iSize = static_cast<int>(m_vecTextureInfo.size());
	fwrite(&iSize, sizeof(int), 1, pFile);

	for (int i = 0; i < iSize; ++i)
	{
		fwrite(&m_vecTextureInfo[i]->bColorKeyEnable, sizeof(bool), 1, pFile);
		fwrite(&m_vecTextureInfo[i]->iColorKey, sizeof(unsigned int), 1, pFile);

		int iNameLength = static_cast<int>(lstrlen(m_vecTextureInfo[i]->cFileName));
		fwrite(&iNameLength, sizeof(int), 1, pFile);
		fwrite(&m_vecTextureInfo[i]->cFileName, sizeof(TCHAR), iNameLength, pFile);
	}
}

void CTexture::Load(FILE* pFile)
{
	int iLength = 0;
	fread(&iLength, sizeof(int), 1, pFile);

	char	cName[64] = {};
	fread(cName, sizeof(char), iLength, pFile);
	m_strName = cName;
	
	fread(&m_eTextureType, sizeof(ETexture_Type), 1, pFile);

	int iSize = 0;
	fread(&iSize, sizeof(int), 1, pFile);

	if (iSize == 1)
	{
		bool	bColorKeyEnable = false;
		unsigned int	iColorKey = 0;

		fread(&bColorKeyEnable, sizeof(bool), 1, pFile);
		fread(&iColorKey, sizeof(unsigned int), 1, pFile);

		int iNameLength = 0;
		fread(&iNameLength, sizeof(int), 1, pFile);

		TCHAR	cFileName[MAX_PATH] = {};
		fread(&cFileName, sizeof(TCHAR), iNameLength, pFile);

		LoadTexture(m_strName, cFileName);

		if (bColorKeyEnable)
			SetColorKey(iColorKey);
	}

	else
	{
		std::vector<std::wstring>	vecFileName;
		std::vector<bool>	vecColorKeyEnable;
		std::vector<unsigned int>	vecColorKey;

		for (int i = 0; i < iSize; ++i)
		{
			bool	bColorKeyEnable = false;
			unsigned int	iColorKey = 0;

			fread(&bColorKeyEnable, sizeof(bool), 1, pFile);
			fread(&iColorKey, sizeof(unsigned int), 1, pFile);

			vecColorKeyEnable.push_back(bColorKeyEnable);
			vecColorKey.push_back(iColorKey);

			int iNameLength = 0;
			fread(&iNameLength, sizeof(int), 1, pFile);

			TCHAR	cFileName[MAX_PATH] = {};
			fread(&cFileName, sizeof(TCHAR), iNameLength, pFile);

			vecFileName.push_back(cFileName);
		}

		LoadTexture(m_strName, vecFileName);

		for (int i = 0; i < iSize; ++i)
		{
			if (!vecColorKeyEnable[i])
				continue;

			SetColorKey(vecColorKey[i], i);
		}
	}
}

CTexture* CTexture::LoadStatic(FILE* pFile, CScene* pScene)
{
	CTexture* pResult = nullptr;

	int iLength = 0;
	fread(&iLength, sizeof(int), 1, pFile);

	char	cName[64] = {};
	fread(cName, sizeof(char), iLength, pFile);

	ETexture_Type	eTextureType;

	fread(&eTextureType, sizeof(ETexture_Type), 1, pFile);

	int iSize = 0;
	fread(&iSize, sizeof(int), 1, pFile);

	if (iSize == 1)
	{
		bool	bColorKeyEnable = false;
		unsigned int	iColorKey = 0;

		fread(&bColorKeyEnable, sizeof(bool), 1, pFile);
		fread(&iColorKey, sizeof(unsigned int), 1, pFile);

		int iNameLength = 0;
		fread(&iNameLength, sizeof(int), 1, pFile);

		TCHAR	cFileName[MAX_PATH] = {};
		fread(cFileName, sizeof(TCHAR), iNameLength, pFile);

		pScene->GetSceneResource()->LoadTexture(cName, cFileName);

		if (bColorKeyEnable)
			pScene->GetSceneResource()->SetTextureColorKey(cName, iColorKey);

		pResult = pScene->GetSceneResource()->FindTexture(cName);
	}

	else
	{
		std::vector<std::wstring>	vecFileName;
		std::vector<bool>	vecColorKeyEnable;
		std::vector<unsigned int>	vecColorKey;

		for (int i = 0; i < iSize; ++i)
		{
			bool	bColorKeyEnable = false;
			unsigned int	iColorKey = 0;

			fread(&bColorKeyEnable, sizeof(bool), 1, pFile);
			fread(&iColorKey, sizeof(unsigned int), 1, pFile);

			vecColorKeyEnable.push_back(bColorKeyEnable);
			vecColorKey.push_back(iColorKey);

			int iNameLength = 0;
			fread(&iNameLength, sizeof(int), 1, pFile);

			TCHAR	cFileName[MAX_PATH] = {};
			fread(cFileName, sizeof(TCHAR), iNameLength, pFile);

			vecFileName.push_back(cFileName);
		}

		pScene->GetSceneResource()->LoadTexture(cName, vecFileName);

		for (int i = 0; i < iSize; ++i)
		{
			if (!vecColorKeyEnable[i])
				continue;

			pScene->GetSceneResource()->SetTextureColorKey(cName, vecColorKey[i], i);
		}

		pResult = pScene->GetSceneResource()->FindTexture(cName);
	}

	return pResult;
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
