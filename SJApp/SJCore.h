#pragma once

#include <SJScene.h>
#include <SJString.h>
#include <map>
#include <SJSceneManager.h>

// 분류 : 컨텐츠 
// 용도 : 업데이터(현재 장면을 돌려주는 역할을 합니다) or 매니저(Scene을 관리한다)
// 설명 : 게임의 시작을 관리하고 게임의 전반적인 내용을 관리할 클래스

class SJCore
{
private: // Static Var
public: // Static Func
private: // member Var

public:
    static SJSceneManager SceneManager;

private: // constructer destructer
	SJCore();
	~SJCore();

public: // delete constructer 
    SJCore(const SJCore& _Other) = delete;
    SJCore(const SJCore&& _Other) = delete;

public: // delete operator
    SJCore& operator=(const SJCore& _Other) = delete;
    SJCore& operator=(const SJCore&& _Other) = delete;

public: // member Func
    static void Start();
    static void Update();
    static void End();
};

