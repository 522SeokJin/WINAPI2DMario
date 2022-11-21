#include "Stage1Scene.h"
#include <SJActor.h>
#include <SJWindow.h>
#include <SJInput.h>

#include "SJCore.h"
#include "Stage1_Terrain.h"
#include "Pipe.h"
#include "FadeActor.h"
#include "UIStage.h"
#include "ItemBox.h"
#include "Mario.h"
#include "Goomba.h"
#include "Red_Goomba.h"
#include "Koopa_Troopa.h"
#include "Block.h"
#include "Coin.h"
#include "Mushroom.h"
#include "RacoonLeaf.h"
#include "StageBonus.h"
#include "BonusEffect.h"
#include "UI_Power.h"
#include "BlockPaticle.h"
#include "Piranha_Plant.h"
#include "Plant_Fire.h"

#include "Course_Clear.h"
#include "You_Got_A_Card.h"
#include "BonusCard.h"
#include "EventCollider.h"

#include "LogicValue.h"

// Static Var
// Static Func

// member Var

Stage1Scene::Stage1Scene()
	: m_CardObject(nullptr)
	, m_UICardObject(nullptr)
	, m_FontObject1(nullptr)
	, m_FontObject2(nullptr)
	, m_EventCol()
{

}

Stage1Scene::~Stage1Scene()
{

}

// member Func

void Stage1Scene::ClearFontOn1()
{
	m_FontObject1->On();
}

void Stage1Scene::ClearFontOn2()
{
	m_FontObject2->On();

	m_CardObject->On();
}

void Stage1Scene::GoToBossStage()
{
	SJCore::SceneManager.ChangeScene(L"BossStage");
}

void Stage1Scene::Start()
{
	if (true == LogicValue::BGMPlayer.IsPlaying())
	{
		LogicValue::BGMPlayer.Stop();
	}

	LogicValue::BGMPlayer = SJSound::Play(L"Stage1_Theme.mp3", -1);

	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MARIO, (int)LogicValue::COLLISIONGROUP::MONSTER);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MARIO, (int)LogicValue::COLLISIONGROUP::BLOCK);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MARIO, (int)LogicValue::COLLISIONGROUP::PROJECTILE);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MARIO, (int)LogicValue::COLLISIONGROUP::MONSTER_PROJECTILE);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MARIO, (int)LogicValue::COLLISIONGROUP::ITEM);

	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::ITEMBOX, (int)LogicValue::COLLISIONGROUP::MARIO);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::ITEMBOX, (int)LogicValue::COLLISIONGROUP::PROJECTILE);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::ITEMBOX, (int)LogicValue::COLLISIONGROUP::MARIO_PROJECTILE);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::BLOCK, (int)LogicValue::COLLISIONGROUP::MARIO_PROJECTILE);

	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MONSTER, (int)LogicValue::COLLISIONGROUP::PROJECTILE);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MONSTER, (int)LogicValue::COLLISIONGROUP::MONSTER);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MONSTER, (int)LogicValue::COLLISIONGROUP::MARIO_PROJECTILE);

	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::PROJECTILE, (int)LogicValue::COLLISIONGROUP::BLOCK);

	SetCamPos(float4{0, 672 + 108 - 47});

	{
		Mario* Object = CreateActor<Mario>();
		Object->SetPos(float4{ 92, 1252 });
		//Object->SetPos(float4{ 5758, 1252 });
		//Object->SetPos(float4{ 7654, 1252 });
		Object->SetSize(float4{ 44, 44 });
		Object->SetPixelPos();

		LogicValue::Mario = Object;
		//SetCamPos(float4{ LogicValue::Mario->GetPos().x - SJWindow::GetSize().hx(), float(672 + 108 - 47) });
	}

	GlobalObjSet();
	ItemBoxSet();
	CoinSet();
	BlockSet();
	MonsterSet();
}

