#pragma once
#include <SJActor.h>

// 분류 :
// 용도 : 
// 설명 : 

class SJRendererAnimation;

class TitleAnimation : public SJActor
{
private: // Static Var
public: // Static Func
private: // member Var
    SJRendererAnimation* AniRenderer;

public: // constructer destructer
	TitleAnimation();
	~TitleAnimation();

public: // delete constructer 
    TitleAnimation(const TitleAnimation& _Other) = delete;
    TitleAnimation(const TitleAnimation&& _Other) = delete;

public: // delete operator
    TitleAnimation& operator=(const TitleAnimation& _Other) = delete;
    TitleAnimation& operator=(const TitleAnimation&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override; // 돈다
};

