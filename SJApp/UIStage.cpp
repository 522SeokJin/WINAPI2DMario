#include "UIStage.h"
#include <SJWindow.h>
#include <SJWindowResMgr.h>
#include <SJTimer.h>
#include <SJRendererBasic.h>

#include "LogicValue.h"
// Static Var
// Static Func

// member Var

UIStage::UIStage()
{

}

UIStage::~UIStage()
{

}

// member Func

void UIStage::Start()
{
	{
		SJRendererBasic* NewRenderer = CreateRenderer<SJRendererBasic>((int)LogicValue::RENDERGROUP::UI);
		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"UIStage.bmp");
		NewRenderer->TransSetting(L"UIStage.bmp", Image->GetImageSize(), Image->GetImageSize().hfloat4());
	}
}

void UIStage::Update()
{

}