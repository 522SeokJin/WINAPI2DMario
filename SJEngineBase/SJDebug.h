#pragma once
#include "SJString.h"

// �з� : �����
// �뵵 : ����
// ���� : �� Ŭ������ ������ �������� �Լ��� ���ڸ��� �̿��Ѵ�.
//        ���� ��üȭ�ؼ� ����� �� ���� �����ڸ� private�� ���Ҵ�.

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

