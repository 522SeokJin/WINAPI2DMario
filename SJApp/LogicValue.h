#pragma once
#include "SJRendererBasic.h"
#include <SJSound.h>

// 분류 :
// 용도 : 
// 설명 : 

enum class MARIOTYPE
{
	SMALL,
	SUPER,
	RACOON,
};

class Mario;
class Bowser;
class BlockPaticle;
class BossBlockPaticle;
class Smoke_Effect;
class Open_Door;
class FadeActor;

class LogicValue
{
public:
	enum class RENDERGROUP
	{
		TERRAIN_COLLIDER = 0,
		BACKGROUND,
		OBJECT,
		TERRAIN_OBJECT,
		LEAF,
		TERRAIN_COLLIDER_VIEW,
		MONSTER,
		PLAYER,
		TOP_OBJECT,
		UI,
		UI_OBJECT,
	};

	enum class COLLISIONGROUP
	{
		MARIO,
		MARIO_PROJECTILE,
		ITEM,
		BLOCK,
		ITEMBOX,
		MONSTER,
		MONSTER_PROJECTILE,
		PROJECTILE,
		UI,
	};

	enum class BONUSTYPE
	{
		MUSHROOM,
		FLOWER,
		STAR,
	};

public: // Static Var
	static SoundPlayer			BGMPlayer;
    static SJRendererBasic*		TitleCursorRenderer;
	static BONUSTYPE			Bonus;
	static bool					bCleared;

	static FadeActor*			FadeEffect;
	static Mario*				Mario;
	static Bowser*				Bowser;
	static float				AccelTime;
	static MARIOTYPE			PrevMarioType;

	static BlockPaticle*		BlockPaticle[4];
	static BossBlockPaticle*	BossBlockPaticle[4];
	static Smoke_Effect*		Smoke[2];
	static Open_Door*			OpenDoor;

public: // Static Func

private: // member Var

public: // constructer destructer
	LogicValue();
	~LogicValue();

public: // delete constructer 
    LogicValue(const LogicValue& _Other) = delete;
    LogicValue(const LogicValue&& _Other) = delete;

public: // delete operator
    LogicValue& operator=(const LogicValue& _Other) = delete;
    LogicValue& operator=(const LogicValue&& _Other) = delete;

public: // member Func
};

