#pragma once
#include "Object.h"
#include <SJFSM.h>

// 분류 :
// 용도 : 
// 설명 : 

class Plant_Fire : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    float                   m_Power;
    float                   m_Radian;
    SJCollision*            m_Col;

public:
    SJFSM<Plant_Fire>       m_FSM;

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // constructer destructer
    Plant_Fire();
    ~Plant_Fire();

public: // delete constructer 
    Plant_Fire(const Plant_Fire& _Other) = delete;
    Plant_Fire(const Plant_Fire&& _Other) = delete;

public: // delete operator
    Plant_Fire& operator=(const Plant_Fire& _Other) = delete;
    Plant_Fire& operator=(const Plant_Fire&& _Other) = delete;

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
};

