#include "Course_Clear.h"
#include <SJWindowResMgr.h>
#include <SJRendererBasic.h>
#include "LogicValue.h"

// Static Var
// Static Func

// member Var

Course_Clear::Course_Clear()
	: m_Renderer(nullptr)
{

}

Course_Clear::~Course_Clear()
{

}

// member Func

void Course_Clear::Start()
{
	m_Renderer = CreateRenderer<SJRendererBasic>((int)LogicValue::RENDERGROUP::UI);
	SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"Font_Course_Clear.bmp");
	m_Renderer->TransSetting(L"Font_Course_Clear.bmp", Image->GetImageSize());
}

void Course_Clear::Update()
{
	
}