#include "Stage1_Terrain.h"
#include <SJWindow.h>
#include <SJWindowResMgr.h>
#include <SJTimer.h>
#include <SJRendererBasic.h>
#include "LogicValue.h"


// Static Var
// Static Func

// member Var

Stage1_Terrain::Stage1_Terrain()
	: ColliderRenderer(nullptr)
{

}

Stage1_Terrain::~Stage1_Terrain()
{

}


// member Func

void Stage1_Terrain::Start()
{
	{
		SJRendererBasic* NewRenderer = CreateRenderer<SJRendererBasic>((int)LogicValue::RENDERGROUP::BACKGROUND);
		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"Stage1.bmp");
		NewRenderer->TransSetting(L"Stage1.bmp", Image->GetImageSize(), Image->GetImageSize().hfloat4());
	}

	{
		SJRendererBasic* NewRenderer = CreateRenderer<SJRendererBasic>((int)LogicValue::RENDERGROUP::TERRAIN_COLLIDER);
		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"Stage1_Collider.bmp");
		NewRenderer->TransSetting(L"Stage1_Collider.bmp", Image->GetImageSize(), Image->GetImageSize().hfloat4());
	}

	{
		ColliderRenderer = CreateRenderer<SJRendererBasic>((int)LogicValue::RENDERGROUP::TERRAIN_COLLIDER_VIEW);
		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"Stage1_Collider.bmp");
		ColliderRenderer->TransSetting(L"Stage1_Collider.bmp", Image->GetImageSize(), Image->GetImageSize().hfloat4());
		ColliderRenderer->SetAlpha(254);
		ColliderRenderer->Off();
	}
}

void Stage1_Terrain::Update()
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

void Stage1_Terrain::OffTask()
{
	int a = 0;
}