#include "You_Got_A_Card.h"
#include <SJWindowResMgr.h>
#include <SJRendererBasic.h>
#include "LogicValue.h"

// Static Var
// Static Func

// member Var

You_Got_A_Card::You_Got_A_Card()
	: m_Renderer(nullptr)
{

}

You_Got_A_Card::~You_Got_A_Card()
{

}

// member Func

void You_Got_A_Card::Start()
{
	m_Renderer = CreateRenderer<SJRendererBasic>((int)LogicValue::RENDERGROUP::UI);
	SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"Font_You_Got_A_Card.bmp");
	m_Renderer->TransSetting(L"Font_You_Got_A_Card.bmp", Image->GetImageSize());
}

void You_Got_A_Card::Update()
{

}