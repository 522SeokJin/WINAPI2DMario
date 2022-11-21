#include "Mario.h"
#include <SJWindow.h>
#include <SJRendererBasic.h>
#include <SJInput.h>
#include <SJTimer.h>
#include <SJRendererAnimation.h>
#include <SJWindowResMgr.h>
#include "LogicValue.h"
#include <SJCollision.h>
#include "Koopa_Troopa.h"
#include "SJCore.h"
#include "FadeActor.h"
#include "Bowser.h"
#include "Open_Door.h"
#include "Smoke_Effect.h"

// Static Var
// Static Func

// member Var

Mario::Mario()
	: m_Type(MARIOTYPE::SMALL)
	, m_RunPos(float4::ZERO)
	, m_JumpPos(float4::ZERO)
	, m_Power(10.f)
	, m_MaxPower(300.f)
	, m_AccelMaxPower(500.f)
	, m_fAccelTime(0)
	, m_JumpPower(0)
	, m_JumpMaxPower(600.f)
	, m_Col(nullptr)
	, m_TailCol(nullptr)
	, m_CarryObj(nullptr)
	, m_LeftKeyLock(false)
	, m_RightKeyLock(false)
	, m_OverlapCol(0)
	, m_bAccel(false)
	, m_bTailDelay(false)
	, m_fTailDelay(0)
	, m_bNoDamage(false)
{

}

Mario::~Mario()
{
	
}

// member Func

void Mario::StartCollision(SJCollision* _This, SJCollision* _Other)
{
	
	if ((int)LogicValue::COLLISIONGROUP::MONSTER == _Other->GetOrder())
	{
		if ((int)COLLISIONDATA::TOP == _Other->GetCheckData())
		{
			if (m_bDelay)
			{
				m_Col->Off();
				m_CollisionEventer.CreateTimeEvent(0.2f, this, &Mario::CollisionOn);

				if (nullptr != m_CarryObj)
				{
					m_FSM.ChangeState(L"CARRYFOOT");
				}
				else
				{
					m_FSM.ChangeState(L"FOOT");
				}

				SetDelay();
			}
		}
		else if ((int)COLLISIONDATA::EVENT == _Other->GetCheckData())
		{
			if ((int)LogicValue::COLLISIONGROUP::MARIO == _This->GetOrder())
			{
				if (m_bDelay)
				{

					if (true == SJInput::IsPress(L"X"))
					{
						m_CarryObj = dynamic_cast<Koopa_Troopa*>(_Other->GetActor());
						if (nullptr != m_CarryObj)
						{
							m_FSM.ChangeState(L"CARRYIDLE");
						}
					}
					else
					{
						if (0 < m_OverlapCol)
						{
							m_FSM.ChangeState(L"BLOCKKICK");
						}
						else
						{
							m_FSM.ChangeState(L"KICK");
						}
					}
					SetDelay();
				}
			}
			
		}
		else if ((int)COLLISIONDATA::SIDE == _Other->GetCheckData() || (int)COLLISIONDATA::NORMAL == _Other->GetCheckData())
		{
			if ((int)LogicValue::COLLISIONGROUP::MARIO == _This->GetOrder())
			{
				if (m_bDelay)
				{
					if (false == m_bNoDamage)
					{
						if (MARIOTYPE::SMALL == m_Type)
						{
							m_FSM.ChangeState(L"DEAD");
						}
						else
						{
							m_FSM.ChangeState(L"POWERDOWN");
						}
					}
					SetDelay();
				}
			}
		}
	}

	if ((int)LogicValue::COLLISIONGROUP::PROJECTILE == _Other->GetOrder())
	{
		if ((int)LogicValue::COLLISIONGROUP::MARIO == _This->GetOrder())
		{
			if (m_bDelay)
			{
				if (false == m_bNoDamage)
				{
					if (MARIOTYPE::SMALL == m_Type)
					{
						m_FSM.ChangeState(L"DEAD");
					}
					else
					{
						m_FSM.ChangeState(L"POWERDOWN");
					}
				}
				SetDelay();
			}
		}
	}
}

