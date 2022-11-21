#pragma once
#include <vector>
#include "SJTimer.h"
#include "SJDebug.h"

// 분류 : 
// 용도 : n초 후 n의 함수를 실행하는 클래스
// 설명 : 

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
		float				m_Time;				// 1초동안
		float				m_MaxTime;
		EventTarget*		m_Obj;
		void(EventTarget::* m_StartFunc)();		// 이 이벤트가 시작할때 실행되는 함수
		void(EventTarget::* m_EndFunc)();		// 시간이 모두 종료되면 실행되는 함수
		void(EventTarget::* m_StayFunc)();		// 시간이 가는도중 계속 실행되는 함수

	public:
		bool Update()	// bool 값 = TimeEvent가 끝났는지 판별하는 논리값, 끝나면 true
		{
			if (m_Time >= m_MaxTime) // TimeEvent 시작, m_Time == m_MaxTime 인 상태에서 시작함
			{
				m_Time -= SJTimer::FDeltaTime();
				if (nullptr == m_StartFunc)
				{
					return false;
				}

				// 함수포인터의 실행
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

				// 함수포인터의 실행
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
	bool m_Loop;	// 다시 반복

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
		, void(EventTarget::* _EndFunc)()					// 1초가 지난다음 실행하는 함수
		, void(EventTarget::* _StartFunc)()	= nullptr		// 0.0초에 실행되는 함수
		, void(EventTarget::* _StayFunc)()	= nullptr		// 0 ~ 1초 사이에 프레임마다 실행되는 함수
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
		, void(EventTarget::* _StayFunc)()					// 0 ~ 1초 사이에 프레임마다 실행되는 함수
		, void(EventTarget::* _EndFunc)() = nullptr			// 1초가 지난다음 실행하는 함수
		, void(EventTarget::* _StartFunc)() = nullptr		// 0.0초에 실행되는 함수
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
		, void(EventTarget::* _StartFunc)() 				// 0.0초에 실행되는 함수
		, void(EventTarget::* _EndFunc)() = nullptr			// 1초가 지난다음 실행하는 함수
		, void(EventTarget::* _StayFunc)() = nullptr		// 0 ~ 1초 사이에 프레임마다 실행되는 함수
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

			// 처음부터 다시 돈다.
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