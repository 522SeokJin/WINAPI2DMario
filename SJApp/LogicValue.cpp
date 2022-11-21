#include "LogicValue.h"

// Static Var
SoundPlayer				LogicValue::BGMPlayer;
SJRendererBasic*		LogicValue::TitleCursorRenderer;
LogicValue::BONUSTYPE	LogicValue::Bonus;
bool					LogicValue::bCleared;
float					LogicValue::AccelTime;
FadeActor*				LogicValue::FadeEffect;
Mario*					LogicValue::Mario;
Bowser*					LogicValue::Bowser;
MARIOTYPE				LogicValue::PrevMarioType;

BlockPaticle*			LogicValue::BlockPaticle[];
BossBlockPaticle*		LogicValue::BossBlockPaticle[];
Smoke_Effect*			LogicValue::Smoke[];
Open_Door*				LogicValue::OpenDoor;


// Static Func

// member Var

LogicValue::LogicValue()
{
	bCleared = false;
	PrevMarioType = MARIOTYPE::SMALL;
}

LogicValue::~LogicValue()
{

}

// member Func