#include "Goomba.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include <SJWindow.h>
#include <SJCollision.h>

#include "LogicValue.h"

// Static Var
// Static Func

// member Var

Goomba::Goomba()
	: m_RunPos(float4::ZERO)
	, m_JumpPos(float4::ZERO)
	, m_Power(100.f)
	, m_JumpPower(0)
	, m_JumpMaxPower(600.f)
	, m_Col(nullptr)
	, m_TopCol(nullptr)
{

}

Goomba::~Goomba()
{

}

// member Func

void Goomba::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TOP == _This->GetCheckData())
		{
			m_FSM.ChangeState(L"DEAD");
		}
	}

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

void Goomba::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Goomba.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Goomba.bmp")->ImageCut(5, 1);

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER);
	m_Col->SetScale({ 48, 30 });
	m_Col->SetPivotPos({ 0.f, -18.f });
	m_Col->SetCheckData((int)COLLISIONDATA::SIDE);
	m_Col->AddStartEvent(this, &Goomba::StartCollision);

	m_TopCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER);
	m_TopCol->SetScale({ 36, 24 });
	m_TopCol->SetPivotPos({ 0.f, -36.f });
	m_TopCol->SetCheckData((int)COLLISIONDATA::TOP);
	m_TopCol->AddStartEvent(this, &Goomba::StartCollision);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::MONSTER);
	m_AniRenderer->SetRenderScale({ 128, 128 });
	m_AniRenderer->CreateAnimation(L"Goomba_Move", L"Goomba.bmp", 0, 1, 0.13f);
	m_AniRenderer->CreateAnimation(L"Goomba_Dead", L"Goomba.bmp", 2, 2);
	m_AniRenderer->CreateAnimation(L"Goomba_FlyDead", L"Goomba.bmp", 3, 3);

	m_FSM.CreateState(L"IDLE", this, &Goomba::IDLEStay, &Goomba::IDLEStart, &Goomba::IDLEEnd);
	m_FSM.CreateState(L"DEAD", this, &Goomba::DEADStay, &Goomba::DEADStart, &Goomba::DEADEnd);
	m_FSM.CreateState(L"FLYDEAD", this, &Goomba::FLYDEADStay, &Goomba::FLYDEADStart, &Goomba::FLYDEADEnd);

	m_FSM.ChangeState(L"IDLE");
}

void Goomba::Update()
{	
	SetPixelPos();

	m_FSM.Update();

	m_Move = m_RunPos + m_JumpPos;

	MovePos(m_Move);

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::DEATH))
	{
		Death();
	}
}

void Goomba::DEADAnimation()
{
	m_Col->Off();
	m_TopCol->Off();
	m_AniRenderer->ChangeAnimation(L"Goomba_Dead");
}

void Goomba::DEAD()
{
	Death();
}

void Goomba::DebugRender()
{
	PixelView();

	CollisionView(m_Col);
	CollisionView(m_TopCol);
}