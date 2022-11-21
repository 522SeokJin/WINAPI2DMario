#include "Pipe.h"
#include <SJWindowResMgr.h>
#include <SJRendererAnimation.h>
#include "LogicValue.h"

// Static Var
// Static Func

// member Var

Pipe::Pipe()
	: m_Type(PIPETYPE::LONG)
{

}

Pipe::~Pipe()
{

}

// member Func

void Pipe::Start()
{
	SJWindowResMgr::Inst().FindImage(L"Pipe1.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Pipe1.bmp")->ImageCut(1, 1);
	SJWindowResMgr::Inst().FindImage(L"Pipe2.bmp")->SetTransColor(RGB(255, 0, 255));
	SJWindowResMgr::Inst().FindImage(L"Pipe2.bmp")->ImageCut(1, 1);

	m_AniRenderer = CreateRenderer<SJRendererAnimation>((int)LogicValue::RENDERGROUP::TOP_OBJECT);
	m_AniRenderer->SetRenderScale({ 256, 256 });
	m_AniRenderer->CreateAnimation(L"Pipe_Long", L"Pipe1.bmp", 0, 0);
	m_AniRenderer->CreateAnimation(L"Pipe_Short", L"Pipe2.bmp", 0, 0);
	m_AniRenderer->ChangeAnimation(L"Pipe_Long");
}

void Pipe::Update()
{
	switch (m_Type)
	{
	case PIPETYPE::SHORT:
		m_AniRenderer->ChangeAnimation(L"Pipe_Short");
		break;
	case PIPETYPE::LONG:
		m_AniRenderer->ChangeAnimation(L"Pipe_Long");
		break;
	default:
		break;
	}
}

void Pipe::DebugRender()
{

}
