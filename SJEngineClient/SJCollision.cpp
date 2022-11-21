#include "SJCollision.h"
#include "SJActor.h"

// Static Var
// Static Func

// member Var

SJCollision::SJCollision()
	: m_Type(COLTYPE::RECT)
	, m_Order(0)
	, m_Actor(nullptr)
	, m_PivotPos(float4::ZERO)
	, m_Data()
	, m_CheckData(-1)
{
	m_Data.Size = { 1, 1 };
}

SJCollision::~SJCollision()
{
	for (size_t i = 0; i < StartEvent.size(); i++)
	{
		delete StartEvent[i];
	}
	for (size_t i = 0; i < StayEvent.size(); i++)
	{
		delete StayEvent[i];
	}
	for (size_t i = 0; i < EndEvent.size(); i++)
	{
		delete EndEvent[i];
	}
}

// member Func

void SJCollision::CollisionDataUpdate()
{
	// ķ�� �ƹ��� �ǹ̵� ����.
	// ����浹ü�� ��ġ�� 0,0
	// ������������ ����ؼ� ��ġ�� �������ش�.

	m_Data.Pos = GetActor()->GetPos() + m_PivotPos;
}


void SJCollision::CollisionCheck(SJCollision* _Other)
{
	COLTYPE ThisColType = m_Type;
	COLTYPE OtherColType = _Other->m_Type;


	if (true == Collision2DCheck::ColFunc[(int)ThisColType][(int)OtherColType](m_Data, _Other->m_Data))
	{
		if (m_ColSet.end() == m_ColSet.find(_Other))
		{
			// �浹 ����
			UpdateStartEvent(this, _Other);
			_Other->UpdateStartEvent(_Other, this);
		}
		else
		{
			// �浹 ��
			UpdateStayEvent(this, _Other);
			_Other->UpdateStayEvent(_Other, this);
		}
	}
	else
	{
		if (m_ColSet.end() != m_ColSet.find(_Other))
		{
			UpdateEndEvent(this, _Other);
			_Other->UpdateEndEvent(_Other, this);
		}
	}
}

void SJCollision::ReleaseUpdate()
{
	std::set<SJCollision*>::iterator iter = m_ColSet.begin();

	for (; iter != m_ColSet.end();)
	{
		for (size_t i = 0; i < EndEvent.size(); i++)
		{
			EndEvent[i]->CallBack(this, (*iter));
		}

		(*iter)->UpdateEndEvent(*iter, this);
		iter = m_ColSet.erase(iter);
	}
}

void SJCollision::DeathTask()
{
	ReleaseUpdate();
}

void SJCollision::OffTask()
{
	ReleaseUpdate();
}