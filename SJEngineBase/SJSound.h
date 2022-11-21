#pragma once
#include "fmod.hpp"
#include "SJDebug.h"
#include <map>

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

// fmod는 사운드 라이브러리 중에서 다양한 확장자와 3d사운드까지 지원하는
// 굉장히 좋은 라이브러리로 무료로 풀리는 라이브러리중 거의 종결자라고 할수 있는 라이브러리
// mp3 ogg등등 거의 모든 사운드를 지원한다.

// 분류 :
// 용도 : 
// 설명 : 

class SJString;

class SJSound
{
public:
    class SJSoundPlayer
    {
        friend SJSound;
    private:
        FMOD::Channel* Channel;
    public:
        void Stop()
        {
            if (nullptr == Channel)
            {
                //SJDebug::AssertMsg(L"if (nullptr == Channel)");
                return;
            }

            Channel->stop();
        }
        bool IsPlaying()
        {
            bool bPlay;

            if (nullptr == Channel)
            {
                //SJDebug::AssertMsg(L"if (nullptr == Channel)");
                return false;
            }

            bool test = Channel->isPlaying(&bPlay);

            return Channel->isPlaying(&bPlay);
        }
    public:
        SJSoundPlayer() : Channel(nullptr)
        {

        }

    private:
        SJSoundPlayer(FMOD::Channel* _Channel) : Channel(_Channel)
        {

        }
    };

private:
    static FMOD::System*                        m_pFmodSystem;
    static std::map<SJString, SJSound*>         m_SoundMap;

private:
    static void Init();

    class StaticInst
    {
        friend SJSound;
    private:
        StaticInst();
        ~StaticInst();
    };

    friend StaticInst;
    static StaticInst Inst;

public:
    static void Update();
    static void Release();
    static void Load(const SJString& _Path);
    // -1 무한루프
    static SJSoundPlayer Play(const SJString& _Name, int _LoopCount = 0);

private: // Static Var
public: // Static Func
private: // member Var
    FMOD::Sound* m_pSound;

public: // constructer destructer
	SJSound();
	~SJSound();

public: // delete constructer 
    SJSound(const SJSound& _Other) = delete;
    SJSound(const SJSound&& _Other) = delete;

public: // delete operator
    SJSound& operator=(const SJSound& _Other) = delete;
    SJSound& operator=(const SJSound&& _Other) = delete;

public: // member Func
    void Create(const SJString& _Path);

    // -1 무한루프
    FMOD::Channel* Play(int _LoopCount);
};

using SoundPlayer = SJSound::SJSoundPlayer;
