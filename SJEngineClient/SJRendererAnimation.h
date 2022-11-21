#pragma once
#include "SJRenderer.h"
#include <SJWinImage.h>
#include <SJString.h>
#include <map>

// 분류 :
// 용도 : 
// 설명 : 

class SJRendererAnimation : public SJRenderer
{
private:
    class Animation
    {
    public:
        SJWinImage*     m_Image;
        float           m_FrameTime;    // 이미지 한장한장이 바뀌는 시간.
        float           m_InitialFrameTime; // 처음 세팅한 FrameTime
        float           m_CurTime;      // 현재 애니메이션 시간
        int             m_StartFrame;   // 시작 프레임
        int             m_EndFrame;     // 끝나는 프레임
        int             m_CurFrame;     // 현재 프레임
        bool            m_IsLoop;
        int             TransColor;

    public:
        bool IsEnd()
        {
            return m_CurFrame == m_EndFrame;
        }

        void SetFrameTime(float _FrameTime)
        {
            m_FrameTime = _FrameTime;
        }

        float GetFrameTime()
        {
            return m_FrameTime;
        }

        float GetInitialFrameTime()
        {
            return m_InitialFrameTime;
        }

        int GetCurFrame()
        {
            return m_CurFrame;
        }

    public:
        void Update();
        void Reset();

    public:
        Animation();
        ~Animation();

    };

private: // Static Var
public: // Static Func
private: // member Var
    std::map<SJString, Animation> m_Animation;
    Animation* m_CurAnimation;

public:
    bool IsEnd()
    {
        return m_CurAnimation->IsEnd();
    }

    Animation* GetCurAnimation()
    {
        return m_CurAnimation;
    }


public: // constructer destructer
    SJRendererAnimation();
    ~SJRendererAnimation();

public: // delete constructer 
    SJRendererAnimation(const SJRendererAnimation& _Other) = delete;
    SJRendererAnimation(const SJRendererAnimation&& _Other) = delete;

public: // delete operator
    SJRendererAnimation& operator=(const SJRendererAnimation& _Other) = delete;
    SJRendererAnimation& operator=(const SJRendererAnimation&& _Other) = delete;

public:
    Animation* FindAnimation(const SJString& _Name);

public: // member Func
    void CreateAnimation(const SJString& _AniName, const SJString& _ImageName, int _Start, int _End, float _FrameTime = 0.05f, bool _Loop = true);
    void ChangeAnimation(const SJString& _AniName);

public:
    void Render() override;
};

