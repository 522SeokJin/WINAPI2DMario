#include "SJTimer.h"

// Static Var
SJTimer SJTimer::MainTimer;

// Static Func

// member Var

SJTimer::SJTimer()
	: m_CountTime()
	, m_CurTime()
	, m_PrevTime()
	, m_DDeltaTime()
	, m_FDeltaTime()
{
	// 1초에 컴퓨터가 샐수 있는 숫자
	QueryPerformanceFrequency(&m_CountTime);

	// 현재까지 얼마나 샜느냐. m_CurTime 
	// 바로 이전 프레임까지 얼마나 샜느냐. m_PrevTime 
	Reset();
}

SJTimer::~SJTimer()
{

}

// member Func

double SJTimer::GetDDeltaTime()
{
	return m_DDeltaTime;
}

float SJTimer::GetFDeltaTime()
{
	return m_FDeltaTime;
}

void SJTimer::Reset()
{
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_PrevTime);
}

void SJTimer::CalTime()
{
	QueryPerformanceCounter(&m_CurTime);
	__int64 InterCount = m_CurTime.QuadPart - m_PrevTime.QuadPart;
	m_DDeltaTime = (double)InterCount / (double)m_CountTime.QuadPart;
	m_FDeltaTime = (float)m_DDeltaTime;
	m_PrevTime.QuadPart = m_CurTime.QuadPart;
}



