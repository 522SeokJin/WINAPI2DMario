#include "BossStage_Terrain.h"
#include <SJWindow.h>
#include <SJWindowResMgr.h>
#include <SJTimer.h>
#include <SJRendererBasic.h>
#include "LogicValue.h"

// Static Var
// Static Func

// member Var

BossStage_Terrain::BossStage_Terrain()
	: ColliderRenderer(nullptr)
{

}

BossStage_Terrain::~BossStage_Terrain()
{

}

// member Func

void BossStage_Terrain::Start()
{
	{
		SJRendererBasic* NewRenderer = CreateRenderer<SJRendererBasic>((int)LogicValue::RENDERGROUP::BACKGROUND);
		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"BossStage.bmp");
		NewRenderer->TransSetting(L"BossStage.bmp", Image->GetImageSize(), Image->GetImageSize().hfloat4());
	}

	{
		SJRendererBasic* NewRenderer = CreateRenderer<SJRendererBasic>((int)LogicValue::RENDERGROUP::TERRAIN_COLLIDER);
		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"BossStage_Collider.bmp");
		NewRenderer->TransSetting(L"BossStage_Collider.bmp", Image->GetImageSize(), Image->GetImageSize().hfloat4());
	}

	{
		ColliderRenderer = CreateRenderer<SJRendererBasic>((int)LogicValue::RENDERGROUP::TERRAIN_COLLIDER_VIEW);
		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"BossStage_Collider.bmp");
		ColliderRenderer->TransSetting(L"BossStage_Collider.bmp", Image->GetImageSize(), Image->GetImageSize().hfloat4());
		ColliderRenderer->SetAlpha(254);
		ColliderRenderer->Off();
	}
}

void BossStage_Terrain::Update()
{
	if (true == SJInput::IsDown(L"DebugMode"))
	{
		if (true == ColliderRenderer->IsOn())
		{
			ColliderRenderer->Off();
			GetScene()->m_DebugModeOff();
		}
		else
		{
			ColliderRenderer->On();
			GetScene()->m_DebugModeOn();
		}
	}
}

void BossStage_Terrain::OffTask()
{
	int a = 0;
}