
#include "Stage.h"
#include "SceneResource.h"

void CStage::LoadAnimationSequence()
{
	PlayerAnimation();
	EnemyAnimation();
	BossAnimation();
	TearAnimation();
}

void CStage::PlayerAnimation()
{
	// ============== Head ==============
	// -------------- Idle --------------
	GetSceneResource()->CreateAnimationSequence("HeadIdleUp", "HeadIdleUp", TEXT("Player/Head/Idle_Up.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadIdleUp");
	GetSceneResource()->AddAnimationFrameData("HeadIdleUp", Vector2(0.f, 0.f), Vector2(84.f, 75.f));

	GetSceneResource()->CreateAnimationSequence("HeadIdleLeft", "HeadIdleLeft", TEXT("Player/Head/Idle_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadIdleLeft");
	GetSceneResource()->AddAnimationFrameData("HeadIdleLeft", Vector2(0.f, 0.f), Vector2(84.f, 75.f));

	GetSceneResource()->CreateAnimationSequence("HeadIdleDown", "HeadIdleDown", TEXT("Player/Head/Idle_Down.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadIdleDown");
	GetSceneResource()->AddAnimationFrameData("HeadIdleDown", Vector2(0.f, 0.f), Vector2(84.f, 75.f));

	GetSceneResource()->CreateAnimationSequence("HeadIdleRight", "HeadIdleRight", TEXT("Player/Head/Idle_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadIdleRight");
	GetSceneResource()->AddAnimationFrameData("HeadIdleRight", Vector2(0.f, 0.f), Vector2(84.f, 75.f));

	// -------------- Fire --------------

	GetSceneResource()->CreateAnimationSequence("HeadFireUp", "HeadFireUp", TEXT("Player/Head/Fire_Up.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadFireUp");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeadFireUp", Vector2(i * 84.f, 0.f), Vector2(84.f, 75.f));
	}

	GetSceneResource()->CreateAnimationSequence("HeadFireLeft", "HeadFireLeft", TEXT("Player/Head/Fire_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadFireLeft");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeadFireLeft", Vector2(i * 84.f, 0.f), Vector2(84.f, 75.f));
	}

	GetSceneResource()->CreateAnimationSequence("HeadFireDown", "HeadFireDown", TEXT("Player/Head/Fire_Down.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadFireDown");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeadFireDown", Vector2(i * 84.f, 0.f), Vector2(84.f, 75.f));
	}

	GetSceneResource()->CreateAnimationSequence("HeadFireRight", "HeadFireRight", TEXT("Player/Head/Fire_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadFireRight");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeadFireRight", Vector2(i * 84.f, 0.f), Vector2(84.f, 75.f));
	}

	// ============== Body ==============
	// -------------- Idle --------------

	GetSceneResource()->CreateAnimationSequence("BodyIdleDown", "BodyIdleDown", TEXT("Player/Body/Move_Down.bmp"));
	GetSceneResource()->SetTextureColorKey("BodyIdleDown");
	GetSceneResource()->AddAnimationFrameData("BodyIdleDown", Vector2(224.f, 0.f), Vector2(56.f, 45.f));

	// -------------- Move --------------

	GetSceneResource()->CreateAnimationSequence("BodyMoveUp", "BodyMoveUp", TEXT("Player/Body/Move_Up.bmp"));
	GetSceneResource()->SetTextureColorKey("BodyMoveUp");

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i == 1 && j == 2)	// 8 �������� �� �ݺ��� ����
				break;

			GetSceneResource()->AddAnimationFrameData("BodyMoveUp", Vector2(static_cast<float>(56.f * j), static_cast<float>(45.f * i)), Vector2(56.f, 45.f));
		}
	}

	GetSceneResource()->CreateAnimationSequence("BodyMoveLeft", "BodyMoveLeft", TEXT("Player/Body/Move_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("BodyMoveLeft");

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			GetSceneResource()->AddAnimationFrameData("BodyMoveLeft", Vector2(static_cast<float>(56.f * j), static_cast<float>(42.f * i)), Vector2(56.f, 42.f));
		}
	}

	GetSceneResource()->CreateAnimationSequence("BodyMoveDown", "BodyMoveDown", TEXT("Player/Body/Move_Down.bmp"));
	GetSceneResource()->SetTextureColorKey("BodyMoveDown");

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i == 1 && j == 4)	// 9 �������� �� �ݺ��� ����
				break;

			GetSceneResource()->AddAnimationFrameData("BodyMoveDown", Vector2(static_cast<float>(56.f * j), static_cast<float>(45.f * i)), Vector2(56.f, 45.f));
		}
	}

	GetSceneResource()->CreateAnimationSequence("BodyMoveRight", "BodyMoveRight", TEXT("Player/Body/Move_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("BodyMoveRight");

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			GetSceneResource()->AddAnimationFrameData("BodyMoveRight", Vector2(static_cast<float>(56.f * j), static_cast<float>(42.f * i)), Vector2(56.f, 42.f));
		}
	}
}

