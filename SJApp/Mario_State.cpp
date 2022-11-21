#include "Mario.h"
#include <SJRendererAnimation.h>
#include <SJInput.h>
#include "LogicValue.h"
#include <SJSound.h>
#include "Koopa_Troopa.h"
#include <SJCollision.h>

void Mario::POWERUPStart()
{
	m_bNoDamage = true;

	if (MARIOTYPE::SMALL == m_Type)
	{
		SJSound::Play(L"Powerup.wav");

		if (0 == m_POWERUPEventer.IsEventSize())
		{
			m_POWERUPEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpSmall);
			m_POWERUPEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpMedium);
			m_POWERUPEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpSmall);
			m_POWERUPEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpMedium);
			m_POWERUPEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpSuper);
			m_POWERUPEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpMedium);
			m_POWERUPEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpSuper);
			m_POWERUPEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpEnd);
		}

		m_POWERUPEventer.Reset();
	}
	else if (MARIOTYPE::SUPER == m_Type)
	{
		SJSound::Play(L"Transformation.wav");

		if (0 == m_RACOONUPEventer.IsEventSize())
		{
			m_RACOONUPEventer.CreateTimeEventStart(0.20f, this, &Mario::PowerUpRacoon);
			m_RACOONUPEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpEnd);
		}

		m_RACOONUPEventer.Reset();
	}

	m_SaveMovePos = m_Move;
	m_RunPos = 0;
	m_JumpPos = 0;

}
void Mario::POWERUPStay()
{
	m_POWERUPEventer.Update();
	m_RACOONUPEventer.Update();

	m_RunPos = 0;
	m_JumpPos = 0;
}
void Mario::POWERUPEnd()
{
	m_RunPos = m_SaveMovePos.x;
	m_JumpPos = m_SaveMovePos.y;

	m_bNoDamage = false;
}

void Mario::POWERDOWNStart()
{
	m_bNoDamage = true;

	if (MARIOTYPE::SUPER == m_Type)
	{
		SJSound::Play(L"Pipe.wav");

		if (0 == m_POWERDOWNEventer.IsEventSize())
		{
			m_POWERDOWNEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpSuper);
			m_POWERDOWNEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpMedium);
			m_POWERDOWNEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpSuper);
			m_POWERDOWNEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpMedium);
			m_POWERDOWNEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpSmall);
			m_POWERDOWNEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpMedium);
			m_POWERDOWNEventer.CreateTimeEvent(0.1f, this, &Mario::PowerUpSmall);
			m_POWERDOWNEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEnd);
		}

		m_POWERDOWNEventer.Reset();
	}
	else if (MARIOTYPE::RACOON == m_Type)
	{
		SJSound::Play(L"Transformation.wav");

		if (0 == m_RACOONDOWNEventer.IsEventSize())
		{
			m_RACOONDOWNEventer.CreateTimeEventStart(0.20f, this, &Mario::PowerDownRacoon);
			m_RACOONDOWNEventer.CreateTimeEvent(0.1f, this, &Mario::PowerRacoonDownEnd);
		}

		m_RACOONDOWNEventer.Reset();
	}
	else
	{
		m_FSM.ChangeState(L"DEAD");
	}


	m_SaveMovePos = m_Move;
	m_RunPos = 0;
	m_JumpPos = 0;
}
void Mario::POWERDOWNStay()
{
	m_POWERDOWNEventer.Update();
	m_RACOONDOWNEventer.Update();

	m_RunPos = 0;
	m_JumpPos = 0;
}
void Mario::POWERDOWNEnd()
{
	m_RunPos = m_SaveMovePos.x;
	m_JumpPos = m_SaveMovePos.y;
}

