#pragma once
#include <SJEngineBasePublic.h>
#include <Windows.h>
#include <SJString.h>
#include "SJWinImage.h"
#include <SJTimer.h>
#include <SJInput.h>
#include <SJSound.h>

// 분류 :
// 용도 : 
// 설명 : 

class SJWindow
{
private: // Static Var
    static float4           m_Size;
    static float4           m_Pos;
    static HWND             m_WindowHWnd;
    static bool             m_bWindowProgress;

    static HDC              m_WindowDC;
    static SJWinImage       m_WindowMainImage;
    static SJWinImage       m_DoubleBufferImage;

    static __int64 WINDOWEVENT(HWND, unsigned int, unsigned __int64, __int64);

public:
    static HWND GetHwnd()
    {
        return m_WindowHWnd;
    }

    static HDC GetWindowDC()
    {
        return m_WindowMainImage.ImageDC();
    }

    static HDC GetBackBufferDC()
    {
        return m_DoubleBufferImage.ImageDC();
    }

    static SJWinImage& GetWindowImage()
    {
        return m_WindowMainImage;
    }

    static SJWinImage& GetBackBufferImage()
    {
        return m_DoubleBufferImage;
    }

public:
    static void BackBufferCopy();
    static void WindowEnd()
    {
        m_bWindowProgress = false;
    }

public: // Static Func
    template<typename Updater>
    static void Loop()
    {
		Updater::Start();

		MSG MsgData;

		while (m_bWindowProgress)
		{
            SJTimer::MainTimer.CalTime();

            SJInput::Update();
            SJSound::Update();

			if (0 != PeekMessage(&MsgData, m_WindowHWnd, 0, 0, PM_REMOVE))
			{
				// 생긴 일을 처리해주는 함수.
				DispatchMessage(&MsgData);
                
                Updater::Update();
			}
			else
			{
                Updater::Update();
			}
		}

        // os에서 빌려온 기능의 파괴함수 실행
        Updater::End();

        // Destory를 하지않으면 메모리 누수 발생
        DestroyWindow(m_WindowHWnd);
        m_WindowHWnd = nullptr;
    }
    static void CreateSJWindow(HINSTANCE _ProcessHandle, const SJString& _Name, float4 _Pos, float4 _Size);

private: // member Var

public: // constructer destructer
	SJWindow();
	~SJWindow();

public: // delete constructer 
    SJWindow(const SJWindow& _Other) = delete;
    SJWindow(const SJWindow&& _Other) = delete;

public: // delete operator
    SJWindow& operator=(const SJWindow& _Other) = delete;
    SJWindow& operator=(const SJWindow&& _Other) = delete;

public: // member Func

    static float4 GetSize();

    static void SetSize(float4 _Size);
    static void SetPos(float4 _Pos);
    static void SetSizeAndPos(float4 _Pos, float4 _Size);
};

