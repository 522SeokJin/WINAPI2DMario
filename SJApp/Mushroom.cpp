#include "Mushroom.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Mario.h"

// Static Var
// Static Func

// member Var

Mushroom::Mushroom()
	: m_Power(200.f)
	, m_JumpPower(0)
	, m_JumpMaxPower(600.f)
	, m_RunPos (float4::ZERO)
	, m_JumpPos(float4::ZERO)
	, m_Col(nullptr)
{

}

Mushroom::~Mushroom()
{

}

// member Func

void Mushroom::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if (MARIOTYPE::SMALL == LogicValue::Mario->GetType())
		{
			LogicValue::Mario->m_FSM.ChangeState(L"POWERUP");
		}
		Death();
	}
}

void Mushroom::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Mushroom::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Mushroom::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Mushroom.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Mushroom.bmp")->ImageCut(1, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Mushroom", L"Mushroom.bmp", 0, 0);
	m_AniRenderer->ChangeAnimation(L"Mushroom");

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::ITEM);
	m_Col->SetScale({ 48, 48 });
	m_Col->AddStartEvent(this, &Mushroom::StartCollision);
	m_Col->AddStayEvent(this, &Mushroom::StayCollision);
	m_Col->AddEndEvent(this, &Mushroom::EndCollision);

	m_FSM.CreateState(L"IDLE", this, &Mushroom::IDLEStay, &Mushroom::IDLEStart, &Mushroom::IDLEEnd);
	m_FSM.CreateState(L"MOVE", this, &Mushroom::MOVEStay, &Mushroom::MOVEStart, &Mushroom::MOVEEnd);
	m_FSM.CreateState(L"MOVEFALL", this, &Mushroom::MOVEFALLStay, &Mushroom::MOVEFALLStart, &Mushroom::MOVEFALLEnd);

	m_FSM.ChangeState(L"IDLE");
}

void Mushroom::Update()
{
	SetPixelPos(float4{0, 24});

	m_FSM.Update();

	m_Move = m_RunPos + m_JumpPos;

	MovePos(m_Move);
}

void Mushroom::DebugRender()
{
	PixelView();

	CollisionView(m_Col);
}

void Mushroom::IDLEStart()
{

}
void Mushroom::IDLEStay()
{

}
void Mushroom::IDLEEnd()
{

}

void Mushroom::MOVEStart()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void Mushroom::MOVEStay()
{
	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
	{
		if (eDIR::LEFT == m_Dir)
		{
			m_Dir = eDIR::RIGHT;
			m_fDir = float4::RIGHT;
		}
		else
		{
			m_Dir = eDIR::LEFT;
			m_fDir = float4::LEFT;
		}
	}

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"MOVEFALL");
	}
}
void Mushroom::MOVEEnd()
{

}

void Mushroom::MOVEFALLStart()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void Mushroom::MOVEFALLStay()
{
	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
	{
		if (eDIR::LEFT == m_Dir)
		{
			m_Dir = eDIR::RIGHT;
			m_fDir = float4::RIGHT;
		}
		else
		{
			m_Dir = eDIR::LEFT;
			m_fDir = float4::LEFT;
		}
	}

	if (false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::FREE) ||
		false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM], (int)PIXELCOLOR::FREE) ||
		false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM], (int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"MOVE");
	}
}
void Mushroom::MOVEFALLEnd()
{

}