#include "TitleBackGround.h"
#include <SJWindowResMgr.h>
#include <SJRendererBasic.h>
#include <SJRendererAnimation.h>

// Static Var
// Static Func

// member Var

TitleBackGround::TitleBackGround()
{

}

TitleBackGround::~TitleBackGround()
{

}

// member Func

void TitleBackGround::Start()
{
	{
		SJRendererBasic* NewRenderer = CreateRenderer<SJRendererBasic>(0);
		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"Title.bmp");
		NewRenderer->TransSetting(L"Title.bmp", Image->GetImageSize());
	}
}

void TitleBackGround::Update()
{

}
