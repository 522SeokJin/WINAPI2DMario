#pragma once
#include "SJString.h"

// 분류 : 디버그
// 용도 : 헬퍼
// 설명 : 이 클래스는 오로지 전역적인 함수와 인자만을 이용한다.
//        절대 객체화해서 사용할 수 없게 생성자를 private로 막았다.

class SJDebug
{
private: // Static Var
public: // Static Func
    static void LeakCheck();
    static void AssertMsg(const SJString& _ErrorMsg);
    static void AssertMsg(const std::string& _ErrorMsg);
    static void OutPutMsg(const SJString& _ErrorMsg);
    // OutputDebugString(L"Test\n");

private: // member Var

private: // constructer destructer
	SJDebug();
	~SJDebug();

public: // delete constructer 
    SJDebug(const SJDebug& _Other) = delete;
    SJDebug(const SJDebug&& _Other) = delete;

public: // delete operator
    SJDebug& operator=(const SJDebug& _Other) = delete;
    SJDebug& operator=(const SJDebug&& _Other) = delete;

public: // member Func
};

