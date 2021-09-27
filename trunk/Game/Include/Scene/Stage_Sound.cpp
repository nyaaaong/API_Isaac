
#include "Stage.h"
#include "SceneResource.h"

void CStage::LoadSound()
{
	PlayerSound();
	EnemySound();
	BossSound();
	EffectSound();
}

void CStage::LoadBGM()
{
	if (m_iStage == 1)
	{
		GetSceneResource()->LoadSound("BGM", true, "Stage1BGM", "Music/Stage1.ogg");
		GetSceneResource()->SoundPlay("Stage1BGM");
	}
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
