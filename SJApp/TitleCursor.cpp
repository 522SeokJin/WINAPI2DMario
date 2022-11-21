#include "TitleCursor.h"
#include <SJWindowResMgr.h>
#include <SJRendererBasic.h>
#include <SJInput.h>
#include "LogicValue.h"

// Static Var
// Static Func

// member Var

TitleCursor::TitleCursor()
	: m_Lock(false)
	, m_Start(true)
{

}

TitleCursor::~TitleCursor()
{

}

// member Func

void TitleCursor::Start()
{

	LogicValue::TitleCursorRenderer = CreateRenderer<SJRendererBasic>(1);
	SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"TitleCursor.bmp");
	LogicValue::TitleCursorRenderer->TransSetting(L"TitleCursor.bmp", Image->GetImageSize());
}

void TitleCursor::Update()
{
	// 226, 445
	// 226, 493

	if (false == m_Lock)
	{
		if (true == SJInput::IsPress(L"UP"))
		{
			SetPos(float4{ 226, 445 });
			m_Start = true;
		}
		if (true == SJInput::IsPress(L"DOWN"))
		{
			SetPos(float4{ 226, 493 });
			m_Start = false;
		}
	}

	if (true == SJInput::IsDown(L"Start"))
	{
		m_Lock = true;
	}
}