void Mario::StayCollision(SJCollision* _This, SJCollision* _Other)
{
	if ((int)COLLISIONDATA::NORMAL == _Other->GetCheckData())
	{
		if (m_bDelay)
		{
			if (false == m_bNoDamage)
			{
				if (MARIOTYPE::SMALL == m_Type)
				{
					m_FSM.ChangeState(L"DEAD");
				}
				else
				{
					m_FSM.ChangeState(L"POWERDOWN");
				}
			}
			SetDelay();
		}
	}
}

void Mario::EndCollision(SJCollision* _This, SJCollision* _Other)
{

}

void Mario::Start()
{
	SJWindowResMgr::Inst().FindImage(L"SmallMario_Right.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"SmallMario_Right.bmp")->ImageCut(5, 4);
	SJWindowResMgr::Inst().FindImage(L"SmallMario_Left.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"SmallMario_Left.bmp")->ImageCut(5, 4);

	SJWindowResMgr::Inst().FindImage(L"SuperMario_Right.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"SuperMario_Right.bmp")->ImageCut(5, 6);
	SJWindowResMgr::Inst().FindImage(L"SuperMario_Left.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"SuperMario_Left.bmp")->ImageCut(5, 6);

	SJWindowResMgr::Inst().FindImage(L"RacoonMario_Right.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"RacoonMario_Right.bmp")->ImageCut(5, 7);
	SJWindowResMgr::Inst().FindImage(L"RacoonMario_Left.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"RacoonMario_Left.bmp")->ImageCut(5, 7);

	SJWindowResMgr::Inst().FindImage(L"RacoonChange.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"RacoonChange.bmp")->ImageCut(5, 3);

	m_Col = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MARIO);
	m_Col->SetScale({ 48, 48 });
	m_Col->SetPivotPos({0.f, -24.f});
	m_Col->AddStartEvent(this, &Mario::StartCollision);
	m_Col->AddStayEvent(this, &Mario::StayCollision);
	m_Col->AddEndEvent(this, &Mario::EndCollision);


	m_TailCol = CreateCollision<SJCollision>((int)LogicValue::COLLISIONGROUP::MARIO_PROJECTILE);
	m_TailCol->SetScale({ 33, 18 });
	m_TailCol->SetPivotPos({ 30, -21 });
	m_TailCol->AddStartEvent(this, &Mario::StartCollision);
	m_TailCol->AddStayEvent(this, &Mario::StayCollision);
	m_TailCol->AddEndEvent(this, &Mario::EndCollision);

	m_TailCol->Off();

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::PLAYER);
	
	m_AniRenderer->SetRenderScale({ 256, 256 });

	SetAnimation();

	m_FSM.CreateState(L"POWERUP", this, &Mario::POWERUPStay, &Mario::POWERUPStart, &Mario::POWERUPEnd);
	m_FSM.CreateState(L"POWERDOWN", this, &Mario::POWERDOWNStay, &Mario::POWERDOWNStart, &Mario::POWERDOWNEnd);
	m_FSM.CreateState(L"IDLE", this, &Mario::IDLEStay, &Mario::IDLEStart);
	m_FSM.CreateState(L"BLOCKIDLE", this, &Mario::BLOCKIDLEStay, &Mario::BLOCKIDLEStart);
	m_FSM.CreateState(L"CARRYIDLE", this, &Mario::CARRYIDLEStay, &Mario::CARRYIDLEStart, &Mario::CARRYIDLEEnd);
	m_FSM.CreateState(L"BLOCKCARRYIDLE", this, &Mario::BLOCKCARRYIDLEStay, &Mario::BLOCKCARRYIDLEStart, &Mario::BLOCKCARRYIDLEEnd);
	m_FSM.CreateState(L"RUN", this, &Mario::RUNStay, &Mario::RUNStart, &Mario::RUNEnd);
	m_FSM.CreateState(L"BLOCKRUN", this, &Mario::BLOCKRUNStay, &Mario::BLOCKRUNStart, &Mario::BLOCKRUNEnd);
	m_FSM.CreateState(L"CARRYRUN", this, &Mario::CARRYRUNStay, &Mario::CARRYRUNStart, &Mario::CARRYRUNEnd);
	m_FSM.CreateState(L"BLOCKCARRYRUN", this, &Mario::BLOCKCARRYRUNStay, &Mario::BLOCKCARRYRUNStart, &Mario::BLOCKCARRYRUNEnd);
	m_FSM.CreateState(L"SKID", this, &Mario::SKIDStay, &Mario::SKIDStart, &Mario::SKIDEnd);
	m_FSM.CreateState(L"BLOCKSKID", this, &Mario::BLOCKSKIDStay, &Mario::BLOCKSKIDStart, &Mario::BLOCKSKIDEnd);
	m_FSM.CreateState(L"JUMP", this, &Mario::JUMPStay, &Mario::JUMPStart, &Mario::JUMPEnd);
	m_FSM.CreateState(L"TALLJUMP", this, &Mario::TALLJUMPStay, &Mario::TALLJUMPStart, &Mario::TALLJUMPEnd);
	m_FSM.CreateState(L"TALLATTACK", this, &Mario::TALLATTACKStay, &Mario::TALLATTACKStart, &Mario::TALLATTACKEnd);
	m_FSM.CreateState(L"TALLATTACKFALL", this, &Mario::TALLATTACKFALLStay, &Mario::TALLATTACKFALLStart, &Mario::TALLATTACKFALLEnd);
	m_FSM.CreateState(L"BLOCKJUMP", this, &Mario::BLOCKJUMPStay, &Mario::BLOCKJUMPStart, &Mario::BLOCKJUMPEnd);
	m_FSM.CreateState(L"CARRYJUMP", this, &Mario::CARRYJUMPStay, &Mario::CARRYJUMPStart, &Mario::CARRYJUMPEnd);
	m_FSM.CreateState(L"FALL", this, &Mario::FALLStay, &Mario::FALLStart, &Mario::FALLEnd);
	m_FSM.CreateState(L"CARRYFALL", this, &Mario::CARRYFALLStay, &Mario::CARRYFALLStart, &Mario::CARRYFALLEnd);
	m_FSM.CreateState(L"FOOT", this, &Mario::FOOTStay, &Mario::FOOTStart, &Mario::FOOTEnd);
	m_FSM.CreateState(L"CARRYFOOT", this, &Mario::CARRYFOOTStay, &Mario::CARRYFOOTStart, &Mario::CARRYFOOTEnd);
	m_FSM.CreateState(L"SIT", this, &Mario::SITStay, &Mario::SITStart, &Mario::SITEnd);
	m_FSM.CreateState(L"BLOCKSIT", this, &Mario::BLOCKSITStay, &Mario::BLOCKSITStart, &Mario::BLOCKSITEnd);
	m_FSM.CreateState(L"SITJUMP", this, &Mario::SITJUMPStay, &Mario::SITJUMPStart, &Mario::SITJUMPEnd);
	m_FSM.CreateState(L"SITFALL", this, &Mario::SITFALLStay, &Mario::SITFALLStart, &Mario::SITFALLEnd);
	m_FSM.CreateState(L"KICK", this, &Mario::KICKStay, &Mario::KICKStart, &Mario::KICKEnd);
	m_FSM.CreateState(L"BLOCKKICK", this, &Mario::BLOCKKICKStay, &Mario::BLOCKKICKStart, &Mario::BLOCKKICKEnd);
	m_FSM.CreateState(L"KICKFALL", this, &Mario::KICKFALLStay, &Mario::KICKFALLStart, &Mario::KICKFALLEnd);
	m_FSM.CreateState(L"CLEARFALL", this, &Mario::CLEARFALLStay, &Mario::CLEARFALLStart, &Mario::CLEARFALLEnd);
	m_FSM.CreateState(L"CLEARRUN", this, &Mario::CLEARRUNStay, &Mario::CLEARRUNStart, &Mario::CLEARRUNEnd);
	m_FSM.CreateState(L"DEAD", this, &Mario::DEADStay, &Mario::DEADStart, &Mario::DEADEnd);

	m_FSM.ChangeState(L"IDLE");

	m_Type = LogicValue::PrevMarioType;

	SetDir(eDIR::RIGHT);
}

void Mario::Update()
{
	CalDelay();

	LogicValue::PrevMarioType = m_Type;

	m_CollisionEventer.Update();
	m_AlphaBlendEventer.Update();
	SetCollision();

	m_Move = float4::ZERO;

	SetKeyMoveDir();
	SetPixelPos();

	m_FSM.Update();

	AccelSound();
	SetAccelGauge();

	m_Move = m_RunPos + m_JumpPos;
	CameraMove();
	MovePos(m_Move);

	m_PrevDir = m_Dir;

	if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::BOTTOM], (int)PIXELCOLOR::DEATH))
	{
		m_FSM.ChangeState(L"DEAD");
	}
}

void Mario::CameraMove()
{
	SJString CurScene = SJCore::SceneManager.GetCurSceneName();

	SJWinImage* FindImage = nullptr;
	if (SJString(L"Stage1") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"Stage1.bmp");

		int Left = GetScene()->GetCamPos().ix();
		int Right = GetScene()->GetCamPos().ix() + SJWindow::GetSize().ix();
		int Up = GetScene()->GetCamPos().iy();
		int Down = GetScene()->GetCamPos().iy() + SJWindow::GetSize().iy();

		float4 CamPos = GetScene()->GetCamPos();

		// 가장자리에서는 카메라가 움직이면 안된다.GetCamPos()
		if (GetPos().ix() >= SJWindow::GetSize().ihx() &&
			GetPos().ix() < FindImage->GetImageSize().x - SJWindow::GetSize().ihx())
		{
			XCamera(CamPos);
		}

		if (GetPos().iy() <= 733 + 0.5f * SJWindow::GetSize().ihy() &&
			GetPos().iy() > SJWindow::GetSize().ihy() - 0.5f * SJWindow::GetSize().ihy())
		{
			YCamera(CamPos);
		}

		if (Down > 1405)
		{
			CamPos.y = 733;
			GetScene()->SetCamPos(CamPos);
		}
	}
	else if (SJString(L"BossStage") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"BossStage.bmp");
	}
	else
	{
		//SJDebug::AssertMsg(L"if (SJString(Stage1) == CurScene)");
	}

	
}

