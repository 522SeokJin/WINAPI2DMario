#pragma once
#include "Object.h"

// �з� :
// �뵵 : 
// ���� : 

class UI_Power : public Object
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    UI_Power();
    ~UI_Power();

public: // delete constructer 
    UI_Power(const UI_Power& _Other) = delete;
    UI_Power(const UI_Power&& _Other) = delete;

public: // delete operator
    UI_Power& operator=(const UI_Power& _Other) = delete;
    UI_Power& operator=(const UI_Power&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

};

