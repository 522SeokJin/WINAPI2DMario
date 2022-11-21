#pragma once
#include "Object.h"

// 분류 :
// 용도 : 
// 설명 : 

class BonusCard : public Object
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    BonusCard();
    ~BonusCard();

public: // delete constructer 
    BonusCard(const BonusCard& _Other) = delete;
    BonusCard(const BonusCard&& _Other) = delete;

public: // delete operator
    BonusCard& operator=(const BonusCard& _Other) = delete;
    BonusCard& operator=(const BonusCard&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

};