void Mario::IDLEStart()
{
	ChangeAnimation(L"Idle");

	m_JumpPos = float4::ZERO;
	m_JumpPower = 0.f;
}
void Mario::IDLEStay()
{
	m_JumpPos = float4::ZERO;

	if (true == SJInput::IsPress(L"LEFT") ||
		true == SJInput::IsPress(L"RIGHT"))
	{
		m_FSM.ChangeState(L"RUN");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"JUMP");
	}

	if (true == SJInput::IsDown(L"X") && MARIOTYPE::RACOON == GetType())
	{
		m_FSM.ChangeState(L"TALLATTACK");
	}

	if (true == SJInput::IsPress(L"X") && nullptr != m_CarryObj)
	{
		m_FSM.ChangeState(L"CARRYIDLE");
	}

	if (m_PrevDir != m_Dir && m_RunPos.x != 0.f)
	{
		m_FSM.ChangeState(L"SKID");
	}

	if (true == SJInput::IsPress(L"DOWN") && m_Type != MARIOTYPE::SMALL)
	{
		m_FSM.ChangeState(L"SIT");
	}

	m_RunPos = m_RunPos * 0.95f;

	if (abs(m_RunPos.x) < 0.1f)
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE))
	{
		m_RunPos = 0;
	}

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"FALL");
	}
}

void Mario::IDLEEnd()
{

}

void Mario::BLOCKIDLEStart()
{
	ChangeAnimation(L"Idle");

	m_JumpPos = float4::ZERO;
	m_JumpPower = 0.f;
}
void Mario::BLOCKIDLEStay()
{

	if (true == SJInput::IsPress(L"LEFT") ||
		true == SJInput::IsPress(L"RIGHT"))
	{
		m_FSM.ChangeState(L"BLOCKRUN");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"BLOCKJUMP");
	}

	if (true == SJInput::IsPress(L"X") && nullptr != m_CarryObj)
	{
		m_FSM.ChangeState(L"BLOCKCARRYIDLE");
		return;
	}

	if (m_PrevDir != m_Dir && m_RunPos.x != 0.f)
	{
		m_FSM.ChangeState(L"BLOCKSKID");
	}

	if (true == SJInput::IsPress(L"DOWN") && m_Type != MARIOTYPE::SMALL)
	{
		m_FSM.ChangeState(L"BLOCKSIT");
	}

	m_RunPos = m_RunPos * 0.95f;

	if (abs(m_RunPos.x) < 0.1f)
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE))
	{
		m_RunPos = 0;
	}
}

void Mario::BLOCKIDLEEnd()
{

}

void Mario::CARRYIDLEStart()
{
	ChangeAnimation(L"CarryIdle");

	m_JumpPos = float4::ZERO;
	m_JumpPower = 0.f;
}
void Mario::CARRYIDLEStay()
{
	CarryAction();

	if (true == SJInput::IsPress(L"LEFT") ||
		true == SJInput::IsPress(L"RIGHT"))
	{
		m_FSM.ChangeState(L"CARRYRUN");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"CARRYJUMP");
	}

	m_RunPos = m_RunPos * 0.95f;

	if (abs(m_RunPos.x) < 0.1f)
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE))
	{
		m_RunPos = 0;
	}

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"CARRYFALL");
	}
}
void Mario::CARRYIDLEEnd()
{

}

void Mario::BLOCKCARRYIDLEStart()
{
	ChangeAnimation(L"CarryIdle");

	m_JumpPos = float4::ZERO;
	m_JumpPower = 0.f;
}
void Mario::BLOCKCARRYIDLEStay()
{
	CarryAction();

	if (true == SJInput::IsPress(L"LEFT") ||
		true == SJInput::IsPress(L"RIGHT"))
	{
		m_FSM.ChangeState(L"BLOCKCARRYRUN");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"CARRYJUMP");
	}

	m_RunPos = m_RunPos * 0.95f;

	if (abs(m_RunPos.x) < 0.1f)
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE))
	{
		m_RunPos = 0;
	}
}
void Mario::BLOCKCARRYIDLEEnd()
{

}

