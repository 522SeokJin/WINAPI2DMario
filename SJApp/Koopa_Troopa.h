#pragma once
#include "Object.h"
#include <SJFSM.h>
#include <SJTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 

enum class TROOPATYPE
{
    NORMAL,
    WING,
};

class SJRendererAnimation;

class Koopa_Troopa : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    TROOPATYPE                          m_Type;

    float4                              m_RunPos;
    float4                              m_JumpPos;

    float                               m_Power;
    float                               m_KickPower;
    float                               m_JumpPower;
    float                               m_JumpMaxPower;

    SJCollision*                        m_Col;
    SJCollision*                        m_TopCol;
    SJCollision*                        m_EventCol;
    SJCollision*                        m_ProjectileCol;

    SJFSM<Koopa_Troopa>                 m_FSM;
private:
    float                               m_ReviveTime;
    SJTimeEventer<Koopa_Troopa>         m_ReviveEventer;

public:
    SJFSM<Koopa_Troopa>& GetFSM() 
    {
        return m_FSM;
    }
    SJCollision* GetEventCol()
    {
        return m_EventCol;
    }
    void SetType(TROOPATYPE _Type)
    {
        m_Type = _Type;
    }

public: // constructer destructer
    Koopa_Troopa();
    ~Koopa_Troopa();

public: // delete constructer 
    Koopa_Troopa(const Koopa_Troopa& _Other) = delete;
    Koopa_Troopa(const Koopa_Troopa&& _Other) = delete;

public: // delete operator
    Koopa_Troopa& operator=(const Koopa_Troopa& _Other) = delete;
    Koopa_Troopa& operator=(const Koopa_Troopa&& _Other) = delete;

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override; // 돈다.
    void DebugRender() override;

public:
    void MoveTroopa();
    void ReviveTimeEvent();
    void ReviveChangeState();

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

    void HIDEStart();
    void HIDEStay();
    void HIDEEnd();

    void HIDEFALLStart();
    void HIDEFALLStay();
    void HIDEFALLEnd();

    void KICKEDStart();
    void KICKEDStay();
    void KICKEDEnd();

    void KICKEDFALLStart();
    void KICKEDFALLStay();
    void KICKEDFALLEnd();

    void DEADStart();
    void DEADStay();
    void DEADEnd();
};

