#include "SJWindowResMgr.h"
#include <SJPath.h>
#include <SJDebug.h>

// Static Var
// Static Func

// member Var

SJWindowResMgr::SJWindowResMgr()
{

}

SJWindowResMgr::~SJWindowResMgr()
{
    Release();
}

// member Func

void SJWindowResMgr::Release()
{
    std::map<SJString, SJWinImage*>::iterator iter = m_Image.begin();

    for (; iter != m_Image.end(); ++iter)
    {
        if (nullptr != iter->second)
        {
            delete iter->second;
            iter->second = nullptr;
        }
    }

    m_Image.clear();
}

SJWinImage* SJWindowResMgr::FindImage(const SJString& _Name)
{
    if (m_Image.end() == m_Image.find(_Name))
    {
        return nullptr;
    }

    // iterator로 찾고 second까지 복사를 다 해준다.
    // 내부에서 알아서 동작
    return m_Image[_Name];
}

void SJWindowResMgr::ImageLoad(const SJString& _Path)
{
    SJString FileName = SJPath::IOName(_Path);

    if (nullptr != FindImage(FileName))
    {
        SJDebug::AssertMsg(L"if (nullptr != FindImage(FileName))");
        return;
    }

    SJWinImage* NewImage = new SJWinImage();
    NewImage->Load(_Path);
    m_Image.insert(std::map<SJString, SJWinImage*>::value_type(FileName, NewImage));
}

