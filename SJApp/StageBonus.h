#pragma once
#include "Object.h"
#include <SJCollision.h>

// 분류 :
// 용도 : 
// 설명 : 

class BonusEffect;

class StageBonus : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    SJCollision*                m_Col;

    BonusEffect*                m_Effect;

public:
    void SetEffect(BonusEffect* _Effect)
    {
        m_Effect = _Effect;
    }

public: // constructer destructer
    StageBonus();
    ~StageBonus();

public: // delete constructer 
    StageBonus(const StageBonus& _Other) = delete;
    StageBonus(const StageBonus&& _Other) = delete;

public: // delete operator
    StageBonus& operator=(const StageBonus& _Other) = delete;
    StageBonus& operator=(const StageBonus&& _Other) = delete;

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

