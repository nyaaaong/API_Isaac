
#include "Stage.h"
#include "SceneResource.h"

void CStage::LoadSound()
{
	PlayerSound();
	EnemySound();
	BossSound();
	EffectSound();
}

void CStage::PlayerSound()
{
	// 피격음, 죽음
	GetSceneResource()->LoadSound("Effect", false, "PlayerHit", "Effect/Hit.wav");
	GetSceneResource()->LoadSound("Effect", false, "PlayerDie", "Effect/Die.wav");
}

void CStage::EnemySound()
{
	// 죽음
	GetSceneResource()->LoadSound("Effect", false, "EnemyDie", "Effect/Enemy_Die.wav");

	// Charger 공격사운드
	GetSceneResource()->LoadSound("Effect", false, "ChargerAttack", "Effect/Enemy_Charger.wav");
}

void CStage::BossSound()
{
	// 죽음
	GetSceneResource()->LoadSound("Effect", false, "MotherDie", "Effect/Mother/Dead.wav");

	// 공격 패턴
	GetSceneResource()->LoadSound("Effect", false, "MotherAttack", "Effect/Mother/Attack.wav");

	// 바닥에 발을 찍을때 충격파음
	GetSceneResource()->LoadSound("Effect", false, "MotherAttackEnd", "Effect/Mother/AttackEnd.wav");

	// 아이작!
	GetSceneResource()->LoadSound("Effect", false, "MotherCall1", "Effect/Mother/Call1.wav");
	GetSceneResource()->LoadSound("Effect", false, "MotherCall2", "Effect/Mother/Call2.wav");
	GetSceneResource()->LoadSound("Effect", false, "MotherCall3", "Effect/Mother/Call3.wav");

	// 피부 패턴
	GetSceneResource()->LoadSound("Effect", false, "MotherSummon", "Effect/Mother/Summon.wav");

	// 아이작 피격
	GetSceneResource()->LoadSound("Effect", false, "MotherIsaacHit", "Effect/Mother/Isaac_Hit.wav");
}

void CStage::EffectSound()
{
	// 눈물 발사 및 제거
	GetSceneResource()->LoadSound("Effect", false, "Tear", "Effect/Tear.wav");
	GetSceneResource()->LoadSound("Effect", false, "TearDrop", "Effect/Tear_Drop.wav");

	// 폭탄
	GetSceneResource()->LoadSound("Effect", false, "BombExplosion", "Effect/Bomb_Explosion.mp3");

	// 방 닫힘, 열림
	GetSceneResource()->LoadSound("Effect", false, "DoorClose", "Effect/Door_Close.wav");
	GetSceneResource()->LoadSound("Effect", false, "DoorOpen", "Effect/Door_Open.wav");
}