void Mario::RUNStart()
{
	if (m_fAccelTime >= 6)
	{
		ChangeAnimation(L"FastRun");
	}
	else
	{
		ChangeAnimation(L"SlowRun");
	}
}
void Mario::RUNStay()
{
	MoveMario();

	if (m_fAccelTime >= 6)
	{
		ChangeAnimation(L"FastRun");
	}
	else
	{
		ChangeAnimation(L"SlowRun");
	}

	if (true == SJInput::IsFree(L"LEFT")
		&& true == SJInput::IsFree(L"RIGHT"))
	{
		m_FSM.ChangeState(L"IDLE");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"JUMP");
	}

	if (true == SJInput::IsDown(L"X") && MARIOTYPE::RACOON == GetType())
	{
		m_FSM.ChangeState(L"TALLATTACK");
	}

	if (true == SJInput::IsPress(L"X") && nullptr != m_CarryObj)
	{
		m_FSM.ChangeState(L"CARRYRUN");
	}

	if (m_PrevDir != m_Dir)
	{
		m_FSM.ChangeState(L"SKID");
	}

	if (true == SJInput::IsDown(L"DOWN") && m_Type != MARIOTYPE::SMALL)
	{
		m_FSM.ChangeState(L"SIT");
	}

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"FALL");
	}
}
void Mario::RUNEnd()
{
	
}

void Mario::BLOCKRUNStart()
{
	if (m_fAccelTime >= 6)
	{
		ChangeAnimation(L"FastRun");
	}
	else
	{
		ChangeAnimation(L"SlowRun");
	}
}
void Mario::BLOCKRUNStay()
{
	if (m_fAccelTime >= 6)
	{
		ChangeAnimation(L"FastRun");
	}
	else
	{
		ChangeAnimation(L"SlowRun");
	}

	MoveMario();

	if (true == SJInput::IsFree(L"LEFT")
		&& true == SJInput::IsFree(L"RIGHT"))
	{
		m_FSM.ChangeState(L"BLOCKIDLE");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"BLOCKJUMP");
	}

	if (true == SJInput::IsPress(L"X") && nullptr != m_CarryObj)
	{
		m_FSM.ChangeState(L"CARRYRUN");
	}

	if (m_PrevDir != m_Dir)
	{
		m_FSM.ChangeState(L"BLOCKSKID");
	}

	if (true == SJInput::IsDown(L"DOWN") && m_Type != MARIOTYPE::SMALL)
	{
		m_FSM.ChangeState(L"BLOCKSIT");
	}
}

void Mario::BLOCKRUNEnd()
{

}



void Mario::CARRYRUNStart()
{
	ChangeAnimation(L"CarryRun");
}
void Mario::CARRYRUNStay()
{
	MoveMario();
	CarryAction();

	if (true == SJInput::IsFree(L"LEFT")
		&& true == SJInput::IsFree(L"RIGHT"))
	{
		m_FSM.ChangeState(L"CARRYIDLE");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"CARRYJUMP");
	}

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"CARRYFALL");
	}
}

void Mario::CARRYRUNEnd()
{

}

void Mario::BLOCKCARRYRUNStart()
{
	ChangeAnimation(L"CarryRun");
}
void Mario::BLOCKCARRYRUNStay()
{
	MoveMario();
	CarryAction();

	if (true == SJInput::IsFree(L"LEFT")
		&& true == SJInput::IsFree(L"RIGHT"))
	{
		m_FSM.ChangeState(L"BLOCKCARRYIDLE");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"CARRYJUMP");
	}
}

void Mario::BLOCKCARRYRUNEnd()
{

}

void Mario::SKIDStart()
{
	ChangeAnimation(L"Skid");

	m_SkidSound = SJSound::Play(L"Skid.wav", -1);
}

void Mario::SKIDStay()
{
	MoveMario();

	if (true == SJInput::IsFree(L"LEFT")
		&& true == SJInput::IsFree(L"RIGHT"))
	{
		m_FSM.ChangeState(L"IDLE");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"JUMP");
	}

	if (true == SJInput::IsDown(L"X") && MARIOTYPE::RACOON == GetType())
	{
		m_FSM.ChangeState(L"TALLATTACK");
	}

	if (true == SJInput::IsPress(L"LEFT") && m_RunPos.x < 0.f )
	{
		m_FSM.ChangeState(L"RUN");
	}

	if (true == SJInput::IsPress(L"RIGHT") && m_RunPos.x > 0.f)
	{
		m_FSM.ChangeState(L"RUN");
	}

	if (true == SJInput::IsDown(L"DOWN") && m_Type != MARIOTYPE::SMALL)
	{
		m_FSM.ChangeState(L"SIT");
	}

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"FALL");
	}
}

