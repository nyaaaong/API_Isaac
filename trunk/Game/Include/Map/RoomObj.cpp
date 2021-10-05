
#include "RoomObj.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Resource/ResourceManager.h"

CRoomObj::CRoomObj()	:
	m_eObject(OBJ_ROCK),
	m_pScene(nullptr),
	m_iZOrder(static_cast<int>(EZOrder::RoomObject))
{
}

CRoomObj::~CRoomObj()
{
}

bool CRoomObj::Init()
{
	switch (m_eObject)
	{
	case OBJ_ROCK:
		m_pTexture = CResourceManager::GetInst()->FindTexture("Object1");
		break;
	case OBJ_IRON:
		m_pTexture = CResourceManager::GetInst()->FindTexture("Object2");
		break;
	case OBJ_SPIKE:
		m_pTexture = CResourceManager::GetInst()->FindTexture("Object3");
		break;
	case OBJ_POOP:
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
}

void CRoomObj::Render(HDC hDC)
{
	if (m_pTexture)
	{
		Vector2	tCamPos = m_pScene->GetCamera()->GetPos();
		m_pTexture->Render(hDC, m_tPos - tCamPos, Vector2(0.f, 0.f), m_tSize);
	}
}