void Mario::XCamera(float4& _CamPos)
{
	SJWinImage* FindImage = SJWindowResMgr::Inst().FindImage(L"Stage1.bmp");

	// 카메라의 사각형 정의

	int Left = GetScene()->GetCamPos().ix();
	int Right = GetScene()->GetCamPos().ix() + SJWindow::GetSize().ix();
	int Up = GetScene()->GetCamPos().iy();
	int Down = GetScene()->GetCamPos().iy() + SJWindow::GetSize().iy();

	if (0 >= Left)
	{
		_CamPos.x = 3;
		GetScene()->SetCamPos(_CamPos);
		return;
	}

	if (Right >= FindImage->GetImageSize().ix() - 1)
	{
		_CamPos.x = FindImage->GetImageSize().x - 3 - SJWindow::GetSize().x;
		GetScene()->SetCamPos(_CamPos);
		return;
	}

	GetScene()->SetCamMove({ m_Move.x , 0.f });
}
void Mario::YCamera(float4& _CamPos)
{
	SJWinImage* FindImage = SJWindowResMgr::Inst().FindImage(L"Stage1.bmp");

	// 카메라의 사각형 정의

	int Left = GetScene()->GetCamPos().ix();
	int Right = GetScene()->GetCamPos().ix() + SJWindow::GetSize().ix();
	int Up = GetScene()->GetCamPos().iy();
	int Down = GetScene()->GetCamPos().iy() + SJWindow::GetSize().iy();

	if (0 >= Up)
	{
		_CamPos.y = 3;
		GetScene()->SetCamPos(_CamPos);
		return;
	}

	//if (Down >= FindImage->GetImageSize().iy() - 1)
	if (Down > 1405)
	{
		//CamPos.y = FindImage->GetImageSize().y - 3 - SJWindow::GetSize().y;
		_CamPos.y = 733;
		GetScene()->SetCamPos(_CamPos);
		return;
	}

	GetScene()->SetCamMove({ 0.f , m_Move.y });
}

