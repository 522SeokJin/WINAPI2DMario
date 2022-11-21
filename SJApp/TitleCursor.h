#pragma once
#include <SJActor.h>
#include <SJTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 

class TitleCursor : public SJActor
{
private: // Static Var
public: // Static Func
private: // member Var
    bool m_Lock;
public:
    bool m_Start;

public: // constructer destructer
	TitleCursor();
	~TitleCursor();

public: // delete constructer 
    TitleCursor(const TitleCursor& _Other) = delete;
    TitleCursor(const TitleCursor&& _Other) = delete;

public: // delete operator
    TitleCursor& operator=(const TitleCursor& _Other) = delete;
    TitleCursor& operator=(const TitleCursor&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override; // 돈다
};

