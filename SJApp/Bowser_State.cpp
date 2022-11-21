#include "Bowser.h"
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include "Mario.h"
#include <SJCollision.h>

void Bowser::WAITStart()
{
	ChangeAnimation(L"Idle");
}
void Bowser::WAITStay()
{

}
void Bowser::WAITEnd()
{

}

void Bowser::APPEARStart()
{
	LogicValue::BGMPlayer = SJSound::Play(L"Bowser_Battle.mp3", -1);

	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;

	m_Ratio = 0;

	m_Fire[0]->SetDir(m_Dir);
	m_Fire[0]->Off();
	m_Fire[1]->SetDir(m_Dir);
	m_Fire[1]->Off();
}
void Bowser::APPEARStay()
{
	m_Ratio += SJTimer::FDeltaTime();

	SetPos(float4::Lerp2DMax(float4{ 624, 675 }, float4{ 624, 1107 }, 1.5f * m_Ratio));

	if (float4{ 624, 1107 } == GetPos())
	{
		m_FSM.ChangeState(L"IDLE");
	}
}
void Bowser::APPEAREnd()
{
	m_Ratio = 0;
}

void Bowser::IDLEStart()
{
	m_JumpPos = float4::ZERO;
	m_JumpPower = 0.f;

	if (0 == m_JumpEventer.IsEventSize())
	{
		m_JumpEventer.CreateTimeEvent(1.f, this, &Bowser::Jump);
		m_JumpEventer.CreateTimeEvent(1.f, this, &Bowser::Jump);
		m_JumpEventer.CreateTimeEvent(1.f, this, &Bowser::Jump);
		m_JumpEventer.CreateTimeEvent(1.f, this, &Bowser::Jump);
	}
}
void Bowser::IDLEStay()
{
	m_FireEventer.Update();
	m_JumpEventer.Update();
}
void Bowser::IDLEEnd()
{

}

void Bowser::JUMPStart()
{
	m_JumpPos = float4::ZERO;
	m_JumpPower = m_JumpMaxPower;
}
void Bowser::JUMPStay()
{
	m_FireEventer.Update();
	m_JumpEventer.Update();

	m_JumpPower -= 0.5f * m_Gravity * SJTimer::FDeltaTime();

	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < 0)
	{
		m_FSM.ChangeState(L"FALL");
	}
}
void Bowser::JUMPEnd()
{

}

void Bowser::FALLStart()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void Bowser::FALLStay()
{
	m_FireEventer.Update();
	m_JumpEventer.Update();

	m_JumpPower -= 0.5f * m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM], (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM], (int)PIXELCOLOR::GROUND))
	{
		m_FSM.ChangeState(L"IDLE");
	}
}
void Bowser::FALLEnd()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}

void Bowser::ATTACKJUMPStart()
{
	m_Ratio = 0;

	m_SaveLocation = GetPos();

	float MarioPos = LogicValue::Mario->GetPos().x;
	int Sub_Num = 9999, Sub_Num_Buff;

	for (int i = 0; i < 15; i++)
	{
		if (MarioPos > m_JumpLocation[i].x)
		{
			Sub_Num_Buff = static_cast<int>(MarioPos - m_JumpLocation[i].x);
		}
		else
		{
			Sub_Num_Buff = static_cast<int>(m_JumpLocation[i].x - MarioPos);
		}

		if (Sub_Num >= Sub_Num_Buff)
		{
			Sub_Num = Sub_Num_Buff;
			m_FallPos = i;
		}
	}
}
void Bowser::ATTACKJUMPStay()
{
	m_Ratio += SJTimer::FDeltaTime();

	SetPos(float4::Lerp2DMax(m_SaveLocation, m_JumpLocation[m_FallPos], 3.f * m_Ratio));

	if (m_JumpLocation[m_FallPos] == GetPos())
	{
		m_FSM.ChangeState(L"ATTACKFALL");
	}
}
void Bowser::ATTACKJUMPEnd()
{
	m_Ratio = 0;
}

void Bowser::ATTACKFALLStart()
{
	ChangeAnimation(L"Fall");

	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;

	m_BlockCol->On();
}
void Bowser::ATTACKFALLStay()
{
	m_JumpPower -= m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -3 * m_JumpMaxPower)
	{
		m_JumpPower = -3 * m_JumpMaxPower;
	}

	if (false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::FREE) ||
		false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM], (int)PIXELCOLOR::FREE) ||
		false == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM], (int)PIXELCOLOR::FREE))
	{
		m_FSM.ChangeState(L"FIND");
	}
}
void Bowser::ATTACKFALLEnd()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
	SJSound::Play(L"Thwomp.wav");

	m_CamShakeEventer.Reset();
	m_CamShakeCheck = true;
}

void Bowser::ATTACKAFTERFALLStart()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}
void Bowser::ATTACKAFTERFALLStay()
{
	m_FireEventer.Update();
	m_JumpEventer.Update();

	m_JumpPower -= 0.5f * m_Gravity * SJTimer::FDeltaTime();
	m_JumpPos = float4::UP * m_JumpPower * SJTimer::FDeltaTime();

	if (m_JumpPower < -m_JumpMaxPower)
	{
		m_JumpPower = -m_JumpMaxPower;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM], (int)PIXELCOLOR::GROUND) ||
		true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM], (int)PIXELCOLOR::GROUND))
	{
		m_FSM.ChangeState(L"FIND");
	}
}
void Bowser::ATTACKAFTERFALLEnd()
{
	m_JumpPower = 0;
	m_JumpPos = float4::ZERO;
}

void Bowser::FINDStart()
{
	if (0 == m_FindEventer.IsEventSize())
	{
		m_FindEventer.CreateTimeEvent(0.5f, this, &Bowser::Fall);
		m_FindEventer.CreateTimeEventStart(0.3f, this, &Bowser::SitUp);
		m_FindEventer.CreateTimeEventStay(0.7f, this, &Bowser::FindLeftToRight);
		m_FindEventer.CreateTimeEventStay(0.7f, this, &Bowser::FindRightToLeft);
		m_FindEventer.CreateTimeEventStay(0.7f, this, &Bowser::BackToIdle);
	}

	m_FindEventer.Reset();
}
void Bowser::FINDStay()
{
	m_FindEventer.Update();
}
void Bowser::FINDEnd()
{

}

void Bowser::BACKTOIDLEStart() 
{
	if (0 == m_BackToIdleEventer.IsEventSize())
	{
		m_BackToIdleEventer.CreateTimeEvent(0.3f, this, &Bowser::Turn);
		m_BackToIdleEventer.CreateTimeEvent(0.1f, this, &Bowser::GoToIdle);
	}

	m_BackToIdleEventer.Reset();
}
void Bowser::BACKTOIDLEStay()
{
	m_BackToIdleEventer.Update();
}
void Bowser::BACKTOIDLEEnd()
{

}

void Bowser::DEATHStart()
{
	if (false == LogicValue::BGMPlayer.IsPlaying())
	{
		LogicValue::BGMPlayer.Stop();
	}

	SJSound::Play(L"Bowser_Falling.wav");

	if (0 == m_DeathEventer.IsEventSize())
	{
		m_DeathEventer.CreateTimeEvent(3.5f, this, &Bowser::TouchGround);
		m_DeathEventer.CreateTimeEvent(3.f, this, &Bowser::ClearSound);
		m_DeathEventer.CreateTimeEvent(7.f, this, &Bowser::OpenDoor);
	}

	m_DeathEventer.Reset();

}
void Bowser::DEATHStay()
{
	m_DeathEventer.Update();
}
void Bowser::DEATHEnd()
{

}