void Mario::ChangeAnimation(const SJString& _Name)
{
	SJString AniName;

	switch (m_Type)
	{
	case MARIOTYPE::SMALL:
		AniName = L"Small_";
		break;
	case MARIOTYPE::SUPER:
		AniName = L"Super_";
		break;
	case MARIOTYPE::RACOON:
		AniName = L"Racoon_";
		break;
	default:
		break;
	}

	m_CurAniName = _Name;
	AniName += m_CurAniName;

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

void Mario::SetKeyMoveDir()
{
	if (true == SJInput::IsPress(L"LEFT"))
	{
		m_Dir = eDIR::LEFT;
		m_fDir = float4::LEFT;
		m_TailCol->SetPivotPos({ -30, -21 });
	}
	else if (true == SJInput::IsPress(L"RIGHT"))
	{
		m_Dir = eDIR::RIGHT;
		m_fDir = float4::RIGHT;
		m_TailCol->SetPivotPos({ 30, -21 });
	}

	if (m_PrevDir != m_Dir)
	{
		ChangeAnimation(m_CurAniName);
	}

	//m_PrevDir = m_Dir;
}

void Mario::MoveMario()
{
	// 속도에 따른 발 빠르기 조정
	float FootSpeed = 0.1f;
	float CurFrameTime = m_AniRenderer->GetCurAnimation()->GetInitialFrameTime();
	FootSpeed = float4::Lerp2DMax(3 * CurFrameTime, CurFrameTime, abs(m_RunPos.x) / (m_AccelMaxPower * SJTimer::FDeltaTime())).x;
	m_AniRenderer->GetCurAnimation()->SetFrameTime(FootSpeed);

	if ( (true == SJInput::IsPress(L"LEFT") && false == m_LeftKeyLock) || 
		(true == SJInput::IsPress(L"RIGHT") && false == m_RightKeyLock) )
	{
		m_RunPos += m_fDir * m_Power * SJTimer::FDeltaTime();

		switch (m_Dir)
		{
		case eDIR::LEFT:
			if (true == SJInput::IsPress(L"X"))
			{
				if (m_RunPos.x < (m_fDir * m_AccelMaxPower * SJTimer::FDeltaTime()).x)
				{
					m_RunPos = m_fDir * m_AccelMaxPower * SJTimer::FDeltaTime();
				}
			}
			else
			{
				if (m_RunPos.x < (m_fDir * m_MaxPower * SJTimer::FDeltaTime()).x)
				{
					m_RunPos = m_fDir * m_MaxPower * SJTimer::FDeltaTime();
				}
			}
			break;
		case eDIR::RIGHT:
			if (true == SJInput::IsPress(L"X"))
			{
				if (m_RunPos.x > (m_fDir * m_AccelMaxPower * SJTimer::FDeltaTime()).x)
				{
					m_RunPos = m_fDir * m_AccelMaxPower * SJTimer::FDeltaTime();
				}
			}
			else
			{
				if (m_RunPos.x > (m_fDir * m_MaxPower * SJTimer::FDeltaTime()).x)
				{
					m_RunPos = m_fDir * m_MaxPower * SJTimer::FDeltaTime();
				}
			}
			break;
		default:
			break;
		}
	}

	if (true == PixelCheckAllBottom((int)PIXELCOLOR::FREE))
	{
		if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
			true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_TOP], m_RunPos, (int)PIXELCOLOR::GROUND) ||
			true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM], m_RunPos, (int)PIXELCOLOR::GROUND))
		{
			m_RunPos = 0;
		}

		if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
			true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP], m_RunPos, (int)PIXELCOLOR::GROUND) ||
			true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM], m_RunPos, (int)PIXELCOLOR::GROUND))
		{
			m_RunPos = 0;
		}
	}
	else
	{
		if (true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::RIGHT], m_RunPos, (int)PIXELCOLOR::GROUND) ||
			true == PixelCheck(m_PixelCheck[(int)PIXELCHECK::LEFT], m_RunPos, (int)PIXELCOLOR::GROUND))
		{
			m_RunPos = 0;
		}
	}

	if (true == PixelCheckAllRight(m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE) ||
		true == PixelCheckAllLeft(m_RunPos, (int)PIXELCOLOR::OUT_OF_IMAGE))
	{
		m_RunPos = 0;
	}
}

