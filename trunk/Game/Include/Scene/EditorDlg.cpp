
#include "EditorDlg.h"
#include "../GameManager.h"

CEditorDlg* g_hDlg;

CEditorDlg::CEditorDlg()	:
	m_hDlg(0),
	m_iID(0),
	m_bOpen(true),
	m_pScene(nullptr)
{
	g_hDlg = this;
}

CEditorDlg::~CEditorDlg()
{
	if (m_hDlg)
		DestroyWindow(m_hDlg);
}

bool CEditorDlg::Init(int iID)
{
	m_hDlg = CreateDialog(CGameManager::GetInst()->GetWindowInstance(), MAKEINTRESOURCE(iID), CGameManager::GetInst()->GetWindowHandle(), CEditorDlg::WndProc);

	ShowWindow(m_hDlg, SW_SHOW);

    return true;
}

void CEditorDlg::Show()
{
	if (m_bOpen)
	{
		m_bOpen = false;
		ShowWindow(m_hDlg, SW_HIDE);
	}

	else
	{
		m_bOpen = true;
		ShowWindow(m_hDlg, SW_SHOW);
	}
}

void CEditorDlg::Create()
{
	BOOL	bTransfer = FALSE;

	int	iCountX = GetDlgItemInt(m_hDlg, IDC_EDIT_COUNT_X, &bTransfer, TRUE);
	int	iCountY = GetDlgItemInt(m_hDlg, IDC_EDIT_COUNT_Y, &bTransfer, TRUE);
	int	iSizeX = GetDlgItemInt(m_hDlg, IDC_EDIT_SIZE_X, &bTransfer, TRUE);
	int	iSizeY = GetDlgItemInt(m_hDlg, IDC_EDIT_SIZE_Y, &bTransfer, TRUE);
}

LRESULT CEditorDlg::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			break;
		case IDCANCEL:
			break;
		case IDC_BUTTON_CREATE:
			g_hDlg->Create();
			break;
		}
		break;
	default:
		break;
	}

	return 0;
}
