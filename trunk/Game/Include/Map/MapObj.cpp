
#include "MapObj.h"

CMapObj::CMapObj()	:
	m_eObject(OBJ_ROCK),
	m_tSize(75.f, 75.f)
{
}

CMapObj::~CMapObj()
{
}

bool CMapObj::Init()
{
	return true;
}

void CMapObj::Update(float fTime)
{
}

void CMapObj::PostUpdate(float fTime)
{
}

void CMapObj::PrevUpdate(float fTime)
{
}

void CMapObj::Render(HDC hDC)
{
}

void CMapObj::SetObject(EObject eObject)
{
	switch (eObject)
	{
	case OBJ_ROCK:
		break;
	case OBJ_IRON:
		break;
	case OBJ_SPIKE:
		break;
	case OBJ_POOP:
		break;
	}
}
