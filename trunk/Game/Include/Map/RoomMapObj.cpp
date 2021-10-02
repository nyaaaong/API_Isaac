
#include "RoomMapObj.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Resource/ResourceManager.h"

CRoomMapObj::CRoomMapObj()	:
	m_eObject(OBJ_ROCK),
	m_pScene(nullptr),
	m_iZOrder(static_cast<int>(EZOrder::RoomMapObject))
{
}

CRoomMapObj::~CRoomMapObj()
{
}

bool CRoomMapObj::Init()
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

void CRoomMapObj::Update(float fTime)
{
}

void CRoomMapObj::PostUpdate(float fTime)
{
}

void CRoomMapObj::Render(HDC hDC)
{
	if (m_pTexture)
	{
		Vector2	tCamPos = m_pScene->GetCamera()->GetPos();
		m_pTexture->Render(hDC, m_tPos - tCamPos, Vector2(0.f, 0.f), m_tSize);
	}
}