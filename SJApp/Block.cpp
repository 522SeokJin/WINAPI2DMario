#include "Block.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Mario.h"
#include "BlockPaticle.h"
#include "Object.h"

// Static Var
// Static Func

// member Var

Block::Block()
	: m_Col(nullptr)
	, m_SideCol(nullptr)
	, m_BottomCol(nullptr)
{

}

Block::~Block()
{

}

// member Func
void Block::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TERRAIN == _This->GetCheckData())
		{
			BlockLogicStartCol(_This);

			LogicValue::Mario->m_OverlapCol += 1;
		}
		else if((int)COLLISIONDATA::BOTTOM == _This->GetCheckData())
		{
			if (MARIOTYPE::SMALL != LogicValue::Mario->GetType())
			{
				SJSound::Play(L"Block_Break.wav");

				for (size_t i = 0; i < 4; i++)
				{
					LogicValue::BlockPaticle[i]->ResetPaticle();
					LogicValue::BlockPaticle[i]->SetPos(_This->GetActor()->GetPos());
					LogicValue::BlockPaticle[i]->On();
					LogicValue::BlockPaticle[i]->m_FSM.ChangeState(L"MOVE");
				}

				Death();
			}
			else
			{
				SJSound::Play(L"Bump.wav");
			}
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::MONSTER == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TERRAIN == _This->GetCheckData())
		{
			if (GetPos().iy() - 16 >= _Other->GetActor()->GetPos().iy())
			{
				
			}
			else if (GetPos().iy() - 16 < _Other->GetActor()->GetPos().iy()) // 상대가 나보다 아래에 있다.
			{
				if (_This->GetCol2DData().Left() > _Other->GetActor()->GetPos().ix() ||
					_This->GetCol2DData().Right() < _Other->GetActor()->GetPos().ix())
				{
					
				}
				// 바닥에서 친 경우
				else
				{

				}
			}
		}
	}
	if ((int)LogicValue::COLLISIONGROUP::PROJECTILE == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::SIDE == _This->GetCheckData())
		{
			SJSound::Play(L"Block_Break.wav");

			for (size_t i = 0; i < 4; i++)
			{
				LogicValue::BlockPaticle[i]->ResetPaticle();
				LogicValue::BlockPaticle[i]->SetPos(_This->GetActor()->GetPos());
				LogicValue::BlockPaticle[i]->On();
				LogicValue::BlockPaticle[i]->m_FSM.ChangeState(L"MOVE");
			}

			Object* Obj = dynamic_cast<Object*>(_Other->GetActor());

			switch (Obj->m_Dir)
			{
			case eDIR::LEFT:
				Obj->SetDir(eDIR::RIGHT);
				break;
			case eDIR::RIGHT:
				Obj->SetDir(eDIR::LEFT);
				break;
			default:
				break;
			}

			Death();
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::MARIO_PROJECTILE == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::SIDE == _This->GetCheckData())
		{
			SJSound::Play(L"Block_Break.wav");

			for (size_t i = 0; i < 4; i++)
			{
				LogicValue::BlockPaticle[i]->ResetPaticle();
				LogicValue::BlockPaticle[i]->SetPos(_This->GetActor()->GetPos());
				LogicValue::BlockPaticle[i]->On();
				LogicValue::BlockPaticle[i]->m_FSM.ChangeState(L"MOVE");
			}

			Death();
		}
	}
}

void Block::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Block::EndCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TERRAIN == _This->GetCheckData())
		{
			BlockLogicEndCol(_This);
		}
	}
}

void Block::BlockLogicStartCol(SJCollision* _Col)
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
			if (LogicValue::Mario->m_FSM.GetCurStateName().is_find(L"SIT"))
			{
				LogicValue::Mario->m_FSM.ChangeState(L"SIT");
			}
			else
			{
				LogicValue::Mario->m_FSM.ChangeState(L"IDLE");
			}
		}
	}
}

void Block::BlockLogicEndCol(SJCollision* _Col)
{
	LogicValue::Mario->m_OverlapCol -= 1;

	if (LogicValue::Mario->m_OverlapCol < 0)
	{
		SJDebug::AssertMsg(L"if (LogicValue::Mario->m_OverlapCol < 0)");
	}

	if (0 == LogicValue::Mario->m_OverlapCol)
	{
		if (true == SJInput::IsFree(L"Z"))
		{
			LogicValue::Mario->m_FSM.ChangeState(L"IDLE");
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

void Block::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Block.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Block.bmp")->ImageCut(5, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::TERRAIN_OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Block", L"Block.bmp", 0, 3, 0.15f);
	m_AniRenderer->ChangeAnimation(L"Block");

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::BLOCK);
	m_Col->SetScale({ 48, 48 });
	m_Col->SetCheckData((int)COLLISIONDATA::TERRAIN);
	m_Col->AddStartEvent(this, &Block::StartCollision);
	m_Col->AddStayEvent(this, &Block::StayCollision);
	m_Col->AddEndEvent(this, &Block::EndCollision);

	m_SideCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::BLOCK);
	m_SideCol->SetScale({ 52, 8 });
	m_SideCol->SetCheckData((int)COLLISIONDATA::SIDE);
	m_SideCol->AddStartEvent(this, &Block::StartCollision);
	m_SideCol->AddStayEvent(this, &Block::StayCollision);
	m_SideCol->AddEndEvent(this, &Block::EndCollision);

	m_BottomCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::BLOCK);
	m_BottomCol->SetScale({ 4, 4 });
	m_BottomCol->SetCheckData((int)COLLISIONDATA::BOTTOM);
	m_BottomCol->SetPivotPos({ 0, 24 });
	m_BottomCol->AddStartEvent(this, &Block::StartCollision);
	m_BottomCol->AddStayEvent(this, &Block::StayCollision);
	m_BottomCol->AddEndEvent(this, &Block::EndCollision);
}

void Block::Update()
{

}

void Block::DebugRender()
{
	CollisionView(m_Col);
	CollisionView(m_SideCol);
	CollisionView(m_BottomCol);
}