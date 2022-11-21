#include "Plant_Fire.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Mario.h"

// Static Var
// Static Func

// member Var

Plant_Fire::Plant_Fire()
	: m_Power(200.f)
	, m_Col(nullptr)
{

}

Plant_Fire::~Plant_Fire()
{

}

// member Func
void Plant_Fire::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if (false == LogicValue::Mario->m_bNoDamage)
	{
		if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
		{
			LogicValue::Mario->m_FSM.ChangeState(L"POWERDOWN");
		}
	}
}

void Plant_Fire::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Plant_Fire::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Plant_Fire::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Plant_Fire.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Plant_Fire.bmp")->ImageCut(5, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::TOP_OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Fire", L"Plant_Fire.bmp", 0, 3);

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER_PROJECTILE);
	m_Col->SetScale({ 24, 24 });
	m_Col->AddStartEvent(this, &Plant_Fire::StartCollision);
	m_Col->AddStayEvent(this, &Plant_Fire::StayCollision);
	m_Col->AddEndEvent(this, &Plant_Fire::EndCollision);

	m_FSM.CreateState(L"IDLE", this, &Plant_Fire::IDLEStay, &Plant_Fire::IDLEStart, &Plant_Fire::IDLEEnd);
	m_FSM.CreateState(L"MOVE", this, &Plant_Fire::MOVEStay, &Plant_Fire::MOVEStart, &Plant_Fire::MOVEEnd);

	m_FSM.ChangeState(L"IDLE");
}

void Plant_Fire::Update()
{
	m_FSM.Update();

	MovePos(m_Move);
}

void Plant_Fire::DebugRender()
{
	CollisionView(m_Col);
}

//////////////////////////////////////////////////////////////	FSM

void Plant_Fire::IDLEStart()
{
	m_AniRenderer->ChangeAnimation(L"Fire");
}
void Plant_Fire::IDLEStay()
{

}
void Plant_Fire::IDLEEnd()
{

}

void Plant_Fire::MOVEStart()
{
	float4 SubBuff = LogicValue::Mario->GetPos() - GetPos();

	m_Radian = atan2f(SubBuff.y - 24, SubBuff.x);

}
void Plant_Fire::MOVEStay()
{
	m_Move.x = cosf(m_Radian) * m_Power * SJTimer::FDeltaTime();
	m_Move.y = sinf(m_Radian) * m_Power * SJTimer::FDeltaTime();
}
void Plant_Fire::MOVEEnd()
{

}