void Stage1Scene::SceneUpdate()
{
	if (true == LogicValue::bCleared)
	{
		if (0 == m_ClearEventer.IsEventSize())
		{
			m_ClearEventer.CreateTimeEvent(1.5f, this, &Stage1Scene::ClearFontOn1);
			m_ClearEventer.CreateTimeEvent(1.0f, this, &Stage1Scene::ClearFontOn2);
			m_ClearEventer.CreateTimeEvent(2.0f, this, &Stage1Scene::GoToBossStage);
		}

		m_ClearEventer.Update();
	}

	if (true == SJInput::IsDown(L"SmallMario"))
	{
		LogicValue::Mario->GetType() = MARIOTYPE::SUPER;
		LogicValue::Mario->m_FSM.ChangeState(L"POWERDOWN");
	}
	if (true == SJInput::IsDown(L"SuperMario"))
	{
		LogicValue::Mario->GetType() = MARIOTYPE::SMALL;
		LogicValue::Mario->m_FSM.ChangeState(L"POWERUP");
	}
	if (true == SJInput::IsDown(L"RacoonMario"))
	{
		LogicValue::Mario->GetType() = MARIOTYPE::SUPER;
		LogicValue::Mario->m_FSM.ChangeState(L"POWERUP");
	}

	if (SJInput::IsDown(L"R"))
	{
		if (LogicValue::Mario->m_bNoDamage)
		{
			LogicValue::Mario->m_bNoDamage = false;
		}
		else
		{
			LogicValue::Mario->m_bNoDamage = true;
		}
	}

	if (true == SJInput::IsDown(L"M"))
	{
		if (true == LogicValue::BGMPlayer.IsPlaying())
		{
			LogicValue::BGMPlayer = SJSound::Play(L"Stage1_Theme.mp3", -1);
		}
		else
		{
			LogicValue::BGMPlayer.Stop();
		}
	}
}

