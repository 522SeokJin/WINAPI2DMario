#include "Koopa_Troopa.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include <SJWindow.h>
#include <SJCollision.h>
#include "Mario.h"

#include "LogicValue.h"

// Static Var
// Static Func

// member Var

Koopa_Troopa::Koopa_Troopa()
	: m_Type(TROOPATYPE::NORMAL)
	, m_RunPos(float4::ZERO)
	, m_JumpPos(float4::ZERO)
	, m_JumpPower(0)
	, m_JumpMaxPower(600.f)
	, m_Power(100.f)
	, m_KickPower(500.f)
	, m_Col(nullptr)
	, m_TopCol(nullptr)
	, m_EventCol(nullptr)
	, m_ProjectileCol(nullptr)
	, m_ReviveTime(0.25f)
{

}

Koopa_Troopa::~Koopa_Troopa()
{

}

// member Func

void Koopa_Troopa::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::EVENT == _This->GetCheckData())
		{
			m_EventCol->Off();

			if (true == SJInput::IsPress(L"X") && false == LogicValue::Mario->IsCarry())
			{
				m_Col->Off();
				m_TopCol->Off();
				m_ProjectileCol->Off();
				return;
			}
			
			if (true == SJInput::IsFree(L"X"))
			{
				m_Col->Off();
				m_TopCol->On();
				m_ProjectileCol->On();

				if (GetPos().x < LogicValue::Mario->GetPos().x)
				{
					m_Dir = eDIR::LEFT;
					m_fDir = float4::LEFT;
					LogicValue::Mario->SetDir(eDIR::LEFT);
				}

				if (GetPos().x >= LogicValue::Mario->GetPos().x)
				{
					m_Dir = eDIR::RIGHT;
					m_fDir = float4::RIGHT;
					LogicValue::Mario->SetDir(eDIR::RIGHT);
				}

				m_FSM.ChangeState(L"KICKED");
			}
		}
		
	}

	if ((int)LogicValue::COLLISIONGROUP::PROJECTILE == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TOP != _This->GetCheckData())
		{
			SJSound::Play(L"Kick.wav");

			m_Col->Off();
			m_TopCol->Off();
			m_EventCol->Off();
			m_ProjectileCol->Off();

			m_FSM.ChangeState(L"DEAD");
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::MARIO_PROJECTILE == _Other->GetOrder())
	{

		if ((int)COLLISIONDATA::TOP != _This->GetCheckData())
		{
			SJSound::Play(L"Kick.wav");

			m_Col->Off();
			m_TopCol->Off();
			m_EventCol->Off();
			m_ProjectileCol->Off();

			m_FSM.ChangeState(L"DEAD");
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::MONSTER == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::SIDE == _This->GetCheckData() && (int)COLLISIONDATA::SIDE == _Other->GetCheckData())
		{
			switch (m_Dir)
			{
			case eDIR::LEFT:
				m_Dir = eDIR::RIGHT;
				m_fDir = float4::RIGHT;
				break;
			case eDIR::RIGHT:
				m_Dir = eDIR::LEFT;
				m_fDir = float4::LEFT;
				break;
			default:
				break;
			}
		}
	}
}

void Koopa_Troopa::StayCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Koopa_Troopa::EndCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TOP == _This->GetCheckData())
		{
			switch (m_Type)
			{
			case TROOPATYPE::NORMAL:
				m_Col->Off();
				m_TopCol->Off();
				m_ProjectileCol->Off();
				m_EventCol->On();

				m_FSM.ChangeState(L"HIDE");
				break;
			case TROOPATYPE::WING:
				m_Type = TROOPATYPE::NORMAL;
				break;
			default:
				break;
			}
		}
	}
}

