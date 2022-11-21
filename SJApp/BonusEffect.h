#pragma once
#include "Object.h"
#include <SJCollision.h>

// 분류 :
// 용도 : 
// 설명 : 

class BonusEffect : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    bool    m_bMoveOn;

public:
    void SetMoveOn()
    {
        m_bMoveOn = true;
    }

public: // constructer destructer
    BonusEffect();
    ~BonusEffect();

public: // delete constructer 
    BonusEffect(const BonusEffect& _Other) = delete;
    BonusEffect(const BonusEffect&& _Other) = delete;

public: // delete operator
    BonusEffect& operator=(const BonusEffect& _Other) = delete;
    BonusEffect& operator=(const BonusEffect&& _Other) = delete;

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

};

