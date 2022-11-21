#pragma once
#include "Object.h"
#include <SJFSM.h>
#include <SJTimeEventer.h>
#include <SJSound.h>
#include "LogicValue.h"
#include <SJRendererAnimation.h>
#include <SJCollision.h>

// 분류 :
// 용도 : 
// 설명 : 

class Koopa_Troopa;
class Mario : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    MARIOTYPE               m_Type;
public:
    float4                  m_RunPos;
    float4                  m_JumpPos;
private:
    float                   m_Power;
    float                   m_MaxPower;
    float                   m_AccelMaxPower;
    float                   m_fAccelTime;

    float                   m_JumpPower;
    float                   m_JumpMaxPower;

protected:
    SJCollision*            m_Col;
    SJCollision*            m_TailCol;
    bool                    m_bTailDelay;
    float                   m_fTailDelay;

public:
    bool                    m_LeftKeyLock;
    bool                    m_RightKeyLock;
public:
    SJFSM<Mario>            m_FSM;
    class Koopa_Troopa*     m_CarryObj;
    int                     m_OverlapCol;

public:
    bool                    m_bNoDamage;

private:
    SJTimeEventer<Mario>    m_CollisionEventer;
    SJTimeEventer<Mario>    m_AlphaBlendEventer;

    SJTimeEventer<Mario>    m_JUMPEventer;
    SJTimeEventer<Mario>    m_KICKEventer;
    SJTimeEventer<Mario>    m_BLOCKKICKEventer;
    SJTimeEventer<Mario>    m_POWERUPEventer;
    SJTimeEventer<Mario>    m_POWERDOWNEventer;
    SJTimeEventer<Mario>    m_RACOONUPEventer;
    SJTimeEventer<Mario>    m_RACOONDOWNEventer;
    SJTimeEventer<Mario>    m_DEADEventer;

    float4                  m_SaveMovePos;

private:
    SoundPlayer             m_SkidSound;
    SoundPlayer             m_FullAccelSound;
    bool                    m_bAccel;

public:
    MARIOTYPE& GetType()
    {
        return m_Type;
    }

    bool IsCarry()
    {
        if (nullptr == m_CarryObj)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void Revive();

public: // constructer destructer
    Mario();
    ~Mario();

public: // delete constructer 
    Mario(const Mario& _Other) = delete;
    Mario(const Mario&& _Other) = delete;

public: // delete operator
    Mario& operator=(const Mario& _Other) = delete;
    Mario& operator=(const Mario&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override; // 돈다
    void DebugRender() override;

    void SetAnimation();    // CreateAnimation
    void ChangeAnimation(const SJString& _Name) override;

public:
    void SetKeyMoveDir();
    void MoveMario();
    void CarryAction();
    void SetCollision();
    void SetAccelGauge();
    void AccelSound();
    void CalDelay();

    void CameraMove();  // 가장자리 카메라 고정
    void XCamera(float4& _CamPos);
    void YCamera(float4& _CamPos);

    SJString MARIOTYPEtoString(MARIOTYPE _TYPE);

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

    void CollisionOn()
    {
        m_Col->On();
    }
    void CollisionOff()
    {
        m_Col->Off();
    }

    void PowerUpSmall()
    {
        m_Type = MARIOTYPE::SMALL;
        ChangeAnimation(L"Idle");
    }
    void PowerUpMedium()
    {
        m_Type = MARIOTYPE::SUPER;
        ChangeAnimation(L"Change");
    }
    void PowerUpSuper()
    {
        m_Type = MARIOTYPE::SUPER;
        ChangeAnimation(L"Idle");
    }
    void PowerUpRacoon()
    {
        m_Type = MARIOTYPE::RACOON;
        ChangeAnimation(L"Change");
    }
    void PowerDownRacoon()
    {
        ChangeAnimation(L"Change");
        m_Type = MARIOTYPE::SUPER;
    }

    void PowerUpEnd();

    void PowerRacoonDownEnd();
    void NoDamageOn()
    {
        m_bNoDamage = true;
    }
    void NoDamageOff()
    {
        m_bNoDamage = false;
    }

    void PowerDownEnd();

    void PowerDownEffectOn()
    {
        m_AniRenderer->SetAlpha(125);
    }
    void PowerDownEffectOff()
    {
        m_AniRenderer->SetAlpha(255);
    }

public: /////////////////////////////////////// FSM
    void POWERUPStart();
    void POWERUPStay();
    void POWERUPEnd();

    void POWERDOWNStart();
    void POWERDOWNStay();
    void POWERDOWNEnd();

    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void BLOCKIDLEStart();
    void BLOCKIDLEStay();
    void BLOCKIDLEEnd();

    void CARRYIDLEStart();
    void CARRYIDLEStay();
    void CARRYIDLEEnd();

    void BLOCKCARRYIDLEStart();
    void BLOCKCARRYIDLEStay();
    void BLOCKCARRYIDLEEnd();

    void RUNStart();
    void RUNStay();
    void RUNEnd();

    void BLOCKRUNStart();
    void BLOCKRUNStay();
    void BLOCKRUNEnd();

    void CARRYRUNStart();
    void CARRYRUNStay();
    void CARRYRUNEnd();

    void BLOCKCARRYRUNStart();
    void BLOCKCARRYRUNStay();
    void BLOCKCARRYRUNEnd();

    void SKIDStart();
    void SKIDStay();
    void SKIDEnd();

    void BLOCKSKIDStart();
    void BLOCKSKIDStay();
    void BLOCKSKIDEnd();

    void TALLATTACKStart();
    void TALLATTACKStay();
    void TALLATTACKEnd();

    void TALLATTACKFALLStart();
    void TALLATTACKFALLStay();
    void TALLATTACKFALLEnd();

    void JUMPStart();
    void JUMPStay();
    void JUMPEnd();

    void TALLJUMPStart();
    void TALLJUMPStay();
    void TALLJUMPEnd();

    void BLOCKJUMPStart();
    void BLOCKJUMPStay();
    void BLOCKJUMPEnd();

    void CARRYJUMPStart();
    void CARRYJUMPStay();
    void CARRYJUMPEnd();

    void JUMPCheckEvent();

    void FALLStart();
    void FALLStay();
    void FALLEnd();

    void CARRYFALLStart();
    void CARRYFALLStay();
    void CARRYFALLEnd();

    void FOOTStart();
    void FOOTStay();
    void FOOTEnd();

    void CARRYFOOTStart();
    void CARRYFOOTStay();
    void CARRYFOOTEnd();

    void SITStart();
    void SITStay();
    void SITEnd();

    void BLOCKSITStart();
    void BLOCKSITStay();
    void BLOCKSITEnd();

    void SITJUMPStart();
    void SITJUMPStay();
    void SITJUMPEnd();

    void SITFALLStart();
    void SITFALLStay();
    void SITFALLEnd();

    void KICKStart();
    void KICKStay();
    void KICKEnd();
    void BLOCKKICKStart();
    void BLOCKKICKStay();
    void BLOCKKICKEnd();
    void KICKFALLStart();
    void KICKFALLStay();
    void KICKFALLEnd();
    void KICKBacktoIdle();
    void KICKBacktoBlockIdle();

    void CLEARFALLStart();
    void CLEARFALLStay();
    void CLEARFALLEnd();

    void CLEARRUNStart();
    void CLEARRUNStay();
    void CLEARRUNEnd();

    void DEADStart();
    void DEADStay();
    void DEADEnd();
};