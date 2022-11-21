#pragma once
#include "Object.h"
#include <SJCollision.h>

// 분류 :
// 용도 : 
// 설명 : 

enum class EVENTTYPE
{
    CREATEMONSTER,
    BOWSERAPPEAR,
};

class EventCollider : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    EVENTTYPE                   m_Type;
    SJCollision*                m_Col;
    std::vector<SJActor*>       m_Monster;


public:
    void SetCreateEvent(SJActor* _Monster)
    {
        m_Monster.push_back(_Monster);
    }

    void SetType(EVENTTYPE _Type)
    {
        m_Type = _Type;
    }

public: // constructer destructer
    EventCollider();
    ~EventCollider();

public: // delete constructer 
    EventCollider(const EventCollider& _Other) = delete;
    EventCollider(const EventCollider&& _Other) = delete;

public: // delete operator
    EventCollider& operator=(const EventCollider& _Other) = delete;
    EventCollider& operator=(const EventCollider&& _Other) = delete;

public:
    void CollisionOn()
    {
        m_Col->On();
    }
    void CollisionOff()
    {
        m_Col->Off();
    }

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

};