void CStage::EnemyAnimation()
{
}

void CStage::BossAnimation()
{
	// ============== Monstro ==============
	// -------------- Idle --------------
	GetSceneResource()->CreateAnimationSequence("MonstroIdleLeft", "MonstroIdleLeft", TEXT("Monster/Boss/Monstro/Monstro_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("MonstroIdleLeft");
	GetSceneResource()->AddAnimationFrameData("MonstroIdleLeft", Vector2(0.f, 0.f), Vector2(256.f, 256.f));

	GetSceneResource()->CreateAnimationSequence("MonstroIdleRight", "MonstroIdleRight", TEXT("Monster/Boss/Monstro/Monstro_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("MonstroIdleRight");
	GetSceneResource()->AddAnimationFrameData("MonstroIdleRight", Vector2(0.f, 0.f), Vector2(256.f, 256.f));

	// -------------- Move --------------
	GetSceneResource()->CreateAnimationSequence("MonstroMoveLeft", "MonstroMoveLeft", TEXT("Monster/Boss/Monstro/Monstro_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("MonstroMoveLeft");

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("MonstroMoveLeft", Vector2(i * 256.f, 256.f), Vector2(256.f, 256.f));
	}

	GetSceneResource()->CreateAnimationSequence("MonstroMoveRight", "MonstroMoveRight", TEXT("Monster/Boss/Monstro/Monstro_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("MonstroMoveRight");

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("MonstroMoveRight", Vector2(i * 256.f, 256.f), Vector2(256.f, 256.f));
	}

	// -------------- Attack --------------
	GetSceneResource()->CreateAnimationSequence("MonstroFireLeft", "MonstroFireLeft", TEXT("Monster/Boss/Monstro/Monstro_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("MonstroFireLeft");

	for (int i = 1; i <= 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("MonstroFireLeft", Vector2(i * 256.f, 0.f), Vector2(256.f, 256.f));
	}

	GetSceneResource()->CreateAnimationSequence("MonstroFireRight", "MonstroFireRight", TEXT("Monster/Boss/Monstro/Monstro_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("MonstroFireRight");

	for (int i = 1; i <= 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("MonstroFireRight", Vector2(i * 256.f, 0.f), Vector2(256.f, 256.f));
	}

	// -------------- Jump --------------
	GetSceneResource()->CreateAnimationSequence("MonstroJumpLeft", "MonstroJumpLeft", TEXT("Monster/Boss/Monstro/Monstro_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("MonstroJumpLeft");

	for (int i = 0; i < 6; ++i)
	{
		if (i == 4)
			continue;

		GetSceneResource()->AddAnimationFrameData("MonstroJumpLeft", Vector2(i * 256.f, 256.f), Vector2(256.f, 256.f));
	}

	GetSceneResource()->CreateAnimationSequence("MonstroJumpRight", "MonstroJumpRight", TEXT("Monster/Boss/Monstro/Monstro_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("MonstroJumpRight");

	for (int i = 0; i < 6; ++i)
	{
		if (i == 4)
			continue;

		GetSceneResource()->AddAnimationFrameData("MonstroJumpRight", Vector2(i * 256.f, 256.f), Vector2(256.f, 256.f));
	}
}

void CStage::TearAnimation()
{
	GetSceneResource()->CreateAnimationSequence("PlayerTear", "PlayerTear", TEXT("Player/Tear/Tear.bmp"));
	GetSceneResource()->SetTextureColorKey("PlayerTear");
	GetSceneResource()->AddAnimationFrameData("PlayerTear", Vector2(0.f, 0.f), Vector2(80.f, 80.f));

	GetSceneResource()->CreateAnimationSequence("PlayerTearDrop", "PlayerTearDrop", TEXT("Player/Tear/Tear_Drop.bmp"));
	GetSceneResource()->SetTextureColorKey("PlayerTearDrop");

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			GetSceneResource()->AddAnimationFrameData("PlayerTearDrop", Vector2(j * 192.f, i * 192.f), Vector2(192.f, 192.f));
		}
	}

	GetSceneResource()->CreateAnimationSequence("MonsterTear", "MonsterTear", TEXT("Monster/Tear/Tear.bmp"));
	GetSceneResource()->SetTextureColorKey("MonsterTear");
	GetSceneResource()->AddAnimationFrameData("MonsterTear", Vector2(0.f, 0.f), Vector2(80.f, 80.f));

	GetSceneResource()->CreateAnimationSequence("MonsterTearDrop", "MonsterTearDrop", TEXT("Monster/Tear/Tear_Drop.bmp"));
	GetSceneResource()->SetTextureColorKey("MonsterTearDrop");

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			GetSceneResource()->AddAnimationFrameData("MonsterTearDrop", Vector2(j * 192.f, i * 192.f), Vector2(192.f, 192.f));
		}
	}
}