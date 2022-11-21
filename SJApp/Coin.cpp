#include "Coin.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>

// Static Var
// Static Func

// member Var

Coin::Coin()
	: m_Col(nullptr)
{

}

Coin::~Coin()
{

}

// member Func

void Coin::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		SJSound::Play(L"Coin.wav");
		Death();
	}
}

void Coin::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Coin::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Coin::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Coin.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Coin.bmp")->ImageCut(5, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Coin", L"Coin.bmp", 0, 4, 0.15f);
	m_AniRenderer->ChangeAnimation(L"Coin");

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::ITEM);
	m_Col->SetScale({ 48, 48 });
	m_Col->AddStartEvent(this, &Coin::StartCollision);
	m_Col->AddStayEvent(this, &Coin::StayCollision);
	m_Col->AddEndEvent(this, &Coin::EndCollision);
}

void Coin::Update()
{

}

void Coin::DebugRender()
{
	CollisionView(m_Col);
}