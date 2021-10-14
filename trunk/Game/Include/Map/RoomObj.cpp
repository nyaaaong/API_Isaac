
#include "RoomObj.h"
#include "RoomMap.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Resource/ResourceManager.h"

CRoomObj::CRoomObj()	:
	m_eType(MT_ROCK),
	m_pScene(nullptr),
	m_iZOrder(static_cast<int>(EZOrder::RoomObject)),
	m_fMaxLife(4.f),
	m_fLife(4.f)
{
}

CRoomObj::~CRoomObj()
{
}

bool CRoomObj::Init()
{
	switch (m_eType)
	{
	case MT_ROCK:
		m_pTexture = CResourceManager::GetInst()->FindTexture("Object1");
		break;
	case MT_IRON:
		m_pTexture = CResourceManager::GetInst()->FindTexture("Object2");
		break;
	case MT_SPIKE:
		m_pTexture = CResourceManager::GetInst()->FindTexture("Object3");
		break;
	case MT_POOP:
		m_pTexture = CResourceManager::GetInst()->FindTexture("Object4");
		break;
	}

	return true;
}

void CRoomObj::Update(float fTime)
{
}

void CRoomObj::PostUpdate(float fTime)
{
	switch (m_eType)
	{
	case MT_ROCK:
		RockUpdater();
		break;
	case MT_IRON:
		break;
	case MT_SPIKE:
		break;
	case MT_POOP:
		PoopUpdater();
		break;
	}
}

void CRoomObj::Render(HDC hDC)
{
	if (m_pTexture)
	{
		m_pTexture->Render(hDC, m_tPos, Vector2(0.f, 0.f), m_tSize);
	}

	if (m_pScene->IsEditor() && m_eType == MT_SPAWN)
	{
		RECT	rc = { static_cast<LONG>(m_tPos.x), static_cast<LONG>(m_tPos.y), static_cast<LONG>(m_tPos.x + m_tSize.x), static_cast<LONG>(m_tPos.y + m_tSize.y) };
		FrameRect(hDC, &rc, CGameManager::GetInst()->GetGreenBrush());
	}
}

void CRoomObj::RockUpdater()
{
	if (m_fLife == m_fMaxLife)
		return;

	m_fLife = 0.f;

	m_pTexture = CResourceManager::GetInst()->FindTexture("Rock_0");
	m_pTexture->SetColorKey();
}

void CRoomObj::PoopUpdater()
{
	if (m_fLife == m_fMaxLife)
		return;

	if (m_fLife == 3.f)
		m_pTexture = CResourceManager::GetInst()->FindTexture("Poop_3");

	else if (m_fLife == 2.f)
		m_pTexture = CResourceManager::GetInst()->FindTexture("Poop_2");

	else if (m_fLife == 1.f)
		m_pTexture = CResourceManager::GetInst()->FindTexture("Poop_1");

	else if (m_fLife == 0.f)
		m_pTexture = CResourceManager::GetInst()->FindTexture("Poop_0");

	m_pTexture->SetColorKey();
}
