#pragma once
#include "Object.h"
#include <SJFSM.h>

// 분류 :
// 용도 : 
// 설명 : 

class Bowser_Fire : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    float                   m_Power;
    float                   m_JumpPower;
    float                   m_JumpMaxPower;

    float4                  m_SaveMarioLocation;
    float4                  m_SaveFireLocation;

    SJCollision*            m_Col;

    float                   m_Ratio;

public:
    SJFSM<Bowser_Fire>     m_FSM;

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // constructer destructer
    Bowser_Fire();
    ~Bowser_Fire();

public: // delete constructer 
    Bowser_Fire(const Bowser_Fire& _Other) = delete;
    Bowser_Fire(const Bowser_Fire&& _Other) = delete;

public: // delete operator
    Bowser_Fire& operator=(const Bowser_Fire& _Other) = delete;
    Bowser_Fire& operator=(const Bowser_Fire&& _Other) = delete;

public:
    void Reset();

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

    void MOVESTRAIGHTStart();
    void MOVESTRAIGHTStay();
    void MOVESTRAIGHTEnd();
};

