#include "Piranha_Plant.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include <SJWindow.h>
#include <SJCollision.h>
#include "Plant_Fire.h"
#include "Mario.h"

#include "LogicValue.h"

// Static Var
// Static Func

// member Var

Piranha_Plant::Piranha_Plant()
	: m_Color(PLANTCOLOR::GREEN)
	, m_Type(PLANTTYPE::NORMAL)
	, m_FireDir(PLANTFIREDIR::NONE)
	, m_Fire(nullptr)
	, m_Col(nullptr)
	, m_SaveLocation(float4::ZERO)
	, m_Ratio(0)
	, m_fWait(0)
{

}

Piranha_Plant::~Piranha_Plant()
{

}

// member Func

void Piranha_Plant::StartCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Piranha_Plant::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Piranha_Plant_Left.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Piranha_Plant_Left.bmp")->ImageCut(5, 3);
	SJWindowResMgr::Inst().FindImage(L"Piranha_Plant_Right.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Piranha_Plant_Right.bmp")->ImageCut(5, 3);

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER);
	m_Col->SetScale({ 48, 96 });
	m_Col->SetCheckData((int)COLLISIONDATA::NORMAL);
	m_Col->AddStartEvent(this, &Piranha_Plant::StartCollision);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::MONSTER);
	m_AniRenderer->SetRenderScale({ 256, 256 });

	m_AniRenderer->CreateAnimation(L"Green_Idle_Left", L"Piranha_Plant_Left.bmp", 0, 1, 0.2f);
	m_AniRenderer->CreateAnimation(L"Green_Idle_Down_Left", L"Piranha_Plant_Left.bmp", 2, 3, 0.2f);
	m_AniRenderer->CreateAnimation(L"Green_Idle_Up_Left", L"Piranha_Plant_Left.bmp", 4, 5, 0.2f);
	m_AniRenderer->CreateAnimation(L"Red_Idle_Left", L"Piranha_Plant_Left.bmp", 6, 7, 0.2f);
	m_AniRenderer->CreateAnimation(L"Red_Idle_Down_Left", L"Piranha_Plant_Left.bmp", 8, 9, 0.2f);
	m_AniRenderer->CreateAnimation(L"Red_Idle_Up_Left", L"Piranha_Plant_Left.bmp", 10, 11, 0.2f);

	m_AniRenderer->CreateAnimation(L"Green_Idle_Right", L"Piranha_Plant_Right.bmp", 0, 1, 0.2f);
	m_AniRenderer->CreateAnimation(L"Green_Idle_Down_Right", L"Piranha_Plant_Right.bmp", 2, 3, 0.2f);
	m_AniRenderer->CreateAnimation(L"Green_Idle_Up_Right", L"Piranha_Plant_Right.bmp", 4, 5, 0.2f);
	m_AniRenderer->CreateAnimation(L"Red_Idle_Right", L"Piranha_Plant_Right.bmp", 6, 7, 0.2f);
	m_AniRenderer->CreateAnimation(L"Red_Idle_Down_Right", L"Piranha_Plant_Right.bmp", 8, 9, 0.2f);
	m_AniRenderer->CreateAnimation(L"Red_Idle_Up_Right", L"Piranha_Plant_Right.bmp", 10, 11, 0.2f);

	m_FSM.CreateState(L"IDLE", this, &Piranha_Plant::IDLEStay, &Piranha_Plant::IDLEStart, &Piranha_Plant::IDLEEnd);
	m_FSM.CreateState(L"MOVEUP", this, &Piranha_Plant::MOVEUPStay, &Piranha_Plant::MOVEUPStart, &Piranha_Plant::MOVEUPEnd);
	m_FSM.CreateState(L"MOVEDOWN", this, &Piranha_Plant::MOVEDOWNStay, &Piranha_Plant::MOVEDOWNStart, &Piranha_Plant::MOVEDOWNEnd);
	m_FSM.CreateState(L"FIRE", this, &Piranha_Plant::FIREStay, &Piranha_Plant::FIREStart, &Piranha_Plant::FIREEnd);

	m_FSM.ChangeState(L"IDLE");
}

void Piranha_Plant::Update()
{
	SetFireDir();
	
	m_FSM.Update();

	MovePos(m_Move);
}

void Piranha_Plant::DebugRender()
{
	CollisionView(m_Col);
}

void Piranha_Plant::ChangeAnimation(const SJString& _Name)
{
	// m_Color(PLANTCOLOR::GREEN)
	// m_Type(PLANTTYPE::NORMAL)
	// m_FireDir(PLANTFIREDIR::NONE)

	SJString AniName;

	switch (m_Color)
	{
	case PLANTCOLOR::GREEN:
		AniName += L"Green_";
		break;
	case PLANTCOLOR::RED:
		AniName += L"Red_";
		break;
	default:
		break;
	}

	m_CurAniName = _Name;
	AniName += m_CurAniName;

	if (PLANTTYPE::FIRE == m_Type)
	{
		switch (m_FireDir)
		{
		case PLANTFIREDIR::NONE:
			SJDebug::AssertMsg(L"if (PLANTTYPE::FIRE == m_Type)");
			break;
		case PLANTFIREDIR::UP:
			AniName += L"_Up";
			break;
		case PLANTFIREDIR::DOWN:
			AniName += L"_Down";
			break;
		default:
			break;
		}
	}

	switch (m_Dir)
	{
	case eDIR::LEFT:
		AniName += L"_Left";
		break;
	case eDIR::RIGHT:
		AniName += L"_Right";
		break;
	default:
		break;
	}

	m_AniRenderer->ChangeAnimation(AniName);
}

void Piranha_Plant::Fire()
{
	float4 FirePos = GetPos();
	FirePos.y -= 24;

	m_Fire->On();
	m_Fire->SetPos(FirePos);
	m_Fire->m_FSM.ChangeState(L"MOVE");
}

void Piranha_Plant::SetFireDir()
{
	if (PLANTTYPE::FIRE == m_Type)
	{
		if (LogicValue::Mario->GetPos().y - GetPos().y >= 0)
		{
			m_FireDir = PLANTFIREDIR::DOWN;
		}
		else
		{
			m_FireDir = PLANTFIREDIR::UP;
		}
	}

	if (LogicValue::Mario->GetPos().x - GetPos().x >= 0)
	{
		SetDir(eDIR::RIGHT);
	}
	else
	{
		SetDir(eDIR::LEFT);
	}
}