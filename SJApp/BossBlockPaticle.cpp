#include "BossBlockPaticle.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Mario.h"

// Static Var
// Static Func

// member Var

BossBlockPaticle::BossBlockPaticle()
	: m_Power(200.f)
	, m_JumpPower(0)
	, m_JumpMaxPower(900.f)
	, m_RunPos(float4::ZERO)
	, m_JumpPos(float4::ZERO)
	, m_PaticleDir(PATICLEDIR::LEFTTOP)
{

}

BossBlockPaticle::~BossBlockPaticle()
{

}

// member Func


void BossBlockPaticle::Start()
{
	SJWindowResMgr::Inst().FindImage(L"BossBlockPaticle.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"BossBlockPaticle.bmp")->ImageCut(1, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::TOP_OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"BossBlockPaticle", L"BossBlockPaticle.bmp", 0, 0);
	m_AniRenderer->ChangeAnimation(L"BossBlockPaticle");

	m_FSM.CreateState(L"IDLE", this, &BossBlockPaticle::IDLEStay, &BossBlockPaticle::IDLEStart, &BossBlockPaticle::IDLEEnd);
	m_FSM.CreateState(L"MOVE", this, &BossBlockPaticle::MOVEStay, &BossBlockPaticle::MOVEStart, &BossBlockPaticle::MOVEEnd);

	m_FSM.ChangeState(L"IDLE");
}

void BossBlockPaticle::Update()
{
	m_FSM.Update();

	m_Move = m_RunPos + m_JumpPos;

	MovePos(m_Move);
}

void BossBlockPaticle::DebugRender()
{

}

void BossBlockPaticle::IDLEStart()
{

}
void BossBlockPaticle::IDLEStay()
{

}
void BossBlockPaticle::IDLEEnd()
{

}

void BossBlockPaticle::MOVEStart()
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
void BossBlockPaticle::MOVEStay()
{
	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();

	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();
	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}
}
void BossBlockPaticle::MOVEEnd()
{

}

void BossBlockPaticle::ResetPaticle()
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