void Stage1Scene::MonsterSet()
{
	{
		Goomba* Object = CreateActor<Goomba>();
		Object->SetDir(eDIR::LEFT);
		Object->SetPos(float4{ 672, 1252 });
		Object->SetSize(float4{ 48, 48 });
		Object->SetPixelPos();
	}

	{
		Koopa_Troopa* Object = CreateActor<Koopa_Troopa>();
		Object->SetDir(eDIR::LEFT);
		Object->SetPos(float4{ 1746, 1098 });
		Object->SetSize(float4{ 48, 48 });
		Object->SetPixelPos();
		Object->SetType(TROOPATYPE::NORMAL);
	}

	// EventCol 0
	{
		{
			Goomba* Object = CreateActor<Goomba>();
			Object->SetDir(eDIR::LEFT);
			Object->SetPos(float4{ 2800, 1200 });
			Object->SetSize(float4{ 48, 48 });
			Object->SetPixelPos();
			Object->Off();
			m_EventCol[0]->SetCreateEvent(Object);
		}

		{
			Goomba* Object = CreateActor<Goomba>();
			Object->SetDir(eDIR::LEFT);
			Object->SetPos(float4{ 3000, 1200 });
			Object->SetSize(float4{ 48, 48 });
			Object->SetPixelPos();
			Object->Off();
			m_EventCol[0]->SetCreateEvent(Object);
		}

		{
			Red_Goomba* Object = CreateActor<Red_Goomba>();
			Object->SetDir(eDIR::LEFT);
			Object->SetPos(float4{ 3300, 1200 });
			Object->SetSize(float4{ 48, 48 });
			Object->SetPixelPos();
			Object->SetType(GOOMBATYPE::WING);
			Object->Off();
			m_EventCol[0]->SetCreateEvent(Object);
		}
	}

	// EventCol 1
	{
		{
			Koopa_Troopa* Object = CreateActor<Koopa_Troopa>();
			Object->SetPos(float4{ 4035, 843 });
			Object->SetSize(float4{ 48, 48 });
			Object->SetPixelPos();
			Object->SetType(TROOPATYPE::WING);
			Object->Off();
			m_EventCol[1]->SetCreateEvent(Object);
		}

		{
			Koopa_Troopa* Object = CreateActor<Koopa_Troopa>();
			Object->SetPos(float4{ 4163, 882 });
			Object->SetSize(float4{ 48, 48 });
			Object->SetPixelPos();
			Object->SetType(TROOPATYPE::WING);
			Object->Off();
			m_EventCol[1]->SetCreateEvent(Object);
		}

		{
			Koopa_Troopa* Object = CreateActor<Koopa_Troopa>();
			Object->SetPos(float4{ 4293, 921 });
			Object->SetSize(float4{ 48, 48 });
			Object->SetPixelPos();
			Object->SetType(TROOPATYPE::WING);
			Object->Off();
			m_EventCol[1]->SetCreateEvent(Object);
		}

		{
			Koopa_Troopa* Object = CreateActor<Koopa_Troopa>();
			Object->SetPos(float4{ 4465, 1209 });
			Object->SetSize(float4{ 48, 48 });
			Object->SetPixelPos();
			Object->SetType(TROOPATYPE::NORMAL);
			Object->Off();
			m_EventCol[1]->SetCreateEvent(Object);
		}

		{
			Goomba* Object = CreateActor<Goomba>();
			Object->SetPos(float4{ 4366, 1224 + 24 });
			Object->SetSize(float4{ 48, 48 });
			Object->SetPixelPos();
			Object->Off();
			m_EventCol[1]->SetCreateEvent(Object);
		}
	}

	{
		Koopa_Troopa* Object = CreateActor<Koopa_Troopa>();
		Object->SetPos(float4{ 6510, 1008 });
		Object->SetSize(float4{ 48, 48 });
		Object->SetPixelPos();
		Object->SetType(TROOPATYPE::NORMAL);
	}

	{
		Plant_Fire* FireObj = CreateActor<Plant_Fire>();
		FireObj->SetPos(float4{ 0, 0 });
		FireObj->Off();

		Piranha_Plant* Object = CreateActor<Piranha_Plant>();
		Object->SetPos(float4{ 1104, 1152 + 20 });
		Object->SetSize(float4{ 48, 96 });
		Object->SetPixelPos();
		Object->SetColor(PLANTCOLOR::RED);
		Object->SetType(PLANTTYPE::FIRE);
		Object->SetFireObj(FireObj);
	}

	{
		Plant_Fire* FireObj = CreateActor<Plant_Fire>();
		FireObj->SetPos(float4{ 0, 0 });
		FireObj->Off();

		Piranha_Plant* Object = CreateActor<Piranha_Plant>();
		Object->SetPos(float4{ 5424, 1200 + 20 });
		Object->SetSize(float4{ 48, 96 });
		Object->SetPixelPos();
		Object->SetColor(PLANTCOLOR::GREEN);
		Object->SetType(PLANTTYPE::NORMAL);
		Object->SetFireObj(FireObj);
	}

	{
		Plant_Fire* FireObj = CreateActor<Plant_Fire>();
		FireObj->SetPos(float4{ 0, 0 });
		FireObj->Off();

		Piranha_Plant* Object = CreateActor<Piranha_Plant>();
		Object->SetPos(float4{ 5616, 1152 + 20 });
		Object->SetSize(float4{ 48, 96 });
		Object->SetPixelPos();
		Object->SetColor(PLANTCOLOR::GREEN);
		Object->SetType(PLANTTYPE::FIRE);
		Object->SetFireObj(FireObj);
	}
}

