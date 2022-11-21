#pragma once
#include "Object.h"
#include <SJCollision.h>

// 분류 :
// 용도 : 
// 설명 : 

class Coin : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    SJCollision* m_Col;

public: // constructer destructer
    Coin();
    ~Coin();

public: // delete constructer 
    Coin(const Coin& _Other) = delete;
    Coin(const Coin&& _Other) = delete;

public: // delete operator
    Coin& operator=(const Coin& _Other) = delete;
    Coin& operator=(const Coin&& _Other) = delete;

public:
    void CollisionOn()
    {
        m_Col->On();
    }
    void CollisionOff()
    {
        m_Col->Off();
    }

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

};

