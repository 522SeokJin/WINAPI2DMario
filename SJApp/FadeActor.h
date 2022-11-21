#pragma once
#include <SJActor.h>
#include <SJTimeEventer.h>

// ºÐ·ù :
// ¿ëµµ : 
// ¼³¸í : 

class SJRendererBasic;

class FadeActor : public SJActor
{
private: // Static Var
public: // Static Func
private: // member Var
    SJRendererBasic*        m_Render;
    float                   m_Alpha;

public:
    SJTimeEventer<FadeActor>  FadeTimer;

public: // constructer destructer
	FadeActor();
	~FadeActor();

public: // delete constructer 
    FadeActor(const FadeActor& _Other) = delete;
    FadeActor(const FadeActor&& _Other) = delete;

public: // delete operator
    FadeActor& operator=(const FadeActor& _Other) = delete;
    FadeActor& operator=(const FadeActor&& _Other) = delete;

public: // member Func
    void Start() override; // µ·´Ù.
    void Update() override; // µ·´Ù.

    void FadeInStart();
    void FadeIn();
    void FadeInEnd();

    void FadeOutStart();
    void FadeOut();
    void FadeOutEnd();
};