void Mario::SKIDEnd()
{
	m_SkidSound.Stop();
}

void Mario::BLOCKSKIDStart()
{
	ChangeAnimation(L"Skid");

	m_SkidSound = SJSound::Play(L"Skid.wav", -1);
}
void Mario::BLOCKSKIDStay()
{
	MoveMario();

	if (true == SJInput::IsFree(L"LEFT")
		&& true == SJInput::IsFree(L"RIGHT"))
	{
		m_FSM.ChangeState(L"BLOCKIDLE");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"BLOCKJUMP");
	}

	if (true == SJInput::IsPress(L"LEFT") && m_RunPos.x < 0.f)
	{
		m_FSM.ChangeState(L"BLOCKRUN");
	}

	if (true == SJInput::IsPress(L"RIGHT") && m_RunPos.x > 0.f)
	{
		m_FSM.ChangeState(L"BLOCKRUN");
	}

	if (true == SJInput::IsDown(L"DOWN") && m_Type != MARIOTYPE::SMALL)
	{
		m_FSM.ChangeState(L"SIT");
	}
}
void Mario::BLOCKSKIDEnd()
{
	m_SkidSound.Stop();
}

void Mario::JUMPCheckEvent()
{
	if (true == SJInput::IsPress(L"Z"))
	{
		m_JumpPower += m_Gravity * SJTimer::FDeltaTime();
	}
}

void Mario::JUMPStart()
{
	if (m_fAccelTime >= 6)
	{
		ChangeAnimation(L"FastJump");
	}
	else
	{
		ChangeAnimation(L"SlowJump");
	}

	SJSound::Play(L"Mario_Jump.wav");

	m_JumpPos = float4::ZERO;
	m_JumpPower = m_JumpMaxPower;

	if (0 == m_JUMPEventer.IsEventSize())
	{
		m_JUMPEventer.CreateTimeEventStay(0.3f, this, &Mario::JUMPCheckEvent);
	}

	m_JUMPEventer.Reset();
}
void Mario::JUMPStay()
{
	m_JUMPEventer.Update();

	MoveMario();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (true == SJInput::IsPress(L"X") && nullptr != m_CarryObj)
	{
		m_FSM.ChangeState(L"CARRYJUMP");
	}

	if (true == SJInput::IsDown(L"X") && MARIOTYPE::RACOON == GetType())
	{
		m_FSM.ChangeState(L"TALLATTACKFALL");
	}

	if (m_JumpPower < 0)
	{
		m_FSM.ChangeState(L"FALL");
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND))
	{
		m_JumpPos = float4::ZERO;
		m_JumpPower = 0;
		m_FSM.ChangeState(L"FALL");
	}
}

void Mario::JUMPEnd()
{

}

void Mario::TALLJUMPStart()
{
	if (m_fAccelTime >= 6)
	{
		ChangeAnimation(L"FastTail");
		m_JumpPower = 400.f;
	}
	else
	{
		ChangeAnimation(L"SlowTail");
		m_JumpPower = 100.f;
	}

	SJSound::Play(L"Tail_Effect.wav");

	m_JumpPos = float4::ZERO;

}
void Mario::TALLJUMPStay()
{
	MoveMario();

	m_JumpPower -= 0.25f * m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_fAccelTime >= 6 && true == m_bTailDelay)
	{
		if (true == SJInput::IsDown(L"Z"))
		{
			m_fTailDelay = 0;
			m_bTailDelay = false;
			ChangeAnimation(L"FastTail");
			SJSound::Play(L"Tail_Effect.wav");
			m_JumpPower = 400.f;
		}
	}

	//if (true == SJInput::IsPress(L"X") && nullptr != m_CarryObj)
	//{
	//	m_FSM.ChangeState(L"CARRYJUMP");
	//}

	if (m_JumpPower < 0)
	{
		m_FSM.ChangeState(L"FALL");
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND))
	{
		m_JumpPos = float4::ZERO;
		m_JumpPower = 0;
		m_FSM.ChangeState(L"FALL");
	}
}

