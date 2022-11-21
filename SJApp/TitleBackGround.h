#pragma once
#include <SJActor.h>

// 분류 :
// 용도 : 
// 설명 : 

class SJRendererAnimation;

class TitleBackGround : public SJActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
	TitleBackGround();
	~TitleBackGround();

public: // delete constructer 
    TitleBackGround(const TitleBackGround& _Other) = delete;
    TitleBackGround(const TitleBackGround&& _Other) = delete;

public: // delete operator
    TitleBackGround& operator=(const TitleBackGround& _Other) = delete;
    TitleBackGround& operator=(const TitleBackGround&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override; // 돈다
};

