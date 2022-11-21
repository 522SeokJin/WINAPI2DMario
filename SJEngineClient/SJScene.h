#pragma once
#include <SJEngineBasePublic.h>
#include <SJEnginePlatformPublic.h>
#include <list>
#include <map>
#include <set>

// set == value���� ��
// set ->second�� ����

// �з� : ������Ʈ
// �뵵 : ��������(���Ϳ� �ڱ��ڽ��� �Լ����� �����ų�̴ϴ�) �Ŵ���(���� �ڱ�ȿ��� �پ��� �ֵ��� ������ �̴ϴ�.)
// ���� : ����̶�� ������ ������� ����� �� ���信 ���� �⺻ ��ɵ��� �����ϴ� Ŭ����

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
	virtual ~SJScene(); // �Ҹ��ڿ� virtual �ڽ� �Ҹ��ڱ��� ȣ���ϱ� ���ؼ�

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
    // ������ ���ִ� ������ ���� �Ѵ�.
    // ���Ϳ��� ������
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

        // ����� �浹ü�׷��� ������ �߰�
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

