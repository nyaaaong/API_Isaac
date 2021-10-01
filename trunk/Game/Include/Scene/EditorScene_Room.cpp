
#include "EditorScene.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../PathManager.h"
#include "../Map/Map.h"

void CEditorScene::NextRoom(float fTime)
{
	++m_iCurRoom;

	if (m_iCurRoom > m_iMaxRoom)
		m_iCurRoom = m_iMaxRoom;

	SetMap("Room", m_iCurRoom);
}

void CEditorScene::PrevRoom(float fTime)
{
	--m_iCurRoom;

	if (m_iCurRoom < 1)
		m_iCurRoom = 1;

	SetMap("Room", m_iCurRoom);
}

void CEditorScene::ClearRoom(float fTime)
{
	GetCurrentMap()->Clear();
}

void CEditorScene::SaveRoom(float fTime)
{
	CInput::GetInst()->SetShowCursor(true);

	TCHAR	cFilePath[MAX_PATH] = {};

	OPENFILENAME	tOpenFile = {};

	tOpenFile.lStructSize = sizeof(OPENFILENAME);
	tOpenFile.hwndOwner = CGameManager::GetInst()->GetWindowHandle();
	tOpenFile.lpstrFilter = TEXT("맵 데이터 (*.dat)\0*.dat");
	tOpenFile.lpstrFile = cFilePath;
	tOpenFile.nMaxFile = MAX_PATH;
	tOpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(MAP_PATH)->cPath;

	if (GetSaveFileName(&tOpenFile) != 0)
	{
		// .dat이 붙었는지 확인
		int	iPathLength = static_cast<int>(lstrlen(cFilePath));

		TCHAR	cDat[5] = TEXT("tad.");
		bool	bFind = true;

		for (int i = 1; i < 5; ++i)
		{
			if (cFilePath[iPathLength - i] != cDat[i - 1])
			{
				bFind = false;
				break;
			}
		}

		if (!bFind) // dat 확장자가 붙지 않았을 경우 붙여준다.
			lstrcat(cFilePath, TEXT(".dat"));

		char	cFullPath[MAX_PATH] = {};

#ifdef UNICODE
		int	iConvertLength = WideCharToMultiByte(CP_ACP, 0, cFilePath, -1, nullptr, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, cFilePath, -1, cFullPath, iConvertLength, 0, 0);
#else
		strcpy_s(cFullPath, cFilePath);
#endif // UNICODE

		Save(cFullPath);
	}

	CInput::GetInst()->SetShowCursor(false);
}

void CEditorScene::LoadRoom(float fTime)
{
	CInput::GetInst()->SetShowCursor(true);

	TCHAR	cFilePath[MAX_PATH] = {};

	OPENFILENAME	tOpenFile = {};

	tOpenFile.lStructSize = sizeof(OPENFILENAME);
	tOpenFile.hwndOwner = CGameManager::GetInst()->GetWindowHandle();
	tOpenFile.lpstrFilter = TEXT("맵 데이터 (*.dat)\0*.dat");
	tOpenFile.lpstrFile = cFilePath;
	tOpenFile.nMaxFile = MAX_PATH;
	tOpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(MAP_PATH)->cPath;

	if (GetOpenFileName(&tOpenFile) != 0)
	{
		char	cFullPath[MAX_PATH] = {};

#ifdef UNICODE
		int	iConvertLength = WideCharToMultiByte(CP_ACP, 0, cFilePath, -1, nullptr, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, cFilePath, -1, cFullPath, iConvertLength, 0, 0);
#else
		strcpy_s(cFullPath, cFilePath);
#endif // UNICODE

		Load(cFullPath);
	}

	CInput::GetInst()->SetShowCursor(false);
}