void Mario::TALLJUMPEnd()
{

}

void Mario::TALLATTACKStart()
{
	if (MARIOTYPE::RACOON != GetType())
	{
		SJDebug::AssertMsg(L"if (MARIOTYPE::RACOON != GetType())");
	}

	SJSound::Play(L"Tail_Effect.wav");

	ChangeAnimation(L"TailAttack");
}
void Mario::TALLATTACKStay()
{
	MoveMario();

	int CurFrame = m_AniRenderer->GetCurAnimation()->GetCurFrame();
	
	if (CurFrame == 18)
	{
		m_TailCol->On();
	}
	else
	{
		m_TailCol->Off();
	}

	if (m_AniRenderer->GetCurAnimation()->IsEnd())
	{
		m_FSM.ChangeState(L"IDLE");
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE))
	{
		m_RunPos = 0;
	}
}
void Mario::TALLATTACKEnd()
{
	m_TailCol->Off();
}

void Mario::TALLATTACKFALLStart()
{
	if (MARIOTYPE::RACOON != GetType())
	{
		SJDebug::AssertMsg(L"if (MARIOTYPE::RACOON != GetType())");
	}

	SJSound::Play(L"Tail_Effect.wav");

	ChangeAnimation(L"TailAttack");
}
void Mario::TALLATTACKFALLStay()
{
	MoveMario();

	int CurFrame = m_AniRenderer->GetCurAnimation()->GetCurFrame();

	if (CurFrame == 18)
	{
		m_TailCol->On();
	}
	else
	{
		m_TailCol->Off();
	}

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (m_AniRenderer->GetCurAnimation()->IsEnd())
	{
		m_FSM.ChangeState(L"FALL");
	}

	if (false == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_JumpPos = 0;

		if (m_AniRenderer->GetCurAnimation()->IsEnd())
		{
			m_FSM.ChangeState(L"IDLE");
		}
	}
}
void Mario::TALLATTACKFALLEnd()
{
	m_TailCol->Off();
}

void Mario::BLOCKJUMPStart()
{
	if (m_fAccelTime >= 6)
	{
		ChangeAnimation(L"FastJump");
	}
	else
	{
		ChangeAnimation(L"SlowJump");
	}

	SJSound::Play(L"Mario_Jump.wav");

	m_JumpPos = float4::ZERO;
	m_JumpPower = m_JumpMaxPower;

	if (0 == m_JUMPEventer.IsEventSize())
	{
		m_JUMPEventer.CreateTimeEventStay(0.3f, this, &Mario::JUMPCheckEvent);
	}

	m_JUMPEventer.Reset();
}
void Mario::BLOCKJUMPStay()
{
	m_JUMPEventer.Update();

	MoveMario();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (true == SJInput::IsPress(L"X") && nullptr != m_CarryObj)
	{
		m_FSM.ChangeState(L"CARRYJUMP");
	}

	if (m_JumpPower < 0)
	{
		m_FSM.ChangeState(L"FALL");
	}

	if (true == PixelCheckAllTop(m_JumpPos, (int)PIXELCOLOR::GROUND))
	{
		m_JumpPos = float4::ZERO;
		m_JumpPower = 0;
		m_FSM.ChangeState(L"FALL");
	}
}

void Mario::BLOCKJUMPEnd()
{

}

