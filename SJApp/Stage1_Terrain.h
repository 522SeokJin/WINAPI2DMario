#pragma once
#include <SJActor.h>

// 분류 :
// 용도 : 
// 설명 : 

class SJRendererBasic;

class Stage1_Terrain : public SJActor
{
private: // Static Var
public: // Static Func
private: // member Var
    SJRendererBasic* ColliderRenderer;

public: // constructer destructer
	Stage1_Terrain();
	~Stage1_Terrain();

public: // delete constructer 
    Stage1_Terrain(const Stage1_Terrain& _Other) = delete;
    Stage1_Terrain(const Stage1_Terrain&& _Other) = delete;

public: // delete operator
    Stage1_Terrain& operator=(const Stage1_Terrain& _Other) = delete;
    Stage1_Terrain& operator=(const Stage1_Terrain&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override; // 돈다.
    void OffTask() override;
};

