#include "Ending.h"
#include <SJWindowResMgr.h>
#include <SJRendererBasic.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"

// Static Var
// Static Func

// member Var

Ending::Ending()
{

}

Ending::~Ending()
{

}

// member Func

void Ending::Start()
{
	{
		SJRendererBasic* NewRenderer = CreateRenderer<SJRendererBasic>((int)LogicValue::RENDERGROUP::BACKGROUND);
		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"Ending.bmp");
		NewRenderer->TransSetting(L"Ending.bmp", Image->GetImageSize());
	}
}

void Ending::Update()
{

}