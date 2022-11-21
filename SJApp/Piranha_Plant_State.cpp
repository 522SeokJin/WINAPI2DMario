#include "Piranha_Plant.h"
#include "LogicValue.h"
#include "Mario.h"
#include "Plant_Fire.h"

void Piranha_Plant::IDLEStart()
{
	ChangeAnimation(L"Idle");
}
void Piranha_Plant::IDLEStay()
{
	ChangeAnimation(L"Idle");

	// 일정 사거리 안으로 들어온 경우
	if (300.f > abs(GetPos().x - LogicValue::Mario->GetPos().x))
	{
		m_FSM.ChangeState(L"MOVEUP");
	}
}
void Piranha_Plant::IDLEEnd()
{

}

void Piranha_Plant::MOVEUPStart()
{
	m_SaveLocation = GetPos();
	m_Ratio = 0;
	m_fWait = 0;
}
void Piranha_Plant::MOVEUPStay()
{
	m_Ratio += 2 * SJTimer::FDeltaTime();

	SetPos(float4::Lerp2DMax(m_SaveLocation, float4{m_SaveLocation.x, m_SaveLocation.y - GetSize().y - 20}, m_Ratio));

	if (GetPos() == float4{ m_SaveLocation.x, m_SaveLocation.y - GetSize().y - 20 })
	{
		if (PLANTTYPE::FIRE == m_Type)
		{
			m_FSM.ChangeState(L"FIRE");
		}
		else
		{
			m_fWait += SJTimer::FDeltaTime();

			if (m_fWait > 2.f)
			{
				m_FSM.ChangeState(L"MOVEDOWN");
			}
		}
	}
}
void Piranha_Plant::MOVEUPEnd()
{

}

void Piranha_Plant::FIREStart()
{
	ChangeAnimation(L"Idle");

	m_Fire->m_FSM.ChangeState(L"IDLE");

	if (0 == m_FireEventer.IsEventSize())
	{
		m_FireEventer.CreateTimeEvent(2.f, this, &Piranha_Plant::Fire);
		m_FireEventer.CreateTimeEvent(2.f, this, &Piranha_Plant::MoveDown);
	}

	m_FireEventer.Reset();
}
void Piranha_Plant::FIREStay()
{
	ChangeAnimation(L"Idle");
	m_FireEventer.Update();
}
void Piranha_Plant::FIREEnd()
{

}

void Piranha_Plant::MOVEDOWNStart()
{
	m_SaveLocation = GetPos();
	m_Ratio = 0;

	if (0 == m_WaitEventer.IsEventSize())
	{
		m_WaitEventer.CreateTimeEvent(3.f, this, &Piranha_Plant::Idle);
	}
	m_WaitEventer.Reset();
}
void Piranha_Plant::MOVEDOWNStay()
{
	m_WaitEventer.Update();

	m_Ratio += 2 * SJTimer::FDeltaTime();
	SetPos(float4::Lerp2DMax(m_SaveLocation, float4{ m_SaveLocation.x, m_SaveLocation.y + GetSize().y + 20 }, m_Ratio));

}
void Piranha_Plant::MOVEDOWNEnd()
{

}

