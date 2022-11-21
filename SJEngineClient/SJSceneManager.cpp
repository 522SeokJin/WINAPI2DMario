#include "SJSceneManager.h"
#include <SJDebug.h>
#include <map>

// Static Var
// Static Func

// member Var


SJSceneManager::SJSceneManager()
    : m_CurScene(nullptr)
    , m_CurSceneName()
    , m_NextScene(nullptr)

{

}

SJSceneManager::~SJSceneManager()
{
    std::map<SJString, SJScene*>::iterator iter = m_AllScene.begin();

    for (; iter != m_AllScene.end(); ++iter)
    {
        if (nullptr != iter->second)
        {
            delete iter->second;
            iter->second = nullptr;
        }
    }

    // Ȯ���ϰ��ϱ� ���� �ѹ� �� Clear�ϴ°�
    m_AllScene.clear();
}

// member Func

SJScene* SJSceneManager::FindScene(const SJString& _Name)
{
    if (m_AllScene.end() == m_AllScene.find(_Name))
    {
        return nullptr;
    }

    return m_AllScene[_Name];
}

void SJSceneManager::ChangeScene(const SJString& _Name)
{
    m_NextScene = FindScene(_Name);
    m_CurSceneName = _Name;

    if (nullptr == m_NextScene)
    {
        SJDebug::AssertMsg(L"if (nullptr == m_NextScene)");
    }
}

void SJSceneManager::ChangeCheck()
{
    if (nullptr != m_NextScene)
    {
        if (nullptr != m_CurScene)
        {
            m_CurScene->SceneChangeEnd();
        }

        m_CurScene = m_NextScene;
        m_CurScene->SetCurScene(m_NextScene);

        m_CurScene->SceneChangeStart();

        m_NextScene = nullptr;
    }
}