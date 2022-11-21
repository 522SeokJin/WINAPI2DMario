#pragma once
#include "SJRenderer.h"
#include <SJWinImage.h>
#include <SJDebug.h>

// 분류 :
// 용도 : 
// 설명 : 

class SJActor;

class SJRendererBasic : public SJRenderer
{
private: // Static Var
public: // Static Func
private: // member Var
    SJWinImage*     m_Image;

public:
    void SetCutData(int _Index)
    {
        if (nullptr == m_Image)
        {
            SJDebug::AssertMsg("if (nullptr == m_Image)");
        }

        const CutData& Data = m_Image->GetCutData(_Index);

        m_CutPos = Data.m_Pos;
        m_CutSize = Data.m_Size;
    }

    void SetCutPosAndSize(const float4& _Pos, float4& _Size)
    {
        m_CutPos = _Pos;
        m_CutSize = _Size;
    }

    float4 GetCutPos()
    {
        return m_CutPos;
    }

    void SetCutPos(const float4& _Pos)
    {
        m_CutPos = _Pos;
    }

    float4 GetCutSize()
    {
        return m_CutSize;
    }

    void SetCutSize(const float4& _Size)
    {
        m_CutSize = _Size;
    }

    // Trans
public:
    void TransSetting(const SJString& _Image, float4 _Scale, float4 _PivotPos = float4{ 0,0 });

public: // constructer destructer
    SJRendererBasic();
    ~SJRendererBasic();

public: // delete constructer 
    SJRendererBasic(const SJRendererBasic& _Other) = delete;
    SJRendererBasic(const SJRendererBasic&& _Other) = delete;

public: // delete operator
    SJRendererBasic& operator=(const SJRendererBasic& _Other) = delete;
    SJRendererBasic& operator=(const SJRendererBasic&& _Other) = delete;

public: // member Func
    void Render() override;
};

