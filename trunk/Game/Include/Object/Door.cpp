
#include "Door.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/RoomBase.h"
#include "../Resource/ResourceManager.h"

void CDoor::SetDoor(bool bIsOpen)
{
	std::string	strName;
	TCHAR	strPath[MAX_PATH] = TEXT("Room/Door/");
	TCHAR	strFileName[MAX_PATH] = {};

	Resolution	tRS = CGameManager::GetInst()->GetResolution();
	Vector2	tScreenLT = m_pScene->GetActivityLT();
	Vector2	tScreenRB = m_pScene->GetActivityRB();

	if (m_eDoorType == DT_NORMAL)
	{
		switch (m_eDoorDir)
		{
		case DD_LEFT:
			strName = "DoorLeft";
			SetPos(tScreenLT.x, tRS.iH * 0.5f);
			SetOffset(-50.f, 0.f);
			lstrcpy(strFileName, TEXT("Door_Left"));
			break;
		case DD_TOP:
			strName = "DoorTop";
			SetPos(tRS.iW * 0.5f, tScreenLT.y);
			SetOffset(0.f, -50.f);
			lstrcpy(strFileName, TEXT("Door_Top"));
			break;
		case DD_RIGHT:
			strName = "DoorRight";
			SetPos(tScreenRB.x, tRS.iH * 0.5f);
			SetOffset(50.f, 0.f);
			lstrcpy(strFileName, TEXT("Door_Right"));
			break;
		case DD_BOTTOM:
			strName = "DoorBottom";
			SetPos(tRS.iW * 0.5f, tScreenRB.y);
			SetOffset(0.f, 50.f);
			lstrcpy(strFileName, TEXT("Door_Bottom"));
			break;
		}
	}

	else if (m_eDoorType == DT_BOSS)
	{
		switch (m_eDoorDir)
		{
		case DD_LEFT:
			strName = "DoorBossLeft";
			SetPos(tScreenLT.x, tRS.iH * 0.5f);
			SetOffset(-50.f, 0.f);
			lstrcpy(strFileName, TEXT("Door_Boss_Left"));
			break;
		case DD_TOP:
			strName = "DoorBossTop";
			SetPos(tRS.iW * 0.5f, tScreenLT.y);
			SetOffset(0.f, -50.f);
			lstrcpy(strFileName, TEXT("Door_Boss_Top"));
			break;
		case DD_RIGHT:
			strName = "DoorBossRight";
			SetPos(tScreenRB.x, tRS.iH * 0.5f);
			SetOffset(50.f, 0.f);
			lstrcpy(strFileName, TEXT("Door_Boss_Right"));
			break;
		case DD_BOTTOM:
			strName = "DoorBossBottom";
			SetPos(tRS.iW * 0.5f, tScreenRB.y);
			SetOffset(0.f, 50.f);
			lstrcpy(strFileName, TEXT("Door_Boss_Bottom"));
			break;
		}
	}

	if (bIsOpen)
	{
		strName += "Open";
		lstrcat(strFileName, TEXT("_Open"));
	}

	lstrcat(strFileName, TEXT(".bmp"));

	lstrcat(strPath, strFileName);

	SetTexture(strName, strPath);
	SetTextureColorKey();
}

void CDoor::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	CObj::CollisionBegin(pSrc, pDest, fTime);
}

void CDoor::Start()
{
	CObj::Start();

	SetDoor(false);
}

bool CDoor::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 0.5f);

	SetZOrder(EZOrder::RoomObject);

	// 충돌 생성

	return true;
}

void CDoor::Update(float fTime)
{
	CObj::Update(fTime);

	if (!m_bOpenStart && dynamic_cast<CRoomBase*>(m_pScene)->IsClearRoom())
	{
		m_bOpenStart = true;

		SetDoor(true);
	}
}

void CDoor::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CDoor::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CDoor* CDoor::Clone()
{
	return new CDoor(*this);
}

CDoor::CDoor()	:
	m_eDoorType(DT_MAX),
	m_eDoorDir(DD_MAX),
	m_bOpenStart(false)
{
}

CDoor::CDoor(const CDoor& obj)	:
	CObj(obj)
{
	m_eDoorType = obj.m_eDoorType;
	m_eDoorDir = obj.m_eDoorDir;
	m_bOpenStart = false;
}

CDoor::~CDoor()
{
}
