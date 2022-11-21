#include "SJRenderer.h"
#include <SJDebug.h>
#include <SJWindow.h>
#include "SJActor.h"

// Static Var
// Static Func

// member Var

SJRenderer::SJRenderer()
	: m_Order(0)
	, m_Actor(nullptr)
	, m_RenderingType(RENDERINGMODE::MAX)
	, m_CutPos()
	, m_CutSize(-1, -1)
	, m_Alpha(255)
{

}

SJRenderer::~SJRenderer()
{

}


// member Func


float4 SJRenderer::CamRenderPos()
{
	if (true == GetActor()->GetCamAffect())
	{
		return GetActor()->GetPos() + m_PivotPos - GetActor()->GetScene()->GetCamPos();

	}
	else if (false == GetActor()->GetCamAffect())
	{
		return GetActor()->GetPos() + m_PivotPos;
	}
	else
	{
		SJDebug::AssertMsg("if (true == GetActor()->GetCamAffect())");
	}
	
	return NULL;
}

void SJRenderer::RenderImage(SJWinImage* _Image)
{
	switch (m_RenderingType)
	{
	case RENDERINGMODE::BIT:
		break;
	case RENDERINGMODE::TRANS:
		SJWindow::GetBackBufferImage().TransparentBltCenter(CamRenderPos(), m_RenderScale, *_Image, m_CutPos, m_CutSize);
		break;
	case RENDERINGMODE::ALPHA:
		SJWindow::GetBackBufferImage().AlphaBltCenter(CamRenderPos(), m_RenderScale, *_Image, m_CutPos, m_CutSize, m_Alpha);
		break;
	case RENDERINGMODE::ROT:
		break;
	case RENDERINGMODE::MAX:
	default:
		SJDebug::AssertMsg("case RENDERINGMODE::MAX:");
		break;
	}
}