#pragma once
#include <SJScene.h>

// 분류 :
// 용도 : 
// 설명 : 

class EndingScene : public SJScene
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    EndingScene();
    ~EndingScene();

public: // delete constructer 
    EndingScene(const EndingScene& _Other) = delete;
    EndingScene(const EndingScene&& _Other) = delete;

public: // delete operator
    EndingScene& operator=(const EndingScene& _Other) = delete;
    EndingScene& operator=(const EndingScene&& _Other) = delete;

public: // member Func
    void Start() override;
    void SceneUpdate() override;
    void SceneDebugRender() override;
};

