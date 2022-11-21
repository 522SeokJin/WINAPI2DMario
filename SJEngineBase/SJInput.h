#pragma once
#include <vector>
#include <map>
#include <cctype>

#include "SJString.h"
#include "SJDebug.h"

// �з� : 
// �뵵 : 
// ���� : ��� �Է��� ������

class SJInput
{
    class SJKey
    {
    public:
        std::vector<int> m_Key;

        bool Down;
        bool Press;
        bool Up;
        bool Free;

    public:
        template<typename ... REST>
        void PushKey(int _Key, REST ... _Arg)
        {
            if ('a' <= _Key && 'z' >= _Key)
            {
                // �ҹ��ڸ� �빮�ڷ�
                _Key = toupper(_Key);
            }

            m_Key.push_back(_Key);
            PushKey(_Arg...);
        }

        void PushKey(int _Key)
        {
            if ('a' <= _Key && 'z' >= _Key)
            {
                // �ҹ��ڸ� �빮�ڷ�.
                _Key = toupper(_Key);
            }
            m_Key.push_back(_Key);
        }

    public:
        bool KeyCheck();
        void Update();

    public:
        SJKey();
        ~SJKey();
    };

private: // Static Var
public: // Static Func
private: // member Var
    static std::map<SJString, SJKey> m_KeyMap;

    // ��Ƽ Ű ����

private:
    static SJKey& FindKey(const SJString& _Name);

public:
    template<typename ... REST>
    static void CreateKey(const SJString& _Name, REST ... _Arg)
    {
        if (m_KeyMap.end() == m_KeyMap.find(_Name))
        {
            // Ű�� �������� ���� -> ����
            m_KeyMap.insert(std::map <SJString, SJKey>::value_type(_Name, SJKey()));
        }
        else
        {
            // �̹� Ű�� �����ϴµ� �ٽ� ������� ��
            SJDebug::AssertMsg("if (m_KeyMap.end() == m_KeyMap.find(_Name))");
        }

        m_KeyMap[_Name].m_Key.reserve(sizeof ... (_Arg));
        m_KeyMap[_Name].PushKey(_Arg...);
    }

public:
    static void Update();

    static bool IsFree(const SJString& _Name);
    static bool IsUp(const SJString& _Name);
    static bool IsPress(const SJString& _Name);
    static bool IsDown(const SJString& _Name);

public: // constructer destructer
	SJInput();
	~SJInput();

public: // delete constructer 
    SJInput(const SJInput& _Other) = delete;
    SJInput(const SJInput&& _Other) = delete;

public: // delete operator
    SJInput& operator=(const SJInput& _Other) = delete;
    SJInput& operator=(const SJInput&& _Other) = delete;

public: // member Func
};

