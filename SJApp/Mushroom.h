#pragma once
#include "Object.h"
#include <SJCollision.h>
#include <SJFSM.h>

// 분류 :
// 용도 : 
// 설명 : 

class Mushroom : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    float               m_Power;
    float               m_JumpPower;
    float               m_JumpMaxPower;

    float4              m_RunPos;
    float4              m_JumpPos;

    SJCollision*        m_Col;

public:
    SJFSM<Mushroom>     m_FSM;

public: // constructer destructer
    Mushroom();
    ~Mushroom();

public: // delete constructer 
    Mushroom(const Mushroom& _Other) = delete;
    Mushroom(const Mushroom&& _Other) = delete;

public: // delete operator
    Mushroom& operator=(const Mushroom& _Other) = delete;
    Mushroom& operator=(const Mushroom&& _Other) = delete;

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

public: /////////////////////////////////////// FSM
    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void MOVEStart();
    void MOVEStay();
    void MOVEEnd();

    void MOVEFALLStart();
    void MOVEFALLStay();
    void MOVEFALLEnd();
};

