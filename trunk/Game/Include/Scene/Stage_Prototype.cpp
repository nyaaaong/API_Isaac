
#include "Stage.h"
#include "../Object/Tear.h"
#include "../Object/PlayerTearEffect.h"
#include "../Object/MonsterTearEffect.h"
#include "../Object/Bomb.h"
#include "../Object/BombExplosionEffect.h"
#include "../Object/Door.h"
#include "../Object/MonsterSpawner.h"
#include "../Object/Heart.h"
#include "../Object/ItemAddEffect.h"

void CStage::CreatePrototypes()
{
	CTear* pPlayerTear = CreatePrototype<CTear>("PlayerTear");
	pPlayerTear->SetTearType(ETearType::Player);

	CPlayerTearEffect* pPlayerTearEffect = CreatePrototype<CPlayerTearEffect>("PlayerTearEffect");

	CTear* pMonsterTear = CreatePrototype<CTear>("MonsterTear");
	pMonsterTear->SetTearType(ETearType::Monster);

	CMonsterTearEffect* pMonsterTearEffect = CreatePrototype<CMonsterTearEffect>("MonsterTearEffect");

	CBomb* pBomb = CreatePrototype<CBomb>("Bomb");
	CBombExplosionEffect*	pExplosion = CreatePrototype<CBombExplosionEffect>("BombExplosion");

	CMonsterSpawner::GetInst()->CreateMonsterPrototype();
	CMonsterSpawner::GetInst()->CreateBossMonsterPrototype();

	CHeart* pHeart = CreatePrototype<CHeart>("Heart");

	CItemAddEffect* pItemAddEffect = CreatePrototype<CItemAddEffect>("ItemAddEffect");
}