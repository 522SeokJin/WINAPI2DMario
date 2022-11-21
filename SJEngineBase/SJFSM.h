#pragma once
#include <map>
#include "SJTimer.h"
#include "SJString.h"
#include "SJDebug.h"

//class EventTarget
//{
//
//};

template<typename EventTarget>
class SJFSM
{
public:
	class State
	{
	public:
		EventTarget* m_Obj;
		void(EventTarget::* m_StartFunc)();		// 이 이벤트가 시작할때 실행되는 함수
		void(EventTarget::* m_EndFunc)();		// 시간이 모두 종료되면 실행되는 함수
		void(EventTarget::* m_StayFunc)();		// 시간이 가는도중 계속 실행되는 함수

	public:
		// 시간에 관계없이 입력이나 의도에 의해 상태를 변화시켜주는 기능을 하는 클래스

		void Start()
		{
			if (nullptr == m_StartFunc)
			{
				return;
			}

			(m_Obj->*m_StartFunc)();
		}

		void End()
		{
			if (nullptr == m_EndFunc)
			{
				return;
			}

			(m_Obj->*m_EndFunc)();
		}

		void Update()
		{
			if (nullptr == m_StayFunc)
			{
				SJDebug::AssertMsg(L"if (nullptr == m_StayFunc)");
			}

			(m_Obj->*m_StayFunc)();
		}

	public:
		State()
			: m_Obj(nullptr)
			, m_StartFunc(nullptr)
			, m_EndFunc(nullptr)
			, m_StayFunc(nullptr)

		{

		}
		~State()
		{

		}
	};

private:
	std::map<SJString, State>	m_State;
	State*						m_CurState;
	SJString					m_CurStateName;

public:
	void CreateState(const SJString& _StateName, EventTarget* _Obj,
		void(EventTarget::* _StayFunc)(),
		void(EventTarget::* _StartFunc)() = nullptr,// 0.0초에 실행되는 함수입니다.
		void(EventTarget::* _EndFunc)() = nullptr  // 0 ~ 1초 사이에 프레임마다 실행되는 함수
	)
	{
		if (m_State.end() != m_State.find(_StateName))
		{
			SJDebug::AssertMsg("if (m_State.end() != m_State.find(_StateName))");
		}

		m_State[_StateName].m_Obj = _Obj;
		m_State[_StateName].m_StartFunc = _StartFunc;
		m_State[_StateName].m_StayFunc = _StayFunc;
		m_State[_StateName].m_EndFunc = _EndFunc;
	}

	void ChangeState(const SJString& _StateName)
	{
		
		if (_StateName == m_CurStateName)
		{
			return;
		}

		if (m_State.end() == m_State.find(_StateName))
		{
			SJDebug::AssertMsg(L"if (m_State.end() == m_State.find(_StateName))");
		}

		if (nullptr != m_CurState)
		{
			m_CurState->End();
		}
		m_CurState = &m_State[_StateName];
		m_CurStateName = _StateName;
		m_CurState->Start();
	}

	State GetCurState()
	{
		return *m_CurState;
	}
	State GetState(const SJString& _Name)
	{
		typename std::map<SJString, State>::iterator iter = m_State.find(_Name);

		if (m_State.end() == iter)
		{
			SJDebug::AssertMsg(L"if (m_State.end() == iter)");
		}

		return iter->second;
	}

	SJString GetCurStateName()
	{
		return m_CurStateName;
	}

	void Update()
	{
		if (nullptr == m_CurState)
		{
			SJDebug::AssertMsg(L"if (nullptr == m_CurState)");
		}
		m_CurState->Update();
	}

public:
	SJFSM()
		: m_CurState(nullptr)
	{

	}
	~SJFSM()
	{
		m_State.clear();
	}
};
