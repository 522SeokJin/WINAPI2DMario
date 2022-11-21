#pragma once
#include <map>
#include <SJString.h>
#include "SJScene.h"

// 분류 : 오브젝트
// 용도 : 매니지먼트
// 설명 : 내가 생각한 장면들을 만드는 것을 도와주고 그 장면들을 관리하는 방식을 정의한다.

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
    // 새로운 Scene을 만드는 기능
    template<typename SceneType>
    SJScene* CreateScene(const SJString& _Name)
    {
        std::map<SJString, SJScene*>::iterator Finditer = m_AllScene.find(_Name);

        if (m_AllScene.end() != Finditer)
        {
            // 찾았다.
            return m_AllScene[_Name];
            //return Finditer->second; // 같은 의미이다.
        }

        SceneType* NewScene = new SceneType();

        //NewScene->Start();

        m_AllScene.insert(std::map<SJString, SJScene*>::value_type(_Name, NewScene));

        return NewScene;
    }

    // 특정 Scene을 삭제하는 기능은 필요시에 만듬

    // 특정 Scene을 찾아주는 기능
    SJScene* FindScene(const SJString& _Name);
    
    // 모든 Scene을 가지고 하는 기능 필요없음

    
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