void Stage1Scene::GlobalObjSet()
{
	{
		SJActor* Object = CreateActor<Stage1_Terrain>();
		Object->SetPos(float4::ZERO);
	}

	{
		Pipe* Object = CreateActor<Pipe>();
		Object->SetPos(float4{ 1104, 1176 });
		Object->SetType(PIPETYPE::LONG);
	}

	{
		Pipe* Object = CreateActor<Pipe>();
		Object->SetPos(float4{ 5424, 1224 });
		Object->SetType(PIPETYPE::SHORT);
	}

	{
		Pipe* Object = CreateActor<Pipe>();
		Object->SetPos(float4{ 5616, 1176 });
		Object->SetType(PIPETYPE::LONG);
	}

	{
		SJActor* Object = CreateActor<UIStage>();
		Object->SetPos(float4{ 0, 564 });
		Object->SetCamAffect(false);
	}

	{
		UI_Power* Object = CreateActor<UI_Power>();
		Object->SetPos(float4{ 274, 603 });
		Object->SetCamAffect(false);
	}

	{
		FadeActor* Object = CreateActor<FadeActor>();
		Object->SetPos(float4::ZERO);
		Object->SetCamAffect(false);

		Object->FadeTimer.CreateTimeEvent(2.0f, Object, &FadeActor::FadeOutEnd, &FadeActor::FadeOutStart, &FadeActor::FadeOut);

		LogicValue::FadeEffect = Object;
	}

	{
		StageBonus* Object = CreateActor<StageBonus>();
		Object->SetPos(float4{ 8088, 1032 });
		Object->SetSize(float4{ 48, 48 });

		BonusEffect* EffectObject = CreateActor<BonusEffect>();
		EffectObject->SetPos(float4{ 8088, 1032 });
		EffectObject->Off();

		Object->SetEffect(EffectObject);
	}

	m_CardObject = CreateActor<BonusCard>();
	m_CardObject->SetPos(float4{ 8255, 909 });
	m_CardObject->Off();

	m_FontObject1 = CreateActor<Course_Clear>();
	m_FontObject1->SetPos(float4{ 8063, 828 });
	m_FontObject1->Off();

	m_FontObject2 = CreateActor<You_Got_A_Card>();
	m_FontObject2->SetPos(float4{ 8017, 900 });
	m_FontObject2->Off();

	m_UICardObject = CreateActor<BonusCard>();
	m_UICardObject->SetPos(float4{ 542, 614 });
	m_UICardObject->SetCamAffect(false);

	m_EventCol[0] = CreateActor<EventCollider>();
	m_EventCol[0]->SetPos(float4{ 2313, 939 });

	m_EventCol[1] = CreateActor<EventCollider>();
	m_EventCol[1]->SetPos(float4{ 3660, 939 });
}

