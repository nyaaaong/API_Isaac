#include "BackGround.h"

void CBackGround::Start()
{
	CObj::Start();

	if (!m_bStartRoom)
		SetTexture("BackGround");

	else
		SetTexture("StartRoom_BackGround");
}

bool CBackGround::Init()
{
	if (!CObj::Init())
		return false;

	return true;
}

void CBackGround::Render(HDC hDC)
{
	CObj::Render(hDC);
}

CBackGround* CBackGround::Clone()
{
	return new CBackGround(*this);
}

CBackGround::CBackGround()	:
	m_bStartRoom(false)
{
	m_eObjectType = EObjectType::Map;
}

CBackGround::CBackGround(const CBackGround& obj)	:
	CObj(obj)
{
	m_bStartRoom = obj.m_bStartRoom;
}

CBackGround::~CBackGround()
{
}
