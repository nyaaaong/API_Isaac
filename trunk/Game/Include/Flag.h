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
	Channel_Wall,
	Channel_Object,
	Channel_PlayerHead,
	Channel_PlayerBody,
	Channel_Monster,
	Channel_PlayerAttack,
	Channel_MonsterAttack,
	Channel_Bomb,
	Channel_BombExplosion,
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
	Effect = -100,
	Monster = -30,
	Player = -20,
	MapObject = -15,
	PlayerBody = -10,
	BackGround = 0
};

enum class ETearType
{
	None,
	Player,
	Monster
};

enum class EObjectType
{
	Object,
	Character,
	Tear,
	Effect,
	Map
};

enum class EDoorDir
{
	Left,
	Top,
	Right,
	Bottom
};

enum EObject
{
	OBJ_NONE,
	OBJ_ROCK,
	OBJ_IRON,
	OBJ_SPIKE,
	OBJ_POOP,
	OBJ_MAX
};

enum class EEditor_State
{
	Idle,
	Saved,
	Loaded
};