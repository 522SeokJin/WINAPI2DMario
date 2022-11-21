#pragma once
#include "Object.h"
#include <SJFSM.h>
#include <SJTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 

enum class PLANTCOLOR
{
    GREEN,
    RED,
};
enum class PLANTTYPE
{
    NORMAL,
    FIRE,
};
enum class PLANTFIREDIR
{
    NONE,
    UP,
    DOWN,
};

class SJRendererAnimation;

class Plant_Fire;

class Piranha_Plant : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    PLANTCOLOR                          m_Color;
    PLANTTYPE                           m_Type;
    PLANTFIREDIR                        m_FireDir;

    Plant_Fire*                         m_Fire;

    float4                              m_SaveLocation;
    float                               m_Ratio;
    float                               m_fWait;

    SJCollision*                        m_Col;

    SJFSM<Piranha_Plant>                m_FSM;

private:
    SJTimeEventer<Piranha_Plant>        m_FireEventer;
    SJTimeEventer<Piranha_Plant>        m_WaitEventer;

public:     // TimeEventer
    void Fire();
    void Idle()
    {
        m_FSM.ChangeState(L"IDLE");
    }
    void MoveDown()
    {
        m_FSM.ChangeState(L"MOVEDOWN");
    }

public:
    void SetType(PLANTTYPE _Type)
    {
        m_Type = _Type;
    }
    void SetColor(PLANTCOLOR _Color)
    {
        m_Color = _Color;
    }
    void SetFireObj(Plant_Fire* _Obj)
    {
        m_Fire = _Obj;
    }
    
    void SetFireDir();

public: // constructer destructer
    Piranha_Plant();
    ~Piranha_Plant();

public: // delete constructer 
    Piranha_Plant(const Piranha_Plant& _Other) = delete;
    Piranha_Plant(const Piranha_Plant&& _Other) = delete;

public: // delete operator
    Piranha_Plant& operator=(const Piranha_Plant& _Other) = delete;
    Piranha_Plant& operator=(const Piranha_Plant&& _Other) = delete;

public:
    void ChangeAnimation(const SJString& _Name) override;

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

    void MOVEUPStart();
    void MOVEUPStay();
    void MOVEUPEnd();

    void MOVEDOWNStart();
    void MOVEDOWNStay();
    void MOVEDOWNEnd();

    void FIREStart();
    void FIREStay();
    void FIREEnd();
};

