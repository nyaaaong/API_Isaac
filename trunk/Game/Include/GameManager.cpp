
#include "GameManager.h"
#include "Timer.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "Scene/MainMenu.h"
#include "PathManager.h"
#include "Resource/ResourceManager.h"
#include "Collision/CollisionManager.h"

CGameManager* CGameManager::m_pInst = nullptr;
bool CGameManager::m_bLoop = true;

CGameManager::CGameManager()	:
	m_hInst(0),
	m_hWnd(0),
	m_hDC(0),
	m_hBackDC(0),
	m_hBackBmp(0),
	m_hPrevBackBmp(0),
	m_tRS{},
	m_fTimeScale(1.f),
	m_pTimer(nullptr),
	m_hGreenBrush(0),
	m_hRedBrush(0),
	m_hGreenPen(0),
	m_hRedPen(0)
{
}

CGameManager::~CGameManager()
{
	CSceneManager::DestroyInst();
	CInput::DestroyInst();
	CCollisionManager::DestroyInst();
	CResourceManager::DestroyInst();
	CPathManager::DestroyInst();
	SAFE_DELETE(m_pTimer);
	SelectObject(m_hBackDC, m_hPrevBackBmp);
	DeleteObject(m_hBackBmp);
	DeleteObject(m_hGreenPen);
	DeleteObject(m_hGreenBrush);
	DeleteObject(m_hRedPen);
	DeleteObject(m_hRedBrush);
	DeleteDC(m_hBackDC);
	ReleaseDC(m_hWnd, m_hDC);
}

float CGameManager::GetDeltaTime() const
{
	return m_pTimer->GetDeltaTime() * m_fTimeScale;
}

bool CGameManager::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	m_tRS.iW = 1280;
	m_tRS.iH = 720;

	Register();
	Create();

	m_hDC = GetDC(m_hWnd);

	if (!CPathManager::GetInst()->Init())
		return false;

	if (!CResourceManager::GetInst()->Init())
		return false;

	if (!CCollisionManager::GetInst()->Init())
		return false;

	if (!CInput::GetInst()->Init(m_hWnd))
		return false;

	if (!CSceneManager::GetInst()->Init())
		return false;

	CSceneManager::GetInst()->CreateScene<CMainMenu>();

	m_pTimer = new CTimer;

	m_hBackDC = CreateCompatibleDC(m_hDC);
	m_hBackBmp = CreateCompatibleBitmap(m_hDC, m_tRS.iW, m_tRS.iH);
	m_hPrevBackBmp = static_cast<HBITMAP>(SelectObject(m_hBackDC, m_hBackBmp));
	m_hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	m_hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	return true;
}

int CGameManager::Run()
{
	MSG msg = {};

	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
			Logic();
	}

	return static_cast<int>(msg.wParam);
}

void CGameManager::Exit()
{
	DestroyWindow(m_hWnd);
}

void CGameManager::Logic()
{
	float fTime = m_pTimer->Update() * m_fTimeScale;

	CResourceManager::GetInst()->Update();

	CInput::GetInst()->Update(fTime);

	if (Update(fTime))
		return;

	if (PostUpdate(fTime))
		return;

	if (Collision(fTime))
		return;

	Render(fTime);
}

bool CGameManager::Update(float fTime)
{
	return CSceneManager::GetInst()->Update(fTime);
}

bool CGameManager::PostUpdate(float fTime)
{
	return CSceneManager::GetInst()->PostUpdate(fTime);
}

bool CGameManager::Collision(float fTime)
{
	return CSceneManager::GetInst()->Collision(fTime);
}

void CGameManager::Render(float fTime)
{
	Rectangle(m_hBackDC, -1, -1, m_tRS.iW + 1, m_tRS.iH + 1);

	CSceneManager::GetInst()->Render(m_hBackDC);

	BitBlt(m_hDC, 0, 0, m_tRS.iW, m_tRS.iH, m_hBackDC, 0, 0, SRCCOPY);

#ifdef _DEBUG
	//	FPS ���
	char	cText[32] = {};

	sprintf_s(cText, "FPS : %.5f", m_pTimer->GetFPS());

	TextOutA(m_hDC, 0, 0, cText, static_cast<int>(strlen(cText)));
#endif // _DEBUG

}

ATOM CGameManager::Register()
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = TEXT("Game");
	wcex.hIconSm = NULL;

	return RegisterClassExW(&wcex);
}

BOOL CGameManager::Create()
{
	m_hWnd = CreateWindowW(TEXT("Game"), TEXT("Game"), WS_OVERLAPPEDWINDOW, 400, 250, m_tRS.iW, m_tRS.iH, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
		return FALSE;

	RECT    rc = { 0, 0, m_tRS.iW, m_tRS.iH };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 400, 250, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}

	return 0;
}