#pragma once
#include "fmod.hpp"
#include "SJDebug.h"
#include <map>

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

// fmod�� ���� ���̺귯�� �߿��� �پ��� Ȯ���ڿ� 3d������� �����ϴ�
// ������ ���� ���̺귯���� ����� Ǯ���� ���̺귯���� ���� �����ڶ�� �Ҽ� �ִ� ���̺귯��
// mp3 ogg��� ���� ��� ���带 �����Ѵ�.

// �з� :
// �뵵 : 
// ���� : 

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
    // -1 ���ѷ���
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

    // -1 ���ѷ���
    FMOD::Channel* Play(int _LoopCount);
};

using SoundPlayer = SJSound::SJSoundPlayer;
