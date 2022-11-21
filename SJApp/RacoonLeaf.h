#pragma once
#include "Object.h"
#include <SJCollision.h>
#include <SJFSM.h>
#include <SJTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 

class RacoonLeaf : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    float                           m_Power;
    float                           m_MaxPower;
    float                           m_JumpPower;
    float                           m_JumpMaxPower;

    float4                          m_RunPos;
    float4                          m_JumpPos;

    eDIR                            m_PrevDir;

    SJCollision*                    m_Col;

public:
    SJFSM<RacoonLeaf>               m_FSM;

private:
    SJTimeEventer<RacoonLeaf>       m_FALLEventer;

public: // constructer destructer
    RacoonLeaf();
    ~RacoonLeaf();

public: // delete constructer 
    RacoonLeaf(const RacoonLeaf& _Other) = delete;
    RacoonLeaf(const RacoonLeaf&& _Other) = delete;

public: // delete operator
    RacoonLeaf& operator=(const RacoonLeaf& _Other) = delete;
    RacoonLeaf& operator=(const RacoonLeaf&& _Other) = delete;

public:
    void CollisionOn()
    {
        m_Col->On();
    }
    void CollisionOff()
    {
        m_Col->Off();
    }
    
    void ChangeIDLEState();
    void ChangeFALLState();

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

    void JUMPStart();
    void JUMPStay();
    void JUMPEnd();

    void FALLLEFTStart();
    void FALLLEFTStay();
    void FALLLEFTEnd();

    void FALLRIGHTStart();
    void FALLRIGHTStay();
    void FALLRIGHTEnd();
};

