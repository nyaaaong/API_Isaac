#pragma once

enum EKeyState
{
	KS_DOWN,
	KS_PUSH,
	KS_UP,
	KS_MAX
};

enum class ETexture_Type
{
	ATLAS,
	FRAME
};

enum class ECollider_Type
{
	Box,
	Sphere,
	Point,
	Line
};

enum ECollision_Channel
{
	Channel_Object,
	Channel_Door,
	Channel_PlayerHead,
	Channel_PlayerBody,
	Channel_Monster,
	Channel_PlayerAttack,
	Channel_MonsterAttack,
	Channel_Bomb,
	Channel_BombExplosion,
	Channel_Effect,
	Channel_Max
};

enum class ECollision_State
{
	Ignore,
	Collision
};

enum class EZOrder
{
	FadeEffect = -10000,
	UI = -1000,
	BackGroundBar = -900,
	Effect = -900,
	Item = -100,
	MotherLeg = -80,
	Monster = -30,
	MonsterDoor = -22,
	Player = -20,
	PlayerBody = -19,
	Bomb = -18,
	RoomObject = -15,
	BackGround = 0
};

enum class ETearType
{
	None,
	Player,
	Monster
};

enum EDoorDir
{
	DD_LEFT,
	DD_TOP,
	DD_RIGHT,
	DD_BOTTOM,
	DD_MAX
};

enum EDoorType
{
	DT_NORMAL,
	DT_BOSS,
	DT_ITEM,
	DT_MAX
};

enum EMapObject_Type
{
	MT_NONE,
	MT_ROCK,
	MT_IRON,
	MT_SPIKE,
	MT_POOP,
	MT_SPAWN,
	MT_MAX
};

enum class EEditor_State
{
	Idle,
	Saved,
	Loaded
};

enum class ESpecial_RoomType
{
	None,
	Start,
	Item,
	Boss
};

enum class EEnemy_Type
{
	Normal,
	Fly
};

enum class EMusic_Type
{
	Boss,
	BossClear
};

enum class EMotherDoor_Type
{
	Hand,
	Eye,
	Skin,
	Max
};