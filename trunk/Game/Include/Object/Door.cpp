
#include "Door.h"
#include "../Scene/RoomBase.h"
#include "../Resource/ResourceManager.h"
#include "../Collision/ColliderBox.h"
#include "../Map/MapManager.h"

void CDoor::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (!CMapManager::GetInst()->GetClearMap(iNum))
			return;

		if (pDest->GetName() == "PlayerBody")
			dynamic_cast<CRoomBase*>(m_pScene)->DoorFunc(m_eDoorDir);
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (!CMapManager::GetInst()->GetClearSpecialMap(eType))
			return;

		if (pDest->GetName() == "PlayerBody")
			dynamic_cast<CRoomBase*>(m_pScene)->DoorFunc(m_eDoorDir);
	}
}

void CDoor::Start()
{
	CObj::Start();

	// �浹 ����
	m_pColliderBox = AddCollider<CColliderBox>("Door");
	m_pColliderBox->SetExtent(m_tSize * 0.3f);
	m_pColliderBox->SetCollisionProfile("Door");

	SetDoor(false);

	m_pColliderBox->SetCollisionBeginFunc<CDoor>(this, &CDoor::CollisionBegin);
}

bool CDoor::Init()
{
	if (!CObj::Init())
		return false;

	SetPivot(0.5f, 0.5f);

	SetZOrder(EZOrder::RoomObject);

	return true;
}

void CDoor::Update(float fTime)
{
	CObj::Update(fTime);

	int iNum = m_pScene->GetCurMapNumber();
	ESpecial_RoomType	eType = m_pScene->GetCurMapType();

	if (iNum != -1)
	{
		if (!m_bOpenStart && CMapManager::GetInst()->GetClearMap(iNum))
		{
			m_bOpenStart = true;

			SetDoor(true);
		}
	}

	else if (eType != ESpecial_RoomType::None)
	{
		if (!m_bOpenStart && CMapManager::GetInst()->GetClearSpecialMap(eType))
		{
			m_bOpenStart = true;

			SetDoor(true);
		}
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

void CDoor::SetDoor(bool bIsOpen)
{
	std::string	strName;
	TCHAR	strPath[MAX_PATH] = TEXT("Room/Door/");
	TCHAR	strFileName[MAX_PATH] = {};

	if (m_eDoorType == DT_NORMAL)
	{
		switch (m_eDoorDir)
		{
		case DD_LEFT:
			strName = "DoorLeft";
			lstrcpy(strFileName, TEXT("Door_Left"));
			break;
		case DD_TOP:
			strName = "DoorTop";
			lstrcpy(strFileName, TEXT("Door_Top"));
			break;
		case DD_RIGHT:
			strName = "DoorRight";
			lstrcpy(strFileName, TEXT("Door_Right"));
			break;
		case DD_BOTTOM:
			strName = "DoorBottom";
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
			lstrcpy(strFileName, TEXT("Door_Boss_Left"));
			break;
		case DD_TOP:
			strName = "DoorBossTop";
			lstrcpy(strFileName, TEXT("Door_Boss_Top"));
			break;
		case DD_RIGHT:
			strName = "DoorBossRight";
			lstrcpy(strFileName, TEXT("Door_Boss_Right"));
			break;
		case DD_BOTTOM:
			strName = "DoorBossBottom";
			lstrcpy(strFileName, TEXT("Door_Boss_Bottom"));
			break;
		}
	}

	else if (m_eDoorType == DT_ITEM)
	{
		switch (m_eDoorDir)
		{
		case DD_LEFT:
			strName = "DoorItemLeft";
			lstrcpy(strFileName, TEXT("Door_Item_Left"));
			break;
		case DD_TOP:
			strName = "DoorItemTop";
			lstrcpy(strFileName, TEXT("Door_Item_Top"));
			break;
		case DD_RIGHT:
			strName = "DoorItemRight";
			lstrcpy(strFileName, TEXT("Door_Item_Right"));
			break;
		case DD_BOTTOM:
			strName = "DoorItemBottom";
			lstrcpy(strFileName, TEXT("Door_Item_Bottom"));
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

	switch (m_eDoorDir)
	{
	case DD_LEFT:
		m_pColliderBox->SetOffset(-15.f, 0.f);
		break;
	case DD_TOP:
		m_pColliderBox->SetOffset(0.f, -15.f);
		break;
	case DD_RIGHT:
		m_pColliderBox->SetOffset(15.f, 0.f);
		break;
	case DD_BOTTOM:
		m_pColliderBox->SetOffset(0.f, 15.f);
		break;
	}
}
