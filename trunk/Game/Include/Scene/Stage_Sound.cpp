
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
	// �ǰ���, ����
	GetSceneResource()->LoadSound("Effect", false, "PlayerHit", "Effect/Hit.wav");
	GetSceneResource()->LoadSound("Effect", false, "PlayerDie", "Effect/Die.wav");
}

void CStage::EnemySound()
{
	// ����
	GetSceneResource()->LoadSound("Effect", false, "EnemyDie", "Effect/Enemy_Die.wav");

	// Charger ���ݻ���
	GetSceneResource()->LoadSound("Effect", false, "ChargerAttack", "Effect/Enemy_Charger.wav");
}

void CStage::BossSound()
{
}

void CStage::EffectSound()
{
	// ���� �߻� �� ����
	GetSceneResource()->LoadSound("Effect", false, "Tear", "Effect/Tear.wav");
	GetSceneResource()->LoadSound("Effect", false, "TearDrop", "Effect/Tear_Drop.wav");

	// ��ź
	GetSceneResource()->LoadSound("Effect", false, "BombExplosion", "Effect/Bomb_Explosion.mp3");

	// �� ����, ����
	GetSceneResource()->LoadSound("Effect", false, "DoorClose", "Effect/Door_Close.wav");
	GetSceneResource()->LoadSound("Effect", false, "DoorOpen", "Effect/Door_Open.wav");
}