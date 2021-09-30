#include "BackGround.h"

bool CBackGround::Init()
{
	if (!CObj::Init())
		return false;

	SetTexture("BackGround");

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

CBackGround::CBackGround()
{
	m_eObjectType = EObjectType::Map;
}

CBackGround::CBackGround(const CBackGround& obj)	:
	CObj(obj)
{
}

CBackGround::~CBackGround()
{
}
