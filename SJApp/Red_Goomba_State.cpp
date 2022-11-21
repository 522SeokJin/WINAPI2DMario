#include "Red_Goomba.h"
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include "Mario.h"


void Red_Goomba::IDLEStart()
{
	switch (m_Type)
	{
	case GOOMBATYPE::NORMAL:
		m_AniRenderer->ChangeAnimation(L"Move");
		break;
	case GOOMBATYPE::WING:
		m_AniRenderer->ChangeAnimation(L"ParaMove");
		break;
	default:
		break;
	}
}

void Red_Goomba::IDLEStay()
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

	switch (m_Type)
	{
	case GOOMBATYPE::NORMAL:
		m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();
		break;
	case GOOMBATYPE::WING:
		m_FSM.ChangeState(L"JUMP");
		break;
	default:
		break;
	}
}

void Red_Goomba::IDLEEnd()
{
	m_RunPos = 0;
}

void Red_Goomba::JUMPStart()
{
	m_JumpPos = float4::ZERO;

	if (0 ==m_JumpCount)
	{
		m_JumpPower = 300.f;
	}
	else if (1 == m_JumpCount)
	{
		m_JumpPower = 300.f;
	}
	else if (2 == m_JumpCount)
	{
		m_JumpPower = 300.f;
	}
	else
	{
		m_JumpPower = m_JumpMaxPower;
		m_AniRenderer->ChangeAnimation(L"FastParaMove");

	}

	if (0 == m_JumpCount)
	{
		if (GetPos().x < LogicValue::Mario->GetPos().x)
		{
			SetDir(eDIR::RIGHT);
		}
		else
		{
			SetDir(eDIR::LEFT);
		}
	}
}
void Red_Goomba::JUMPStay()
{
	if (m_Type == GOOMBATYPE::NORMAL)
	{
		m_FSM.ChangeState(L"FALL");
	}

	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();

	m_JumpPower -= 0.475f * m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < 0)
	{
		m_FSM.ChangeState(L"FALL");
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND))
	{
		m_FSM.ChangeState(L"FALL");
	}
}
void Red_Goomba::JUMPEnd()
{
	if (m_JumpCount++ >= 3)
	{
		m_JumpCount = 0;
		m_AniRenderer->ChangeAnimation(L"ParaMove");
	}
}

void Red_Goomba::FALLStart()
{
	switch (m_Type)
	{
	case GOOMBATYPE::NORMAL:
		m_AniRenderer->ChangeAnimation(L"Move");
		break;
	case GOOMBATYPE::WING:
		m_AniRenderer->ChangeAnimation(L"ParaMove");
		break;
	default:
		break;
	}

	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void Red_Goomba::FALLStay()
{
	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();

	m_JumpPower -= 0.475f* m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::FREE) ||
		false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM], (int)PIXELCOLOR::FREE) ||
		false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM], (int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"IDLE");
	}
}
void Red_Goomba::FALLEnd()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}

void Red_Goomba::DEADStart()
{
	if (0 == m_DEADEventer.IsEventSize())
	{
		m_DEADEventer.CreateTimeEventStart(0.15f, this, &Red_Goomba::DEADAnimation);
		m_DEADEventer.CreateTimeEvent(0.15f, this, &Red_Goomba::DEAD);
	}

	m_RunPos = 0;
	m_JumpPos = float4::ZERO;
}

void Red_Goomba::DEADStay()
{
	m_DEADEventer.Update();
}

void Red_Goomba::DEADEnd()
{

}

void Red_Goomba::FLYDEADStart()
{
	m_AniRenderer->ChangeAnimation(L"FlyDead");

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
void Red_Goomba::FLYDEADStay()
{
	m_JumpPower -= 0.5f * m_Gravity * SJTimer::FDeltaTime();

	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();
	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}
}
void Red_Goomba::FLYDEADEnd()
{

}

