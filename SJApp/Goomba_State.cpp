#include "Goomba.h"
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include "Mario.h"


void Goomba::IDLEStart()
{
	m_AniRenderer->ChangeAnimation(L"Goomba_Move");
}

void Goomba::IDLEStay()
{
	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
	{
		if (eDIR::LEFT == m_Dir)
		{
			SetDir(eDIR::RIGHT);
		}
		else
		{
			SetDir(eDIR::LEFT);
		}
	}

	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();
}

void Goomba::IDLEEnd()
{
	m_RunPos = 0;
}

void Goomba::DEADStart()
{
	if (0 == m_DEADEventer.IsEventSize())
	{
		m_DEADEventer.CreateTimeEventStart(0.15f, this, &Goomba::DEADAnimation);
		m_DEADEventer.CreateTimeEvent(0.15f, this, &Goomba::DEAD);
	}
}

void Goomba::DEADStay()
{
	m_DEADEventer.Update();
}

void Goomba::DEADEnd()
{

}

void Goomba::FLYDEADStart()
{
	m_AniRenderer->ChangeAnimation(L"Goomba_FlyDead");

	if (GetPos().x >= LogicValue::Mario->GetPos().x)
	{
		SetDir(eDIR::RIGHT);
	}
	else
	{
		SetDir(eDIR::LEFT);
	}

	m_JumpPos = float4::ZERO;
	m_JumpPower = m_JumpMaxPower;

	m_RunPos = float4::ZERO;
}
void Goomba::FLYDEADStay()
{
	m_JumpPower -= 0.5f * m_Gravity * SJTimer::FDeltaTime();

	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();
	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}
}
void Goomba::FLYDEADEnd()
{

}