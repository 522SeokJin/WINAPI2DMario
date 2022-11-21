#pragma once

#include <SJScene.h>
#include <SJString.h>
#include <map>
#include <SJSceneManager.h>

// �з� : ������ 
// �뵵 : ��������(���� ����� �����ִ� ������ �մϴ�) or �Ŵ���(Scene�� �����Ѵ�)
// ���� : ������ ������ �����ϰ� ������ �������� ������ ������ Ŭ����

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

