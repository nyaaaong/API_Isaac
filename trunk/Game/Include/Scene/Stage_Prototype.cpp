
#include "Stage.h"
#include "../Object/Tear.h"
#include "../Object/PlayerTearEffect.h"
#include "../Object/MonsterTearEffect.h"
#include "../Object/BossMonstro.h"
#include "../Object/Door.h"

void CStage::CreatePrototypes()
{
	CTear* pPlayerTear = CreatePrototype<CTear>("PlayerTear");
	pPlayerTear->SetTearType(ETearType::Player);

	CPlayerTearEffect* pPlayerTearEffect = CreatePrototype<CPlayerTearEffect>("PlayerTearEffect");

	CTear* pMonsterTear = CreatePrototype<CTear>("MonsterTear");
	pMonsterTear->SetTearType(ETearType::Monster);

	CMonsterTearEffect* pMonsterTearEffect = CreatePrototype<CMonsterTearEffect>("MonsterTearEffect");

	CBossMonstro* pMonstro = CreatePrototype<CBossMonstro>("Monstro");

	//CDoor* pDoor = CreatePrototype<CDoor>("Door");
}