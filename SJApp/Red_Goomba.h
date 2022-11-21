#pragma once
#include "Object.h"
#include <SJFSM.h>
#include <SJTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 

enum class GOOMBATYPE
{
    NORMAL,
    WING,
};

class SJRendererAnimation;

class Red_Goomba : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    GOOMBATYPE                          m_Type;

    float4                              m_RunPos;
    float4                              m_JumpPos;

    float                               m_Power;
    float                               m_JumpPower;
    float                               m_JumpMaxPower;
    int                                 m_JumpCount;

    SJCollision*                        m_Col;
    SJCollision*                        m_TopCol;

    SJFSM<Red_Goomba>                   m_FSM;

private:
    SJTimeEventer<Red_Goomba>           m_DEADEventer;

public:
    void SetType(GOOMBATYPE _Type)
    {
        m_Type = _Type;
    }

public: // constructer destructer
    Red_Goomba();
    ~Red_Goomba();

public: // delete constructer 
    Red_Goomba(const Red_Goomba& _Other) = delete;
    Red_Goomba(const Red_Goomba&& _Other) = delete;

public: // delete operator
    Red_Goomba& operator=(const Red_Goomba& _Other) = delete;
    Red_Goomba& operator=(const Red_Goomba&& _Other) = delete;

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override; // 돈다.
    void DebugRender() override;

public: /////////////////////////////////////// FSM
    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void JUMPStart();
    void JUMPStay();
    void JUMPEnd();

    void FALLStart();
    void FALLStay();
    void FALLEnd();

    void FLYDEADStart();
    void FLYDEADStay();
    void FLYDEADEnd();

    void DEADAnimation();
    void DEAD();
    void DEADStart();
    void DEADStay();
    void DEADEnd();
};

