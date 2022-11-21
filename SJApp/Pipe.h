#pragma once
#include "Object.h"

// 분류 :
// 용도 : 
// 설명 : 

enum class PIPETYPE
{
    SHORT,
    LONG,
};

class Pipe : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    PIPETYPE m_Type;

public:
    void SetType(PIPETYPE _Type)
    {
        m_Type = _Type;
    }

public: // constructer destructer
    Pipe();
    ~Pipe();

public: // delete constructer 
    Pipe(const Pipe& _Other) = delete;
    Pipe(const Pipe&& _Other) = delete;

public: // delete operator
    Pipe& operator=(const Pipe& _Other) = delete;
    Pipe& operator=(const Pipe&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;
};

