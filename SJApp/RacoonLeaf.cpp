#include "RacoonLeaf.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Mario.h"

// Static Var
// Static Func

// member Var

RacoonLeaf::RacoonLeaf()
	: m_Power(10.f)
	, m_MaxPower(300.f)
	, m_JumpPower(0)
	, m_JumpMaxPower(100.f)
	, m_RunPos(float4::ZERO)
	, m_JumpPos(float4::ZERO)
	, m_PrevDir(eDIR::LEFT)
	, m_Col(nullptr)
{

}

RacoonLeaf::~RacoonLeaf()
{

}

// member Func

void RacoonLeaf::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if (MARIOTYPE::RACOON != LogicValue::Mario->GetType())
		{
			LogicValue::Mario->m_FSM.ChangeState(L"POWERUP");
		}

		Death();
	}
}

void RacoonLeaf::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void RacoonLeaf::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void RacoonLeaf::Start()
{
	SJWindowResMgr::Inst().FindImage(L"RacoonLeaf.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"RacoonLeaf.bmp")->ImageCut(5, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::LEAF);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"RacoonLeaf_Left", L"RacoonLeaf.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"RacoonLeaf_Right", L"RacoonLeaf.bmp", 1, 1);

	m_AniRenderer->ChangeAnimation(L"RacoonLeaf_Left");

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::ITEM);
	m_Col->SetScale({ 48, 42 });
	m_Col->AddStartEvent(this, &RacoonLeaf::StartCollision);
	m_Col->AddStayEvent(this, &RacoonLeaf::StayCollision);
	m_Col->AddEndEvent(this, &RacoonLeaf::EndCollision);

	m_FSM.CreateState(L"IDLE", this, &RacoonLeaf::IDLEStay, &RacoonLeaf::IDLEStart, &RacoonLeaf::IDLEEnd);
	m_FSM.CreateState(L"JUMP", this, &RacoonLeaf::JUMPStay, &RacoonLeaf::JUMPStart, &RacoonLeaf::JUMPEnd);
	m_FSM.CreateState(L"FALLLEFT", this, &RacoonLeaf::FALLLEFTStay, &RacoonLeaf::FALLLEFTStart, &RacoonLeaf::FALLLEFTEnd);
	m_FSM.CreateState(L"FALLRIGHT", this, &RacoonLeaf::FALLRIGHTStay, &RacoonLeaf::FALLRIGHTStart, &RacoonLeaf::FALLRIGHTEnd);

	m_FSM.ChangeState(L"JUMP");
}

void RacoonLeaf::Update()
{
	m_FSM.Update();

	m_Move = m_RunPos + m_JumpPos;

	MovePos(m_Move);
}

void RacoonLeaf::DebugRender()
{
	CollisionView(m_Col);
}