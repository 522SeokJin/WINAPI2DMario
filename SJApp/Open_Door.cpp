#include "Open_Door.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "SJCore.h"

// Static Var
// Static Func

// member Var

Open_Door::Open_Door()
	: m_Col(nullptr)
{

}

Open_Door::~Open_Door()
{

}



// member Func

void Open_Door::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	
}

void Open_Door::StayCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if (SJInput::IsDown(L"UP"))
		{
			SJCore::SceneManager.ChangeScene(L"Ending");
		}
	}
}

void Open_Door::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Open_Door::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Open_Door.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Open_Door.bmp")->ImageCut(5, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Open_Door", L"Open_Door.bmp", 0, 3, 0.1f);
	m_AniRenderer->ChangeAnimation(L"Open_Door");

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::ITEM);
	m_Col->SetScale({ 48, 96 });
	m_Col->AddStartEvent(this, &Open_Door::StartCollision);
	m_Col->AddStayEvent(this, &Open_Door::StayCollision);
	m_Col->AddEndEvent(this, &Open_Door::EndCollision);
}

void Open_Door::Update()
{

}

void Open_Door::DebugRender()
{

}