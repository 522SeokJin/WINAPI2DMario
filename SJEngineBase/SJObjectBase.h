#pragma once

// 분류 : 
// 용도 : 
// 설명 : 생명주기가 있거나 업데이트가 있는 클래스들에 기본적인 기능을 제공

class SJObjectBase
{
private: // Static Var
public: // Static Func
private: // member Var
    bool            m_IsOn;
    bool            m_IsDeath;
    bool            m_IsOnTask;
    bool            m_IsOffTask;

    SJObjectBase*   m_Parent;

public:
    SJObjectBase* GetParentBase()
    {
        return m_Parent;
    }
    
    void SetParentBase(SJObjectBase* _Parent)
    {
        m_Parent = _Parent;
    }

public:
    void CallOnTask()
    {
        if (true == m_IsOnTask)
        {
            OnTask();
            m_IsOnTask = false;
        }
    }

    void CallOffTask()
    {
        if (true == m_IsOffTask)
        {
            OffTask();
            m_IsOffTask = false;
        }
    }

    bool IsOn()
    {
        if (nullptr == m_Parent)
        {
            return m_IsOn && (false == m_IsDeath);
        }

        return (m_IsOn && (false == m_IsDeath)) && m_Parent->IsOn();
    }

    void On()
    {

        if (false == m_IsOn)
        {
            m_IsOnTask = true;
            //OnTask();
        }

        m_IsOn = true;
    }


    void Off()
    {
        if (true == m_IsOn)
        {
            m_IsOffTask = true;
            //OffTask();
        }

        m_IsOn = false;
    }

    bool IsDeath()
    {
        if (nullptr == m_Parent)
        {
            return m_IsDeath;
        }

        return m_IsDeath || m_Parent->IsDeath();
    }

    void Death()
    {
        m_IsDeath = true;
    }

public:
    virtual void OnTask() { };
    virtual void OffTask() { };
    virtual void DeathTask() { };

public: // constructer destructer
	SJObjectBase();
	virtual ~SJObjectBase();

public: // delete constructer 
    SJObjectBase(const SJObjectBase& _Other) = delete;
    SJObjectBase(const SJObjectBase&& _Other) = delete;

public: // delete operator
    SJObjectBase& operator=(const SJObjectBase& _Other) = delete;
    SJObjectBase& operator=(const SJObjectBase&& _Other) = delete;

public: // member Func
};

