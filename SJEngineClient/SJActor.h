#pragma once
#include <SJMath.h>
#include <list>
#include "SJScene.h"
#include <SJObjectBase.h>

// �з� : 
// �뵵 : 
// ���� : ����� �̷�� ���� ������ ��ҵ鿡�� ����� �����ϴ� Ŭ����

class SJRenderer;
class SJCollision;

class SJActor : public SJObjectBase
{
    friend SJScene;

public: // Static Var
public: // Static Func
private: // member Var
    SJScene*        m_Scene;
    float4          m_Pos;
    float4          m_Size;

    bool            m_CamAffect;

    std::list<SJRenderer*> m_Renderer;
    std::list<SJCollision*> m_Collision;

public:
    SJScene* GetScene()
    {
        return m_Scene;
    }

    void SetScene(SJScene* _Scene)
    {
        m_Scene = _Scene;
    }

public:
    float4 GetPos() 
    {
        return m_Pos;
    }

    // ī�޶� ���� Position
    float4 GetCamPos()
    {
        return m_Pos - m_Scene->GetCamPos();
    }
    
    void SetPos(const float4& _Other)
    {
        m_Pos = _Other;
    }

    void MovePos(const float4& _Other)
    {
        m_Pos += _Other;
    }

    float4 GetSize() const
    {
        return m_Size;
    }

    void SetSize(const float4& _Size)
    {
        m_Size = _Size;
    }

    bool GetCamAffect()
    {
        return m_CamAffect;
    }

    void SetCamAffect(bool _CamAffect)
    {
        m_CamAffect = _CamAffect;
    }

    ///////////////////////////////////////////////     ����������
public:
    // _Order ������ ������ �ǹ�
    template<typename T>
    T* CreateRenderer(int _Order)
    {
        T* NewT = new T();

        NewT->SetOrder(_Order);

        NewT->SetActor(this);
        NewT->SetParentBase(this);
        m_Renderer.push_back(NewT);

        m_Scene->PushRenderer(NewT);
        return NewT;
    }

    ///////////////////////////////////////////////     �浹ü����
public:
    // _Order �浹ü �׷� ����
    template<typename T>
    T* CreateCollision(int _Order)
    {
        T* NewT = new T();
        NewT->SetOrder(_Order);
        NewT->SetActor(this);
        NewT->SetParentBase(this);
        m_Collision.push_back(NewT);

        m_Scene->PushCollision(NewT);
        return NewT;
    }


public: // constructer destructer
	SJActor();
	virtual ~SJActor();

public: // delete constructer 
    SJActor(const SJActor& _Other) = delete;
    SJActor(const SJActor&& _Other) = delete;

public: // delete operator
    SJActor& operator=(const SJActor& _Other) = delete;
    SJActor& operator=(const SJActor&& _Other) = delete;

public: // member Func
    virtual void Start() {};    // �����Ѵ�.
    virtual void Update() {};   // ����.
    virtual void DebugRender() {};

    void DeathTask() override;

private:
    virtual void Release();
};

