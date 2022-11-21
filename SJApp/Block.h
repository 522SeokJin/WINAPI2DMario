#pragma once
#include "Object.h"
#include <SJTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 

class Block : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    SJCollision*            m_Col;
    SJCollision*            m_SideCol;
    SJCollision*            m_BottomCol;

public: // constructer destructer
    Block();
    ~Block();

public:
    void BlockLogicStartCol(SJCollision* _Col);
    void BlockLogicEndCol(SJCollision* _Col);

public: // delete constructer 
    Block(const Block& _Other) = delete;
    Block(const Block&& _Other) = delete;

public: // delete operator
    Block& operator=(const Block& _Other) = delete;
    Block& operator=(const Block&& _Other) = delete;

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

};

