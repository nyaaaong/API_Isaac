
#include "MapObj.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Resource/ResourceManager.h"

CMapObj::CMapObj()	:
	m_eObject(OBJ_ROCK),
	m_pScene(nullptr),
	m_iZOrder(static_cast<int>(EZOrder::MapObject))
{
}

CMapObj::~CMapObj()
{
}

bool CMapObj::Init()
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

void CMapObj::Update(float fTime)
{
}

void CMapObj::PostUpdate(float fTime)
{
}

void CMapObj::Render(HDC hDC)
{
	if (m_pTexture)
	{
		Vector2	tCamPos = m_pScene->GetCamera()->GetPos();
		m_pTexture->Render(hDC, m_tPos - tCamPos, Vector2(0.f, 0.f), m_tSize);
	}
}

bool CMapObj::IsObj(const Vector2& tPos)
{
	return IsObj(tPos, m_tSize);
}

bool CMapObj::IsObj(const Vector2& tPos, const Vector2& tSize)
{
	if (m_tPos.x < tPos.x + tSize.x && m_tPos.x + m_tSize.x > tPos.x &&
		m_tPos.y < tPos.y + tSize.y && m_tPos.y + m_tSize.y > tPos.y)
		return true;

	return false;
}

void CMapObj::Save(FILE* pFile)
{
	fwrite(&m_tPos, sizeof(Vector2), 1, pFile);
	fwrite(&m_tSize, sizeof(Vector2), 1, pFile);

	fwrite(&m_eObject, sizeof(EObject), 1, pFile);

	fwrite(&m_iZOrder, sizeof(int), 1, pFile);

	if (m_pTexture)
	{
		bool	bTexture = true;
		fwrite(&bTexture, sizeof(bool), 1, pFile);

		m_pTexture->Save(pFile);
	}

	else
	{
		bool	bTexture = false;
		fwrite(&bTexture, sizeof(bool), 1, pFile);
	}
}

void CMapObj::Load(FILE* pFile)
{
	fread(&m_tPos, sizeof(Vector2), 1, pFile);
	fread(&m_tSize, sizeof(Vector2), 1, pFile);

	fread(&m_eObject, sizeof(EObject), 1, pFile);

	fread(&m_iZOrder, sizeof(int), 1, pFile);

	bool	bTexture = true;
	fread(&bTexture, sizeof(bool), 1, pFile);

	if (bTexture)
		m_pTexture = CTexture::LoadStatic(pFile, m_pScene);
}
