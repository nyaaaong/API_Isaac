
#include "RoomObj.h"
#include "RoomMap.h"
#include "MapManager.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Resource/ResourceManager.h"

CRoomObj::CRoomObj()	:
	m_eType(MT_MAX),
	m_iZOrder(static_cast<int>(EZOrder::RoomObject)),
	m_fMaxLife(4.f),
	m_fLife(4.f)
{
}

CRoomObj::~CRoomObj()
{
}

bool CRoomObj::IsObj(CScene* pCurScene, const Vector2& tPos, const Vector2& tSize)
{
	// tPos는 검사할 오브젝트의 위치이며, tSize는 이 블럭의 사이즈이다.
	Vector2	tFieldLT = pCurScene->GetFieldLT();
	Vector2	tFieldRB = pCurScene->GetFieldRB();

	if (tPos.x < tFieldLT.x || tPos.y < tFieldLT.y ||
		tPos.y > tFieldRB.x || tPos.y > tFieldRB.y)
		return true;
	
	else if (m_eType != MT_SPAWN)
	{
		if (m_fLife != 0.f && (m_tPos.x < tPos.x + tSize.x && m_tPos.x + m_tSize.x > tPos.x &&
			m_tPos.y < tPos.y + tSize.y && m_tPos.y + m_tSize.y > tPos.y))
			return true;
	}

	else if (m_eType == MT_SPAWN)
	{
		if ((m_tPos.x < tPos.x && m_tPos.x + m_tSize.x > tPos.x &&
			m_tPos.y < tPos.y && m_tPos.y + m_tSize.y > tPos.y))
			return true;
	}

	return false;
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

	if (CMapManager::GetInst()->IsEditorScene() && m_eType == MT_SPAWN)
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
