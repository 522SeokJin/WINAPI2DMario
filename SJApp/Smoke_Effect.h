#pragma once
#include "Object.h"

// 분류 :
// 용도 : 
// 설명 : 

class Smoke_Effect : public Object
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Smoke_Effect();
    ~Smoke_Effect();

public: // delete constructer 
    Smoke_Effect(const Smoke_Effect& _Other) = delete;
    Smoke_Effect(const Smoke_Effect&& _Other) = delete;

public: // delete operator
    Smoke_Effect& operator=(const Smoke_Effect& _Other) = delete;
    Smoke_Effect& operator=(const Smoke_Effect&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

};

