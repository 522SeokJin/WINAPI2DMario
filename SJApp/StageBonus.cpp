#include "StageBonus.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Mario.h"
#include "BonusEffect.h"

// Static Var
// Static Func

// member Var

StageBonus::StageBonus()
	: m_Col(nullptr)
	, m_Effect(nullptr)
{

}

StageBonus::~StageBonus()
{

}

// member Func

void StageBonus::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		LogicValue::BGMPlayer.Stop();
		LogicValue::BGMPlayer = SJSound::Play(L"Level_Clear.mp3");

		LogicValue::Mario->m_FSM.ChangeState(L"CLEARFALL");

		m_Effect->On();
		m_Effect->SetMoveOn();

		LogicValue::bCleared = true;

		Death();
	}
}

void StageBonus::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void StageBonus::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void StageBonus::Start()
{
	SJWindowResMgr::Inst().FindImage(L"StageBonus.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"StageBonus.bmp")->ImageCut(5, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"StageBonus", L"StageBonus.bmp", 0, 2, 0.15f);
	m_AniRenderer->ChangeAnimation(L"StageBonus");

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::ITEM);
	m_Col->SetScale({ 48, 48 });
	m_Col->AddStartEvent(this, &StageBonus::StartCollision);
	m_Col->AddStayEvent(this, &StageBonus::StayCollision);
	m_Col->AddEndEvent(this, &StageBonus::EndCollision);
}

void StageBonus::Update()
{
	LogicValue::Bonus = (LogicValue::BONUSTYPE)m_AniRenderer->GetCurAnimation()->GetCurFrame();
}

void StageBonus::DebugRender()
{
	CollisionView(m_Col);
}