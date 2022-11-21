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
		void(EventTarget::* m_StartFunc)();		// �� �̺�Ʈ�� �����Ҷ� ����Ǵ� �Լ�
		void(EventTarget::* m_EndFunc)();		// �ð��� ��� ����Ǹ� ����Ǵ� �Լ�
		void(EventTarget::* m_StayFunc)();		// �ð��� ���µ��� ��� ����Ǵ� �Լ�

	public:
		// �ð��� ������� �Է��̳� �ǵ��� ���� ���¸� ��ȭ�����ִ� ����� �ϴ� Ŭ����

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
		void(EventTarget::* _StartFunc)() = nullptr,// 0.0�ʿ� ����Ǵ� �Լ��Դϴ�.
		void(EventTarget::* _EndFunc)() = nullptr  // 0 ~ 1�� ���̿� �����Ӹ��� ����Ǵ� �Լ�
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
