#pragma once
#include <memory>

// 분류 :
// 용도 : 
// 설명 : 

class SJMemory
{
private: // Static Var
public: // Static Func
    template<typename Left, typename Right>
    static void MemCopy(Left& _Left, Right& _Right)
    {
        memcpy_s(&_Left, sizeof(Left), &_Right, sizeof(Right));
    }

    template<typename Data>
    static void MemZero(Data& _Value)
    {
        memset(&_Value, 0, sizeof(_Value));
    }

private: // member Var

public: // constructer destructer
	SJMemory();
	~SJMemory();

public: // delete constructer 
    SJMemory(const SJMemory& _Other) = delete;
    SJMemory(const SJMemory&& _Other) = delete;

public: // delete operator
    SJMemory& operator=(const SJMemory& _Other) = delete;
    SJMemory& operator=(const SJMemory&& _Other) = delete;

public: // member Func
};

