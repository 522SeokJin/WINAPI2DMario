#pragma once
#include <SJActor.h>

// �з� :
// �뵵 : 
// ���� : 

class UIStage : public SJActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
	UIStage();
	~UIStage();

public: // delete constructer 
    UIStage(const UIStage& _Other) = delete;
    UIStage(const UIStage&& _Other) = delete;

public: // delete operator
    UIStage& operator=(const UIStage& _Other) = delete;
    UIStage& operator=(const UIStage&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override; // ����.
};

