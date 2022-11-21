#include "BonusEffect.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include "StageBonus.h"

// Static Var
// Static Func

// member Var

BonusEffect::BonusEffect()
	: m_bMoveOn(false)
{

}

BonusEffect::~BonusEffect()
{

}

// member Func

void BonusEffect::Start()
{
	SJWindowResMgr::Inst().FindImage(L"BonusEffect.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"BonusEffect.bmp")->ImageCut(5, 3);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Mushroom", L"BonusEffect.bmp", 0, 3, 0.05f);
	m_AniRenderer->CreateAnimation(L"Flower", L"BonusEffect.bmp", 4, 7, 0.05f);
	m_AniRenderer->CreateAnimation(L"Star", L"BonusEffect.bmp", 8, 11, 0.05f);

}

void BonusEffect::Update()
{
	if (true == m_bMoveOn)
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
			break;
		}

		m_Move = float4::UP * SJTimer::FDeltaTime() * 400.f;
		MovePos(m_Move);
	}
}

void BonusEffect::DebugRender()
{

}