void Mario::CARRYJUMPStart()
{
	ChangeAnimation(L"CarryJump");
	SJSound::Play(L"Mario_Jump.wav");

	m_JumpPos = float4::ZERO;
	m_JumpPower = m_JumpMaxPower;

	if (0 == m_JUMPEventer.IsEventSize())
	{
		m_JUMPEventer.CreateTimeEventStay(0.3f, this, &Mario::JUMPCheckEvent);
	}

	m_JUMPEventer.Reset();
}
void Mario::CARRYJUMPStay()
{
	m_JUMPEventer.Update();

	MoveMario();
	CarryAction();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < 0)
	{
		m_FSM.ChangeState(L"CARRYFALL");
	}

	if (true == PixelCheckAllTop(m_JumpPos, (int)PIXELCOLOR::GROUND))
	{
		m_FSM.ChangeState(L"CARRYFALL");
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND))
	{
		m_JumpPos = float4::ZERO;
		m_JumpPower = 0;
		m_FSM.ChangeState(L"CARRYFALL");
	}
}
void Mario::CARRYJUMPEnd()
{
	m_JumpPos = float4::ZERO;
	m_JumpPower = 0;
}

void Mario::FALLStart()
{
	if (MARIOTYPE::SMALL == m_Type)
	{
		if (m_fAccelTime >= 6)
		{
			ChangeAnimation(L"FastJump");
		}
		else
		{
			ChangeAnimation(L"SlowJump");
		}
	}
	else
	{
		if (m_fAccelTime >= 6)
		{
			if (MARIOTYPE::RACOON == m_Type)
			{
				ChangeAnimation(L"FastFall");
			}
			else
			{
				ChangeAnimation(L"FastJump");
			}
		}
		else
		{
			ChangeAnimation(L"SlowFall");
		}
	}
}
void Mario::FALLStay() 
{
	MoveMario();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (true == SJInput::IsPress(L"X") && nullptr != m_CarryObj)
	{
		m_FSM.ChangeState(L"CARRYFALL");
	}

	if (MARIOTYPE::RACOON == LogicValue::Mario->GetType() && true == m_bTailDelay)
	{
		if (true == SJInput::IsDown(L"Z"))
		{
			m_fTailDelay = 0;
			m_bTailDelay = false;
			m_FSM.ChangeState(L"TALLJUMP");
		}
	}

	if (true == SJInput::IsDown(L"X") && MARIOTYPE::RACOON == GetType())
	{
		m_FSM.ChangeState(L"TALLATTACKFALL");
	}

	if (false == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"IDLE");
	}
}
void Mario::FALLEnd()
{
	m_JumpPos = float4::ZERO;
	m_JumpPower = 0.f;
}

void Mario::CARRYFALLStart()
{
	ChangeAnimation(L"CarryJump");
}
void Mario::CARRYFALLStay()
{
	MoveMario();
	CarryAction();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (false == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"CARRYIDLE");
	}
}
void Mario::CARRYFALLEnd()
{
	m_JumpPos = float4::ZERO;
	m_JumpPower = 0.f;
}

void Mario::FOOTStart()
{
	if (m_CurAniName != L"Sit")
	{
		if (m_fAccelTime >= 6)
		{
			ChangeAnimation(L"FastJump");
		}
		else
		{
			ChangeAnimation(L"SlowJump");
		}
	}

	SJSound::Play(L"Squish.wav");

	m_JumpPos = float4::ZERO;
	m_JumpPower = m_JumpMaxPower;

	if (0 == m_JUMPEventer.IsEventSize())
	{
		m_JUMPEventer.CreateTimeEventStay(0.3f, this, &Mario::JUMPCheckEvent);
	}

	m_JUMPEventer.Reset();
}
void Mario::FOOTStay()
{
	m_JUMPEventer.Update();

	MoveMario();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < 0)
	{
		if (m_CurAniName == L"Sit")
		{
			m_FSM.ChangeState(L"SITFALL");
		}
		else
		{
			m_FSM.ChangeState(L"FALL");
		}
	}

	if (true == PixelCheckAllTop(m_JumpPos, (int)PIXELCOLOR::GROUND))
	{
		m_JumpPos = float4::ZERO;
		m_JumpPower = 0;
		if (m_CurAniName == L"Sit")
		{
			m_FSM.ChangeState(L"SITFALL");
		}
		else
		{
			m_FSM.ChangeState(L"FALL");
		}
	}
}
void Mario::FOOTEnd()
{
	m_JumpPos = float4::ZERO;
	m_JumpPower = 0.f;
}

