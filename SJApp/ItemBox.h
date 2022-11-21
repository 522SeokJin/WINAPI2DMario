#pragma once
#include "Object.h"
#include <SJTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 

enum class ITEMTYPE
{
    COIN,
    MUSHROOM,
    RACOONMARIO,
};

class ItemBox : public Object
{
private: // Static Var
public: // Static Func
private: // member Var
    SJActor*        m_Item;
    ITEMTYPE        m_ItemType;

    SJCollision*    m_SideCol;
    SJCollision*    m_BottomCol;

    float           m_CoinPower;

private:
    SJTimeEventer<ItemBox>    m_CollisionEventer;
    SJTimeEventer<ItemBox>    m_CoinEventer;
    SJTimeEventer<ItemBox>    m_MushroomEventer;

    void CollisionEvent(SJCollision* _Col);

    void MoveUp();
    void MoveDown();

    void ItemSound();
    void CoinSound();
    void BumpSound();

    void ItemOn();
    void ItemOff();

    void CoinMoveUp();

    void MushroomMoveUp();
    void MushroomOn();
    void MushroomCollisionOn();

    void RacoonLeafOn();

public: // constructer destructer
	ItemBox();
	~ItemBox();

public: // delete constructer 
    ItemBox(const ItemBox& _Other) = delete;
    ItemBox(const ItemBox&& _Other) = delete;

public: // delete operator
    ItemBox& operator=(const ItemBox& _Other) = delete;
    ItemBox& operator=(const ItemBox&& _Other) = delete;

public:
    void SetItem(SJActor* _Item)
    {
        m_Item = _Item;
    }

    void SetItemType(ITEMTYPE _ITEM)
    {
        m_ItemType = _ITEM;
    }

public:
    void StartCollision(SJCollision* _This, SJCollision* _Other);
    void StayCollision(SJCollision* _This, SJCollision* _Other);
    void EndCollision(SJCollision* _This, SJCollision* _Other);

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

};

