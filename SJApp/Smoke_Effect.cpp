#include "Smoke_Effect.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>

// Static Var
// Static Func

// member Var

Smoke_Effect::Smoke_Effect()
{

}

Smoke_Effect::~Smoke_Effect()
{

}

// member Func

void Smoke_Effect::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Smoke_Effect.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Smoke_Effect.bmp")->ImageCut(5, 2);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::TOP_OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Smoke_Effect", L"Smoke_Effect.bmp", 0, 6, 0.05f);
	m_AniRenderer->ChangeAnimation(L"Smoke_Effect");
}

void Smoke_Effect::Update()
{
	if (IsOn())
	{
		m_AniRenderer->ChangeAnimation(L"Smoke_Effect");
	}

	if (m_AniRenderer->IsEnd())
	{
		Off();
	}
}

void Smoke_Effect::DebugRender()
{

}