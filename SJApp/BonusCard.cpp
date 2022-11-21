#include "BonusCard.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>

// Static Var
// Static Func

// member Var

BonusCard::BonusCard()
{

}

BonusCard::~BonusCard()
{

}

// member Func


void BonusCard::Start()
{
	SJWindowResMgr::Inst().FindImage(L"BonusCard.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"BonusCard.bmp")->ImageCut(5, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::UI_OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Mushroom", L"BonusCard.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Flower", L"BonusCard.bmp", 1, 1);
	m_AniRenderer->CreateAnimation(L"Star", L"BonusCard.bmp", 2, 2);
	m_AniRenderer->CreateAnimation(L"None", L"BonusCard.bmp", 3, 3);
	m_AniRenderer->ChangeAnimation(L"None");
}

void BonusCard::Update()
{
	if (true == LogicValue::bCleared)
	{
		switch (LogicValue::Bonus)
		{
		case LogicValue::BONUSTYPE::MUSHROOM:
			m_AniRenderer->ChangeAnimation(L"Mushroom");
			break;
		case LogicValue::BONUSTYPE::FLOWER:
			m_AniRenderer->ChangeAnimation(L"Flower");
			break;
		case LogicValue::BONUSTYPE::STAR:
			m_AniRenderer->ChangeAnimation(L"Star");
			break;
		default:
			m_AniRenderer->ChangeAnimation(L"None");
			break;
		}
	}
}

void BonusCard::DebugRender()
{

}