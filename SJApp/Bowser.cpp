#include "Bowser.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include <SJWindow.h>
#include <SJCollision.h>
#include "LogicValue.h"
#include "Mario.h"
#include "Smoke_Effect.h"
#include "Open_Door.h"

// Static Var
// Static Func

// member Var

Bowser::Bowser()
	: m_RunPos(float4::ZERO)
	, m_JumpPos(float4::ZERO)
	, m_JumpPower(0)
	, m_JumpMaxPower(300.f)
	, m_Ratio(0)
	, m_Col(nullptr)
	, m_BlockCol(nullptr)
	, m_SaveLocation(float4::ZERO)
	, m_FallPos(0)
	, m_FireCount(0)
	, m_Fire()
	, m_CamShakeTime(0)
	, m_CamShakeCheck(false)
{
	m_JumpLocation[0] =	 float4{ 48 * 1, 855 };
	m_JumpLocation[1] =	 float4{ 48 * 2, 855 };
	m_JumpLocation[2] =	 float4{ 48 * 3, 855 };
	m_JumpLocation[3] =	 float4{ 48 * 4, 855 };
	m_JumpLocation[4] =	 float4{ 48 * 5, 855 };
	m_JumpLocation[5] =	 float4{ 48 * 6, 855 };
	m_JumpLocation[6] =	 float4{ 48 * 7, 855 };
	m_JumpLocation[7] =	 float4{ 48 * 8, 855 };
	m_JumpLocation[8] =	 float4{ 48 * 9, 855 };
	m_JumpLocation[9] =	 float4{ 48 * 10, 855 };
	m_JumpLocation[10] = float4{ 48 * 11, 855 };
	m_JumpLocation[11] = float4{ 48 * 12, 855 };
	m_JumpLocation[12] = float4{ 48 * 13, 855 };
	m_JumpLocation[13] = float4{ 48 * 14, 855 };
	m_JumpLocation[14] = float4{ 48 * 15, 855 };
}

Bowser::~Bowser()
{

}

// member Func

void Bowser::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)LogicValue::COLLISIONGROUP::MARIO == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::BOTTOM == _This->GetCheckData())
		{
			LogicValue::Mario->m_OverlapCol = 0;
			if (!LogicValue::Mario->m_FSM.GetCurStateName().is_find(L"POWER"))
			{
				LogicValue::Mario->m_FSM.ChangeState(L"FALL");
			}
		}
	}
}

void Bowser::StayCollision(SJCollision* _This, SJCollision* _Other)
{
	
}

