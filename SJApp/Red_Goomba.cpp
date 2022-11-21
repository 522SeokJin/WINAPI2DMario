#include "Red_Goomba.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include <SJWindow.h>
#include <SJCollision.h>

#include "LogicValue.h"

// Static Var
// Static Func

// member Var

Red_Goomba::Red_Goomba()
	: m_Type(GOOMBATYPE::NORMAL)
	, m_RunPos(float4::ZERO)
	, m_JumpPos(float4::ZERO)
	, m_Power(100.f)
	, m_JumpPower(0)
	, m_JumpMaxPower(600.f)
	, m_Col(nullptr)
	, m_TopCol(nullptr)
	, m_JumpCount(0)
{

}

Red_Goomba::~Red_Goomba()
{

}

// member Func

void Red_Goomba::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::PROJECTILE == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TOP != _This->GetCheckData())
		{
			SJSound::Play(L"Kick.wav");

			m_Col->Off();
			m_TopCol->Off();

			m_FSM.ChangeState(L"FLYDEAD");
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::MARIO_PROJECTILE == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TOP != _This->GetCheckData())
		{
			SJSound::Play(L"Kick.wav");

			m_Col->Off();
			m_TopCol->Off();

			m_FSM.ChangeState(L"FLYDEAD");
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::MONSTER == _Other->GetOrder())
	{
		switch (m_Dir)
		{
		case eDIR::LEFT:
			m_Dir = eDIR::RIGHT;
			m_fDir = float4::RIGHT;
			break;
		case eDIR::RIGHT:
			m_Dir = eDIR::LEFT;
			m_fDir = float4::LEFT;
			break;
		default:
			break;
		}
	}
}

void Red_Goomba::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Red_Goomba::EndCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TOP == _This->GetCheckData())
		{
			switch (m_Type)
			{
			case GOOMBATYPE::NORMAL:
				m_FSM.ChangeState(L"DEAD");
				break;
			case GOOMBATYPE::WING:
				m_Type = GOOMBATYPE::NORMAL;
				break;
			default:
				break;
			}
		}
	}
}

void Red_Goomba::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Red_Goomba.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Red_Goomba.bmp")->ImageCut(5, 2);

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER);
	m_Col->SetScale({ 48, 30 });
	m_Col->SetPivotPos({ 0.f, -18.f });
	m_Col->SetCheckData((int)COLLISIONDATA::SIDE);
	m_Col->AddStartEvent(this, &Red_Goomba::StartCollision);
	m_Col->AddStayEvent(this, &Red_Goomba::StayCollision);
	m_Col->AddEndEvent(this, &Red_Goomba::EndCollision);

	m_TopCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER);
	m_TopCol->SetScale({ 36, 24 });
	m_TopCol->SetPivotPos({ 0.f, -36.f });
	m_TopCol->SetCheckData((int)COLLISIONDATA::TOP);
	m_TopCol->AddStartEvent(this, &Red_Goomba::StartCollision);
	m_TopCol->AddStayEvent(this, &Red_Goomba::StayCollision);
	m_TopCol->AddEndEvent(this, &Red_Goomba::EndCollision);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::MONSTER);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Move", L"Red_Goomba.bmp", 0, 1, 0.13f);
	m_AniRenderer->CreateAnimation(L"ParaMove", L"Red_Goomba.bmp", 2, 3, 0.13f);
	m_AniRenderer->CreateAnimation(L"FastParaMove", L"Red_Goomba.bmp", 2, 3, 0.05f);
	m_AniRenderer->CreateAnimation(L"Dead", L"Red_Goomba.bmp", 4, 4);
	m_AniRenderer->CreateAnimation(L"FlyDead", L"Red_Goomba.bmp", 5, 5);

	m_FSM.CreateState(L"IDLE", this, &Red_Goomba::IDLEStay, &Red_Goomba::IDLEStart, &Red_Goomba::IDLEEnd);
	m_FSM.CreateState(L"JUMP", this, &Red_Goomba::JUMPStay, &Red_Goomba::JUMPStart, &Red_Goomba::JUMPEnd);
	m_FSM.CreateState(L"FALL", this, &Red_Goomba::FALLStay, &Red_Goomba::FALLStart, &Red_Goomba::FALLEnd);
	m_FSM.CreateState(L"DEAD", this, &Red_Goomba::DEADStay, &Red_Goomba::DEADStart, &Red_Goomba::DEADEnd);
	m_FSM.CreateState(L"FLYDEAD", this, &Red_Goomba::FLYDEADStay, &Red_Goomba::FLYDEADStart, &Red_Goomba::FLYDEADEnd);

	m_FSM.ChangeState(L"IDLE");
}

void Red_Goomba::Update()
{
	SetPixelPos();

	m_FSM.Update();

	m_Move = m_RunPos + m_JumpPos;

	MovePos(m_Move);
}

void Red_Goomba::DEADAnimation()
{
	m_Col->Off();
	m_TopCol->Off();
	m_AniRenderer->ChangeAnimation(L"Dead");
}

void Red_Goomba::DEAD()
{
	Death();
}

void Red_Goomba::DebugRender()
{
	PixelView();

	CollisionView(m_Col);
	CollisionView(m_TopCol);
}