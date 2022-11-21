#pragma once
#include <map>
#include <SJString.h>
#include "SJScene.h"

// �з� : ������Ʈ
// �뵵 : �Ŵ�����Ʈ
// ���� : ���� ������ ������ ����� ���� �����ְ� �� ������ �����ϴ� ����� �����Ѵ�.

class SJSceneManager
{
private: // Static Var
public: // Static Func
private: // member Var
    std::map<SJString, SJScene*> m_AllScene;

    SJScene*                    m_CurScene;
    SJString                    m_CurSceneName;
    SJScene*                    m_NextScene;

public:
    SJScene* GetCurScene()
    {
        return m_CurScene;
    }

    SJString GetCurSceneName()
    {
        return m_CurSceneName;
    }

public:
    // ���ο� Scene�� ����� ���
    template<typename SceneType>
    SJScene* CreateScene(const SJString& _Name)
    {
        std::map<SJString, SJScene*>::iterator Finditer = m_AllScene.find(_Name);

        if (m_AllScene.end() != Finditer)
        {
            // ã�Ҵ�.
            return m_AllScene[_Name];
            //return Finditer->second; // ���� �ǹ��̴�.
        }

        SceneType* NewScene = new SceneType();

        //NewScene->Start();

        m_AllScene.insert(std::map<SJString, SJScene*>::value_type(_Name, NewScene));

        return NewScene;
    }

    // Ư�� Scene�� �����ϴ� ����� �ʿ�ÿ� ����

    // Ư�� Scene�� ã���ִ� ���
    SJScene* FindScene(const SJString& _Name);
    
    // ��� Scene�� ������ �ϴ� ��� �ʿ����

    
    void ChangeScene(const SJString& _Name);

    void ChangeCheck();

public: // constructer destructer
	SJSceneManager();
	~SJSceneManager();

public: // delete constructer 
    SJSceneManager(const SJSceneManager& _Other) = delete;
    SJSceneManager(const SJSceneManager&& _Other) = delete;

public: // delete operator
    SJSceneManager& operator=(const SJSceneManager& _Other) = delete;
    SJSceneManager& operator=(const SJSceneManager&& _Other) = delete;

public: // member Func
};

