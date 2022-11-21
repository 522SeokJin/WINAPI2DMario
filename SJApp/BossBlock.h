#pragma once
#include "Object.h"

// 분류 :
// 용도 : 
// 설명 : 

class BossBlock : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    SJCollision* m_Col;
    SJCollision* m_SideCol;
    SJCollision* m_BottomCol;

public: // constructer destructer
    BossBlock();
    ~BossBlock();

public:
    void BossBlockLogicStartCol(SJCollision* _Col);
    void BossBlockLogicEndCol(SJCollision* _Col);

public: // delete constructer 
    BossBlock(const BossBlock& _Other) = delete;
    BossBlock(const BossBlock&& _Other) = delete;

public: // delete operator
    BossBlock& operator=(const BossBlock& _Other) = delete;
    BossBlock& operator=(const BossBlock&& _Other) = delete;

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

};

