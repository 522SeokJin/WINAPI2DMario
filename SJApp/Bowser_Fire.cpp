#include "Bowser_Fire.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Mario.h"

// Static Var
// Static Func

// member Var

Bowser_Fire::Bowser_Fire()
	: m_Power(200.f)
	, m_JumpPower(0)
	, m_JumpMaxPower(600.f)
	, m_Col(nullptr)
	, m_SaveMarioLocation(float4::ZERO)
	, m_SaveFireLocation(float4::ZERO)
	, m_Ratio(0)
{

}

Bowser_Fire::~Bowser_Fire()
{

}

// member Func
void Bowser_Fire::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if (false == LogicValue::Mario->m_bNoDamage)
	{
		if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
		{
			LogicValue::Mario->m_FSM.ChangeState(L"POWERDOWN");
		}
	}
}

void Bowser_Fire::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Bowser_Fire::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Bowser_Fire::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Bowser_Fire_Right.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Bowser_Fire_Right.bmp")->ImageCut(5, 2);
	SJWindowResMgr::Inst().FindImage(L"Bowser_Fire_Left.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Bowser_Fire_Left.bmp")->ImageCut(5, 2);


	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::TOP_OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Fire_Right", L"Bowser_Fire_Right.bmp", 0, 1, 0.01f);
	m_AniRenderer->CreateAnimation(L"Fire_Down_Right", L"Bowser_Fire_Right.bmp", 2, 3, 0.01f);
	m_AniRenderer->CreateAnimation(L"Fire_Up_Right", L"Bowser_Fire_Right.bmp", 4, 5, 0.01f);

	m_AniRenderer->CreateAnimation(L"Fire_Left", L"Bowser_Fire_Left.bmp", 0, 1, 0.01f);
	m_AniRenderer->CreateAnimation(L"Fire_Down_Left", L"Bowser_Fire_Left.bmp", 2, 3, 0.01f);
	m_AniRenderer->CreateAnimation(L"Fire_Up_Left", L"Bowser_Fire_Left.bmp", 4, 5, 0.01f);

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::ITEM);
	m_Col->SetScale({ 36, 36 });
	m_Col->AddStartEvent(this, &Bowser_Fire::StartCollision);
	m_Col->AddStayEvent(this, &Bowser_Fire::StayCollision);
	m_Col->AddEndEvent(this, &Bowser_Fire::EndCollision);

	m_FSM.CreateState(L"IDLE", this, &Bowser_Fire::IDLEStay, &Bowser_Fire::IDLEStart, &Bowser_Fire::IDLEEnd);
	m_FSM.CreateState(L"MOVE", this, &Bowser_Fire::MOVEStay, &Bowser_Fire::MOVEStart, &Bowser_Fire::MOVEEnd);
	m_FSM.CreateState(L"MOVESTRAIGHT", this, &Bowser_Fire::MOVESTRAIGHTStay, &Bowser_Fire::MOVESTRAIGHTStart, &Bowser_Fire::MOVESTRAIGHTEnd);

	m_FSM.ChangeState(L"IDLE");
}

void Bowser_Fire::Update()
{
	m_Ratio += 1.5f * SJTimer::FDeltaTime();

	m_FSM.Update();

	MovePos(m_Move);
}

void Bowser_Fire::DebugRender()
{
	CollisionView(m_Col);
}

void Bowser_Fire::Reset()
{
	ChangeAnimation(L"Fire");

	m_SaveMarioLocation = LogicValue::Mario->GetPos();
	m_SaveMarioLocation.y -= 24.f;
	m_SaveFireLocation = GetPos();

	if (m_SaveMarioLocation.y < m_SaveFireLocation.y) // 마리오가 더 위
	{
		ChangeAnimation(L"Fire_Up");
	}
	else
	{
		ChangeAnimation(L"Fire_Down");
	}

	m_Ratio = 0;
}

//////////////////////////////////////////////////////////////	FSM

void Bowser_Fire::IDLEStart()
{
	ChangeAnimation(L"Fire");
}
void Bowser_Fire::IDLEStay()
{

}
void Bowser_Fire::IDLEEnd()
{

}

void Bowser_Fire::MOVEStart()
{
	m_SaveMarioLocation = LogicValue::Mario->GetPos();
	m_SaveMarioLocation.y -= 24.f;
	m_SaveFireLocation = GetPos();

	if (m_SaveMarioLocation.y < m_SaveFireLocation.y) // 마리오가 더 위
	{
		ChangeAnimation(L"Fire_Up");
	}
	else
	{
		ChangeAnimation(L"Fire_Down");
	}

	m_Ratio = 0;
}
void Bowser_Fire::MOVEStay()
{
	switch (m_Dir)
	{
	case eDIR::LEFT:
		SetPos(float4::Lerp2DMax(m_SaveFireLocation, float4{ m_SaveFireLocation.x - 100, m_SaveMarioLocation.y }, m_Ratio));
		break;
	case eDIR::RIGHT:
		SetPos(float4::Lerp2DMax(m_SaveFireLocation, float4{m_SaveFireLocation.x + 100, m_SaveMarioLocation.y}, m_Ratio));
		break;
	default:
		break;
	}

	if (GetPos().y == m_SaveMarioLocation.y)
	{
		m_FSM.ChangeState(L"MOVESTRAIGHT");
	}
}
void Bowser_Fire::MOVEEnd()
{

}

void Bowser_Fire::MOVESTRAIGHTStart()
{
	ChangeAnimation(L"Fire");
	m_Move = float4::ZERO;
}
void Bowser_Fire::MOVESTRAIGHTStay()
{
	m_Move.x = m_fDir.x * m_Power * SJTimer::FDeltaTime();
}
void Bowser_Fire::MOVESTRAIGHTEnd()
{

}