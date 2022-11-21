#pragma once
#include <SJScene.h>
#include <SJTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 

class BonusCard;
class Course_Clear;
class You_Got_A_Card;
class EventCollider;

class Stage1Scene : public SJScene
{
private: // Static Var
public: // Static Func
private: // member Var
    BonusCard*          m_CardObject;
    BonusCard*          m_UICardObject;
    Course_Clear*       m_FontObject1;
    You_Got_A_Card*     m_FontObject2;
    EventCollider*      m_EventCol[2];

private:
    SJTimeEventer<Stage1Scene>   m_ClearEventer;

public:
    void ClearFontOn1();
    void ClearFontOn2();
    void GoToBossStage();

public:
    void GlobalObjSet();
    void ItemBoxSet();
    void CoinSet();
    void BlockSet();
    void MonsterSet();


public: // constructer destructer
	Stage1Scene();
	~Stage1Scene();

public: // delete constructer 
    Stage1Scene(const Stage1Scene& _Other) = delete;
    Stage1Scene(const Stage1Scene&& _Other) = delete;

public: // delete operator
    Stage1Scene& operator=(const Stage1Scene& _Other) = delete;
    Stage1Scene& operator=(const Stage1Scene&& _Other) = delete;

public: // member Func
    void Start() override;
    void SceneUpdate() override;
    void SceneDebugRender() override;
};

