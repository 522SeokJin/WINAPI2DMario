#include "TitleScene.h"
#include "TitleBackGround.h"
#include <SJWindow.h>
#include <SJWindowResMgr.h>
#include "SJCore.h"
#include "TitleCursor.h"
#include "TitleAnimation.h"
#include <SJTimeEventer.h>
#include "LogicValue.h"

// Static Var
// Static Func

// member Var

TitleScene::TitleScene()
	: m_TitleEvent()
{

}

TitleScene::~TitleScene()
{

}

// member Func

void TitleScene::Start()
{
	{
		SJActor* Object = CreateActor<TitleBackGround>();

		SJWinImage* Image = SJWindowResMgr::Inst().FindImage(L"Title.bmp");

		SJWindow::SetSize(Image->GetImageSize());

		Object->SetPos(SJWindow::GetSize().hfloat4());
	}

	{
		TitleCursor* Object = CreateActor<TitleCursor>();
		Object->SetPos(float4{ 226, 445 });
		Object->SetCamAffect(false);

		m_Cursor = Object;
	}

	{
		SJActor* Object = CreateActor<TitleAnimation>();
		Object->SetPos(float4{ 399, 350 });
		Object->SetCamAffect(false);
	}
}

void TitleScene::SceneUpdate()
{
	m_TitleEvent.Update();

	if (true == SJInput::IsDown(L"Start"))
	{
		if (m_Cursor->m_Start)
		{
			LogicValue::BGMPlayer = SJSound::Play(L"Coin.wav");

			m_TitleEvent.CreateTimeEvent(0.5f, this, &TitleScene::CursorOff);
			m_TitleEvent.CreateTimeEvent(0.1f, this, &TitleScene::CursorOn);
			m_TitleEvent.CreateTimeEvent(0.5f, this, &TitleScene::CursorOff);
			m_TitleEvent.CreateTimeEvent(0.1f, this, &TitleScene::CursorOn);

			m_TitleEvent.CreateTimeEvent(0.5f, this, &TitleScene::Change1Stage);
		}
		else
		{
			SJWindow::WindowEnd();
		}
	}
}
