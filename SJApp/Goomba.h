#pragma once
#include "Object.h"
#include <SJFSM.h>
#include <SJTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 

class SJRendererAnimation;

class Goomba : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    float4                              m_RunPos;
    float4                              m_JumpPos;

    float                               m_Power;
    float                               m_JumpPower;
    float                               m_JumpMaxPower;

    SJCollision*                        m_Col;
    SJCollision*                        m_TopCol;

    SJFSM<Goomba>                       m_FSM;

private:
    SJTimeEventer<Goomba>               m_DEADEventer;

public:
    
public: // constructer destructer
	Goomba();
	~Goomba();

public: // delete constructer 
    Goomba(const Goomba& _Other) = delete;
    Goomba(const Goomba&& _Other) = delete;

public: // delete operator
    Goomba& operator=(const Goomba& _Other) = delete;
    Goomba& operator=(const Goomba&& _Other) = delete;

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override; // 돈다.
    void DebugRender() override;

public: /////////////////////////////////////// FSM
    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void FLYDEADStart();
    void FLYDEADStay();
    void FLYDEADEnd();

    void DEADAnimation();
    void DEAD();
    void DEADStart();
    void DEADStay();
    void DEADEnd();
};