void Stage1Scene::ItemBoxSet()
{
	{
		ItemBox* Object = CreateActor<ItemBox>();

		Coin* CoinObject = CreateActor<Coin>();
		CoinObject->SetPos(float4{ 552, 1080 });
		CoinObject->SetSize(float4{ 48, 48 });
		CoinObject->CollisionOff();
		Object->SetItem(CoinObject);

		Object->SetPos(float4{ 552, 1080 });

	}

	{
		ItemBox* Object = CreateActor<ItemBox>();
		Coin* CoinObject = CreateActor<Coin>();
		CoinObject->SetPos(float4{ 600, 1080 });
		CoinObject->SetSize(float4{ 48, 48 });
		CoinObject->CollisionOff();
		Object->SetItem(CoinObject);

		Object->SetPos(float4{ 600, 1080 });
	}

	{
		ItemBox* Object = CreateActor<ItemBox>();
		Coin* CoinObject = CreateActor<Coin>();
		CoinObject->SetPos(float4{ 696, 936 });
		CoinObject->SetSize(float4{ 48, 48 });
		CoinObject->CollisionOff();
		Object->SetItem(CoinObject);

		Object->SetPos(float4{ 696, 936 });
	}

	{
		Mushroom* MushroomObj = CreateActor<Mushroom>();
		MushroomObj->SetSize(float4{ 48, 48 });
		MushroomObj->SetPos(float4{ 744, 936 });
		MushroomObj->Off();

		ItemBox* Object = CreateActor<ItemBox>();
		Object->SetItem(MushroomObj);
		Object->SetPos(float4{ 744, 936 });
		Object->SetItemType(ITEMTYPE::MUSHROOM);
	}

	{
		ItemBox* Object = CreateActor<ItemBox>();
		Coin* CoinObject = CreateActor<Coin>();
		CoinObject->SetPos(float4{ 1272, 984 });
		CoinObject->SetSize(float4{ 48, 48 });
		CoinObject->CollisionOff();
		Object->SetItem(CoinObject);

		Object->SetPos(float4{ 1272, 984 });
	}

	{
		ItemBox* Object = CreateActor<ItemBox>();
		RacoonLeaf* RacoonLeafObj = CreateActor<RacoonLeaf>();
		RacoonLeafObj->SetSize(float4{ 48, 42 });
		RacoonLeafObj->SetPos(float4{ 1992, 1176 });
		RacoonLeafObj->Off();
		Object->SetItem(RacoonLeafObj);
		Object->SetItemType(ITEMTYPE::RACOONMARIO);
		
		Object->SetPos(float4{ 1992, 1176 });
	}

	{
		ItemBox* Object = CreateActor<ItemBox>();
		Coin* CoinObject = CreateActor<Coin>();
		CoinObject->SetPos(float4{ 2136, 1080 });
		CoinObject->SetSize(float4{ 48, 48 });
		CoinObject->CollisionOff();
		Object->SetItem(CoinObject);

		Object->SetPos(float4{ 2136, 1080 });
	}

	{
		ItemBox* Object = CreateActor<ItemBox>();
		RacoonLeaf* RacoonLeafObj = CreateActor<RacoonLeaf>();
		RacoonLeafObj->SetSize(float4{ 48, 42 });
		RacoonLeafObj->SetPos(float4{ 4440, 1128 });
		RacoonLeafObj->Off();
		Object->SetItem(RacoonLeafObj);
		Object->SetItemType(ITEMTYPE::RACOONMARIO);

		Object->SetPos(float4{ 4440, 1128 });
	}

	{
		ItemBox* Object = CreateActor<ItemBox>();
		Coin* CoinObject = CreateActor<Coin>();
		CoinObject->SetPos(float4{ 4344, 408 });
		CoinObject->SetSize(float4{ 48, 48 });
		CoinObject->CollisionOff();
		Object->SetItem(CoinObject);

		Object->SetPos(float4{ 4344, 408 });
	}
}

void Stage1Scene::CoinSet()
{
	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 3240, 984 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 3336, 888 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 3432, 792 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 3528, 696 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 3624, 600 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4008, 264 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4056, 264 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4104, 264 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4440, 360 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4488, 360 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4632, 408 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4680, 408 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4728, 408 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4776, 408 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4872, 360 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4920, 360 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 4968, 360 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 5016, 360 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 5112, 456 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 5208, 360 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 5304, 408 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 5448, 312 });
		Object->SetSize(float4{ 48, 48 });
	}

	{
		Coin* Object = CreateActor<Coin>();
		Object->SetPos(float4{ 5544, 408 });
		Object->SetSize(float4{ 48, 48 });
	}
}

void Stage1Scene::BlockSet()
{
	{
		for (size_t i = 0; i < 4; i++)
		{
			BlockPaticle* Object = CreateActor<BlockPaticle>();
			Object->SetPos(float4{ 0, 0 });
			Object->SetPaticleDir((PATICLEDIR)i);
			Object->Off();
			LogicValue::BlockPaticle[i] = Object;
		}
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 5976, 1128 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6024, 1128 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6072, 1128 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6120, 1128 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6120, 1176 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6072, 1176 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6024, 1176 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 5976, 1176 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 5928, 1176 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 5928, 1224 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 5880, 1224 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 5976, 1224 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6024, 1224 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6072, 1224 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6120, 1224 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6168, 1224 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6312, 1176 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6312, 1224 });
	}

	{
		SJActor* Object = CreateActor<Block>();
		Object->SetPos(float4{ 6360, 1224 });
	}
}

void Stage1Scene::SceneDebugRender()
{
	{
		SJString PrintText = SJString::ToString(1.0f / SJTimer::MainTimer.GetFDeltaTime());
		TextOut(SJWindow::GetBackBufferDC(), 672, 0, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}
}