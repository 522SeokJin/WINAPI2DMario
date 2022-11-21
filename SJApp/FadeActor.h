#pragma once
#include <SJActor.h>
#include <SJTimeEventer.h>

// �з� :
// �뵵 : 
// ���� : 

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
    void Start() override; // ����.
    void Update() override; // ����.

    void FadeInStart();
    void FadeIn();
    void FadeInEnd();

    void FadeOutStart();
    void FadeOut();
    void FadeOutEnd();
};

