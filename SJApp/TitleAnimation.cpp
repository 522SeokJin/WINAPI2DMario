#include "TitleAnimation.h"
#include <SJWindowResMgr.h>
#include <SJRendererBasic.h>
#include <SJRendererAnimation.h>

// Static Var
// Static Func

// member Var

TitleAnimation::TitleAnimation()
	: AniRenderer(nullptr)
{

}

TitleAnimation::~TitleAnimation()
{

}

// member Func

void TitleAnimation::Start()
{
	SJWindowResMgr::Inst().FindImage(L"TitleAnimation.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"TitleAnimation.bmp")->ImageCut(5, 1);

	AniRenderer = CreateRenderer<SJRendererAnimation>(1);

	AniRenderer->SetRenderScale({ 128, 128 });

	AniRenderer->CreateAnimation(L"TitleAnimation", L"TitleAnimation.bmp", 0, 3, 0.1f);

	AniRenderer->ChangeAnimation(L"TitleAnimation");
}

void TitleAnimation::Update()
{

}