void Koopa_Troopa::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Koopa_Troopa_Left.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Koopa_Troopa_Left.bmp")->ImageCut(5, 3);
	SJWindowResMgr::Inst().FindImage(L"Koopa_Troopa_Right.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Koopa_Troopa_Right.bmp")->ImageCut(5, 3);

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER);
	m_Col->SetScale({ 48, 30 });
	m_Col->SetPivotPos({ 0.f, -18.f });
	m_Col->SetCheckData((int)COLLISIONDATA::SIDE);
	m_Col->AddStartEvent(this, &Koopa_Troopa::StartCollision);
	m_Col->AddStayEvent(this, &Koopa_Troopa::StayCollision);
	m_Col->AddEndEvent(this, &Koopa_Troopa::EndCollision);

	m_TopCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER);
	m_TopCol->SetScale({ 36, 24 });
	m_TopCol->SetPivotPos({ 0.f, -36.f });
	m_TopCol->SetCheckData((int)COLLISIONDATA::TOP);
	m_TopCol->AddStartEvent(this, &Koopa_Troopa::StartCollision);
	m_TopCol->AddStayEvent(this, &Koopa_Troopa::StayCollision);
	m_TopCol->AddEndEvent(this, &Koopa_Troopa::EndCollision);

	m_EventCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER);
	m_EventCol->SetScale({ 48, 48 });
	m_EventCol->SetPivotPos({ 0.f, -24.f });
	m_EventCol->SetCheckData((int)COLLISIONDATA::EVENT);
	m_EventCol->AddStartEvent(this, &Koopa_Troopa::StartCollision);
	m_EventCol->AddStayEvent(this, &Koopa_Troopa::StayCollision);
	m_EventCol->AddEndEvent(this, &Koopa_Troopa::EndCollision);
	m_EventCol->Off();

	m_ProjectileCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::PROJECTILE);
	m_ProjectileCol->SetScale({ 48, 30 });
	m_ProjectileCol->SetPivotPos({ 0.f, -18.f });
	m_ProjectileCol->AddStartEvent(this, &Koopa_Troopa::StartCollision);
	m_ProjectileCol->AddStayEvent(this, &Koopa_Troopa::StayCollision);
	m_ProjectileCol->AddEndEvent(this, &Koopa_Troopa::EndCollision);
	m_ProjectileCol->Off();

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::MONSTER);
	m_AniRenderer->SetRenderScale({ 256, 256 });

	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_Idle_Left", L"Koopa_Troopa_Left.bmp", 0, 1, 0.13f);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_ParaIdle_Left", L"Koopa_Troopa_Left.bmp", 2, 3, 0.13f);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_Hide_Left", L"Koopa_Troopa_Left.bmp", 4, 4);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_Kicked_Left", L"Koopa_Troopa_Left.bmp", 4, 7, 0.035f);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_HideOut_Left", L"Koopa_Troopa_Left.bmp", 8, 9, 0.13f);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_ReverseHide_Left", L"Koopa_Troopa_Left.bmp", 10, 10);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_ReverseHideOut_Left", L"Koopa_Troopa_Left.bmp", 10, 11, 0.13f);

	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_Idle_Right", L"Koopa_Troopa_Right.bmp", 0, 1, 0.13f);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_ParaIdle_Right", L"Koopa_Troopa_Right.bmp", 2, 3, 0.13f);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_Hide_Right", L"Koopa_Troopa_Right.bmp", 4, 4);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_Kicked_Right", L"Koopa_Troopa_Left.bmp", 4, 7, 0.035f);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_HideOut_Right", L"Koopa_Troopa_Right.bmp", 8, 9, 0.13f);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_ReverseHide_Right", L"Koopa_Troopa_Right.bmp", 10, 10);
	m_AniRenderer->CreateAnimation(L"Koopa_Troopa_ReverseHideOut_Right", L"Koopa_Troopa_Right.bmp", 10, 11, 0.13f);

	m_FSM.CreateState(L"IDLE", this, &Koopa_Troopa::IDLEStay, &Koopa_Troopa::IDLEStart, &Koopa_Troopa::IDLEEnd);
	m_FSM.CreateState(L"JUMP", this, &Koopa_Troopa::JUMPStay, &Koopa_Troopa::JUMPStart, &Koopa_Troopa::JUMPEnd);
	m_FSM.CreateState(L"FALL", this, &Koopa_Troopa::FALLStay, &Koopa_Troopa::FALLStart, &Koopa_Troopa::FALLEnd);
	m_FSM.CreateState(L"HIDE", this, &Koopa_Troopa::HIDEStay, &Koopa_Troopa::HIDEStart, &Koopa_Troopa::HIDEEnd);
	m_FSM.CreateState(L"HIDEFALL", this, &Koopa_Troopa::HIDEFALLStay, &Koopa_Troopa::HIDEFALLStart, &Koopa_Troopa::HIDEFALLEnd);
	m_FSM.CreateState(L"KICKED", this, &Koopa_Troopa::KICKEDStay, &Koopa_Troopa::KICKEDStart, &Koopa_Troopa::KICKEDEnd);
	m_FSM.CreateState(L"KICKEDFALL", this, &Koopa_Troopa::KICKEDFALLStay, &Koopa_Troopa::KICKEDFALLStart, &Koopa_Troopa::KICKEDFALLEnd);
	m_FSM.CreateState(L"DEAD", this, &Koopa_Troopa::DEADStay, &Koopa_Troopa::DEADStart, &Koopa_Troopa::DEADEnd);

	m_FSM.ChangeState(L"IDLE");

	SetDir(eDIR::LEFT);
}

void Koopa_Troopa::Update()
{
	m_fDelay += SJTimer::FDeltaTime();

	if (m_fDelay > 0.2f)
	{
		m_bDelay = true;
	}

	m_Move = float4::ZERO;

	SetPixelPos();

	m_FSM.Update();

	m_Move = m_RunPos + m_JumpPos;
	MovePos(m_Move);

	if (m_PrevDir != m_Dir)
	{
		ChangeAnimation(m_CurAniName);

		m_PrevDir = m_Dir;
	}

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::DEATH))
	{
		Death();
	}
}

void Koopa_Troopa::DebugRender()
{
	PixelView();

	CollisionView(m_Col);
	CollisionView(m_TopCol);
	CollisionView(m_EventCol);
	CollisionView(m_ProjectileCol);
}

void Koopa_Troopa::MoveTroopa()
{
	m_RunPos = m_fDir * m_Power * SJTimer::FDeltaTime();

	if (m_bDelay)
	{
		if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
			true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
		{
			if (eDIR::LEFT == m_Dir)
			{
				SetDir(eDIR::RIGHT);
			}
			else
			{
				SetDir(eDIR::LEFT);
			}

			SetDelay();
		}
	}
}

void Koopa_Troopa::ReviveTimeEvent()
{
	ChangeAnimation(L"Koopa_Troopa_HideOut");
}

void Koopa_Troopa::ReviveChangeState()
{
	m_Col->On();
	m_TopCol->On();
	m_EventCol->Off();
	m_FSM.ChangeState(L"IDLE");
}