
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
}

void CStage::EnemySound()
{
}

void CStage::BossSound()
{
}

void CStage::EffectSound()
{
	// 눈물 발사 및 제거
	GetSceneResource()->LoadSound("Effect", false, "Tear", "Effect/Tear.wav");
	GetSceneResource()->LoadSound("Effect", false, "TearDrop", "Effect/Tear_Drop.wav");
}