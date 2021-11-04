
#include "Stage.h"
#include "SceneResource.h"

void CStage::LoadSound()
{
	GetSceneResource()->SetVolume("Effect", 20);

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

	// AngelBaby 공격사운드 1,2
	GetSceneResource()->LoadSound("Effect", false, "AngelBabyAttack1", "Effect/Enemy_AngelBaby1.wav");
	GetSceneResource()->LoadSound("Effect", false, "AngelBabyAttack2", "Effect/Enemy_AngelBaby2.wav");
}

void CStage::BossSound()
{
	// 죽음
	GetSceneResource()->LoadSound("Effect", false, "MotherDie", "Effect/Mother/Dead.wav");

	// 공격 패턴
	GetSceneResource()->LoadSound("Effect", false, "MotherAttack", "Effect/Mother/Attack.wav");

	// 바닥에 발을 찍을때 충격파음
	GetSceneResource()->LoadSound("Effect", false, "MotherAttackEnd", "Effect/Mother/AttackEnd.wav");

	// 바닥에 손으로 찍을때 충격파음
	GetSceneResource()->LoadSound("Effect", false, "MotherHandAttack", "Effect/Mother/HandAttack.wav");

	// 아이작!
	GetSceneResource()->LoadSound("Effect", false, "MotherCall1", "Effect/Mother/Call1.wav");
	GetSceneResource()->LoadSound("Effect", false, "MotherCall2", "Effect/Mother/Call2.wav");

	// 소환 소리
	GetSceneResource()->LoadSound("Effect", false, "MotherSummon", "Effect/Mother/Summon.wav");

	// 아이작 피격
	GetSceneResource()->LoadSound("Effect", false, "MotherIsaacHit", "Effect/Mother/Isaac_Hit.wav");

	// 아이작 우는것 (누워서 발사)
	GetSceneResource()->LoadSound("Effect", false, "IsaacCrying1", "Effect/Isaac/Crying1.wav");
	GetSceneResource()->LoadSound("Effect", false, "IsaacCrying2", "Effect/Isaac/Crying2.wav");

	// 아이작 기상
	GetSceneResource()->LoadSound("Effect", false, "IsaacStandUp", "Effect/Isaac/StandUp.wav");

	// 아이작 눈물발사
	GetSceneResource()->LoadSound("Effect", false, "IsaacFire", "Effect/Isaac/Fire.wav");

	// 아이작 점프
	GetSceneResource()->LoadSound("Effect", false, "IsaacJump", "Effect/Isaac/Jump.wav");

	// 아이작 변신
	GetSceneResource()->LoadSound("Effect", false, "IsaacTransform", "Effect/Isaac/Transform.wav");

	// 아이작 승천
	GetSceneResource()->LoadSound("Effect", false, "IsaacFlying", "Effect/Isaac/Flying.mp3");

	// 아이작 착지
	GetSceneResource()->LoadSound("Effect", false, "IsaacLand", "Effect/Isaac/Land.mp3");
	
	// 아이작 죽음
	GetSceneResource()->LoadSound("Effect", false, "IsaacDie", "Effect/Isaac/Transform.wav");
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

	// 하트 획득, 드랍
	GetSceneResource()->LoadSound("Effect", false, "HeartAdd", "Effect/Item/Heart_Add.mp3");
	GetSceneResource()->LoadSound("Effect", false, "HeartDrop", "Effect/Item/Heart_Drop.mp3");
	
	// 아이템 획득
	GetSceneResource()->LoadSound("Effect", false, "ItemAdd", "Effect/Item/Item_Add.wav");

	// 치트 on/off
	GetSceneResource()->LoadSound("Effect", false, "CheatOn", "Effect/Cheat/On.wav");
	GetSceneResource()->LoadSound("Effect", false, "CheatOff", "Effect/Cheat/Off.wav");
}