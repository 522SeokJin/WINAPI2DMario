#pragma once
#include <SJActor.h>

// 분류 :
// 용도 : 
// 설명 : 

class SJRendererBasic;

class BossStage_Terrain : public SJActor
{
private: // Static Var
public: // Static Func
private: // member Var
    SJRendererBasic* ColliderRenderer;

public: // constructer destructer
	BossStage_Terrain();
	~BossStage_Terrain();

public: // delete constructer 
    BossStage_Terrain(const BossStage_Terrain& _Other) = delete;
    BossStage_Terrain(const BossStage_Terrain&& _Other) = delete;

public: // delete operator
    BossStage_Terrain& operator=(const BossStage_Terrain& _Other) = delete;
    BossStage_Terrain& operator=(const BossStage_Terrain&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void OffTask() override;
};

