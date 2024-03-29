
#include "Stage.h"
#include "SceneResource.h"
#include "SceneManager.h"

void CStage::LoadAnimationSequence()
{
	PlayerAnimation();
	EnemyAnimation();
	BossAnimation();
	TearAnimation();
	BombAnimation();
	ItemAnimation();

	CSceneManager::GetInst()->InputAnimFrameData();
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

	// -------------- ItemIdle --------------
	GetSceneResource()->CreateAnimationSequence("HeadItemIdleUp", "HeadItemIdleUp", TEXT("Player/Head/Item/Idle_Up.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadItemIdleUp");
	GetSceneResource()->AddAnimationFrameData("HeadItemIdleUp", Vector2(0.f, 0.f), Vector2(84.f, 75.f));

	GetSceneResource()->CreateAnimationSequence("HeadItemIdleLeft", "HeadItemIdleLeft", TEXT("Player/Head/Item/Idle_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadItemIdleLeft");
	GetSceneResource()->AddAnimationFrameData("HeadItemIdleLeft", Vector2(0.f, 0.f), Vector2(84.f, 75.f));

	GetSceneResource()->CreateAnimationSequence("HeadItemIdleDown", "HeadItemIdleDown", TEXT("Player/Head/Item/Idle_Down.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadItemIdleDown");
	GetSceneResource()->AddAnimationFrameData("HeadItemIdleDown", Vector2(0.f, 0.f), Vector2(84.f, 75.f));

	GetSceneResource()->CreateAnimationSequence("HeadItemIdleRight", "HeadItemIdleRight", TEXT("Player/Head/Item/Idle_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadItemIdleRight");
	GetSceneResource()->AddAnimationFrameData("HeadItemIdleRight", Vector2(0.f, 0.f), Vector2(84.f, 75.f));

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

	// -------------- ItemFire --------------

	GetSceneResource()->CreateAnimationSequence("HeadItemFireUp", "HeadItemFireUp", TEXT("Player/Head/Item/Fire_Up.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadItemFireUp");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeadItemFireUp", Vector2(i * 84.f, 0.f), Vector2(84.f, 75.f));
	}

	GetSceneResource()->CreateAnimationSequence("HeadItemFireLeft", "HeadItemFireLeft", TEXT("Player/Head/Item/Fire_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadItemFireLeft");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeadItemFireLeft", Vector2(i * 84.f, 0.f), Vector2(84.f, 75.f));
	}

	GetSceneResource()->CreateAnimationSequence("HeadItemFireDown", "HeadItemFireDown", TEXT("Player/Head/Item/Fire_Down.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadItemFireDown");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeadItemFireDown", Vector2(i * 84.f, 0.f), Vector2(84.f, 75.f));
	}

	GetSceneResource()->CreateAnimationSequence("HeadItemFireRight", "HeadItemFireRight", TEXT("Player/Head/Item/Fire_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("HeadItemFireRight");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeadItemFireRight", Vector2(i * 84.f, 0.f), Vector2(84.f, 75.f));
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
			if (i == 1 && j == 2)	// 8 프레임일 시 반복문 종료
				break;

			GetSceneResource()->AddAnimationFrameData("BodyMoveUp", Vector2(56.f * j, 45.f * i), Vector2(56.f, 45.f));
		}
	}

	GetSceneResource()->CreateAnimationSequence("BodyMoveLeft", "BodyMoveLeft", TEXT("Player/Body/Move_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("BodyMoveLeft");

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			GetSceneResource()->AddAnimationFrameData("BodyMoveLeft", Vector2(56.f * j, 42.f * i), Vector2(56.f, 42.f));
		}
	}

	GetSceneResource()->CreateAnimationSequence("BodyMoveDown", "BodyMoveDown", TEXT("Player/Body/Move_Down.bmp"));
	GetSceneResource()->SetTextureColorKey("BodyMoveDown");

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i == 1 && j == 4)	// 9 프레임일 시 반복문 종료
				break;

			GetSceneResource()->AddAnimationFrameData("BodyMoveDown", Vector2(56.f * j, 45.f * i), Vector2(56.f, 45.f));
		}
	}

	GetSceneResource()->CreateAnimationSequence("BodyMoveRight", "BodyMoveRight", TEXT("Player/Body/Move_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("BodyMoveRight");

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			GetSceneResource()->AddAnimationFrameData("BodyMoveRight", Vector2(56.f * j, 42.f * i), Vector2(56.f, 42.f));
		}
	}

	// ============== Isaac ==============
	// -------------- Death --------------

	GetSceneResource()->CreateAnimationSequence("IsaacDeath", "IsaacDeath", TEXT("Player/Hit_Death.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacDeath");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("IsaacDeath", Vector2(128.f * i, 0.f), Vector2(128.f, 128.f));
	}

	// -------------- AddItem --------------

	GetSceneResource()->CreateAnimationSequence("IsaacAddItem", "IsaacAddItem", TEXT("Player/Item/Player_AddItem.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacAddItem");
	GetSceneResource()->AddAnimationFrameData("IsaacAddItem", Vector2(0.f, 0.f), Vector2(84.f, 93.f));
}

void CStage::EnemyAnimation()
{
	// ============== Smoke ==============
	GetSceneResource()->CreateAnimationSequence("Smoke1", "Smoke1", TEXT("Monster/Smoke/Smoke_1.bmp"));
	GetSceneResource()->SetTextureColorKey("Smoke1");

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			GetSceneResource()->AddAnimationFrameData("Smoke1", Vector2(144.f * j, 144.f * i), Vector2(144.f, 144.f));
		}
	}

	GetSceneResource()->CreateAnimationSequence("Smoke2", "Smoke2", TEXT("Monster/Smoke/Smoke_2.bmp"));
	GetSceneResource()->SetTextureColorKey("Smoke2");

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			GetSceneResource()->AddAnimationFrameData("Smoke2", Vector2(288.f * j, 288.f * i), Vector2(288.f, 288.f));
		}
	}

	// ============== Charger ==============
	// -------------- Move --------------
	GetSceneResource()->CreateAnimationSequence("ChargerMoveRight", "ChargerMoveRight", TEXT("Monster/Enemy/Charger/Charger.bmp"));
	GetSceneResource()->SetTextureColorKey("ChargerMoveRight");

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ChargerMoveRight", Vector2(128.f * i, 0.f), Vector2(128.f, 128.f));
	}

	GetSceneResource()->CreateAnimationSequence("ChargerMoveLeft", "ChargerMoveLeft", TEXT("Monster/Enemy/Charger/Charger.bmp"));
	GetSceneResource()->SetTextureColorKey("ChargerMoveLeft");

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ChargerMoveLeft", Vector2(128.f * i, 128.f), Vector2(128.f, 128.f));
	}

	GetSceneResource()->CreateAnimationSequence("ChargerMoveUp", "ChargerMoveUp", TEXT("Monster/Enemy/Charger/Charger.bmp"));
	GetSceneResource()->SetTextureColorKey("ChargerMoveUp");

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ChargerMoveUp", Vector2(128.f * i, 128.f * 2), Vector2(128.f, 128.f));
	}

	GetSceneResource()->CreateAnimationSequence("ChargerMoveDown", "ChargerMoveDown", TEXT("Monster/Enemy/Charger/Charger.bmp"));
	GetSceneResource()->SetTextureColorKey("ChargerMoveDown");

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ChargerMoveDown", Vector2(128.f * i, 128.f * 3), Vector2(128.f, 128.f));
	}

	// -------------- Attack --------------
	GetSceneResource()->CreateAnimationSequence("ChargerAttackRight", "ChargerAttackRight", TEXT("Monster/Enemy/Charger/Charger.bmp"));
	GetSceneResource()->SetTextureColorKey("ChargerAttackRight");
	GetSceneResource()->AddAnimationFrameData("ChargerAttackRight", Vector2(0.f, 128.f * 4), Vector2(128.f, 128.f));

	GetSceneResource()->CreateAnimationSequence("ChargerAttackLeft", "ChargerAttackLeft", TEXT("Monster/Enemy/Charger/Charger.bmp"));
	GetSceneResource()->SetTextureColorKey("ChargerAttackLeft");
	GetSceneResource()->AddAnimationFrameData("ChargerAttackLeft", Vector2(128.f, 128.f * 4), Vector2(128.f, 128.f));

	GetSceneResource()->CreateAnimationSequence("ChargerAttackUp", "ChargerAttackUp", TEXT("Monster/Enemy/Charger/Charger.bmp"));
	GetSceneResource()->SetTextureColorKey("ChargerAttackUp");
	GetSceneResource()->AddAnimationFrameData("ChargerAttackUp", Vector2(128.f * 2, 128.f * 4), Vector2(128.f, 128.f));

	GetSceneResource()->CreateAnimationSequence("ChargerAttackDown", "ChargerAttackDown", TEXT("Monster/Enemy/Charger/Charger.bmp"));
	GetSceneResource()->SetTextureColorKey("ChargerAttackDown");
	GetSceneResource()->AddAnimationFrameData("ChargerAttackDown", Vector2(128.f * 3, 128.f * 4), Vector2(128.f, 128.f));

	// -------------- Die --------------
	GetSceneResource()->CreateAnimationSequence("DieNormal", "DieNormal", TEXT("Monster/Enemy/Die_Normal.bmp"));
	GetSceneResource()->SetTextureColorKey("DieNormal");

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == 2 && j == 3)
				break;

			GetSceneResource()->AddAnimationFrameData("DieNormal", Vector2(192.f * j, 192.f * i), Vector2(192.f, 192.f));
		}
	}

	GetSceneResource()->CreateAnimationSequence("DieFly", "DieFly", TEXT("Monster/Enemy/Die_Fly.bmp"));
	GetSceneResource()->SetTextureColorKey("DieFly");

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == 2 && j == 3)
				break;

			GetSceneResource()->AddAnimationFrameData("DieFly", Vector2(192.f * j, 192.f * i), Vector2(192.f, 192.f));
		}
	}

	// ============== Pooter ==============
	// -------------- Idle --------------
	GetSceneResource()->CreateAnimationSequence("PooterIdleRight", "PooterIdleRight", TEXT("Monster/Enemy/Pooter/Pooter_Idle_R.bmp"));
	GetSceneResource()->SetTextureColorKey("PooterIdleRight");

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PooterIdleRight", Vector2(96.f * i, 0.f), Vector2(96.f, 96.f));
	}

	GetSceneResource()->CreateAnimationSequence("PooterIdleLeft", "PooterIdleLeft", TEXT("Monster/Enemy/Pooter/Pooter_Idle_L.bmp"));
	GetSceneResource()->SetTextureColorKey("PooterIdleLeft");

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PooterIdleLeft", Vector2(96.f * i, 0.f), Vector2(96.f, 96.f));
	}

	// -------------- Fire --------------
	GetSceneResource()->CreateAnimationSequence("PooterFireRight", "PooterFireRight", TEXT("Monster/Enemy/Pooter/Pooter_Fire_R.bmp"));
	GetSceneResource()->SetTextureColorKey("PooterFireRight");

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PooterFireRight", Vector2(96.f * i, 0.f), Vector2(96.f, 96.f));
	}

	GetSceneResource()->CreateAnimationSequence("PooterFireLeft", "PooterFireLeft", TEXT("Monster/Enemy/Pooter/Pooter_Fire_L.bmp"));
	GetSceneResource()->SetTextureColorKey("PooterFireLeft");

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PooterFireLeft", Vector2(96.f * i, 0.f), Vector2(96.f, 96.f));
	}

	// ============== Fly ==============
	// -------------- Idle --------------
	GetSceneResource()->CreateAnimationSequence("FlyIdle", "FlyIdle", TEXT("Monster/Enemy/Fly/Fly_Idle.bmp"));
	GetSceneResource()->SetTextureColorKey("FlyIdle");

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("FlyIdle", Vector2(96.f * i, 0.f), Vector2(96.f, 96.f));
	}

	// ============== RedFly ==============
	// -------------- Idle --------------
	GetSceneResource()->CreateAnimationSequence("RedFlyIdle", "RedFlyIdle", TEXT("Monster/Enemy/RedFly/RedFly_Idle.bmp"));
	GetSceneResource()->SetTextureColorKey("RedFlyIdle");

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("RedFlyIdle", Vector2(96.f * i, 0.f), Vector2(96.f, 96.f));
	}
}

