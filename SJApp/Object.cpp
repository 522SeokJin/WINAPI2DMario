#include "Object.h"
#include <SJWindow.h>
#include <SJCollision.h>
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "SJCore.h"

// Static Var
float Object::m_Gravity = 3000.f;
// Static Func

// member Var

Object::Object()
	: m_PixelCheck{}
	, m_Move(float4::ZERO)
	, m_Dir(eDIR::LEFT)
	, m_PrevDir(eDIR::LEFT)
	, m_fDir(float4::LEFT)
	, m_AniRenderer(nullptr)
	, m_CurAniName(SJString())
	, m_bDelay(false)
	, m_fDelay(0)
{

}

Object::~Object()
{

}

// member Func

void Object::CollisionView(SJCollision* _Data)
{
	if (false == _Data->IsOn())
	{
		return;
	}

	Col2DData Data = _Data->GetCol2DData();
	Data.Pos = GetCamPos() + _Data->GetPivotPos();
	Data.Size = _Data->GetCol2DData().Size;

	HBRUSH Brush, oBrush;
	HPEN Pen, oPen;
	PAINTSTRUCT ps;

	BeginPaint(SJWindow::GetHwnd(), &ps);

	Brush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	oBrush = (HBRUSH)SelectObject(SJWindow::GetBackBufferDC(), Brush);

	Pen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oPen = (HPEN)SelectObject(SJWindow::GetBackBufferDC(), Pen);

	Rectangle(SJWindow::GetBackBufferDC(), Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBottom());

	SelectObject(SJWindow::GetBackBufferDC(), oBrush);
	SelectObject(SJWindow::GetBackBufferDC(), oPen);

	DeleteObject(Brush);
	DeleteObject(Pen);
	EndPaint(SJWindow::GetHwnd(), &ps);
}

void Object::PixelView()
{
	float4 m_PixelCheckCam[(int)PIXELCHECK::MAX];

	m_PixelCheckCam[(int)PIXELCHECK::LEFT] =			m_PixelCheck[(int)PIXELCHECK::LEFT]  - GetScene()->GetCamPos();
	m_PixelCheckCam[(int)PIXELCHECK::LEFT_TOP] =		m_PixelCheck[(int)PIXELCHECK::LEFT_TOP]  - GetScene()->GetCamPos();
	m_PixelCheckCam[(int)PIXELCHECK::LEFT_BOTTOM] =		m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM]  - GetScene()->GetCamPos();
	m_PixelCheckCam[(int)PIXELCHECK::RIGHT] =			m_PixelCheck[(int)PIXELCHECK::RIGHT] - GetScene()->GetCamPos();
	m_PixelCheckCam[(int)PIXELCHECK::RIGHT_TOP] =		m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP] - GetScene()->GetCamPos();
	m_PixelCheckCam[(int)PIXELCHECK::RIGHT_BOTTOM] =	m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM] - GetScene()->GetCamPos();
	m_PixelCheckCam[(int)PIXELCHECK::TOP] =				m_PixelCheck[(int)PIXELCHECK::TOP]  - GetScene()->GetCamPos();
	m_PixelCheckCam[(int)PIXELCHECK::BOTTOM] =			m_PixelCheck[(int)PIXELCHECK::BOTTOM] - GetScene()->GetCamPos();

	Rectangle(SJWindow::GetBackBufferDC(),
		m_PixelCheckCam[(int)PIXELCHECK::LEFT].ix() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::LEFT].iy() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::LEFT].ix() + 3,
		m_PixelCheckCam[(int)PIXELCHECK::LEFT].iy() + 3);
	Rectangle(SJWindow::GetBackBufferDC(),
		m_PixelCheckCam[(int)PIXELCHECK::LEFT_TOP].ix() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::LEFT_TOP].iy() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::LEFT_TOP].ix() + 3,
		m_PixelCheckCam[(int)PIXELCHECK::LEFT_TOP].iy() + 3);
	Rectangle(SJWindow::GetBackBufferDC(),
		m_PixelCheckCam[(int)PIXELCHECK::LEFT_BOTTOM].ix() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::LEFT_BOTTOM].iy() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::LEFT_BOTTOM].ix() + 3,
		m_PixelCheckCam[(int)PIXELCHECK::LEFT_BOTTOM].iy() + 3);
	Rectangle(SJWindow::GetBackBufferDC(),
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT].ix() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT].iy() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT].ix() + 3,
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT].iy() + 3);
	Rectangle(SJWindow::GetBackBufferDC(),
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT_TOP].ix() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT_TOP].iy() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT_TOP].ix() + 3,
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT_TOP].iy() + 3);
	Rectangle(SJWindow::GetBackBufferDC(),
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT_BOTTOM].ix() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT_BOTTOM].iy() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT_BOTTOM].ix() + 3,
		m_PixelCheckCam[(int)PIXELCHECK::RIGHT_BOTTOM].iy() + 3);
	Rectangle(SJWindow::GetBackBufferDC(),
		m_PixelCheckCam[(int)PIXELCHECK::TOP].ix() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::TOP].iy() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::TOP].ix() + 3,
		m_PixelCheckCam[(int)PIXELCHECK::TOP].iy() + 3);
	Rectangle(SJWindow::GetBackBufferDC(),
		m_PixelCheckCam[(int)PIXELCHECK::BOTTOM].ix() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::BOTTOM].iy() - 3,
		m_PixelCheckCam[(int)PIXELCHECK::BOTTOM].ix() + 3,
		m_PixelCheckCam[(int)PIXELCHECK::BOTTOM].iy() + 3);
}

