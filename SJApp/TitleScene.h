#pragma once
#include <SJScene.h>
#include <SJTimeEventer.h>
#include "SJCore.h"
#include "LogicValue.h"

// 분류 :
// 용도 : 
// 설명 : 

class TitleCursor;

class TitleScene : public SJScene
{
private: // Static Var
public: // Static Func
private: // member Var
    SJTimeEventer<TitleScene>   m_TitleEvent;
    TitleCursor*                m_Cursor;

public:

    void CursorOn()
    {
        LogicValue::TitleCursorRenderer->On();
    }
    void CursorOff()
    {
        LogicValue::TitleCursorRenderer->Off();
    }

    void Change1Stage()
    {
        SJCore::SceneManager.ChangeScene(L"Stage1");
    }

public: // constructer destructer
	TitleScene();
	~TitleScene();

public: // delete constructer 
    TitleScene(const TitleScene& _Other) = delete;
    TitleScene(const TitleScene&& _Other) = delete;

public: // delete operator
    TitleScene& operator=(const TitleScene& _Other) = delete;
    TitleScene& operator=(const TitleScene&& _Other) = delete;

public: // member Func
    void Start() override;
    void SceneUpdate() override;
};

