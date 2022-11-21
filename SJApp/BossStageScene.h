#pragma once
#include <SJScene.h>

// 분류 :
// 용도 : 
// 설명 : 

class EventCollider;

class BossStageScene : public SJScene
{
private: // Static Var
public: // Static Func
private: // member Var
    EventCollider* m_EventCol;

public: // constructer destructer
	BossStageScene();
	~BossStageScene();

public: // delete constructer 
    BossStageScene(const BossStageScene& _Other) = delete;
    BossStageScene(const BossStageScene&& _Other) = delete;

public: // delete operator
    BossStageScene& operator=(const BossStageScene& _Other) = delete;
    BossStageScene& operator=(const BossStageScene&& _Other) = delete;

public:
    void GlobalObjSet();
    void BlockSet();

public: // member Func
    void Start() override;
    void SceneUpdate() override;
    void SceneDebugRender() override;
};