void Object::SetPixelPos(float4 _PivotPos)
{
	m_PixelCheck[(int)PIXELCHECK::LEFT] = GetPos() + float4{ -GetSize().hx() + _PivotPos.x, -GetSize().hy() + _PivotPos.y };
	m_PixelCheck[(int)PIXELCHECK::LEFT_TOP] = GetPos() + float4{ -GetSize().hx() + _PivotPos.x, -GetSize().y + _PivotPos.y };
	m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM] = GetPos() + float4{ -GetSize().hx() + _PivotPos.x, _PivotPos.y };
	m_PixelCheck[(int)PIXELCHECK::RIGHT] = GetPos() + float4{ GetSize().hx() + _PivotPos.x, -GetSize().hy() + _PivotPos.y };
	m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP] = GetPos() + float4{ GetSize().hx() + _PivotPos.x, -GetSize().y + _PivotPos.y };
	m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM] = GetPos() + float4{ GetSize().hx() + _PivotPos.x, _PivotPos.y };
	m_PixelCheck[(int)PIXELCHECK::TOP] = GetPos() + float4{ _PivotPos.x, -GetSize().y + _PivotPos.y };
	m_PixelCheck[(int)PIXELCHECK::BOTTOM] = GetPos() + float4{ _PivotPos.x, _PivotPos.y };
}

bool Object::PixelCheck(float4 _PixelPos, float4 _MovePos, int _CheckColor)
{
	SJString CurScene = SJCore::SceneManager.GetCurSceneName();

	SJWinImage* FindImage = nullptr;

	if (SJString(L"Stage1") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"Stage1_Collider.bmp");
	}
	else if (SJString(L"BossStage") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"BossStage_Collider.bmp");
	}
	else
	{
		//SJDebug::AssertMsg(L"if (SJString(Stage1) == CurScene)");
	}


	
	if (nullptr != FindImage)
	{
		float4 CheckPos = _PixelPos + _MovePos;
		int m_CheckColor = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());
		if (m_CheckColor == _CheckColor)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool Object::PixelCheckAllLeft(float4 _MovePos, int _CheckColor)
{
	SJString CurScene = SJCore::SceneManager.GetCurSceneName();

	SJWinImage* FindImage = nullptr;

	if (SJString(L"Stage1") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"Stage1_Collider.bmp");
	}
	else if (SJString(L"BossStage") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"BossStage_Collider.bmp");
	}
	else
	{
		//SJDebug::AssertMsg(L"if (SJString(Stage1) == CurScene)");
	}

	if (nullptr != FindImage)
	{
		float4 CheckPos = m_PixelCheck[(int)PIXELCHECK::LEFT] + _MovePos;
		int m_CheckLeft = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		CheckPos = m_PixelCheck[(int)PIXELCHECK::LEFT_TOP] + _MovePos;
		int m_CheckLeftTop = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		CheckPos = m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM] + _MovePos;
		int m_CheckLeftBottom = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		if (m_CheckLeft == _CheckColor && m_CheckLeftTop == _CheckColor && m_CheckLeftBottom == _CheckColor)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}
