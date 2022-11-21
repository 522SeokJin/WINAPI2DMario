#pragma once
#include "SJRenderer.h"
#include <SJWinImage.h>
#include <SJString.h>
#include <map>

// �з� :
// �뵵 : 
// ���� : 

class SJRendererAnimation : public SJRenderer
{
private:
    class Animation
    {
    public:
        SJWinImage*     m_Image;
        float           m_FrameTime;    // �̹��� ���������� �ٲ�� �ð�.
        float           m_InitialFrameTime; // ó�� ������ FrameTime
        float           m_CurTime;      // ���� �ִϸ��̼� �ð�
        int             m_StartFrame;   // ���� ������
        int             m_EndFrame;     // ������ ������
        int             m_CurFrame;     // ���� ������
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

