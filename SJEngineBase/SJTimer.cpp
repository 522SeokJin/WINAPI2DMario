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
	// 1�ʿ� ��ǻ�Ͱ� ���� �ִ� ����
	QueryPerformanceFrequency(&m_CountTime);

	// ������� �󸶳� ������. m_CurTime 
	// �ٷ� ���� �����ӱ��� �󸶳� ������. m_PrevTime 
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