void Bowser::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Bowser::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Bowser_Left.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Bowser_Left.bmp")->ImageCut(5, 3);

	SJWindowResMgr::Inst().FindImage(L"Bowser_Right.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Bowser_Right.bmp")->ImageCut(5, 3);

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER);
	m_Col->SetScale({ 84 - 10, 120 - 10});
	m_Col->SetPivotPos({ 0, -55 });
	m_Col->SetCheckData((int)COLLISIONDATA::NORMAL);
	m_Col->AddStartEvent(this, &Bowser::StartCollision);

	m_BlockCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MONSTER);
	m_BlockCol->SetScale({ 48, 15 });
	m_BlockCol->SetPivotPos({ 0, 0 });
	m_BlockCol->SetCheckData((int)COLLISIONDATA::BOTTOM);
	m_BlockCol->AddStartEvent(this, &Bowser::StartCollision);
	m_BlockCol->AddStayEvent(this, &Bowser::StayCollision);
	m_BlockCol->AddEndEvent(this, &Bowser::EndCollision);
	m_BlockCol->Off();

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::MONSTER);
	m_AniRenderer->SetRenderScale({ 256, 256 });

	m_AniRenderer->CreateAnimation(L"Idle_Left", L"Bowser_Left.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Fire_Left", L"Bowser_Left.bmp", 2, 3, 0.2f, false);
	m_AniRenderer->CreateAnimation(L"Sit_Left", L"Bowser_Left.bmp", 4, 4);
	m_AniRenderer->CreateAnimation(L"Fall_Left", L"Bowser_Left.bmp", 5, 5);
	m_AniRenderer->CreateAnimation(L"SitUp_Left", L"Bowser_Left.bmp", 6, 7, 0.1f, false);
	m_AniRenderer->CreateAnimation(L"FindLeftToRight_Left", L"Bowser_Left.bmp", 8, 10, 0.2f, false);
	m_AniRenderer->CreateAnimation(L"FindRightToLeft_Left", L"Bowser_Left.bmp", 10, 12, 0.2f, false);
	m_AniRenderer->CreateAnimation(L"TurnToMario_Left", L"Bowser_Left.bmp", 13, 13);

	m_AniRenderer->CreateAnimation(L"Idle_Right", L"Bowser_Right.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Fire_Right", L"Bowser_Right.bmp", 2, 3, 0.2f, false);
	m_AniRenderer->CreateAnimation(L"Sit_Right", L"Bowser_Right.bmp", 4, 4);
	m_AniRenderer->CreateAnimation(L"Fall_Right", L"Bowser_Right.bmp", 5, 5);
	m_AniRenderer->CreateAnimation(L"SitUp_Right", L"Bowser_Right.bmp", 6, 7, 0.1f, false);
	m_AniRenderer->CreateAnimation(L"FindLeftToRight_Right", L"Bowser_Left.bmp", 8, 10, 0.2f, false);
	m_AniRenderer->CreateAnimation(L"FindRightToLeft_Right", L"Bowser_Left.bmp", 10, 12, 0.2f, false);
	m_AniRenderer->CreateAnimation(L"TurnToMario_Right", L"Bowser_Right.bmp", 13, 13);

	if (0 == m_FireEventer.IsEventSize())
	{
		m_FireEventer.CreateTimeEvent(1.f, this, &Bowser::FireEvent);
		m_FireEventer.CreateTimeEvent(0.5f, this, &Bowser::BackToIdleAnim);
		m_FireEventer.CreateTimeEvent(0.5f, this, &Bowser::Stop);
		m_FireEventer.CreateTimeEvent(1.f, this, &Bowser::FireEvent);
		m_FireEventer.CreateTimeEvent(0.5f, this, &Bowser::BackToIdleAnim);
		m_FireEventer.CreateTimeEvent(0.5f, this, &Bowser::Stop);
		m_FireEventer.CreateTimeEvent(0.5f, this, &Bowser::ReadyToJump);
		m_FireEventer.CreateTimeEvent(0.25f, this, &Bowser::JumpToMario);
	}
	m_CamShakeTime = 0.01f;

	m_CamShakeEventer.CreateTimeEvent(0.5f, this, &Bowser::CamShakeEnd, &Bowser::CamShakeStart, &Bowser::CamShakeStay);


	SetDir(eDIR::LEFT);

	m_FSM.CreateState(L"WAIT", this, &Bowser::WAITStay, &Bowser::WAITStart, &Bowser::WAITEnd);
	m_FSM.CreateState(L"APPEAR", this, &Bowser::APPEARStay, &Bowser::APPEARStart, &Bowser::APPEAREnd);

	m_FSM.CreateState(L"IDLE", this, &Bowser::IDLEStay, &Bowser::IDLEStart, &Bowser::IDLEEnd);
	m_FSM.CreateState(L"JUMP", this, &Bowser::JUMPStay, &Bowser::JUMPStart, &Bowser::JUMPEnd);
	m_FSM.CreateState(L"FALL", this, &Bowser::FALLStay, &Bowser::FALLStart, &Bowser::FALLEnd);
	m_FSM.CreateState(L"ATTACKJUMP", this, &Bowser::ATTACKJUMPStay, &Bowser::ATTACKJUMPStart, &Bowser::ATTACKJUMPEnd);
	m_FSM.CreateState(L"ATTACKFALL", this, &Bowser::ATTACKFALLStay, &Bowser::ATTACKFALLStart, &Bowser::ATTACKFALLEnd);
	m_FSM.CreateState(L"ATTACKAFTERFALL", this, &Bowser::ATTACKAFTERFALLStay, &Bowser::ATTACKAFTERFALLStart, &Bowser::ATTACKAFTERFALLEnd);
	m_FSM.CreateState(L"FIND", this, &Bowser::FINDStay, &Bowser::FINDStart, &Bowser::FINDEnd);
	m_FSM.CreateState(L"BACKTOIDLE", this, &Bowser::BACKTOIDLEStay, &Bowser::BACKTOIDLEStart, &Bowser::BACKTOIDLEEnd);
	m_FSM.CreateState(L"DEATH", this, &Bowser::DEATHStay, &Bowser::DEATHStart, &Bowser::DEATHEnd);

	m_FSM.ChangeState(L"WAIT");
}