void Mario::CarryAction()
{
	if (nullptr == m_CarryObj)
	{
		SJDebug::AssertMsg("if (nullptr == m_CarryObj)");
	}

	if (true == SJInput::IsFree(L"X"))
	{
		m_CarryObj->GetEventCol()->On();
		m_CarryObj->GetFSM().ChangeState(L"KICKED");
		return;
	}

	if (true == SJInput::IsPress(L"X"))
	{
		// 왼쪽이면
		switch (m_Dir)
		{
		case eDIR::LEFT:
			if (MARIOTYPE::SMALL == m_Type)
			{
				m_CarryObj->SetPos(GetPos() - float4{ 30, 4 });
			}
			else
			{
				m_CarryObj->SetPos(GetPos() - float4{ 34, 10 });
			}
			break;
		case eDIR::RIGHT:
			m_CarryObj->SetPos(GetPos() + float4{ 30, 0 });
			if (MARIOTYPE::SMALL == m_Type)
			{
				m_CarryObj->SetPos(GetPos() + float4{ 30, -4 });
			}
			else
			{
				m_CarryObj->SetPos(GetPos() + float4{ 34, -10 });
			}
			break;
		default:
			break;
		}
	}
}

void Mario::SetCollision()
{
	if (MARIOTYPE::SMALL == m_Type)
	{
		SetSize(float4{ 44, 44 });
		m_Col->SetScale({ 48, 48 });
		m_Col->SetPivotPos({ 0.f, -24.f });
	}
	else
	{
		if (m_FSM.GetCurStateName().is_find(L"SIT"))
		{
			SetSize(float4{ 44, 44 });
			m_Col->SetScale({ 48, 48 });
			m_Col->SetPivotPos({ 0.f, -24.f });
		}
		else
		{
			SetSize(float4{ 44, 77 });
			m_Col->SetScale({ 48, 81 });
			m_Col->SetPivotPos({ 0.f, -40.5f });
		}
	}
}