bool Object::PixelCheckAllRight(float4 _MovePos, int _CheckColor)
{
	SJString CurScene = SJCore::SceneManager.GetCurSceneName();

	SJWinImage* FindImage = nullptr;

	if (SJString(L"Stage1") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"Stage1_Collider.bmp");
	}
	else if (SJString(L"BossStage") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"BossStage_Collider.bmp");
	}
	else
	{
		//SJDebug::AssertMsg(L"if (SJString(Stage1) == CurScene)");
	}

	if (nullptr != FindImage)
	{
		float4 CheckPos = m_PixelCheck[(int)PIXELCHECK::RIGHT] + _MovePos;
		int m_CheckRight = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		CheckPos = m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP] + _MovePos;
		int m_CheckRightTop = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		CheckPos = m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM] + _MovePos;
		int m_CheckRightBottom = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		if (m_CheckRight == _CheckColor && m_CheckRightTop == _CheckColor && m_CheckRightBottom == _CheckColor)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}
bool Object::PixelCheckAllTop(float4 _MovePos, int _CheckColor)
{
	SJString CurScene = SJCore::SceneManager.GetCurSceneName();

	SJWinImage* FindImage = nullptr;

	if (SJString(L"Stage1") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"Stage1_Collider.bmp");
	}
	else if (SJString(L"BossStage") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"BossStage_Collider.bmp");
	}
	else
	{
		//SJDebug::AssertMsg(L"if (SJString(Stage1) == CurScene)");
	}

	if (nullptr != FindImage)
	{
		float4 CheckPos = m_PixelCheck[(int)PIXELCHECK::TOP] + _MovePos;
		int m_CheckTop = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		CheckPos = m_PixelCheck[(int)PIXELCHECK::LEFT_TOP] + _MovePos;
		int m_CheckLeftTop = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		CheckPos = m_PixelCheck[(int)PIXELCHECK::RIGHT_TOP] + _MovePos;
		int m_CheckRightTop = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		if (m_CheckTop == _CheckColor && m_CheckLeftTop == _CheckColor && m_CheckRightTop == _CheckColor)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}
bool Object::PixelCheckAllBottom(float4 _MovePos, int _CheckColor)
{
	SJString CurScene = SJCore::SceneManager.GetCurSceneName();

	SJWinImage* FindImage = nullptr;

	if (SJString(L"Stage1") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"Stage1_Collider.bmp");
	}
	else if (SJString(L"BossStage") == CurScene)
	{
		FindImage = SJWindowResMgr::Inst().FindImage(L"BossStage_Collider.bmp");
	}
	else
	{
		//SJDebug::AssertMsg(L"if (SJString(Stage1) == CurScene)");
	}

	if (nullptr != FindImage)
	{
		float4 CheckPos = m_PixelCheck[(int)PIXELCHECK::BOTTOM] + _MovePos;
		int m_CheckBottom = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		CheckPos = m_PixelCheck[(int)PIXELCHECK::LEFT_BOTTOM] + _MovePos;
		int m_CheckLeftBottom = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		CheckPos = m_PixelCheck[(int)PIXELCHECK::RIGHT_BOTTOM] + _MovePos;
		int m_CheckRightBottom = FindImage->GetPixelColor(CheckPos.ix(), CheckPos.iy());

		if (m_CheckBottom == _CheckColor && m_CheckLeftBottom == _CheckColor && m_CheckRightBottom == _CheckColor)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool Object::PixelCheckAllLeft(int _CheckColor)
{
	return PixelCheckAllLeft(float4::ZERO, _CheckColor);
}
bool Object::PixelCheckAllRight(int _CheckColor)
{
	return PixelCheckAllRight(float4::ZERO, _CheckColor);
}
bool Object::PixelCheckAllTop(int _CheckColor)
{
	return PixelCheckAllTop(float4::ZERO, _CheckColor);
}
bool Object::PixelCheckAllBottom(int _CheckColor)
{
	return PixelCheckAllBottom(float4::ZERO, _CheckColor);
}

bool Object::PixelCheck(float4 _PixelPos, int _CheckColor)
{
	return PixelCheck(_PixelPos, float4::ZERO, _CheckColor);
}

void Object::SetDir(eDIR _Dir)
{
	m_Dir = _Dir;

	switch (_Dir)
	{
	case eDIR::LEFT:
		m_fDir = float4::LEFT;
		break;
	case eDIR::RIGHT:
		m_fDir = float4::RIGHT;
		break;
	default:
		break;
	}
}

void Object::ChangeAnimation(const SJString& _Name)
{
	m_CurAniName = _Name;
	SJString AniName = m_CurAniName;

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

void Object::SetDelay()
{
	m_bDelay = false;
	m_fDelay = 0;
}