void Bowser::Update()
{
	SetPixelPos();

	m_FSM.Update();

	m_Move = m_RunPos + m_JumpPos;

	MovePos(m_Move);

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::DEATH))
	{
		m_FSM.ChangeState(L"DEATH");
	}

	if (true == m_CamShakeCheck)
	{
		m_CamShakeEventer.Update();
	}
}

void Bowser::DebugRender()
{
	PixelView();

	CollisionView(m_Col);
	CollisionView(m_BlockCol);

	{
		SJString PrintText = L"Bowser State : ";

		PrintText += m_FSM.GetCurStateName();

		TextOut(SJWindow::GetBackBufferDC(), 500, 0, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"m_FallPos ";
		PrintText += SJString::ToString<int>(m_FallPos);

		TextOut(SJWindow::GetBackBufferDC(), 500, 20, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}
}

void Bowser::FindLeftToRight()
{
	ChangeAnimation(L"FindLeftToRight");

	if (true == m_AniRenderer->GetCurAnimation()->IsEnd())
	{
		if (GetPos().x < LogicValue::Mario->GetPos().x)
		{
			SetDir(eDIR::RIGHT);
			m_FSM.ChangeState(L"BACKTOIDLE");
		}
	}
}

void Bowser::FindRightToLeft()
{
	ChangeAnimation(L"FindRightToLeft");

	if (true == m_AniRenderer->GetCurAnimation()->IsEnd())
	{
		if (GetPos().x >= LogicValue::Mario->GetPos().x)
		{
			SetDir(eDIR::LEFT);
			m_FSM.ChangeState(L"BACKTOIDLE");
		}
	}
}

void Bowser::GoToIdle()
{
	m_FireEventer.Reset();
	m_JumpEventer.Reset();

	ChangeAnimation(L"Idle");
	m_FSM.ChangeState(L"IDLE");

	m_Fire[0]->SetDir(m_Dir);
	m_Fire[0]->Off();
	m_Fire[1]->SetDir(m_Dir);
	m_Fire[1]->Off();

}

void Bowser::BackToIdleAnim()
{
	SJSound::Play(L"Fire.wav");

	switch (m_Dir)
	{
	case eDIR::LEFT:
		m_Fire[m_FireCount]->SetPos(float4{ GetPos().x - 45, GetPos().y - 90 });
		break;
	case eDIR::RIGHT:
		m_Fire[m_FireCount]->SetPos(float4{ GetPos().x + 45, GetPos().y - 90 });
		break;
	default:
		break;
	}
	m_Fire[m_FireCount]->On();
	m_Fire[m_FireCount]->Reset();
	m_Fire[m_FireCount++]->m_FSM.ChangeState(L"MOVE");

	if (m_FireCount >= 2)
	{
		m_FireCount = 0;
	}

	ChangeAnimation(L"Idle");
}

void Bowser::CamShakeStart()
{

}

void Bowser::CamShakeStay()
{
	// 이게 캠이 돌아가야할 위치죠?

	int ImageSize = static_cast<int>(SJWindowResMgr::Inst().FindImage(L"BossStage.bmp")->GetImageSize().y);

	float4 PivotPos = float4{ 0, ImageSize - 672 - 300 + 108 };
	PivotPos.y += rand() % 20 - 10;
	GetScene()->SetCamPos(PivotPos);
}

void Bowser::CamShakeEnd()
{
	int ImageSize = static_cast<int>(SJWindowResMgr::Inst().FindImage(L"BossStage.bmp")->GetImageSize().y);
	// 플레이어의 위치에 맞춰서 다시 돌려주는게 가장 중요합니다.
	GetScene()->SetCamPos(float4{ 0, ImageSize - 672 - 300 + 108 });
	m_CamShakeCheck = false;
}

void Bowser::TouchGround()
{
	SJSound::Play(L"Thwomp.wav");

	m_CamShakeEventer.Reset();
	m_CamShakeCheck = true;

}
void Bowser::ClearSound()
{
	SJSound::Play(L"Bowser_Clear.wav");
}
void Bowser::OpenDoor()
{
	SJSound::Play(L"Transformation.wav");

	LogicValue::Smoke[0]->On();
	LogicValue::Smoke[1]->On();
	LogicValue::OpenDoor->On();
}

void Bowser::Reset()
{
	SetDir(eDIR::LEFT);
	m_FSM.ChangeState(L"WAIT");
	SetPos(float4{ 624, 675 });
	m_FireEventer.Reset();
	m_JumpEventer.Reset();
}