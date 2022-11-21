#pragma once
#include <SJEngineBasePublic.h>
#include <SJEnginePlatformPublic.h>
#include <list>
#include <map>
#include <set>

// set == value없는 맵
// set ->second가 없다

// 분류 : 오브젝트
// 용도 : 업데이터(액터와 자기자신을 함수들을 실행시킬겁니다) 매니저(액터 자기안에서 뛰어노는 애들을 관리할 겁니다.)
// 설명 : 장면이라는 개념을 기능으로 만들고 그 개념에 대한 기본 기능들을 제공하는 클래스

class SJRenderer;
class SJCollision;
class SJActor;

class SJScene
{
public: // Static Var
    static bool m_bDebugRender;
public: // Static Func
    static void m_DebugModeOn()
    {
        m_bDebugRender = true;
    }
    static void m_DebugModeOff()
    {
        m_bDebugRender = false;
    }

private: // member Var
    std::list<SJActor*>     m_Actors;
    SJScene*                m_CurScene;
    float4                  m_CamPos;

public:
    float4 GetCamPos()
    {
        return m_CamPos;
    }

    void SetCamPos(const float4& _CamPos)
    {
        m_CamPos = _CamPos;
    }
    void SetCamMove(const float4& _CamPos)
    {
        m_CamPos += _CamPos;
    }
    void SetCurScene(SJScene* _CurScene)
    {
        m_CurScene = _CurScene;
    }
    std::list<SJActor*> GetActors()
    {
        return m_Actors;
    }

public:
    template<typename ActorType>
    ActorType* CreateActor()
    {
        ActorType* NewActor = new ActorType();

        NewActor->SetScene(this);

        NewActor->Start();

        m_Actors.push_back(NewActor);

        return NewActor;
    }

public: // constructer destructer
	SJScene();
	virtual ~SJScene(); // 소멸자에 virtual 자식 소멸자까지 호출하기 위해서

public: // delete constructer 
    SJScene(const SJScene& _Other) = delete;
    SJScene(const SJScene&& _Other) = delete;

public: // delete operator
    SJScene& operator=(const SJScene& _Other) = delete;
    SJScene& operator=(const SJScene&& _Other) = delete;

public: // member Func
    virtual void Start() {}

    void Progress();

    ////////////////////////////////////////////        Rendering
    // 랜더링 해주는 역할은 씬이 한다.
    // 액터에게 빌려서
private:
    std::map<int, std::list<SJRenderer*>> m_RendererLists;

public:
    void PushRenderer(SJRenderer* _Renderer);

private:
    void Render();

    ////////////////////////////////////////////        Collision

private:
    std::map<int, std::list<SJCollision*>> m_CollisionLists;

    std::map<int, std::set<int>> m_LinkCollisionGroup;

public:
    void CollisionGroupLink(int _Left, int _Right)
    {
        if (m_LinkCollisionGroup[_Left].end() != m_LinkCollisionGroup[_Left].find(_Right))
        {
            return;
        }

        // 연결된 충돌체그룹이 없으면 추가
        m_LinkCollisionGroup[_Left].insert(_Right);
    }

public:
    void PushCollision(SJCollision* _Collision);

private:
    void CollisionProcess();
    void CollisionGroupOtherCheck(int _Left, int _Right);
    void CollisionGroupThisCheck(int _Value);

public:
    void Release();
    void OnOffCheck();

    ////////////////////////////////////////////        LogicUpdate
public:
    virtual void SceneChangeStart();
    virtual void SceneChangeEnd();
    virtual void SceneUpdate() {};
    virtual void SceneDebugRender() {};
};

