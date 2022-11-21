#pragma once
#include "Object.h"
#include <SJFSM.h>

// 분류 :
// 용도 : 
// 설명 : 

enum class PATICLEDIR
{
    LEFTTOP,
    RIGHTTOP,
    LEFTBOTTOM,
    RIGHTBOTTOM,
};

class BlockPaticle : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    float                   m_Power;
    float                   m_JumpPower;
    float                   m_JumpMaxPower;

    float4                  m_RunPos;
    float4                  m_JumpPos;

    PATICLEDIR              m_PaticleDir;

public:
    SJFSM<BlockPaticle>     m_FSM;

public:
    void SetPaticleDir(PATICLEDIR _Dir)
    {
        m_PaticleDir = _Dir;
    }
    void ResetPaticle();

public: // constructer destructer
    BlockPaticle();
    ~BlockPaticle();

public: // delete constructer 
    BlockPaticle(const BlockPaticle& _Other) = delete;
    BlockPaticle(const BlockPaticle&& _Other) = delete;

public: // delete operator
    BlockPaticle& operator=(const BlockPaticle& _Other) = delete;
    BlockPaticle& operator=(const BlockPaticle&& _Other) = delete;

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

