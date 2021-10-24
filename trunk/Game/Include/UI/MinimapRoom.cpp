
#include "MinimapRoom.h"

CMinimapRoom::CMinimapRoom()	:
	m_eType(EMinimapRoom_Type::Normal),
	m_bStart(false)
{
}

CMinimapRoom::CMinimapRoom(const CMinimapRoom& widget)	:
	CUIImage(widget)
{
	m_eType = widget.m_eType;
	m_bStart = false;
}

CMinimapRoom::~CMinimapRoom()
{
}

bool CMinimapRoom::Init()
{
	if (!CUIImage::Init())
		return false;

	SetTexture("ActiveRoom", TEXT("UI/Minimap/Active_Room.bmp"));
	SetTextureColorKey();
	SetTexture("ActiveItemRoom", TEXT("UI/Minimap/Active_ItemRoom.bmp"));
	SetTextureColorKey();

	SetZOrder(EZOrder::UIBackGround);
	return true;
}

void CMinimapRoom::Update(float fTime)
{
	if (!m_bStart)
	{
		switch (m_eType)
		{
		case EMinimapRoom_Type::Normal:
			SetTexture("ActiveRoom");
			break;
		case EMinimapRoom_Type::Item:
			SetTexture("ActiveItemRoom");
			break;
		}
	}
}
