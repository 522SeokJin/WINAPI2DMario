#include "BlockPaticle.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Mario.h"

// Static Var
// Static Func

// member Var

BlockPaticle::BlockPaticle()
	: m_Power(200.f)
	, m_JumpPower(0)
	, m_JumpMaxPower(600.f)
	, m_RunPos(float4::ZERO)
	, m_JumpPos(float4::ZERO)
	, m_PaticleDir(PATICLEDIR::LEFTTOP)
{

}

BlockPaticle::~BlockPaticle()
{

}

// member Func


void BlockPaticle::Start()
{
	SJWindowResMgr::Inst().FindImage(L"BlockPaticle.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"BlockPaticle.bmp")->ImageCut(1, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::TOP_OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"BlockPaticle", L"BlockPaticle.bmp", 0, 0);
	m_AniRenderer->ChangeAnimation(L"BlockPaticle");

	m_FSM.CreateState(L"IDLE", this, &BlockPaticle::IDLEStay, &BlockPaticle::IDLEStart, &BlockPaticle::IDLEEnd);
	m_FSM.CreateState(L"MOVE", this, &BlockPaticle::MOVEStay, &BlockPaticle::MOVEStart, &BlockPaticle::MOVEEnd);

	m_FSM.ChangeState(L"IDLE");
}

void BlockPaticle::Update()
{
	m_FSM.Update();

	m_Move = m_RunPos + m_JumpPos;

	MovePos(m_Move);
}

void BlockPaticle::DebugRender()
{

}

void BlockPaticle::IDLEStart()
{

}
void BlockPaticle::IDLEStay()
{

}
void BlockPaticle::IDLEEnd()
{

}

void BlockPaticle::MOVEStart()
{
	switch (m_PaticleDir)
	{
	case PATICLEDIR::LEFTTOP:
		m_JumpPower = m_JumpMaxPower;
		SetDir(eDIR::LEFT);
		break;
	case PATICLEDIR::RIGHTTOP:
		m_JumpPower = m_JumpMaxPower;
		SetDir(eDIR::RIGHT);
		break;
	case PATICLEDIR::LEFTBOTTOM:
		m_JumpPower = 0.5f * m_JumpMaxPower;
		SetDir(eDIR::LEFT);
		break;
	case PATICLEDIR::RIGHTBOTTOM:
		m_JumpPower = 0.5f * m_JumpMaxPower;
		SetDir(eDIR::RIGHT);
		break;
	default:
		break;
	}

	m_JumpPos = float4::ZERO;
	m_RunPos = float4::ZERO;
}
void BlockPaticle::MOVEStay()
{
	m_JumpPower -= 0.75f * m_Gravity * SJTimer::FDeltaTime();

	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();
	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}
}
void BlockPaticle::MOVEEnd()
{
	
}

void BlockPaticle::ResetPaticle()
{
	switch (m_PaticleDir)
	{
	case PATICLEDIR::LEFTTOP:
		m_JumpPower = m_JumpMaxPower;
		SetDir(eDIR::LEFT);
		break;
	case PATICLEDIR::RIGHTTOP:
		m_JumpPower = m_JumpMaxPower;
		SetDir(eDIR::RIGHT);
		break;
	case PATICLEDIR::LEFTBOTTOM:
		m_JumpPower = 0.5f * m_JumpMaxPower;
		SetDir(eDIR::LEFT);
		break;
	case PATICLEDIR::RIGHTBOTTOM:
		m_JumpPower = 0.5f * m_JumpMaxPower;
		SetDir(eDIR::RIGHT);
		break;
	default:
		break;
	}

	m_JumpPos = float4::ZERO;
	m_RunPos = float4::ZERO;
}