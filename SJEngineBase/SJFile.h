#pragma once
#include "SJPath.h"
#include "SJDebug.h"

#include <map>
#include <list>
#include <vector>

// 분류 : IO 파일입출력에 동원되는 녀석
// 용도 : 
// 설명 : 이 객체가 파일을 의미하게 된다.
//        파일이 할수 있는일을 함수로서 표현한다.
//        파일이라면 Create 파일을 만든다.
//        write 파일내가 데이터를 "파일에 쓰는 기능을 시험해봤습니다" 쓴다.

class SJFile : public SJPath
{
private: // Static Var
public: // Static Func

private: // member Var
    FILE* m_Handle;
    int m_CurMemoryPostion;
    size_t m_FileSize;
    SJString m_Mode;

public:
    bool IsReadOpen()
    {
        return m_Mode.is_find(L"r");
    }
    bool IsWriteOpen()
    {
        return m_Mode.is_find(L"w");
    }
    size_t FileSize();

public: // constructer destructer
    SJFile();
    SJFile(const SJString& _Path);
    ~SJFile();

public: // delete constructer 
    SJFile(const SJFile& _Other) : SJPath(_Other), m_Handle(nullptr), m_CurMemoryPostion(0), m_FileSize(0)
    {

    }
    SJFile(const SJFile&& _Other) noexcept : SJPath(_Other), m_Handle(nullptr), m_CurMemoryPostion(0), m_FileSize(0)
    {

    }

public: // delete operator
    SJFile& operator=(const SJFile& _Other) = delete;
    SJFile& operator=(const SJFile&& _Other) = delete;

public: // member Func
    void Open(const wchar_t* _Mode);
    void Close();

public:
    template<typename T>
    void operator << (T& _Value)
    {
        Write((void*)&_Value, sizeof(_Value), 1);
    }
    // 템플릿 특수화
    template<>
    void operator <<(SJString& _Value)
    {
        const SJString& ConstStr = _Value;
        operator<<(ConstStr);
    }

    template<>
    void operator << (const SJString& _Value)
    {
        std::string Convert = _Value.wStringToString();

        int Size = (int)Convert.size();

        Write(&Size, sizeof(int), 1);
        //글자수이지 바이트수가 아니므로
        // sizeof(wchar_t) * Size

        // 멀티바이트로 바꿔서 저장.

        Write((void*)Convert.c_str(), Size, 1);
    }

    template<typename KEY, typename VALUE>
    void operator << (std::map<KEY, VALUE>& _Value)
    {
        int Size = (int)_Value.size();
        this->operator<<(Size);

        typename std::map<KEY, VALUE>::iterator Start = _Value.begin();
        typename std::map<KEY, VALUE>::iterator End = _Value.end();

        for (; Start != End; ++Start)
        {
            const KEY& Key = Start->first;
            VALUE& Value = Start->second;

            operator<<(Key);
            operator<<(Value);
        }
    }

    template<typename T>
    void WriteType(T& _Value, size_t _Count = 1)
    {
        Write(&_Value, sizeof(_Value), _Count);
    }

    void Write(void* _Ptr, size_t _Size, size_t _Count = 1);

public:
    template<typename T>
    void operator >> (T& _Value)
    {
        Read(&_Value, sizeof(_Value), sizeof(_Value), 1);
    }

    // 템플릿 특수화
    // GameEngineString만 특별하게 처리해주세요
    template<>
    void operator >> (SJString& _Value)
    {
        int Size = 0;

        Read(&Size, sizeof(int), sizeof(int), 1);

        // 24글자가 저장되어 있다.

        if (0 >= Size)
        {
            SJDebug::AssertMsg(L"Read Size if (0 >= Size)");
        }

        std::string ReadBuffer;

        ReadBuffer.resize(Size);

        Read(&ReadBuffer[0], Size, Size, 1);


        _Value.StringTowString(ReadBuffer);
    }

    template<typename KEY, typename VALUE>
    void operator >> (std::map<KEY, VALUE>& _Value)
    {
        int Size;
        this->operator>>(Size);
        
        KEY ReadKey = KEY();
        VALUE ReadValue = VALUE();

        for (int i = 0; i < Size; i++)
        {
            operator>><KEY>(ReadKey);
            operator>><VALUE>(ReadValue);

            _Value.insert(std::map<KEY, VALUE>::value_type(ReadKey, ReadValue));
        }
    }

    template<typename T>
    void ReadType(T& _Value, size_t _Count = 1)
    {
        Read(&_Value, sizeof(_Value), sizeof(_Value), _Count);
    }

    void Read(void* _Ptr, size_t _BufferSize, size_t _ReadSize, size_t _Count = 1);
};

