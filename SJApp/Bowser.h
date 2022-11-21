#pragma once
#include "Object.h"
#include <SJFSM.h>
#include <SJTimeEventer.h>
#include "Bowser_Fire.h"

// 분류 :
// 용도 : 
// 설명 : 

class SJRendererAnimation;

class Bowser : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    float4                              m_RunPos;
    float4                              m_JumpPos;
    float                               m_JumpPower;
    float                               m_JumpMaxPower;

    float4                              m_SaveLocation;
    float4                              m_JumpLocation[15];
    int                                 m_FallPos;

    float                               m_Ratio;

    SJCollision*                        m_Col;
    SJCollision*                        m_BlockCol;

    int                                 m_FireCount;

public:
    SJFSM<Bowser>                       m_FSM;
    Bowser_Fire*                        m_Fire[2];

public:
    SJTimeEventer<Bowser>               m_JumpEventer;
    SJTimeEventer<Bowser>               m_FireEventer;
    SJTimeEventer<Bowser>               m_FindEventer;
    SJTimeEventer<Bowser>               m_BackToIdleEventer;

public:
    SJTimeEventer<Bowser>               m_CamShakeEventer;
    float                               m_CamShakeTime;
    bool                                m_CamShakeCheck;

public:
    SJTimeEventer<Bowser>               m_DeathEventer;
    
public: // TimeEventer
    void FireEvent()
    {
        ChangeAnimation(L"Fire");
    }
    void BackToIdleAnim();
    void GoToIdle();
    void BackToIdle()
    {
        m_FSM.ChangeState(L"BACKTOIDLE");
    }
    void ReadyToJump()
    {
        ChangeAnimation(L"Sit");
    }
    void JumpToMario()
    {
        m_FSM.ChangeState(L"ATTACKJUMP");
    }
    void Jump()
    {
        m_FSM.ChangeState(L"JUMP");
    }
    void SitUp()
    {
        ChangeAnimation(L"SitUp");
    }
    void Fall()
    {
        ChangeAnimation(L"Fall");
    }
    void Turn()
    {
        ChangeAnimation(L"TurnToMario");
    }
    void Stop()
    {
        ChangeAnimation(L"Idle");
    }
    void FindLeftToRight();
    void FindRightToLeft();

    void CamShakeStart();
    void CamShakeStay();
    void CamShakeEnd();

public: // Death TimeEvent
    void TouchGround();
    void ClearSound();
    void OpenDoor();

public:
    void Reset();

public: // constructer destructer
    Bowser();
    ~Bowser();

public: // delete constructer 
    Bowser(const Bowser& _Other) = delete;
    Bowser(const Bowser&& _Other) = delete;

public: // delete operator
    Bowser& operator=(const Bowser& _Other) = delete;
    Bowser& operator=(const Bowser&& _Other) = delete;

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override; // 돈다.
    void DebugRender() override;

public: /////////////////////////////////////// FSM
    void WAITStart();
    void WAITStay();
    void WAITEnd();

    void APPEARStart();
    void APPEARStay();
    void APPEAREnd();

    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();
    
    void JUMPStart();
    void JUMPStay();
    void JUMPEnd();

    void FALLStart();
    void FALLStay();
    void FALLEnd();

    void ATTACKJUMPStart();
    void ATTACKJUMPStay();
    void ATTACKJUMPEnd();

    void ATTACKFALLStart();
    void ATTACKFALLStay();
    void ATTACKFALLEnd();

    void ATTACKAFTERFALLStart();
    void ATTACKAFTERFALLStay();
    void ATTACKAFTERFALLEnd();

    void FINDStart();
    void FINDStay();
    void FINDEnd();

    void BACKTOIDLEStart();
    void BACKTOIDLEStay();
    void BACKTOIDLEEnd();

    void DEATHStart();
    void DEATHStay();
    void DEATHEnd();
};

