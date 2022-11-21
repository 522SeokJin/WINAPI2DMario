#pragma once
#include <SJActor.h>

// �з� :
// �뵵 : 
// ���� : 

class Ending : public SJActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
	Ending();
	~Ending();

public: // delete constructer 
    Ending(const Ending& _Other) = delete;
    Ending(const Ending&& _Other) = delete;

public: // delete operator
    Ending& operator=(const Ending& _Other) = delete;
    Ending& operator=(const Ending&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
};

