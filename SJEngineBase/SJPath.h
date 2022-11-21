#pragma once
#include "SJString.h"

// 분류 :
// 용도 : 
// 설명 : 

class SJPath : public SJString
{
public:
    static bool IsExist(const SJString& _Path);
    static SJString IOName(const SJString& _Path)
    {
        SJString ReturnName = _Path.CutIndex(_Path.find_last_index(L"\\", _Path.size() - 2), _Path.size());
        ReturnName.EraseAll(L"\\");
        return ReturnName;
    }

public:
    SJString IOName()
    {
        //SJString ReturnName = CutIndex(find_last_index(L"\\", size() - 2), size());
        //ReturnName.EraseAll(L"\\");

        return IOName(*this);
    }

public:
    SJString GetPath()
    {
        return *this;
    }

public: // Static Func
    bool IsExist();

public: // constructer destructer
	SJPath();
    SJPath(const SJString& _Path);
	~SJPath();

public: // member Func

};

