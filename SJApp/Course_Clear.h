#pragma once
#include "Object.h"

// 분류 :
// 용도 : 
// 설명 : 

class SJRendererBasic;

class Course_Clear : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    SJRendererBasic*     m_Renderer;

public: // constructer destructer
    Course_Clear();
    ~Course_Clear();

public: // delete constructer 
    Course_Clear(const Course_Clear& _Other) = delete;
    Course_Clear(const Course_Clear&& _Other) = delete;

public: // delete operator
    Course_Clear& operator=(const Course_Clear& _Other) = delete;
    Course_Clear& operator=(const Course_Clear&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override; // 돈다
};

