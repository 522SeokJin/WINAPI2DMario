#pragma once
#include <vector>
#include "SJTimer.h"
#include "SJDebug.h"

// �з� : 
// �뵵 : n�� �� n�� �Լ��� �����ϴ� Ŭ����
// ���� : 

//class EventTarget
//{
//
//};

template<typename EventTarget>
class SJTimeEventer
{
public:
	class TimeEvent
	{
	public:
		float				m_Time;				// 1�ʵ���
		float				m_MaxTime;
		EventTarget*		m_Obj;
		void(EventTarget::* m_StartFunc)();		// �� �̺�Ʈ�� �����Ҷ� ����Ǵ� �Լ�
		void(EventTarget::* m_EndFunc)();		// �ð��� ��� ����Ǹ� ����Ǵ� �Լ�
		void(EventTarget::* m_StayFunc)();		// �ð��� ���µ��� ��� ����Ǵ� �Լ�

	public:
		bool Update()	// bool �� = TimeEvent�� �������� �Ǻ��ϴ� ����, ������ true
		{
			if (m_Time >= m_MaxTime) // TimeEvent ����, m_Time == m_MaxTime �� ���¿��� ������
			{
				m_Time -= SJTimer::FDeltaTime();
				if (nullptr == m_StartFunc)
				{
					return false;
				}

				// �Լ��������� ����
				(m_Obj->*m_StartFunc)();
				return false;
			}

			m_Time -= SJTimer::FDeltaTime();

			if (0.0 <= m_Time)
			{
				if (nullptr == m_StayFunc)
				{
					return false;
				}

				// �Լ��������� ����
				(m_Obj->*m_StayFunc)();

				return false;
			}

			m_Time = m_MaxTime;

			if (nullptr == m_EndFunc)
			{
				return true;
			}

			(m_Obj->*m_EndFunc)();
			return true;
		}

	public:
		void Reset()
		{
			m_Time = m_MaxTime;
		}

		TimeEvent()
			: m_Time(0.0f)
			, m_MaxTime(0.0f)
			, m_Obj(nullptr)
			, m_StartFunc()
			, m_EndFunc()
			, m_StayFunc()
		{

		}
		~TimeEvent()
		{

		}
	};

private:
	int m_CurEvent;
	std::vector<TimeEvent> m_Events;
	bool m_Loop;	// �ٽ� �ݺ�

public:
	size_t IsEventSize()
	{
		return m_Events.size();
	}

public:
	void LoopOn()
	{
		m_Loop = true;
	}

	bool IsEnd()
	{
		return m_CurEvent >= m_Events.size();
	}

	void CreateTimeEvent(float _Time, EventTarget* _Obj
		, void(EventTarget::* _EndFunc)()					// 1�ʰ� �������� �����ϴ� �Լ�
		, void(EventTarget::* _StartFunc)()	= nullptr		// 0.0�ʿ� ����Ǵ� �Լ�
		, void(EventTarget::* _StayFunc)()	= nullptr		// 0 ~ 1�� ���̿� �����Ӹ��� ����Ǵ� �Լ�
	)
	{
		m_Events.resize(m_Events.size() + 1);
		m_Events[m_Events.size() - 1].m_StartFunc = _StartFunc;
		m_Events[m_Events.size() - 1].m_StayFunc = _StayFunc;
		m_Events[m_Events.size() - 1].m_EndFunc = _EndFunc;
		m_Events[m_Events.size() - 1].m_Time = _Time;
		m_Events[m_Events.size() - 1].m_MaxTime = _Time;
		m_Events[m_Events.size() - 1].m_Obj = _Obj;
	}

	void CreateTimeEventStay(float _Time, EventTarget* _Obj
		, void(EventTarget::* _StayFunc)()					// 0 ~ 1�� ���̿� �����Ӹ��� ����Ǵ� �Լ�
		, void(EventTarget::* _EndFunc)() = nullptr			// 1�ʰ� �������� �����ϴ� �Լ�
		, void(EventTarget::* _StartFunc)() = nullptr		// 0.0�ʿ� ����Ǵ� �Լ�
	)
	{
		m_Events.resize(m_Events.size() + 1);
		m_Events[m_Events.size() - 1].m_StartFunc = _StartFunc;
		m_Events[m_Events.size() - 1].m_StayFunc = _StayFunc;
		m_Events[m_Events.size() - 1].m_EndFunc = _EndFunc;
		m_Events[m_Events.size() - 1].m_Time = _Time;
		m_Events[m_Events.size() - 1].m_MaxTime = _Time;
		m_Events[m_Events.size() - 1].m_Obj = _Obj;
	}

	void CreateTimeEventStart(float _Time, EventTarget* _Obj
		, void(EventTarget::* _StartFunc)() 				// 0.0�ʿ� ����Ǵ� �Լ�
		, void(EventTarget::* _EndFunc)() = nullptr			// 1�ʰ� �������� �����ϴ� �Լ�
		, void(EventTarget::* _StayFunc)() = nullptr		// 0 ~ 1�� ���̿� �����Ӹ��� ����Ǵ� �Լ�
	)
	{
		m_Events.resize(m_Events.size() + 1);
		m_Events[m_Events.size() - 1].m_StartFunc = _StartFunc;
		m_Events[m_Events.size() - 1].m_StayFunc = _StayFunc;
		m_Events[m_Events.size() - 1].m_EndFunc = _EndFunc;
		m_Events[m_Events.size() - 1].m_Time = _Time;
		m_Events[m_Events.size() - 1].m_MaxTime = _Time;
		m_Events[m_Events.size() - 1].m_Obj = _Obj;
	}

	void Reset()
	{
		m_CurEvent = 0;

		for (size_t i = 0; i < m_Events.size(); i++)
		{
			m_Events[i].Reset();
		}
	}

	void Update()
	{
		if (0 == m_Events.size())
		{
			//SJDebug::AssertMsg("if (0 == m_Events.size())");

			return;
		}

		if (m_Events.size() <= m_CurEvent)
		{
			if (false == m_Loop)
			{
				return;
			}

			// ó������ �ٽ� ����.
			m_CurEvent = 0;
		}

		if (true == m_Events[m_CurEvent].Update())
		{
			++m_CurEvent;
		}
	}

public:
	float GetTime()
	{
		return m_Events[m_CurEvent].m_Time;
	}

	float GetMaxTime()
	{
		return m_Events[m_CurEvent].m_MaxTime;;
	}

public:
	SJTimeEventer()
		: m_CurEvent(0)
		, m_Loop(false)
	{

	}
	~SJTimeEventer()
	{

	}
};