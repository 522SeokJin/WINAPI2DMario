#pragma once
#include <SJObjectBase.h>
#include <SJMath.h>

// 분류 :
// 용도 : 
// 설명 : 
enum class RENDERINGMODE
{
    BIT,
    TRANS,
    ALPHA,  // 반투명
    ROT,    // 회전
    MAX,
};

class SJActor;
class SJWinImage;

class SJRenderer : public SJObjectBase
{
private: // Static Var
public: // Static Func
protected: // member Var
    RENDERINGMODE   m_RenderingType;

    // 렌더링 되는 순서를 정함
    int             m_Order;

    // 자신을 가진 액터를 안다.
    SJActor*        m_Actor;

    // 렌더링을 하는 클래스는 모두 사이즈가 있어야한다.
    float4          m_RenderScale;
    float4          m_PivotPos;
    float4          m_CutPos;
    float4          m_CutSize;

    unsigned char   m_Alpha;

    //float4          m_RenderScale;
    //int             m_TransColor;

    //void TransRender();

public:
    void SetAlpha(unsigned char _Alpha)
    {
        m_Alpha = _Alpha;

        if (255 > _Alpha)
        {
            m_RenderingType = RENDERINGMODE::ALPHA;
        }
        else
        {
            m_RenderingType = RENDERINGMODE::TRANS;
        }
    }

public:
    float4 GetPivotPos()
    {
        return m_PivotPos;
    }

    void SetPivotPos(float4 _PivotPos)
    {
        m_PivotPos = _PivotPos;
    }

    float4 GetRenderScale()
    {
        return m_RenderScale;
    }

    void SetRenderScale(float4 _RenderScale)
    {
        m_RenderScale = _RenderScale;
    }

public:
    void SetOrder(int _Order)
    {
        m_Order = _Order;
    }

    int GetOrder()
    {
        return m_Order;
    }

    void SetActor(SJActor* _Actor)
    {
        m_Actor = _Actor;
    }

    SJActor* GetActor()
    {
        return m_Actor;
    }

public:
    float4 CamRenderPos();

public: // constructer destructer
    SJRenderer();
    virtual ~SJRenderer();

public: // delete constructer 
    SJRenderer(const SJRenderer& _Other) = delete;
    SJRenderer(const SJRenderer&& _Other) = delete;

public: // delete operator
    SJRenderer& operator=(const SJRenderer& _Other) = delete;
    SJRenderer& operator=(const SJRenderer&& _Other) = delete;

public: // member Func
    void RenderImage(SJWinImage* _Image);

    virtual void Render() = 0;
};

