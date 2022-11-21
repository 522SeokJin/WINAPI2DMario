#pragma once
#include "Object.h"

// 분류 :
// 용도 : 
// 설명 : 

class SJRendererBasic;

class You_Got_A_Card : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    SJRendererBasic* m_Renderer;

public: // constructer destructer
    You_Got_A_Card();
    ~You_Got_A_Card();

public: // delete constructer 
    You_Got_A_Card(const You_Got_A_Card& _Other) = delete;
    You_Got_A_Card(const You_Got_A_Card&& _Other) = delete;

public: // delete operator
    You_Got_A_Card& operator=(const You_Got_A_Card& _Other) = delete;
    You_Got_A_Card& operator=(const You_Got_A_Card&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override; // 돈다
};

