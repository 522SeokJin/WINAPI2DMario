#include "FadeActor.h"
#include <SJRendererBasic.h>
#include <SJTimer.h>
#include <SJWindowResMgr.h>

// Static Var
// Static Func

// member Var

FadeActor::FadeActor()
	: m_Render(nullptr)
	, m_Alpha(255)

{

}

FadeActor::~FadeActor()
{

}

// member Func

void FadeActor::Start()
{
	{
		m_Render = CreateRenderer<SJRendererBasic>(200);
		m_Render->TransSetting(L"Black.bmp", { 768.0f, 672.0f }, { 768.0f * 0.5f, 672.0f * 0.5f });
	}

	//FadeTimer.CreateTimeEvent(3.0f, this, &FadeActor::FadeInEnd, &FadeActor::FadeInStart, &FadeActor::FadeIn);
	//FadeTimer.CreateTimeEvent(3.0f, this, &FadeActor::FadeOutEnd, &FadeActor::FadeOutStart, &FadeActor::FadeOut);
}

void FadeActor::Update()
{
	FadeTimer.Update();
}

void FadeActor::FadeInStart()
{
	m_Alpha = 0.0f;
}

void FadeActor::FadeIn()
{
	m_Render->SetAlpha(float4::Lerp2DMax(0, 255, 1 - FadeTimer.GetTime() / FadeTimer.GetMaxTime()).ix());
}

void FadeActor::FadeInEnd()
{

}

void FadeActor::FadeOutStart()
{
	m_Alpha = 255.0f;
}

void FadeActor::FadeOut()
{
	m_Render->SetAlpha(float4::Lerp2DMax(0, 255, FadeTimer.GetTime() / FadeTimer.GetMaxTime()).ix());
}

void FadeActor::FadeOutEnd()
{

}