void Mario::SetAccelGauge()
{
	if (abs(m_RunPos.x) > m_MaxPower * SJTimer::FDeltaTime())
	{
		if (true == SJInput::IsPress(L"X"))
		{
			m_fAccelTime += 3.f * SJTimer::FDeltaTime();
		}

		if (m_fAccelTime > 7)
		{
			m_fAccelTime = 7;
		}
	}
	else
	{
		m_fAccelTime -= 6.f * SJTimer::FDeltaTime();
		if (m_fAccelTime < 0)
		{
			m_fAccelTime = 0;
		}
	}

	LogicValue::AccelTime = m_fAccelTime;
}

void Mario::AccelSound()
{
	if (m_fAccelTime >= 6)
	{
		if (false == m_bAccel)
		{
			m_FullAccelSound = SJSound::Play(L"FullAccel.wav", -1);
			m_bAccel = true;
		}
	}
	else
	{
		m_bAccel = false;
		m_FullAccelSound.Stop();
	}
}

void Mario::DebugRender()
{
	PixelView();

	CollisionView(m_Col);
	CollisionView(m_TailCol);

	{
		SJString PrintText = L"Mario Position : ";
		PrintText += GetPos().ix();
		PrintText += L" ";
		PrintText += GetPos().iy();
		TextOut(SJWindow::GetBackBufferDC(), 0, 0, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"CamPos : ";
		PrintText += GetScene()->GetCamPos().ix();
		PrintText += L" ";
		PrintText += GetScene()->GetCamPos().iy();
		TextOut(SJWindow::GetBackBufferDC(), 0, 20, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"Mario State : ";
		PrintText += m_FSM.GetCurStateName();

		TextOut(SJWindow::GetBackBufferDC(), 0, 40, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"Move Force : ";
		PrintText += SJString::ToString<float>(m_Move.x);
		PrintText += L" ";
		PrintText += SJString::ToString<float>(m_Move.y);;

		TextOut(SJWindow::GetBackBufferDC(), 0, 60, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"m_RunPos : ";
		PrintText += SJString::ToString<float>(m_RunPos.x);
		PrintText += L" ";
		PrintText += SJString::ToString<float>(m_RunPos.y);;

		TextOut(SJWindow::GetBackBufferDC(), 0, 80, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"m_Type : ";
		PrintText += MARIOTYPEtoString(m_Type);

		TextOut(SJWindow::GetBackBufferDC(), 0, 100, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"m_fAccelTime : ";
		PrintText += SJString::ToString<float>(m_fAccelTime);

		TextOut(SJWindow::GetBackBufferDC(), 0, 120, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"m_OverlapCol : ";
		PrintText += SJString::ToString<int>(m_OverlapCol);

		TextOut(SJWindow::GetBackBufferDC(), 0, 140, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"m_LeftKeyLock : ";
		PrintText += SJString::ToString<bool>(m_LeftKeyLock);

		TextOut(SJWindow::GetBackBufferDC(), 0, 160, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"m_RightKeyLock : ";
		PrintText += SJString::ToString<bool>(m_RightKeyLock);

		TextOut(SJWindow::GetBackBufferDC(), 0, 180, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}

	{
		SJString PrintText = L"m_bNoDamage : ";
		PrintText += SJString::ToString<bool>(m_bNoDamage);

		TextOut(SJWindow::GetBackBufferDC(), 0, 200, PrintText.c_str(), lstrlen(PrintText.c_str()));
	}
}

SJString Mario::MARIOTYPEtoString(MARIOTYPE _TYPE)
{
	switch (_TYPE)
	{
	case MARIOTYPE::SMALL:
		return SJString(L"SMALL");
		break;
	case MARIOTYPE::SUPER:
		return SJString(L"SUPER");
		break;
	case MARIOTYPE::RACOON:
		return SJString(L"RACOON");
		break;
	default:
		return nullptr;
		break;
	}
}

void Mario::PowerDownEnd()
{
	if (0 == m_AlphaBlendEventer.IsEventSize())
	{
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOn);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOff);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOn);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOff);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOn);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOff);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOn);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOff);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOn);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOff);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOn);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::PowerDownEffectOff);
		m_AlphaBlendEventer.CreateTimeEvent(0.1f, this, &Mario::NoDamageOff);
	}

	m_AlphaBlendEventer.Reset();

	if (0 == m_OverlapCol)
	{
		m_FSM.ChangeState(L"FALL");
	}
	else
	{
		m_FSM.ChangeState(L"BLOCKIDLE");
	}
}

