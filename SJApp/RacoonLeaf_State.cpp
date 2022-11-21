#include "RacoonLeaf.h"
#include <SJRendererAnimation.h>

void RacoonLeaf::IDLEStart()
{

}
void RacoonLeaf::IDLEStay()
{
	m_FALLEventer.Update();

	m_RunPos *= 0.9f;
	m_JumpPos *= 0.9f;
}
void RacoonLeaf::IDLEEnd()
{

}

void RacoonLeaf::JUMPStart()
{
	m_JumpPos = float4::ZERO;
	m_JumpPower = 1000.f;
}
void RacoonLeaf::JUMPStay()
{
	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < 0)
	{
		m_FSM.ChangeState(L"FALLLEFT");
	}
}
void RacoonLeaf::JUMPEnd()
{
	m_Col->On();
}

void RacoonLeaf::ChangeFALLState()
{
	if (eDIR::LEFT == m_PrevDir)
	{
		m_FSM.ChangeState(L"FALLRIGHT");
	}
	else
	{
		m_FSM.ChangeState(L"FALLLEFT");
	}
}

void RacoonLeaf::ChangeIDLEState()
{
	m_FSM.ChangeState(L"IDLE");
}

void RacoonLeaf::FALLLEFTStart()
{
	SetDir(eDIR::LEFT);

	m_AniRenderer->ChangeAnimation(L"RacoonLeaf_Left");

	m_PrevDir = eDIR::LEFT;

	m_FALLEventer.CreateTimeEvent(0.5f, this, &RacoonLeaf::ChangeIDLEState);
	m_FALLEventer.CreateTimeEvent(0.2f, this, &RacoonLeaf::ChangeFALLState);

	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void RacoonLeaf::FALLLEFTStay()
{
	m_FALLEventer.Update();

	m_RunPos += m_fDir * m_Power * SJTimer::FDeltaTime();

	if (m_RunPos.x < m_fDir.x * m_MaxPower * SJTimer::FDeltaTime())
	{
		m_RunPos = m_fDir * m_MaxPower * SJTimer::FDeltaTime();
	}

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}
}
void RacoonLeaf::FALLLEFTEnd()
{

}

void RacoonLeaf::FALLRIGHTStart()
{
	SetDir(eDIR::RIGHT);
	m_AniRenderer->ChangeAnimation(L"RacoonLeaf_Right");

	m_PrevDir = eDIR::RIGHT;

	m_FALLEventer.CreateTimeEvent(0.5f, this, &RacoonLeaf::ChangeIDLEState);
	m_FALLEventer.CreateTimeEvent(0.2f, this, &RacoonLeaf::ChangeFALLState);

	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void RacoonLeaf::FALLRIGHTStay()
{
	m_FALLEventer.Update();

	m_RunPos += m_fDir * m_Power * SJTimer::FDeltaTime();

	if (m_RunPos.x > m_fDir.x * m_MaxPower * SJTimer::FDeltaTime())
	{
		m_RunPos = m_fDir * m_MaxPower * SJTimer::FDeltaTime();
	}

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}
}
void RacoonLeaf::FALLRIGHTEnd()
{

}