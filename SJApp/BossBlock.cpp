#include "BossBlock.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Mario.h"
#include "Bowser.h"
#include "LogicValue.h"
#include "BossBlockPaticle.h"

// Static Var
// Static Func

// member Var

BossBlock::BossBlock()
	: m_Col(nullptr)
	, m_SideCol(nullptr)
	, m_BottomCol(nullptr)
{

}

BossBlock::~BossBlock()
{

}

// member Func
void BossBlock::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TERRAIN == _This->GetCheckData())
		{
			BossBlockLogicStartCol(_This);

			LogicValue::Mario->m_OverlapCol += 1;
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::MARIO_PROJECTILE == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::SIDE == _This->GetCheckData())
		{
			SJSound::Play(L"Block_Break.wav");

			for (size_t i = 0; i < 4; i++)
			{
				LogicValue::BossBlockPaticle[i]->ResetPaticle();
				LogicValue::BossBlockPaticle[i]->SetPos(LogicValue::Bowser->GetPos());
				LogicValue::BossBlockPaticle[i]->On();
				LogicValue::BossBlockPaticle[i]->m_FSM.ChangeState(L"MOVE");
			}

			Death();
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::MONSTER == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::BOTTOM == _Other->GetCheckData())
		{
			if ((int)COLLISIONDATA::TERRAIN == _This->GetCheckData())
			{
				LogicValue::Bowser->m_FSM.ChangeState(L"ATTACKAFTERFALL");

				SJSound::Play(L"Block_Break.wav");

				for (size_t i = 0; i < 4; i++)
				{
					LogicValue::BossBlockPaticle[i]->ResetPaticle();
					LogicValue::BossBlockPaticle[i]->SetPos(LogicValue::Bowser->GetPos());
					LogicValue::BossBlockPaticle[i]->On();
					LogicValue::BossBlockPaticle[i]->m_FSM.ChangeState(L"MOVE");
				}

				_Other->Off();

				Off();
			}
		}

		if ((int)COLLISIONDATA::NORMAL == _Other->GetCheckData())
		{
			if ((int)COLLISIONDATA::TERRAIN == _This->GetCheckData())
			{
				if (SJString(L"ATTACKAFTERFALL") == LogicValue::Bowser->m_FSM.GetCurStateName())
				{
					LogicValue::Bowser->m_FSM.ChangeState(L"FIND");
				}

				if (SJString(L"FALL") == LogicValue::Bowser->m_FSM.GetCurStateName())
				{
					LogicValue::Bowser->m_FSM.ChangeState(L"IDLE");
				}
			}
		}
	}
}

void BossBlock::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void BossBlock::EndCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TERRAIN == _This->GetCheckData())
		{
			BossBlockLogicEndCol(_This);
		}
	}
}

void BossBlock::BossBlockLogicStartCol(SJCollision* _Col)
{
	if (GetPos().iy() - 16 >= LogicValue::Mario->GetPos().iy())
	{
		LogicValue::Mario->m_FSM.ChangeState(L"BLOCKIDLE");
	}
	else if (GetPos().iy() - 16 < LogicValue::Mario->GetPos().iy()) // 상대가 나보다 아래에 있다.
	{
		// 왼쪽, 오른쪽에서 친 경우
		if (_Col->GetCol2DData().Left() > LogicValue::Mario->GetPos().ix())
		{
			LogicValue::Mario->m_RightKeyLock = true;

			if (LogicValue::Mario->m_RunPos.x > 0)
			{
				LogicValue::Mario->m_RunPos = 0;
			}
		}
		else if (_Col->GetCol2DData().Right() < LogicValue::Mario->GetPos().ix())
		{
			LogicValue::Mario->m_LeftKeyLock = true;

			if (LogicValue::Mario->m_RunPos.x < 0)
			{
				LogicValue::Mario->m_RunPos = 0;
			}
		}
		// 바닥에서 친 경우
		else
		{
			LogicValue::Mario->m_FSM.ChangeState(L"IDLE");
		}
	}
}

void BossBlock::BossBlockLogicEndCol(SJCollision* _Col)
{
	LogicValue::Mario->m_OverlapCol -= 1;

	if (LogicValue::Mario->m_OverlapCol < 0)
	{
		LogicValue::Mario->m_OverlapCol = 0;
	}

	if (0 == LogicValue::Mario->m_OverlapCol)
	{
		if (SJString(L"DEAD") != LogicValue::Mario->m_FSM.GetCurStateName())
		{
			if (true == SJInput::IsFree(L"Z"))
			{
				LogicValue::Mario->m_FSM.ChangeState(L"IDLE");
			}
		}
	}

	// 왼쪽, 오른쪽에서 친 경우
	if (_Col->GetCol2DData().Left() > LogicValue::Mario->GetPos().ix())
	{
		LogicValue::Mario->m_RightKeyLock = false;
	}
	else if (_Col->GetCol2DData().Right() < LogicValue::Mario->GetPos().ix())
	{
		LogicValue::Mario->m_LeftKeyLock = false;
	}
}

void BossBlock::Start()
{
	SJWindowResMgr::Inst().FindImage(L"BossBlock.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"BossBlock.bmp")->ImageCut(1, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::TERRAIN_OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"BossBlock", L"BossBlock.bmp", 0, 0);
	m_AniRenderer->ChangeAnimation(L"BossBlock");

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::BLOCK);
	m_Col->SetScale({ 48, 48 });
	m_Col->SetCheckData((int)COLLISIONDATA::TERRAIN);
	m_Col->AddStartEvent(this, &BossBlock::StartCollision);
	m_Col->AddStayEvent(this, &BossBlock::StayCollision);
	m_Col->AddEndEvent(this, &BossBlock::EndCollision);

	m_SideCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::BLOCK);
	m_SideCol->SetScale({ 52, 4 });
	m_SideCol->SetCheckData((int)COLLISIONDATA::SIDE);
	m_SideCol->AddStartEvent(this, &BossBlock::StartCollision);
	m_SideCol->AddStayEvent(this, &BossBlock::StayCollision);
	m_SideCol->AddEndEvent(this, &BossBlock::EndCollision);

	m_BottomCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::BLOCK);
	m_BottomCol->SetScale({ 4, 4 });
	m_BottomCol->SetCheckData((int)COLLISIONDATA::BOTTOM);
	m_BottomCol->SetPivotPos({ 0, 24 });
	m_BottomCol->AddStartEvent(this, &BossBlock::StartCollision);
	m_BottomCol->AddStayEvent(this, &BossBlock::StayCollision);
	m_BottomCol->AddEndEvent(this, &BossBlock::EndCollision);
}

void BossBlock::Update()
{

}

void BossBlock::DebugRender()
{
	CollisionView(m_Col);
	CollisionView(m_SideCol);
	CollisionView(m_BottomCol);
}