void CStage::BossAnimation()
{
	// ============== Mother ==============
	// -------------- Leg --------------
	GetSceneResource()->CreateAnimationSequence("MotherLeg", "MotherLeg", TEXT("Monster/Boss/Mother_Leg.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherLeg");
	GetSceneResource()->AddAnimationFrameData("MotherLeg", Vector2(0.f, 0.f), Vector2(387.f, 754.f));

	// -------------- Hand --------------
	GetSceneResource()->CreateAnimationSequence("MotherHandTop", "MotherHandTop", TEXT("Monster/Boss/Mother_Hand_Top.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherHandTop");
	GetSceneResource()->AddAnimationFrameData("MotherHandTop", Vector2(0.f, 0.f), Vector2(127.f, 110.f));
	GetSceneResource()->AddAnimationFrameData("MotherHandTop", Vector2(127.f, 0.f), Vector2(236.f, 255.f));

	GetSceneResource()->CreateAnimationSequence("MotherHandBottom", "MotherHandBottom", TEXT("Monster/Boss/Mother_Hand_Bottom.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherHandBottom");
	GetSceneResource()->AddAnimationFrameData("MotherHandBottom", Vector2(0.f, 0.f), Vector2(127.f, 110.f));
	GetSceneResource()->AddAnimationFrameData("MotherHandBottom", Vector2(127.f, 0.f), Vector2(236.f, 255.f));

	GetSceneResource()->CreateAnimationSequence("MotherHandLeft", "MotherHandLeft", TEXT("Monster/Boss/Mother_Hand_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherHandLeft");
	GetSceneResource()->AddAnimationFrameData("MotherHandLeft", Vector2(0.f, 0.f), Vector2(110.f, 127.f));
	GetSceneResource()->AddAnimationFrameData("MotherHandLeft", Vector2(0.f, 127.f), Vector2(255.f, 236.f));

	GetSceneResource()->CreateAnimationSequence("MotherHandRight", "MotherHandRight", TEXT("Monster/Boss/Mother_Hand_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherHandRight");
	GetSceneResource()->AddAnimationFrameData("MotherHandRight", Vector2(0.f, 0.f), Vector2(110.f, 127.f));
	GetSceneResource()->AddAnimationFrameData("MotherHandRight", Vector2(0.f, 127.f), Vector2(255.f, 236.f));

	// -------------- Skin --------------
	GetSceneResource()->CreateAnimationSequence("MotherSkinTop", "MotherSkinTop", TEXT("Monster/Boss/Mother_Skin_Top.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherSkinTop");
	GetSceneResource()->AddAnimationFrameData("MotherSkinTop", Vector2(0.f, 0.f), Vector2(142.f, 121.f));

	GetSceneResource()->CreateAnimationSequence("MotherSkinBottom", "MotherSkinBottom", TEXT("Monster/Boss/Mother_Skin_Bottom.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherSkinBottom");
	GetSceneResource()->AddAnimationFrameData("MotherSkinBottom", Vector2(0.f, 0.f), Vector2(142.f, 121.f));

	GetSceneResource()->CreateAnimationSequence("MotherSkinLeft", "MotherSkinLeft", TEXT("Monster/Boss/Mother_Skin_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherSkinLeft");
	GetSceneResource()->AddAnimationFrameData("MotherSkinLeft", Vector2(0.f, 0.f), Vector2(121.f, 142.f));

	GetSceneResource()->CreateAnimationSequence("MotherSkinRight", "MotherSkinRight", TEXT("Monster/Boss/Mother_Skin_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherSkinRight");
	GetSceneResource()->AddAnimationFrameData("MotherSkinRight", Vector2(0.f, 0.f), Vector2(121.f, 142.f));

	// -------------- Eye --------------
	GetSceneResource()->CreateAnimationSequence("MotherEyeTop", "MotherEyeTop", TEXT("Monster/Boss/Mother_Eye_Top.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherEyeTop");
	GetSceneResource()->AddAnimationFrameData("MotherEyeTop", Vector2(0.f, 0.f), Vector2(126.f, 132.f));

	GetSceneResource()->CreateAnimationSequence("MotherEyeBottom", "MotherEyeBottom", TEXT("Monster/Boss/Mother_Eye_Bottom.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherEyeBottom");
	GetSceneResource()->AddAnimationFrameData("MotherEyeBottom", Vector2(0.f, 0.f), Vector2(126.f, 132.f));

	GetSceneResource()->CreateAnimationSequence("MotherEyeLeft", "MotherEyeLeft", TEXT("Monster/Boss/Mother_Eye_Left.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherEyeLeft");
	GetSceneResource()->AddAnimationFrameData("MotherEyeLeft", Vector2(0.f, 0.f), Vector2(132.f, 126.f));

	GetSceneResource()->CreateAnimationSequence("MotherEyeRight", "MotherEyeRight", TEXT("Monster/Boss/Mother_Eye_Right.bmp"));
	GetSceneResource()->SetTextureColorKey("MotherEyeRight");
	GetSceneResource()->AddAnimationFrameData("MotherEyeRight", Vector2(0.f, 0.f), Vector2(132.f, 126.f));

	// ============== Isaac ==============
	// -------------- Create --------------
	GetSceneResource()->CreateAnimationSequence("IsaacCreate", "IsaacCreate", TEXT("Monster/Boss/Isaac/Create.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacCreate");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("IsaacCreate", Vector2(240.f * i, 0.f), Vector2(240.f, 240.f));
	}

	// -------------- Lying --------------
	GetSceneResource()->CreateAnimationSequence("IsaacLying", "IsaacLying", TEXT("Monster/Boss/Isaac/Lying.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacLying");

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("IsaacLying", Vector2(240.f * i, 0.f), Vector2(240.f, 240.f));
	}

	// -------------- StandUp --------------
	GetSceneResource()->CreateAnimationSequence("IsaacStandUp", "IsaacStandUp", TEXT("Monster/Boss/Isaac/StandUp.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacStandUp");

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("IsaacStandUp", Vector2(240.f * i, 0.f), Vector2(240.f, 240.f));
	}

	// -------------- Stand --------------
	GetSceneResource()->CreateAnimationSequence("IsaacStand", "IsaacStand", TEXT("Monster/Boss/Isaac/Stand.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacStand");
	GetSceneResource()->AddAnimationFrameData("IsaacStand", Vector2(0.f, 0.f), Vector2(240.f, 240.f));

	// -------------- Jump --------------
	GetSceneResource()->CreateAnimationSequence("IsaacJump", "IsaacJump", TEXT("Monster/Boss/Isaac/Jump.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacJump");

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("IsaacJump", Vector2(240.f * i, 0.f), Vector2(240.f, 240.f));
	}

	// -------------- Transform --------------
	GetSceneResource()->CreateAnimationSequence("IsaacTransform", "IsaacTransform", TEXT("Monster/Boss/Isaac/Transform.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacTransform");

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("IsaacTransform", Vector2(240.f * i, 0.f), Vector2(240.f, 240.f));
	}

	// -------------- Idle --------------
	GetSceneResource()->CreateAnimationSequence("IsaacIdle", "IsaacIdle", TEXT("Monster/Boss/Isaac/Idle.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacIdle");

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("IsaacIdle", Vector2(240.f * i, 0.f), Vector2(240.f, 240.f));
	}

	// -------------- Flying --------------
	GetSceneResource()->CreateAnimationSequence("IsaacFlying", "IsaacFlying", TEXT("Monster/Boss/Isaac/Flying.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacFlying");

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("IsaacFlying", Vector2(240.f * i, 0.f), Vector2(240.f, 240.f));
	}

	// -------------- Land --------------
	GetSceneResource()->CreateAnimationSequence("IsaacLand", "IsaacLand", TEXT("Monster/Boss/Isaac/Land.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacLand");

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("IsaacLand", Vector2(240.f * i, 0.f), Vector2(240.f, 240.f));
	}

	// -------------- Charge --------------
	GetSceneResource()->CreateAnimationSequence("IsaacCharge", "IsaacCharge", TEXT("Monster/Boss/Isaac/Charge.bmp"));
	GetSceneResource()->SetTextureColorKey("IsaacCharge");

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("IsaacCharge", Vector2(240.f * i, 0.f), Vector2(240.f, 240.f));
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

void CStage::BombAnimation()
{
	GetSceneResource()->CreateAnimationSequence("BombExplosion", "BombExplosion", TEXT("Player/Bomb/Explosion/Explosion.bmp"));
	GetSceneResource()->SetTextureColorKey("BombExplosion");

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			GetSceneResource()->AddAnimationFrameData("BombExplosion", Vector2(j * 288.f, i * 288.f), Vector2(288.f, 288.f));
		}
	}
}

void CStage::ItemAnimation()
{
	GetSceneResource()->CreateAnimationSequence("ItemAddEffect", "ItemAddEffect", TEXT("Item/Item_Add_Animation.bmp"));
	GetSceneResource()->SetTextureColorKey("ItemAddEffect");

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			GetSceneResource()->AddAnimationFrameData("ItemAddEffect", Vector2(j * 96.f, i * 96.f), Vector2(96.f, 96.f));
		}
	}
}
