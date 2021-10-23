
#include "Stage.h"
#include "SceneManager.h"
#include "../GameManager.h"
#include "../Object/Player.h"
#include "../Object/PlayerBody.h"
#include "../Object/ObjManager.h"
#include "../UI/PlayerHUD.h"

void CStage::CreatePlayer(const Vector2& tStartPos)
{
	Vector2 tPos;
	Resolution	tRS = CGameManager::GetInst()->GetResolution();
	const Vector2	tCenterPos = Vector2((float)tRS.iW * 0.5f, (float)tRS.iH * 0.5f);
	const Vector2	tPrevPos = CSceneManager::GetInst()->GetPrevScenePlayerPos();
	const Vector2	tFieldLT = GetFieldLT();
	const Vector2	tFieldRB = GetFieldRB();

	const Vector2	tDirL = Vector2(tFieldLT.x + 70.f, tFieldRB.y * 0.55f);;
	const Vector2	tDirR = Vector2(tFieldRB.x - 70.f, tFieldRB.y * 0.55f);
	const Vector2	tDirT = Vector2(tFieldRB.x * 0.56f, tFieldLT.y);
	const Vector2	tDirB = Vector2(tFieldRB.x * 0.56f, tFieldRB.y - 80.f);

	if (tPrevPos != tPos) // ������ ���� ����� �ݴ�� tPos�� �����ش�.
	{
		if (tPrevPos == Vector2::LEFT)
			tPos = tDirR;

		else if (tPrevPos == Vector2::RIGHT)
			tPos = tDirL;

		else if (tPrevPos == Vector2::UP)
			tPos = tDirB;

		else if (tPrevPos == Vector2::DOWN)
			tPos = tDirT;
	}

	else // ����� �� �׽�Ʈ�� ���ؼ� ���� �濡�� ������ ���� ��� ����� �����ش�.
		tPos = tCenterPos;

	CPlayer* pPlayer = CreateObject<CPlayer>("Player", tPos, Vector2(84.f, 75.f));

	CPlayerBody* pPlayerBody = CreateObject<CPlayerBody>("PlayerBody", tPos, Vector2(56.f, 45.f));
	SetPlayer(pPlayer, pPlayerBody);

	m_pPlayerHUD = CreateUIWindow<CPlayerHUD>("PlayerHUD");
	m_pPlayerHUD->SetPlayer(pPlayer);
}
