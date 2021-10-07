
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
}

void CStage::EnemySound()
{
}

void CStage::BossSound()
{
}

void CStage::EffectSound()
{
	// ���� �߻� �� ����
	GetSceneResource()->LoadSound("Effect", false, "Tear", "Effect/Tear.wav");
	GetSceneResource()->LoadSound("Effect", false, "TearDrop", "Effect/Tear_Drop.wav");
}