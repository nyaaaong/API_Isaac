
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

	// AngelBaby ���ݻ��� 1,2
	GetSceneResource()->LoadSound("Effect", false, "AngelBabyAttack1", "Effect/Enemy_AngelBaby1.wav");
	GetSceneResource()->LoadSound("Effect", false, "AngelBabyAttack2", "Effect/Enemy_AngelBaby2.wav");
}

void CStage::BossSound()
{
	// ����
	GetSceneResource()->LoadSound("Effect", false, "MotherDie", "Effect/Mother/Dead.wav");

	// ���� ����
	GetSceneResource()->LoadSound("Effect", false, "MotherAttack", "Effect/Mother/Attack.wav");

	// �ٴڿ� ���� ������ �������
	GetSceneResource()->LoadSound("Effect", false, "MotherAttackEnd", "Effect/Mother/AttackEnd.wav");

	// �ٴڿ� ������ ������ �������
	GetSceneResource()->LoadSound("Effect", false, "MotherHandAttack", "Effect/Mother/HandAttack.wav");

	// ������!
	GetSceneResource()->LoadSound("Effect", false, "MotherCall1", "Effect/Mother/Call1.wav");
	GetSceneResource()->LoadSound("Effect", false, "MotherCall2", "Effect/Mother/Call2.wav");

	// ��ȯ �Ҹ�
	GetSceneResource()->LoadSound("Effect", false, "MotherSummon", "Effect/Mother/Summon.wav");

	// ������ �ǰ�
	GetSceneResource()->LoadSound("Effect", false, "MotherIsaacHit", "Effect/Mother/Isaac_Hit.wav");

	// ������ ��°� (������ �߻�)
	GetSceneResource()->LoadSound("Effect", false, "IsaacCrying1", "Effect/Isaac/Crying1.wav");
	GetSceneResource()->LoadSound("Effect", false, "IsaacCrying2", "Effect/Isaac/Crying2.wav");

	// ������ ���
	GetSceneResource()->LoadSound("Effect", false, "IsaacStandUp", "Effect/Isaac/StandUp.wav");

	// ������ �����߻�
	GetSceneResource()->LoadSound("Effect", false, "IsaacFire", "Effect/Isaac/Fire.wav");

	// ������ ����
	GetSceneResource()->LoadSound("Effect", false, "IsaacJump", "Effect/Isaac/Jump.wav");

	// ������ ����
	GetSceneResource()->LoadSound("Effect", false, "IsaacTransform", "Effect/Isaac/Transform.wav");

	// ������ ��õ
	GetSceneResource()->LoadSound("Effect", false, "IsaacFlying", "Effect/Isaac/Flying.mp3");

	// ������ ����
	GetSceneResource()->LoadSound("Effect", false, "IsaacLand", "Effect/Isaac/Land.mp3");
	
	// ������ ����
	GetSceneResource()->LoadSound("Effect", false, "IsaacDie", "Effect/Isaac/Transform.wav");
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

	// ��Ʈ ȹ��, ���
	GetSceneResource()->LoadSound("Effect", false, "HeartAdd", "Effect/Item/Heart_Add.mp3");
	GetSceneResource()->LoadSound("Effect", false, "HeartDrop", "Effect/Item/Heart_Drop.mp3");
	
	// ������ ȹ��
	GetSceneResource()->LoadSound("Effect", false, "ItemAdd", "Effect/Item/Item_Add.wav");

	// ġƮ on/off
	GetSceneResource()->LoadSound("Effect", false, "CheatOn", "Effect/Cheat/On.wav");
	GetSceneResource()->LoadSound("Effect", false, "CheatOff", "Effect/Cheat/Off.wav");
}