void Mario::PowerRacoonDownEnd()
{
	m_CollisionEventer.CreateTimeEvent(0.5f, this, &Mario::NoDamageOff);
	
	if (0 == m_OverlapCol)
	{
		m_FSM.ChangeState(L"FALL");
	}
	else
	{
		m_FSM.ChangeState(L"BLOCKIDLE");
	}
}

void Mario::PowerUpEnd()
{
	if (0 == m_OverlapCol)
	{
		m_FSM.ChangeState(L"FALL");
	}
	else
	{
		m_FSM.ChangeState(L"BLOCKIDLE");
	}
}

void Mario::Revive()
{
	SJString CurScene = SJCore::SceneManager.GetCurSceneName();
	
	if (SJString(L"Stage1") == CurScene)
	{
		m_Type = MARIOTYPE::SMALL;
		SetPos(float4{ 92, 1252 });
		GetScene()->SetCamPos(float4{ 0, 672 + 108 - 47 });
		m_FSM.ChangeState(L"IDLE");
		m_bNoDamage = false;
		m_OverlapCol = 0;
		LogicValue::FadeEffect->FadeTimer.Reset();

		LogicValue::BGMPlayer = SJSound::Play(L"Stage1_Theme.mp3", -1);
	}
	else if (SJString(L"BossStage") == CurScene)
	{
		m_Type = MARIOTYPE::SMALL;
		SetPos(float4{ 70, 1006 });
		GetScene()->SetCamPos(float4{ 0, 672 + 108 - 47 });
		m_FSM.ChangeState(L"IDLE");
		m_bNoDamage = false;
		m_OverlapCol = 0;
		LogicValue::FadeEffect->FadeTimer.Reset();
		LogicValue::Bowser->Reset();

		std::list<SJActor*> ActorList = SJCore::SceneManager.GetCurScene()->GetActors();
		std::list<SJActor*>::iterator iter = ActorList.begin();

		for (; iter != ActorList.end(); ++iter)
		{
			if (false == (*iter)->IsOn())
			{
				(*iter)->On();
			}
		}
		
		LogicValue::Bowser->m_Fire[0]->Off();
		LogicValue::Bowser->m_Fire[1]->Off();
		LogicValue::Smoke[0]->Off();
		LogicValue::Smoke[1]->Off();
		LogicValue::OpenDoor->Off();
	}
}

void Mario::CalDelay()
{
	m_fTailDelay += SJTimer::FDeltaTime();

	if (m_fTailDelay > 0.25f)
	{
		m_bTailDelay = true;
	}

	m_fDelay += SJTimer::FDeltaTime();

	if (m_fDelay > 0.2f)
	{
		m_bDelay = true;
	}
}