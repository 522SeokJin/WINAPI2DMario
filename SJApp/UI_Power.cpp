#include "UI_Power.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"

// Static Var
// Static Func

// member Var

UI_Power::UI_Power()
{

}

UI_Power::~UI_Power()
{

}

// member Func

void UI_Power::Start()
{
	SJWindowResMgr::Inst().FindImage(L"UI_Power.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"UI_Power.bmp")->ImageCut(5, 2);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::UI_OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Power_0", L"UI_Power.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Power_1", L"UI_Power.bmp", 1, 1);
	m_AniRenderer->CreateAnimation(L"Power_2", L"UI_Power.bmp", 2, 2);
	m_AniRenderer->CreateAnimation(L"Power_3", L"UI_Power.bmp", 3, 3);
	m_AniRenderer->CreateAnimation(L"Power_4", L"UI_Power.bmp", 4, 4);
	m_AniRenderer->CreateAnimation(L"Power_5", L"UI_Power.bmp", 5, 5);
	m_AniRenderer->CreateAnimation(L"Power_6", L"UI_Power.bmp", 6, 7, 0.1f);
	m_AniRenderer->ChangeAnimation(L"Power_0");
}

void UI_Power::Update()
{
	int PowerGauge = static_cast<int>(LogicValue::AccelTime);

	if (0 >= PowerGauge)
	{
		m_AniRenderer->ChangeAnimation(L"Power_0");
	}
	else if (1 == PowerGauge)
	{
		m_AniRenderer->ChangeAnimation(L"Power_1");
	}
	else if (2 == PowerGauge)
	{
		m_AniRenderer->ChangeAnimation(L"Power_2");
	}
	else if (3 == PowerGauge)
	{
		m_AniRenderer->ChangeAnimation(L"Power_3");
	}
	else if (4 == PowerGauge)
	{
		m_AniRenderer->ChangeAnimation(L"Power_4");
	}
	else if (5 == PowerGauge)
	{
		m_AniRenderer->ChangeAnimation(L"Power_5");
	}
	else
	{
		m_AniRenderer->ChangeAnimation(L"Power_6");
	}
}

void UI_Power::DebugRender()
{

}