void Mario::CARRYFOOTStart()
{
	SJSound::Play(L"Squish.wav");

	m_JumpPos = float4::ZERO;
	m_JumpPower = m_JumpMaxPower;

	if (0 == m_JUMPEventer.IsEventSize())
	{
		m_JUMPEventer.CreateTimeEventStay(0.3f, this, &Mario::JUMPCheckEvent);
	}

	m_JUMPEventer.Reset();
}
void Mario::CARRYFOOTStay()
{
	m_JUMPEventer.Update();

	MoveMario();
	CarryAction();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < 0)
	{
		m_FSM.ChangeState(L"CARRYFALL");
	}

	if (true == PixelCheckAllTop(m_JumpPos, (int)PIXELCOLOR::GROUND))
	{
		m_JumpPos = float4::ZERO;
		m_JumpPower = 0;
		m_FSM.ChangeState(L"CARRYFALL");
	}
}
void Mario::CARRYFOOTEnd()
{

}

void Mario::SITStart()
{
	if(MARIOTYPE::SMALL == m_Type)
	{
		SJDebug::AssertMsg(L"case MARIOTYPE::SMALL:");
	}

	ChangeAnimation(L"Sit");

}
void Mario::SITStay()
{
	if (true == SJInput::IsFree(L"DOWN"))
	{
		m_FSM.ChangeState(L"IDLE");
	}

	if (true == SJInput::IsPress(L"LEFT") ||
		true == SJInput::IsPress(L"RIGHT"))
	{
		m_FSM.ChangeState(L"RUN");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"SITJUMP");
	}

	m_RunPos = m_RunPos * 0.95f;

	if (abs(m_RunPos.x) < 0.1f)
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE))
	{
		m_RunPos = 0;
	}

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"SITFALL");
	}
}
void Mario::SITEnd()
{

}

void Mario::BLOCKSITStart()
{
	if (MARIOTYPE::SMALL == m_Type)
	{
		SJDebug::AssertMsg(L"case MARIOTYPE::SMALL:");
	}

	ChangeAnimation(L"Sit");

}
void Mario::BLOCKSITStay()
{
	if (true == SJInput::IsFree(L"DOWN"))
	{
		m_FSM.ChangeState(L"BLOCKIDLE");
	}

	if (true == SJInput::IsPress(L"LEFT") ||
		true == SJInput::IsPress(L"RIGHT"))
	{
		m_FSM.ChangeState(L"BLOCKRUN");
	}

	if (true == SJInput::IsDown(L"Z"))
	{
		m_FSM.ChangeState(L"SITJUMP");
	}

	m_RunPos = m_RunPos * 0.95f;

	if (abs(m_RunPos.x) < 0.1f)
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
	{
		m_RunPos = 0;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE))
	{
		m_RunPos = 0;
	}
}
void Mario::BLOCKSITEnd()
{

}

void Mario::SITJUMPStart()
{
	SJSound::Play(L"Mario_Jump.wav");

	m_JumpPos = float4::ZERO;
	m_JumpPower = m_JumpMaxPower;

	if (0 == m_JUMPEventer.IsEventSize())
	{
		m_JUMPEventer.CreateTimeEventStay(0.3f, this, &Mario::JUMPCheckEvent);
	}

	m_JUMPEventer.Reset();
}
void Mario::SITJUMPStay()
{
	m_JUMPEventer.Update();

	MoveMario();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < 0)
	{
		m_FSM.ChangeState(L"SITFALL");
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP], m_JumpPos, (int)PIXELCOLOR::GROUND))
	{
		m_JumpPos = float4::ZERO;
		m_JumpPower = 0;
		m_FSM.ChangeState(L"SITFALL");
	}
}
void Mario::SITJUMPEnd()
{

}

