
#include "Room.h"
#include "SceneResource.h"
#include "../Object/Door.h"

bool CRoom::Init()
{
	if (!CStage::Init())
		return false;

	return true;
}

void CRoom::CreateDoor()
{
	int iCount = rand() % 4 + 1;

	for (int i = 0; i < iCount; ++i)
	{
		CDoor* pDoor = new CDoor;

		pDoor->SetScene(this);

		if (!pDoor->Init())
		{
			SAFE_DELETE(pDoor);
			return;
		}

		m_vecDoor.push_back(pDoor);
	}
}

void CRoom::CreateMonster()
{

	/*Vector2	tPlayerPos = GetPlayer()->GetPos();

	CSharedPtr<CBossMonstro> pMonstro = CreateObject<CBossMonstro>("Monstro", "Monstro", Vector2(tPlayerPos.x + 600.f, tPlayerPos.y + 20.f));
	m_pPlayerHUD->SetBossMonster(static_cast<CCharacter*>(pMonstro));*/
}

bool CRoom::Update(float fTime)
{
	CStage::Update(fTime);

	return true;
}

bool CRoom::PostUpdate(float fTime)
{
	CStage::PostUpdate(fTime);

	return true;
}

bool CRoom::Collision(float fTime)
{
	CStage::Collision(fTime);

	return true;
}

bool CRoom::Render(HDC hDC)
{
	CStage::Render(hDC);

	return true;
}

CRoom::CRoom()	:
	m_iLeftDoor(0),
	m_iTopDoor(0),
	m_iRightDoor(0),
	m_iBottomDoor(0)
{
}

CRoom::~CRoom()
{
	size_t iSize = m_vecDoor.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		SAFE_RELEASE(m_vecDoor[i]);
	}
}
