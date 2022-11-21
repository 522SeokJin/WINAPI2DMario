#include "BossStageScene.h"
#include "BossStage_Terrain.h"
#include "LogicValue.h"
#include "FadeActor.h"
#include "BonusCard.h"
#include "UIStage.h"
#include <SJWindowResMgr.h>
#include "Mario.h"
#include "UI_Power.h"
#include "BossBlock.h"
#include "Bowser.h"
#include "BossBlockPaticle.h"
#include "Bowser_Fire.h"
#include "Smoke_Effect.h"
#include "Open_Door.h"
#include "EventCollider.h"

// Static Var
// Static Func

// member Var

BossStageScene::BossStageScene()
	: m_EventCol(nullptr)
{

}

BossStageScene::~BossStageScene()
{

}

// member Func

void BossStageScene::Start()
{
	if (false == LogicValue::BGMPlayer.IsPlaying())
	{
		LogicValue::BGMPlayer.Stop();
	}

	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MARIO, (int)LogicValue::COLLISIONGROUP::MONSTER);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MARIO, (int)LogicValue::COLLISIONGROUP::BLOCK);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MARIO, (int)LogicValue::COLLISIONGROUP::PROJECTILE);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MARIO, (int)LogicValue::COLLISIONGROUP::ITEM);

	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::ITEMBOX, (int)LogicValue::COLLISIONGROUP::MARIO);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::ITEMBOX, (int)LogicValue::COLLISIONGROUP::PROJECTILE);

	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MONSTER, (int)LogicValue::COLLISIONGROUP::PROJECTILE);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MONSTER, (int)LogicValue::COLLISIONGROUP::MONSTER);
	CollisionGroupLink((int)LogicValue::COLLISIONGROUP::MONSTER, (int)LogicValue::COLLISIONGROUP::BLOCK);

	int ImageSize = static_cast<int>(SJWindowResMgr::Inst().FindImage(L"BossStage.bmp")->GetImageSize().y);

	SetCamPos(float4{ 0, ImageSize - 672 - 300 + 108});

	{
		Mario* Object = CreateActor<Mario>();
		Object->SetPos(float4{ 70, 1006 });
		Object->SetSize(float4{ 44, 44 });
		Object->SetPixelPos();
		LogicValue::Mario = Object;
	}

	{
		Bowser_Fire* FireObj1 = CreateActor<Bowser_Fire>();
		FireObj1->SetPos(float4{ 0, 0 });
		FireObj1->Off();
		Bowser_Fire* FireObj2 = CreateActor<Bowser_Fire>();
		FireObj2->SetPos(float4{ 0, 0 });
		FireObj2->Off();

		Bowser* Object = CreateActor<Bowser>();
		Object->SetPos(float4{ 624, 675 });
		Object->SetSize(float4{ 64, 117 });
		Object->SetPixelPos();
		LogicValue::Bowser = Object;
		Object->m_Fire[0] = FireObj1;
		Object->m_Fire[1] = FireObj2;
	}

	GlobalObjSet();
	BlockSet();
}

void BossStageScene::GlobalObjSet()
{
	{
		SJActor* Object = CreateActor<BossStage_Terrain>();
		Object->SetPos(float4::ZERO);
	}

	{
		Smoke_Effect* Object = CreateActor<Smoke_Effect>();
		Object->SetPos(float4{ 720, 1032 });
		Object->Off();

		LogicValue::Smoke[0] = Object;
	}

	{
		Smoke_Effect* Object = CreateActor<Smoke_Effect>();
		Object->SetPos(float4{ 720, 1032 + 48 });
		Object->Off();

		LogicValue::Smoke[1] = Object;
	}

	{
		Open_Door* Object = CreateActor<Open_Door>();
		Object->SetPos(float4{ 720, 1056 });
		Object->Off();

		LogicValue::OpenDoor = Object;
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
		BonusCard* Object = CreateActor<BonusCard>();
		Object->SetPos(float4{ 542, 614 });
		Object->SetCamAffect(false);
	}

	m_EventCol = CreateActor<EventCollider>();
	m_EventCol->SetPos(float4{ 192, 798 });
	m_EventCol->SetType(EVENTTYPE::BOWSERAPPEAR);
}
void BossStageScene::BlockSet()
{
	{
		for (size_t i = 0; i < 4; i++)
		{
			BossBlockPaticle* Object = CreateActor<BossBlockPaticle>();
			Object->SetPos(float4{ 0, 0 });
			Object->Off();
			LogicValue::BossBlockPaticle[i] = Object;
			LogicValue::BossBlockPaticle[i]->SetPaticleDir((PATICLEDIR)i);

		}
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 120, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 168, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 216, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 264, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 312, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 360, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 408, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 456, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 504, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 552, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 600, 1176 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 552, 1224 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 504, 1224 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 456, 1224 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 408, 1224 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 360, 1224 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 312, 1224 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 264, 1224 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 216, 1224 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 312, 1272 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 360, 1272 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 408, 1272 });
	}

	{
		SJActor* Object = CreateActor<BossBlock>();
		Object->SetPos(float4{ 456, 1272 });
	}
}

void BossStageScene::SceneUpdate()
{
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
			LogicValue::BGMPlayer = SJSound::Play(L"Bowser_Battle.mp3", -1);
		}
		else
		{
			LogicValue::BGMPlayer.Stop();
		}
	}
}

void BossStageScene::SceneDebugRender()
{
	{
		SJString PrintText = SJString::ToString(1.0f / SJTimer::MainTimer.GetFDeltaTime());
		TextOut(SJWindow::GetBackBufferDC(), 672, 0, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}
}