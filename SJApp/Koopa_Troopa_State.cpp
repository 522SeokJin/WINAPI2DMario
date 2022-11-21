#include "Koopa_Troopa.h"
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include "Mario.h"
#include <SJCollision.h>

void Koopa_Troopa::IDLEStart()
{
	switch (m_Type)
	{
	case TROOPATYPE::NORMAL:
		ChangeAnimation(L"Koopa_Troopa_Idle");
		break;
	case TROOPATYPE::WING:
		ChangeAnimation(L"Koopa_Troopa_ParaIdle");
		break;
	default:
		break;
	}
}
void Koopa_Troopa::IDLEStay()
{
	if (false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::FREE) && TROOPATYPE::NORMAL == m_Type)
	{
		if (m_bDelay)
		{
			if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM], (int)PIXELCOLOR::FREE) ||
				true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM], (int)PIXELCOLOR::FREE))
			{
				if (eDIR::LEFT == m_Dir)
				{
					SetDir(eDIR::RIGHT);
				}
				else
				{
					SetDir(eDIR::LEFT);
				}
				SetDelay();
			}
		}
	}

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"FALL");
	}
	else
	{
		switch (m_Type)
		{
		case TROOPATYPE::NORMAL:
			MoveTroopa();
			break;
		case TROOPATYPE::WING:
			m_FSM.ChangeState(L"JUMP");
			break;
		default:
			break;
		}
	}
	
}
void Koopa_Troopa::IDLEEnd()
{

}

void Koopa_Troopa::JUMPStart()
{
	m_JumpPos = float4::ZERO;
	m_JumpPower = m_JumpMaxPower;
}
void Koopa_Troopa::JUMPStay()
{
	if (m_Type == TROOPATYPE::NORMAL)
	{
		m_FSM.ChangeState(L"FALL");
	}

	MoveTroopa();

	m_JumpPower -= 0.475f * m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < 0)
	{
		m_FSM.ChangeState(L"FALL");
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) )
	{
		m_FSM.ChangeState(L"FALL");
	}
}
void Koopa_Troopa::JUMPEnd()
{

}

void Koopa_Troopa::FALLStart()
{
	switch (m_Type)
	{
	case TROOPATYPE::NORMAL:
		ChangeAnimation(L"Koopa_Troopa_Idle");
		break;
	case TROOPATYPE::WING:
		ChangeAnimation(L"Koopa_Troopa_ParaIdle");
		break;
	default:
		break;
	}

	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void Koopa_Troopa::FALLStay()
{
	MoveTroopa();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
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
void Koopa_Troopa::FALLEnd()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}

void Koopa_Troopa::HIDEStart()
{
	ChangeAnimation(L"Koopa_Troopa_Hide");

	m_RunPos = 0;
	m_JumpPos = float4::ZERO;
	m_JumpPower = m_JumpMaxPower;

	if (0 == m_ReviveEventer.IsEventSize())
	{
		m_ReviveEventer.CreateTimeEvent(4.f, this, &Koopa_Troopa::ReviveTimeEvent);
		m_ReviveEventer.CreateTimeEvent(1.f, this, &Koopa_Troopa::ReviveChangeState);
	}

	m_ReviveEventer.Reset();
}
void Koopa_Troopa::HIDEStay()
{
	if (false == LogicValue::Mario->IsCarry())
	{
		m_ReviveEventer.Update();
	}

	if (true == (*GetEventCol()).IsOn())
	{
		if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
		{
			m_FSM.ChangeState(L"HIDEFALL");
		}
	}
}
void Koopa_Troopa::HIDEEnd()
{

}

void Koopa_Troopa::HIDEFALLStart()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void Koopa_Troopa::HIDEFALLStay()
{
	m_ReviveEventer.Update();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::FREE) ||
		false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM], (int)PIXELCOLOR::FREE) ||
		false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM], (int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"HIDE");
	}
}
void Koopa_Troopa::HIDEFALLEnd()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}

void Koopa_Troopa::KICKEDStart()
{
	ChangeAnimation(L"Koopa_Troopa_Kicked");
}
void Koopa_Troopa::KICKEDStay()
{
	m_RunPos = m_fDir * m_KickPower * SJTimer::FDeltaTime();

	if(m_bDelay)
	{
		if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
			true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
		{
			if (eDIR::LEFT == m_Dir)
			{
				m_Dir = eDIR::RIGHT;
				m_fDir = float4::RIGHT;
				SJSound::Play(L"Bump.wav");
			}
			else
			{
				m_Dir = eDIR::LEFT;
				m_fDir = float4::LEFT;
				SJSound::Play(L"Bump.wav");
			}

			SetDelay();
		}
	}
	

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"KICKEDFALL");
	}
}
void Koopa_Troopa::KICKEDEnd()
{

}

void Koopa_Troopa::KICKEDFALLStart()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void Koopa_Troopa::KICKEDFALLStay()
{
	m_RunPos = m_fDir * m_KickPower * SJTimer::FDeltaTime();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (m_bDelay)
	{
		if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
			true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_TOP], m_RunPos, (int)PIXELCOLOR::GROUND))
		{
			m_Dir = eDIR::RIGHT;
			m_fDir = float4::RIGHT;
			SJSound::Play(L"Bump.wav");

			SetDelay();
		}
		else if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
			true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP], m_RunPos, (int)PIXELCOLOR::GROUND))
		{
			m_Dir = eDIR::LEFT;
			m_fDir = float4::LEFT;
			SJSound::Play(L"Bump.wav");

			SetDelay();
		}
	}
	

	if (false == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"KICKED");
	}
}
void Koopa_Troopa::KICKEDFALLEnd()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}

void Koopa_Troopa::DEADStart()
{
	ChangeAnimation(L"Koopa_Troopa_ReverseHide");

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
void Koopa_Troopa::DEADStay()
{
	m_JumpPower -= 0.5f * m_Gravity * SJTimer::FDeltaTime();

	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();
	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}
}
void Koopa_Troopa::DEADEnd()
{

}