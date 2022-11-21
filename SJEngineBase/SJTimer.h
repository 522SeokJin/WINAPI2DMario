#pragma once
#include <Windows.h>

// 분류 :
// 용도 : 
// 설명 : 

class SJTimer
{
public: // Static Var
    static SJTimer      MainTimer;

public: // Static Func
    static float FDeltaTime(float _Speed = 1.0f)
    {
        return MainTimer.GetFDeltaTime() * _Speed;
    }

public:
    LARGE_INTEGER       m_CountTime;
    LARGE_INTEGER       m_CurTime;
    LARGE_INTEGER       m_PrevTime;
    double              m_DDeltaTime;
    float               m_FDeltaTime;

public:
    double GetDDeltaTime();
    float GetFDeltaTime();
    void Reset();
    void CalTime();


public: // constructer destructer
	SJTimer();
	~SJTimer();


public: // member Func
};

