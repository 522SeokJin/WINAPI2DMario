#include "SJRendererAnimation.h"
#include <SJTimer.h>
#include "SJWindowResMgr.h"
#include <SJDebug.h>
#include <SJWindow.h>


SJRendererAnimation::Animation::Animation()
    : m_Image(nullptr)
    , m_FrameTime(0.1f)
    , m_InitialFrameTime(0.1f)
    , m_CurTime(0.0f)
    , m_StartFrame(-1)
    , m_EndFrame(-1)
    , m_CurFrame(-1)
    , m_IsLoop(true)
    , TransColor(RGB(255, 0, 255))
{

}

SJRendererAnimation::Animation::~Animation()
{

}

void SJRendererAnimation::Animation::Update()
{
    m_CurTime -= SJTimer::FDeltaTime();

    if (0 >= m_CurTime)
    {
        m_CurTime = m_FrameTime;

        // 재생
        if (m_StartFrame < m_EndFrame)
        {
            ++m_CurFrame;

            if (m_CurFrame > m_EndFrame)
            {
                if (true == m_IsLoop)
                {
                    m_CurFrame = m_StartFrame;
                }
                else
                {
                    --m_CurFrame;
                }
            }
        }
        // 역재생
        if (m_StartFrame > m_EndFrame)
        {
            --m_CurFrame;

            if (m_CurFrame < m_EndFrame)
            {
                if (true == m_IsLoop)
                {
                    m_CurFrame = m_StartFrame;
                }
                else
                {
                    ++m_CurFrame;
                }
            }

        }
    }
}

void SJRendererAnimation::Animation::Reset()
{
    m_CurTime = m_FrameTime;
    m_CurFrame = m_StartFrame;
}


// Static Var
// Static Func
// member Var



SJRendererAnimation::SJRendererAnimation()
    : m_CurAnimation(nullptr)
{
    m_RenderingType = RENDERINGMODE::TRANS;
}

SJRendererAnimation::~SJRendererAnimation()
{

}

// member Func

SJRendererAnimation::Animation* SJRendererAnimation::FindAnimation(const SJString& _Name)
{
    if (m_Animation.end() == m_Animation.find(_Name))
    {
        return nullptr;
    }

    return &m_Animation[_Name];
}

void SJRendererAnimation::CreateAnimation(const SJString& _AniName, const SJString& _ImageName, int _Start, int _End, float _FrameTime, bool _Loop)
{
    SJWinImage* FindImage = SJWindowResMgr::Inst().FindImage(_ImageName);

    if (nullptr == FindImage)
    {
        SJDebug::AssertMsg("if (nullptr == FindImage)");
    }

    if (0 >= FindImage->GetCutSize())
    {
        SJDebug::AssertMsg("if (0 >= FindImage->GetCutSize())");
    }

    if (0 > _Start ||
        0 > _End ||
        _Start >= FindImage->GetCutSize() ||
        _End >= FindImage->GetCutSize())
    {
        SJDebug::AssertMsg("_Start And _End Error");
    }

    if (nullptr != FindAnimation(_AniName))
    {
        SJDebug::AssertMsg("_Start And _End Error");
    }

    Animation& NewAni = m_Animation[_AniName];

    NewAni.m_Image = FindImage;
    NewAni.m_EndFrame = _End;
    NewAni.m_StartFrame = _Start;
    NewAni.m_FrameTime = _FrameTime;
    NewAni.m_InitialFrameTime = _FrameTime;
    NewAni.m_IsLoop = _Loop;
    NewAni.Reset();
}

void SJRendererAnimation::ChangeAnimation(const SJString& _AniName)
{
    if (m_CurAnimation == FindAnimation(_AniName))
    {
        return;
    }


    m_CurAnimation = FindAnimation(_AniName);

    if (nullptr == m_CurAnimation)
    {
        SJDebug::AssertMsg("if (nullptr == m_CurAnimation)");
    }

    m_CurAnimation->Reset();
}

void SJRendererAnimation::Render()
{
    if (nullptr == m_CurAnimation)
    {
        SJDebug::AssertMsg("if (nullptr == m_CurAnimation)");
    }
    else
    {
        m_CurAnimation->Update();

        const CutData& Data = m_CurAnimation->m_Image->GetCutData(m_CurAnimation->m_CurFrame);
        m_CutPos = Data.m_Pos;
        m_CutSize = Data.m_Size;

        RenderImage(m_CurAnimation->m_Image);
    }
}
