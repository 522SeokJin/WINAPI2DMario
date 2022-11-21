#pragma once

#include <SJObjectBase.h>
#include <SJMath.h>
#include <set>
#include <vector>

// 분류 :
// 용도 : 
// 설명 : 

class SJActor;

class SJCollision : public SJObjectBase
{
private: // Static Var
public: // Static Func
private: // member Var
    COLTYPE         m_Type;
    int             m_Order;
    // 자신을 가진 액터를 안다.
    SJActor*        m_Actor;
    float4          m_PivotPos;
    Col2DData       m_Data;
    int             m_CheckData;

    std::set<SJCollision*> m_ColSet;

public:
    void SetCheckData(int _CheckData)
    {
        m_CheckData = _CheckData;
    }

    int GetCheckData()
    {
        return m_CheckData;
    }

public: // constructer destructer
	SJCollision();
	~SJCollision();

public:
    void SetScale(float4 _Scale)
    {
        m_Data.Size = _Scale;
    }

    void SetOrder(int _Order)
    {
        m_Order = _Order;
    }

    int GetOrder()
    {
        return m_Order;
    }

    void SetActor(SJActor* _Actor)
    {
        
        m_Actor = _Actor;
    }

    SJActor* GetActor()
    {
        return m_Actor;
    }

    void SetPivotPos(float4 _PivotPos)
    {
        m_PivotPos = _PivotPos;
    }

    float4 GetPivotPos()
    {
        return m_PivotPos;
    }

    void SetCol2DData(Col2DData _Col2DData)
    {
        m_Data = _Col2DData;
    }

    Col2DData GetCol2DData()
    {
        return m_Data;
    }

public: // delete constructer 
    SJCollision(const SJCollision& _Other) = delete;
    SJCollision(const SJCollision&& _Other) = delete;

public: // delete operator
    SJCollision& operator=(const SJCollision& _Other) = delete;
    SJCollision& operator=(const SJCollision&& _Other) = delete;

public: // member Func

    void CollisionDataUpdate();
    void CollisionCheck(SJCollision* _Other);

    void ReleaseUpdate();

    void DeathTask() override;
    void OffTask() override;

private:
    class EventBase
    {
    public:
        virtual void CallBack(SJCollision* _This, SJCollision* _Other) {}
    };

    template<typename EventType>
    class EventBaseTemplate : public EventBase
    {
    public:
        EventType* m_Obj;
        void(EventType::* m_StartFunc)(SJCollision* _This, SJCollision* _Other);

    public:
        void CallBack(SJCollision* _This, SJCollision* _Other) override
        {
            (m_Obj->*m_StartFunc)(_This, _Other);
        }

    public:
        EventBaseTemplate(EventType* _Obj, void(EventType::* _StartFunc)(SJCollision* _This, SJCollision* _Other))
            : m_Obj(_Obj)
            , m_StartFunc(_StartFunc)
        {

        }
    };

private:
    std::vector<EventBase*> StartEvent;
    std::vector<EventBase*> StayEvent;
    std::vector<EventBase*> EndEvent;

public:
    template<typename Target>
    void AddStartEvent(Target* _Obj, void(Target::* _StartFunc)(SJCollision* _This, SJCollision* _Other))
    {
        StartEvent.push_back(new EventBaseTemplate<Target>(_Obj, _StartFunc));
    }

    void UpdateStartEvent(SJCollision* _This, SJCollision* _Other)
    {
        for (size_t i = 0; i < StartEvent.size(); i++)
        {
            m_ColSet.insert(_Other);
            StartEvent[i]->CallBack(_This, _Other);
        }
    }

    template<typename Target>
    void AddStayEvent(Target* _Obj, void(Target::* _StartFunc)(SJCollision* _This, SJCollision* _Other))
    {
        StayEvent.push_back(new EventBaseTemplate<Target>(_Obj, _StartFunc));
    }

    void UpdateStayEvent(SJCollision* _This, SJCollision* _Other)
    {
        for (size_t i = 0; i < StayEvent.size(); i++)
        {
            StayEvent[i]->CallBack(_This, _Other);
        }
    }

    template<typename Target>
    void AddEndEvent(Target* _Obj, void(Target::* _StartFunc)(SJCollision* _This, SJCollision* _Other))
    {
        EndEvent.push_back(new EventBaseTemplate<Target>(_Obj, _StartFunc));
    }

    void UpdateEndEvent(SJCollision* _This, SJCollision* _Other)
    {
        for (size_t i = 0; i < EndEvent.size(); i++)
        {
            EndEvent[i]->CallBack(_This, _Other);
        }

        m_ColSet.erase(_Other);
    }
};

