#pragma once
#include <SJWinImage.h>
#include <map>
#include <SJString.h>

// ºÐ·ù :
// ¿ëµµ : 
// ¼³¸í : ½Ì±ÛÅæ

class SJWindowResMgr
{
private: // Static Var
public: // Static Func
    static SJWindowResMgr& Inst()
    {
        static SJWindowResMgr SingleInst;
        return SingleInst;
    }

private: // member Var
    std::map<SJString, SJWinImage*> m_Image;

public: // member Func
    SJWinImage* FindImage(const SJString& _Name);

    void ImageLoad(const SJString& _Path);

    void Release();

private: // constructer destructer
	SJWindowResMgr();
	~SJWindowResMgr();

public: // delete constructer 
    SJWindowResMgr(const SJWindowResMgr& _Other) = delete;
    SJWindowResMgr(const SJWindowResMgr&& _Other) = delete;

public: // delete operator
    SJWindowResMgr& operator=(const SJWindowResMgr& _Other) = delete;
    SJWindowResMgr& operator=(const SJWindowResMgr&& _Other) = delete;

};

