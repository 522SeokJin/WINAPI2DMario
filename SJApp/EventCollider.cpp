#include "EventCollider.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Bowser.h"

// Static Var
// Static Func

// member Var

EventCollider::EventCollider()
	: m_Type(EVENTTYPE::CREATEMONSTER)
	, m_Col(nullptr)
{

}

EventCollider::~EventCollider()
{

}

// member Func

void EventCollider::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		std::vector<SJActor*>::iterator iter = m_Monster.begin();

		switch (m_Type)
		{
		case EVENTTYPE::CREATEMONSTER:
			for (; iter != m_Monster.end(); ++iter)
			{
				(*iter)->On();
			}
			break;
		case EVENTTYPE::BOWSERAPPEAR:
			LogicValue::Bowser->m_FSM.ChangeState(L"APPEAR");
			break;
		default:
			break;
		}

		Off();
	}
}

void EventCollider::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void EventCollider::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void EventCollider::Start()
{
	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::ITEM);
	m_Col->SetScale({ 100, 5000 });
	m_Col->AddStartEvent(this, &EventCollider::StartCollision);
	m_Col->AddStayEvent(this, &EventCollider::StayCollision);
	m_Col->AddEndEvent(this, &EventCollider::EndCollision);
}

void EventCollider::Update()
{

}

void EventCollider::DebugRender()
{
	CollisionView(m_Col);
}