void Mario::SITFALLStart()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void Mario::SITFALLStay()
{
	MoveMario();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (false == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"SIT");
	}
}
void Mario::SITFALLEnd()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}

void Mario::KICKBacktoIdle()
{
	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"FALL");
	}
	else
	{
		m_FSM.ChangeState(L"IDLE");
	}
}

void Mario::KICKBacktoBlockIdle()
{
	m_FSM.ChangeState(L"BLOCKIDLE");
}
void Mario::KICKStart()
{
	SJSound::Play(L"Kick.wav");

	ChangeAnimation(L"Kick");

	if (0 == m_KICKEventer.IsEventSize())
	{
		m_KICKEventer.CreateTimeEvent(0.2f, this, &Mario::KICKBacktoIdle);
	}

	m_KICKEventer.Reset();
}
void Mario::KICKStay()
{
	m_KICKEventer.Update();

	MoveMario();

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"KICKFALL");
	}

}
void Mario::KICKEnd()
{
	m_CarryObj = nullptr;
}

void Mario::BLOCKKICKStart()
{
	SJSound::Play(L"Kick.wav");

	ChangeAnimation(L"Kick");

	if (0 == m_BLOCKKICKEventer.IsEventSize())
	{
		m_BLOCKKICKEventer.CreateTimeEvent(0.2f, this, &Mario::KICKBacktoBlockIdle);
	}

	m_BLOCKKICKEventer.Reset();
}
void Mario::BLOCKKICKStay()
{
	m_BLOCKKICKEventer.Update();

	MoveMario();
}
void Mario::BLOCKKICKEnd()
{
	m_CarryObj = nullptr;
}

void Mario::KICKFALLStart()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void Mario::KICKFALLStay()
{
	m_KICKEventer.Update();

	MoveMario();

	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (false == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"IDLE");
	}
}
void Mario::KICKFALLEnd()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
	m_CarryObj = nullptr;
}

void Mario::CLEARFALLStart()
{
	ChangeAnimation(L"SlowJump");
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
	m_RunPos = 0;

}
void Mario::CLEARFALLStay()
{
	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (false == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"CLEARRUN");
	}
}
void Mario::CLEARFALLEnd()
{
	m_JumpPos = float4::ZERO;
	m_JumpPower = 0.f;
}

void Mario::CLEARRUNStart()
{
	SetDir(eDIR::RIGHT);
	ChangeAnimation(L"SlowRun");
}
void Mario::CLEARRUNStay()
{

	// 속도에 따른 발 빠르기 조정
	float FootSpeed = 0.03f;

	m_AniRenderer->GetCurAnimation()->SetFrameTime(FootSpeed);

	m_RunPos += float4::RIGHT * m_Power * SJTimer::FDeltaTime();

	if (m_RunPos.x > (float4::RIGHT * m_MaxPower * SJTimer::FDeltaTime()).x)
	{
		m_RunPos = float4::RIGHT * m_MaxPower * SJTimer::FDeltaTime();
	}

}

void Mario::CLEARRUNEnd()
{

}

void Mario::DEADStart()
{
	m_Col->Off();

	if (false == LogicValue::BGMPlayer.IsPlaying())
	{
		LogicValue::BGMPlayer.Stop();
	}

	SJSound::Play(L"Death.wav");
	m_Type = MARIOTYPE::SMALL;
	ChangeAnimation(L"Dead");

	m_JumpPower = 0.5f * m_JumpMaxPower;
	m_JumpPos = float4::ZERO;
	m_RunPos = 0;

	if (0 == m_DEADEventer.IsEventSize())
	{
		m_DEADEventer.CreateTimeEvent(5.f, this, &Mario::Revive);
	}

	m_DEADEventer.Reset();
}
void Mario::DEADStay()
{
	m_DEADEventer.Update();

	m_JumpPower -= 0.1f * m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}
}
void Mario::DEADEnd()
{
	m_Col->On();
}