#include "ItemBox.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>

#include "Mushroom.h"
#include "RacoonLeaf.h"
#include "Mario.h"

//#include "Coin.h"

// Static Var
// Static Func

// member Var

ItemBox::ItemBox()
	: m_Item(nullptr)
	, m_ItemType(ITEMTYPE::COIN)
	, m_SideCol(nullptr)
	, m_BottomCol(nullptr)
	, m_CoinPower(1000.f)
{

}

ItemBox::~ItemBox()
{

}

// member Func

void ItemBox::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::BOTTOM == _This->GetCheckData())
		{
			CollisionEvent(_This);
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::PROJECTILE == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::SIDE == _This->GetCheckData())
		{
			CollisionEvent(_This);
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::MARIO_PROJECTILE == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::SIDE == _This->GetCheckData())
		{
			CollisionEvent(_This);
		}
	}
}

void ItemBox::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void ItemBox::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void ItemBox::MoveUp()
{
	SetPos({ GetPos().x, GetPos().y - 15 });
}
void ItemBox::MoveDown()
{
	SetPos({ GetPos().x, GetPos().y + 15 });
}

void ItemBox::ItemSound()
{
	SJSound::Play(L"Item_Box.wav");
}

void ItemBox::BumpSound()
{
	SJSound::Play(L"Bump.wav");
}

void ItemBox::CoinSound()
{
	SJSound::Play(L"Coin.wav");
}

void ItemBox::CoinMoveUp()
{
	if (nullptr != m_Item)
	{
		m_Item->MovePos(float4::UP * SJTimer::FDeltaTime() * m_CoinPower);
		
		m_CoinPower -= m_Gravity * SJTimer::FDeltaTime();
	}
}

void ItemBox::MushroomMoveUp()
{
	if (nullptr != m_Item)
	{
		m_Item->MovePos(float4::UP * SJTimer::FDeltaTime() * 49.f * 1.25f);
	}
}

void ItemBox::MushroomCollisionOn()
{
	if (nullptr != m_Item)
	{
		Mushroom* MushroomObj = dynamic_cast<Mushroom*>(m_Item);
		MushroomObj->CollisionOn();

		if (LogicValue::Mario->GetPos().x >= MushroomObj->GetPos().x)
		{
			MushroomObj->SetDir(eDIR::LEFT);
		}
		else
		{
			MushroomObj->SetDir(eDIR::RIGHT);
		}

		MushroomObj->m_FSM.ChangeState(L"MOVE");
	}
}

void ItemBox::ItemOn()
{
	if (nullptr != m_Item)
	{
		m_Item->On();
	}
}

void ItemBox::ItemOff()
{
	if (nullptr != m_Item)
	{
		m_Item->Off();
	}
}

void ItemBox::MushroomOn()
{
	if (nullptr != m_Item)
	{
		m_Item->On();
		Mushroom* MushroomObj = dynamic_cast<Mushroom*>(m_Item);
		MushroomObj->CollisionOff();
	}
}

void ItemBox::RacoonLeafOn()
{
	if (nullptr != m_Item)
	{
		m_Item->On();
		RacoonLeaf* RacoonLeafObj = dynamic_cast<RacoonLeaf*>(m_Item);
		RacoonLeafObj->CollisionOff();
	}
}

void ItemBox::Start()
{
	SJWindowResMgr::Inst().FindImage(L"ItemBox.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"ItemBox.bmp")->ImageCut(5, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::TERRAIN_OBJECT);
	m_AniRenderer->SetRenderScale({ 128, 128 });
	m_AniRenderer->CreateAnimation(L"Idle", L"ItemBox.bmp", 0, 3, 0.125f);
	m_AniRenderer->CreateAnimation(L"Empty", L"ItemBox.bmp", 4, 4);
	m_AniRenderer->ChangeAnimation(L"Idle");

	m_SideCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::ITEMBOX);
	m_SideCol->SetScale({ 52, 4 });
	m_SideCol->SetCheckData((int)COLLISIONDATA::SIDE);
	m_SideCol->AddStartEvent(this, &ItemBox::StartCollision);
	m_SideCol->AddStayEvent(this, &ItemBox::StayCollision);
	m_SideCol->AddEndEvent(this, &ItemBox::EndCollision);

	m_BottomCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::ITEMBOX);
	m_BottomCol->SetScale({ 4, 4 });
	m_BottomCol->SetCheckData((int)COLLISIONDATA::BOTTOM);
	m_BottomCol->SetPivotPos({ 0, 24 });
	m_BottomCol->AddStartEvent(this, &ItemBox::StartCollision);
	m_BottomCol->AddStayEvent(this, &ItemBox::StayCollision);
	m_BottomCol->AddEndEvent(this, &ItemBox::EndCollision);
}

void ItemBox::Update()
{
	m_CollisionEventer.Update();
	m_CoinEventer.Update();
	m_MushroomEventer.Update();

	if (false == m_BottomCol->IsOn())
	{
		m_SideCol->Off();
	}
	if (false == m_SideCol->IsOn())
	{
		m_BottomCol->Off();
	}
}

void ItemBox::DebugRender()
{
	CollisionView(m_SideCol);
	CollisionView(m_BottomCol);
}

void ItemBox::CollisionEvent(SJCollision* _Col)
{
	m_CollisionEventer.CreateTimeEvent(0.02f, this, &ItemBox::MoveUp);
	m_CollisionEventer.CreateTimeEvent(0.02f, this, &ItemBox::MoveUp);
	m_CollisionEventer.CreateTimeEvent(0.02f, this, &ItemBox::MoveDown);
	m_CollisionEventer.CreateTimeEvent(0.02f, this, &ItemBox::MoveDown);

	switch (m_ItemType)
	{
	case ITEMTYPE::COIN:
		SJSound::Play(L"Coin.wav");

		m_CoinEventer.CreateTimeEventStay(0.6f, this, &ItemBox::CoinMoveUp);
		m_CoinEventer.CreateTimeEvent(0.1f, this, &ItemBox::ItemOff);
		break;
	case ITEMTYPE::MUSHROOM:
		m_CollisionEventer.CreateTimeEvent(0.01f, this, &ItemBox::ItemSound);
		m_CollisionEventer.CreateTimeEvent(0.01f, this, &ItemBox::MushroomOn);
		m_MushroomEventer.CreateTimeEventStay(0.75f, this, &ItemBox::MushroomMoveUp);
		m_MushroomEventer.CreateTimeEvent(0.1f, this, &ItemBox::MushroomCollisionOn);
		break;
	case ITEMTYPE::RACOONMARIO:
		m_CollisionEventer.CreateTimeEvent(0.01f, this, &ItemBox::BumpSound);
		m_CollisionEventer.CreateTimeEvent(0.01f, this, &ItemBox::RacoonLeafOn);
		break;
	default:
		break;
	}

	m_AniRenderer->ChangeAnimation(L"Empty");
	_Col->Off();
}