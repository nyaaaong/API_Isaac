
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
	// ÇÇ°ÝÀ½, Á×À½
	GetSceneResource()->LoadSound("Effect", false, "PlayerHit", "Effect/Hit.wav");
	GetSceneResource()->LoadSound("Effect", false, "PlayerDie", "Effect/Die.wav");
}

void CStage::EnemySound()
{
	// Á×À½
	GetSceneResource()->LoadSound("Effect", false, "EnemyDie", "Effect/Enemy_Die.wav");

	// Charger °ø°Ý»ç¿îµå
	GetSceneResource()->LoadSound("Effect", false, "ChargerAttack", "Effect/Enemy_Charger.wav");
}

void CStage::BossSound()
{
	// Á×À½
	GetSceneResource()->LoadSound("Effect", false, "MotherDie", "Effect/Mother/Dead.wav");

	// °ø°Ý ÆÐÅÏ
	GetSceneResource()->LoadSound("Effect", false, "MotherAttack", "Effect/Mother/Attack.wav");

	// ¹Ù´Ú¿¡ ¹ßÀ» ÂïÀ»¶§ Ãæ°ÝÆÄÀ½
	GetSceneResource()->LoadSound("Effect", false, "MotherAttackEnd", "Effect/Mother/AttackEnd.wav");

	// ¹Ù´Ú¿¡ ¼ÕÀ¸·Î ÂïÀ»¶§ Ãæ°ÝÆÄÀ½
	GetSceneResource()->LoadSound("Effect", false, "MotherHandAttack", "Effect/Mother/HandAttack.wav");

	// ¾ÆÀÌÀÛ!
	GetSceneResource()->LoadSound("Effect", false, "MotherCall1", "Effect/Mother/Call1.wav");
	GetSceneResource()->LoadSound("Effect", false, "MotherCall2", "Effect/Mother/Call2.wav");

	// ÇÇºÎ ÆÐÅÏ
	GetSceneResource()->LoadSound("Effect", false, "MotherSummon", "Effect/Mother/Summon.wav");

	// ¾ÆÀÌÀÛ ÇÇ°Ý
	GetSceneResource()->LoadSound("Effect", false, "MotherIsaacHit", "Effect/Mother/Isaac_Hit.wav");
}

void CStage::EffectSound()
{
	// ´«¹° ¹ß»ç ¹× Á¦°Å
	GetSceneResource()->LoadSound("Effect", false, "Tear", "Effect/Tear.wav");
	GetSceneResource()->LoadSound("Effect", false, "TearDrop", "Effect/Tear_Drop.wav");

	// ÆøÅº
	GetSceneResource()->LoadSound("Effect", false, "BombExplosion", "Effect/Bomb_Explosion.mp3");

	// ¹æ ´ÝÈû, ¿­¸²
	GetSceneResource()->LoadSound("Effect", false, "DoorClose", "Effect/Door_Close.wav");
	GetSceneResource()->LoadSound("Effect", false, "DoorOpen", "Effect/Door_Open.wav");

	// ÇÏÆ® È¹µæ, µå¶ø
	GetSceneResource()->LoadSound("Effect", false, "HeartAdd", "Effect/Item/Heart_Add.mp3");
	GetSceneResource()->LoadSound("Effect", false, "HeartDrop", "Effect/Item/Heart_Drop.mp3");
}