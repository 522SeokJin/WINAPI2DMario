#pragma once
#include "Object.h"

// 분류 :
// 용도 : 
// 설명 : 

class Open_Door : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    SJCollision* m_Col;

public: // constructer destructer
    Open_Door();
    ~Open_Door();

public: // delete constructer 
    Open_Door(const Open_Door& _Other) = delete;
    Open_Door(const Open_Door&& _Other) = delete;

public: // delete operator
    Open_Door& operator=(const Open_Door& _Other) = delete;
    Open_Door& operator=(const Open_Door&& _Other) = delete;

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

};

