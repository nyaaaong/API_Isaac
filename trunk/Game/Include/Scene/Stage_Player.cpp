
#include "Stage.h"
#include "SceneManager.h"
#include "../Object/Player.h"
#include "../Object/PlayerBody.h"
#include "../UI/PlayerHUD.h"

void CStage::CreatePlayer(const Vector2& tStartPos)
{
	Vector2 tPos;
	Vector2	tFieldLT = GetFieldLT();
	Vector2	tFieldRB = GetFieldRB();

	if (Vector2() != CSceneManager::GetInst()->GetPrevScenePlayerPos()) // ������ ���� ����� �ݴ�� tPos�� �����ش�.
	{
		if (tPos == Vector2::LEFT)
			tPos = Vector2(tFieldRB.x - 100.f, tFieldRB.y * 0.5f);

		else if (tPos == Vector2::RIGHT)
			tPos = Vector2(tFieldLT.x + 100.f, tFieldRB.y * 0.5f);

		else if (tPos == Vector2::UP)
			tPos = Vector2(tFieldRB.x * 0.5f, tFieldRB.y - 100.f);

		else if (tPos == Vector2::DOWN)
			tPos = Vector2(tFieldRB.x * 0.5f, tFieldLT.y + 100.f);
	}

	else // ����� �� �׽�Ʈ�� ���ؼ� ���� �濡�� ������ ���� ��� ���� ���� �������� �����ش�.
	{
		tPos = tStartPos;

		if (tPos == Vector2::LEFT)
			tPos = Vector2(tFieldLT.x + 100.f, tFieldRB.y * 0.5f);

		else if (tPos == Vector2::RIGHT)
			tPos = Vector2(tFieldRB.x - 100.f, tFieldRB.y * 0.5f);

		else if (tPos == Vector2::UP)
			tPos = Vector2(tFieldRB.x * 0.5f, tFieldLT.y + 100.f);

		else if (tPos == Vector2::DOWN)
			tPos = Vector2(tFieldRB.x * 0.5f, tFieldRB.y - 100.f);
	}

	CPlayer* pPlayer = CreateObject<CPlayer>("Player", tPos, Vector2(84.f, 75.f));

	CPlayerBody* pPlayerBody = CreateObject<CPlayerBody>("PlayerBody", tPos, Vector2(56.f, 45.f));
	SetPlayer(pPlayer, pPlayerBody);

	m_pPlayerHUD = CreateUIWindow<CPlayerHUD>("PlayerHUD");
	m_pPlayerHUD->SetPlayer(pPlayer);
}
