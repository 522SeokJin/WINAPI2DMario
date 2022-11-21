#pragma once
#include "SJPath.h"
#include "SJString.h"

// 분류 :
// 용도 : 
// 설명 : 
class SJFile;

class SJDirectory : public SJPath
{
private: // Static Var
public: // Static Func
private: // member Var

public:
    static void GetCurrentDirectoryPath(SJString& _String);
    static SJString GetCurrentDirectoryPath();

public: // constructer destructer
	SJDirectory();
	~SJDirectory();

public: // delete constructer 
    SJDirectory(const SJDirectory& _Other) = delete;
    SJDirectory(const SJDirectory&& _Other) = delete;

public: // delete operator
    SJDirectory& operator=(const SJString& _Other)
    {
    }
    SJDirectory& operator=(const SJDirectory& _Other) = delete;
    SJDirectory& operator=(const SJDirectory&& _Other) = delete;

public: // member Func
    SJString DirectoryName();

    void MoveChild(const SJString& _Path);
    void MoveParent();
    void MoveParent(const SJString& _DirName);
    std::vector<SJFile> DirectoryAllFileToVector(const SJString& _CheckPath = L"*.*");

};

